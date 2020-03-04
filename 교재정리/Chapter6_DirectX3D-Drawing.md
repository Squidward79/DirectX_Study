# DirectX3D 그리기 연산
- 렌더링 파이프라인의 구성 및 각종 쉐이더 작성 등 DirectX의 API의 여러 인터페이스와 메서드를 중심으로

## 6.1 Vertex와 GPU에 정점 정보를 알려주는 Input Layout
1. 정점에 위치 이외 추가적인 자료를 부여하기 위하여 구조체를 정의하여 사용한다.
  ``` C++
  예시)
  struct Vertex1
  {
      XMFLOAT3 Pos;
      XMFLOAT4 Color;
      XMFLOAT3 Normal;
  };
  ```
  2. 구조체의 각 성분으로 DirectX에서 무엇을 할 것인지 알려주기 위하여 **Input Layout Description(입력 배치 서술)** 을 사용한다.
   
      - 입력배치서술은 D3D12_INPUT_LAYOUT_DESC 라는 구조체로 대표되는데,</br> 이는 D3D12_INPUT_ELEMENT_DESC 형식의 원소들을 담은 배열과 그 원소의 갯수로 대체된다.(?)
    - D3D12_INPUT_ELEMENT_DESC 배열의 각 원소는 Vertex의 각 성분을 서술하기 때문에, 1:1로 대응되어야 한다. 
  
``` C++
    D3D12_INPUT_ELEMENT_DESC { 
    SPCSTR SemanticName; // 성분에 부여된 문자열 이름. 정점쉐이더 입력서명과 대응시키는 역할
      UINT SemanticIndex; // 색인. 쉐이더에 지정되어 있지 않으면 0 
      DXGI_FORMAT Format; // 정점성분의 자료형을 알려주는 역할. DXGI_FORMAT_0000와 같은 형식으로 지정
      UINT InputSlot; // 해당 성분 자료를 가져올 정점버퍼의 색인 슬롯
      UINT AlignedByteOffset; //시작위치와 해당 정점성분 사이의 거리를 나타내는 오프셋
      D3D12_INPUT_CLASSIFICATION InputSlotClass; // 고급 기법에 사용
      UINT InstanceDataStepRate; // 고급 기법에 사용
    } D3D12_INPUT_ELEMENT_DESC;

- 활용 예)
    D3D12_INPUT_ELEMENT_DESC desc1[] = 
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_PER_VERTEX_DATA, 0}
    }

```

- Input Layout Description은 D3D12_GRAPHICS_PIPELINE_DESC 구조체의 필드로 들어가며, 이것은 Pipeline State Object (PSO)의 일부가 된다.

## 6.2 GPU가 정점에 접근하기 위한 Vertex Buffer
- Vertex의 배열에 GPU가 접근하기 위해, 버퍼라고 부르는 GPU자원인 ID3D12Resource에 넣어야 한다.
- Buffer는 텍스처보다 단순한 자원이므로 자료원소들의 배열을 GPU에 제공할 때 항상 사용한다.

- CPU의 자료를 GPU에 복사해 넣으려면 다음과 같은 방식으로 수행한다.    
`CPU에서 임시 업로드 버퍼자원 생성 -> 업로드 버퍼에 복사 -> GPU의 실제 버퍼로 복사`

- 버퍼에 자원을 넣기만 하면 끝나는 것이 아니고, 버퍼를 파이프라인에 묶어야 한다. </br>(= Input Assembler 단계에서 정점을 파이프라인에 공급할 준비를 한다. 이제야 비로소 GPU에서 자원을 활용할 수 있게 된다.)

#### - Vertex Buffer를 파이프라인에 묶으려면 View (= Descriptor)를 만들어서 적용해야 한다.
``` c++
    D3D12_VERTEX_VIEW 구조체를 사용하여 서술한다.

    D3D12_VERTEX_VIEW {
        D3D12_GPU_VIRTUAL_ADDRESS BufferLocation; // 뷰의 대상이 되는 정점버퍼의 가상 주소
        UINT SizeInBytes; // 정점버퍼의 크기
        UINT StrideInBytes; // 한 정점 원소의 크기 
    } D3D12_VERTEX_BUFFER_VIEW;

    그 후에는 ID3D12GraphicsCommandList::IASetVertexBuffers(StartSlot,NumBuffers, *pViews) 
    메서드를 써서 파이프라인에 묶는다.

    정점을 GPU에 전달했다면, ID3D12GraphicsCommandList::DrawInstanced()로 실제로 정점을 그린다.
``` 

## 6.3 Index와 Index Buffer
- 정점 버퍼와 마찬가지로, GPU가 Index의 배열에 접근하기 위해 버퍼가 필요하다.
- Index Buffer를 파이프라인에 묶으려면 마찬가지로 뷰가 필요하다.
``` c++
    D3D12_INDEX_BUFFER_VIEW 구조체를 사용한다.
    Index Buffer는 ID3D12CommandList::SetIndexBuffer로 파이프라인에 묶고,
    ID3D12GraphicsCommandList::DrawIndexedInstanced로 도형을 그린다.
```

## 6.4 Vertex Shader 
 - 일반적으로 .hlsl 확장자의 텍스트파일로 소스코드를 작성한다.
 - 쉐이더는 하나의 함수이므로 아무 이름이나 사용할 수 있다. 
 - 입력받는 매개변수는 쉐이더의 **Input Signature(입력 서명)** 을 형성한다.
 - 매개변수의 :POSITION 과 같은 의미소(Semantic)들은, 프로그램에서 Input Layout(입력배치)와 Input Signature(입력서명)을 연결하는 역할을 한다. 
 - 따라서 입력배치서술의 명칭과 입력서명은 항상 일치해야 하며, 쉐이더가 요구하는 모든 정보를 정점 자료가 제공해야 한다.
 - 정점 쉐이더의 출력값은 픽셀쉐이더의 입력값이 되므로, 이 역시 입력 서명이 일치해야 한다. 

## 6.5 Pixel Shader
- 픽셀 쉐이더는 모든 Fragment마다 실행된다.
- Fragment는 픽셀과 픽셀의 정보를 포함하는 개념이지만, Pixel과 혼용해서 사용한다.

``` C++
Vertex / Pixel Shader의 간단한 예제코드)

    cbuffer cbPerObject : register(b0) 
    //cbuffer 는 constant buffer 구조체, register(b0)는 자원을 어느 레지스터 슬롯에 묶을 것인지를 정해준다. 
    {
        float4x4 gWorldViewProg;
    }; 

    void VS(float3 iPos : POSITION, float4 iColor : COLOR,
            out float4 oPosH : SV_POSITION, out float4 oColor : COLOR)
    {
        oPosH = mul(float4(iPos, 1.0f), gWorldViewProg);
        oColor = iColor;
    }

    float4 PS(float4 PosH : SV_POSITION, float4 Color : COLOR) : SV_Target
    {
        return Color;
    }
```

## 6.6 Constant Buffer
- 쉐이더 프로그램에서 참조하는 자료를 담은 GPU자원(ID3D12Resource)의 예이다. 
- CPU가 프레임당 한 번 갱신한다. 카메라의 이동 등 매 프레임 갱신할 때 사용한다.
- 크기는 반드시 최소 하드웨어 할등 크기(256bytes)의 배수이어야 한다.
- 상수버퍼는 **업로드 힙(D3D12_HEAP_TYPE_UPLOAD)에 만들어지기 때문에** , CPU에서 자료를 올릴 수 있다.
- Constant Buffer를 파이프라인에 묶으려면 서술자가 필요하다.
  ``` c++
    D3D12_CONSTANT_BUFFER_VIEW_DESC 구조체를 사용한다. (줄여서 CBV)
    인스턴스를 채운 후 ID3D12Device::CreateConstantBufferView를 호출한다.
  ```

## 6.7 파이프라인에 묶을 자원을 알려주는 Root Signature 
- 렌더링 파이프라인에서 반드시 묶어야 하는 자원이 무엇이고 그 자원이 쉐이더 입력 레지스터들에 어떻게 대응되는지 정의한다.
- 즉, 쉐이더가 요구하는 모든 자원을 루트 서명이 제공해야 한다. 
- 루트 서명은 ID3D12RootSignature 인터페이스로 대표된다.
  ``` c++
    Root Signature는 Root Parameter들의 배열로 정의된다.
    이 때 Root Parameter는 루트 상수, 루트 서술자, 서술자 테이블 일 수 있다.
  ```
- 루트 서명은 자원을 실제로 파이프라인에 묶지는 않는다. 다만 무엇을 어떻게 묶어야 할지 알려줄 뿐이다. 

## 6.9 실제로 파이프라인에 묶기 위한 Pipeline State Object
- 렌더링 파이프라인의 상태를 제어하는 대부분은 Pipeline State Object(파이프라인 상태 객체, PSO)라고 부르는 집합체를 통해 지정된다. 
- 파이프라인 상태 객체는 ID3D12PipelineState 인터페이스로 대표된다.
``` c++
    D3D12_GRAPHICS_PIPELINE_STATE_DESC 구조체를 사용한다.
    대표적으로 Root Signature, Vertex Shader, Pixel Shader 등 각종 쉐이더가 있고, 
    그 외에도 스트림 출력, 혼합 방식, 다중 표본화 등 파이프라인 전반에 걸친 상태를 지정한다.
```

- PSO는 모든 렌더 상태를 포함하지는 않는다. 
- DirectX는 기본적으로 State Machine이기 때문에, 명시적으로 변경되기 전에는 처음 설정한 값이 그대로 남아있는 것들이 많다.