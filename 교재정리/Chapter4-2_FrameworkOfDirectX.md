# DirectX의 초기화 과정
1. ID3D12Device 를 생성(디스플레이 어댑터)
2. ID3D12Fence를 생성하고 서술자들의 크기를 얻는다.
3. 4X MSAA 품질수준 지원 여부를 점검한다. (Direct11이 지원되면 항상 지원된다)
4. 명렬대기열,명렬목록할당자,주 명령목록을 생성한다.
5. swap chain을 서술하고 생성한다.
6. 서술자 힙들을 생성한다.
7. 후면 버퍼의 크기를 설정하고, 렌더 대상 뷰를 생성한다.
8. 깊이-스텐실 버퍼를 생성하고, 그와 연관된 깊이-스텐실 뷰를 생성한다.
9. 뷰포트와 scissor rectangle을 설정한다.(scissor rectangle은 특정 픽셀을 선별(culling)하는 용도)

# 시간 측정
- 프레임간 시간 측정을 위해 이 책에서는 windows가 제공하는 성능타이머를 사용한다.
- GameTimer클래스는 Tick() 메소드로 델타타임을 구할 수 있다.
- 그 외에 Reset(), TotalTime(), Start(), Stop() 메소드로 다양한 시간 측정 기능을 사용할 수 있다.


# 예제 프레임워크 분석
``` c++
#pragma comment(lib,"d3dcompiler.lib") 
//설정-라이브러리에서 lib파일을 링크시키지 않고 직접 코드로 링크시키는 전처리기

D3DApp& operator=(const D3DApp& rhs) = delete;
// 클래스에서 특정 연산자를 지원하지 않게 하기 위한 기능, = delete
```

[추가자료(블로그)](https://blog.naver.com/ghalsgg99)