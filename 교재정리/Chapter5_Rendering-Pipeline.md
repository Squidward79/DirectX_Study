# Rendering Pipeline
- **렌더링 파이프라인이란?**
  - 가상카메라에 비친 3차원 장면의 모습에 근거해서 2차원 이미지를 생성하는데 필요한 일련의 단계들
  
  
### 1. 모형의 표현
- DirectX에선 3차원 물체를 삼각형 메시로 근사(approximation)하여 표현한다.
  
### 2. 컴퓨터 색상의 기본 개념
- 컴퓨터는 R, G, B, 세 가지 채널을 조합하여 색상을 표현한다.
- 적색,녹색,청색광의 세기는 0% ~ 100%의 값을 0~1로 정규화하여 사용하는 것이 일반적이다.
- 하나의 색상은 3차원 벡터 (r,g,b)로 나타낼 수 있다.

  #### 2.1 가능한 색상 연산
  + 더하기 빼기 
  - 스칼라 곱셈 (Scalar Multiplication)
  + 변조 (Modulation) = 성분별 곱셈
  - 연산 후 결과값을 0~1 사이로 clamping 해주어야 한다.

  #### 2.2 128비트 색상 
    - 0.0 ~ 1.0 사이의 값을 갖는다.
    - 색상을 4차원 벡터 (r,g,b,a)로 표현한다.
    - Red, Greed, Blue, Alpha 4가지 성분을 가진다.
    - 각 성분은 32비트(4byte), 따라서 32 * 4 = 128bit 
  
  #### 2.3 32비트 색상
    - 0 ~ 255 사이의 값을 값을 갖는다.
    - 색상을 4차원 벡터 (r,g,b,a)로 표현한다.
    - 각 성분은 8비트(1byte), 따라서 8 * 4 = 32bit
    - 하나의 32비트 색상으로 약 1670만개의 색을 표현할 수 있다.

---

## 렌더링 파이프라인 개요 
- 다이렉트X에서 사용하는 렌더링 파이프라인
- 그래픽스 렌더링 파이프라인과의 비교
    -
DirectX 렌더링 파이프라인 | 그래픽스 렌더링 파이프라인 |
---|---|
Input Assembler (입력 조립기) |  |
 ↓ | |
Vertex Shader (정점 쉐이더) | ┐ 정점 처리 |
 ↓ | │ |
Hull Shader (덮개 쉐이더) |│  |
 ↓ | │ |
Tessellator (테셀레이터)|│ |
 ↓ |│ |
 Domain Shader (영역 쉐이더)|│ |
 ↓ |│ |
Geometry Shader (기하 쉐이더) | ┘ |
 ↓ | |
Rasterize (래스터화) | 래스터화  |
 ↓ | |
Pixel Shader (픽셀 쉐이더) | 프래그먼트 처리 |
 ↓ | |
Output Merge (출력 병합)| 출력 병합 |

--- 

- 각각의 Stage에 대한 간단한 설명 
  -

DirectX 렌더링 파이프라인  | 설명 | 필요한 리소스 |
---|---|---|
**Input Assembler** | 3차원 모델의 Vertex 정보를 GPU에 전달 하면 GPU에서 기본 도형으로 조립 | Vertex Buffer 
 ↓ | |
**Vertex Shader**  | 정점데이터의 변환, 조명, 텍스쳐매핑 등 다양한 역할을 수행. HLSL 언어를 이용 </br>로컬공간 -> 월드공간 -> 카메라공간 -> 투영공간 으로 변환 </br> 텍스쳐는 Sampler를 통해 정보를 처리| Sampler, Texture Buffer, Constant Buffer
 ↓  |  |
**Hull Shader** (덮개 쉐이더) | 테셀레이션이 시작되는 단계 </br>폴리곤의 세부도, LOD 메커니즘을 구현하고 분할 방법을 결정</br>  |
 ↓ |  |
Tessellator (테셀레이터)| Hull Shader에서 받은 테셀레이션 계획에 따라 폴리곤 분할  |
 ↓ | |
 Domain Shader (영역 쉐이더)| 분할된 폴리곤에 굴곡을 주기 위해 vertex의 공간 정보 조절 | Buffer
 ↓ | |
Geometry Shader (기하 쉐이더) | 메쉬를 primitive 단위로 다룰 수 있게 함 </br> 기하 쉐이더의 출력을 버퍼에 전달하여 폴리곤을 읽거나 새 기하구조 생성 및 파괴, 버퍼에 저장 등이 가능</br> 모델의 폭발, 이펙트 처리에 유용한 쉐이더 |
 ↓ | Clippling 연산 처리 | |
Rasterize (래스터화) | 벡터 정보를 화면에 출력하기 위해 래스터 이미지로 변환  |
 ↓ | |
Pixel Shader (픽셀 쉐이더) | 렌더링 대상인 픽셀의 색을 계산하여 최종 색상을 결정</br> 범프매핑, 그림자, 반사광, 투명, 안개, 깊이처리 등 복잡한 연산 수행 | Buffer
 ↓ | |
Output Merge (출력 병합)| 최종적으로 처리된 부분을 조합하여 출력을 담당하는 단계 </br> | Depth-Stencil Buffer, Render Target
