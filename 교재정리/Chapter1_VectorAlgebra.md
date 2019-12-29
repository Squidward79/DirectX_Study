# CHAPTER1 벡터대수

## 목차 
- [1.1 벡터](##1.1-벡터)
- [1.2 길이와 단위벡터](##1.2-길이와-단위벡터)
- [1.3 내적](##1.3-내적)




## 1.1 벡터 
 - `Vector` 는 크기(magnitude)와 방향(direction)을 모두 가진 **수량**(quantity)을 나타내는 말이다.
 - 공식적으론 이 **수량**은 벡터값 수량(vector-valued quantity)이라고 부른다. 
 - 힘이나 변위, 속도를 나타내는데 쓰인다.
  
### 1.1.1 벡터좌표계
- 벡터는 같은 벡터라도 기준 좌표계가 다르면 그 좌표의 표현이 달라진다.

### 1.1.2 
  ![image](https://www.google.com/url?sa=i&source=images&cd=&ved=2ahUKEwi71pLiicvmAhXVFYgKHer-DboQjRx6BAgBEAQ&url=https%3A%2F%2Fhns17.tistory.com%2Fm%2F228&psig=AOvVaw3lDXbFkBhAqV3wALA5px3Y&ust=1577166618976254)
   - DirectX는 '왼손좌표계'를 사용한다.

### 1.1.3 
 - 스칼라 곱셈 : 벡터의 길이(크기)를 확대 축소하는 것
 - 부호 반대 : 뒤집는 것 
 - 가해지는 힘들을 벡터덧셈으로 결합하면 '알짜힘'이 나온다.

## 1.2 길이와 단위벡터
- 벡터의 크기는 벡터의 지향선분의 길이이다.
- 벡터의 각 성분을 크기로 나누면 길이가 1인 단위벡터가 된다.
- 이를 '정규화'(normalization) 라고 한다.

## 1.3 내적 
- dot product, inner product, scalar product 라고 불린다. 
- 내적의 결과는 스칼라
- 정의는 `대응되는 성분들의 곱의 합`으로 다음과 같다.
 
     $$ u \cdot v = u_x v_x + u_y v_y + u_z v_z  $$ 

- 두 벡터의 내적은, 두 벡터 사이의 각도의 코사인을 벡터 크기로 비례한 것을 의미한다. (두 각 중 작은 각)
 $$ u \cdot v = \lVert u \rVert \lVert v \rVert \cos\theta $$
  
- 다음과 같은 기하학적 속성을 갖는다. ( 0 < theta < 180 )
   $$ 1. \ \   u \cdot v = 0 \ 이면 \ u \perp v $$ 

   $$2. \ \  u \cdot v > 0 \ 이면 \theta < 90 \ _{(예각을 \ 이룬다)} $$

    $$3. \ \  u \cdot v < 0 \ 이면 \ \theta > 90 \ _{(둔각을 \ 이룬다)} $$


- **투영공식** (두 벡터 v와 n에 대하여 *p*는 n에 대한 v의 `직교투영`이다.)
  $$ p = proj_n(v) = \left( v \cdot \frac n {\lVert n \rVert} \right) \frac n {\lVert n \rVert} = \frac {(v \cdot n)} {\lVert n \rVert} n $$

### 1.3.1 직교화 
- 벡터집합의 모든 벡터가 단위벡터이고 서로 직교할 떄 , 이를 정규직교(orthonormal) 집합이라고 부른다.
- 그람-슈미트 직교화
  - 벡터 v_i를 택한다.
  -  그 벡터에서 직교벡터 집합에 들어있는 다른 벡터들의 방향으로의 부분을 빼서 그 벡터들과 직교가 되게 만든 후 직교벡터 집합에 추가한다. 
  - 모든 벡터가 직교가 될 때까지 반복한다.
  - 집합의 모든 벡터를 정규화한다.

## 1.4 외적
 - cross product, outer product 라고 불린다.
 - 외적의 결과는 벡터
 - 오직 3차원 벡터에 대해서만 존재한다.
 - u v에 외적을 취하면 u v 모두에 직교인 또 다른 벡터 w가 나온다.
 - 정의는 다음과 같다.
  $$ u = (u_x,u_y,u_z) , \ v = (v_x, v_y, v_z) \ 일 때 \\
    w = u \times v = (u_y v_z - u_z v_y, u_z v_x - u_x v_, u_x v_y - u_y v_x) $$

- 왼손 법칙으로 외적의 방향을 알 수 있음 (말아쥐는 손의 엄지손가락 방향)

### 1.4.1 2차원 유사 외적
- 2차원 벡터 u 에 수직인 벡터는 얼마든지 구할 수 있다.
- u에 수직인 벡터 v는 다음과 같다. u v 를 내적해보면 0 이다.
  $$ v = (-u_y, u_x) $$

### 1.4.2 외적을 이용한 직교화
- 하나의 벡터 v0를 선택하여 정규화 하고 w0 라고 한다.
- w2 = w0 X v1 으로 설정한다. w0 과 w2의 길이는 1이다.
- w1 = w2 X w0 으로 설정한다. 이러면 {w0, w1, w2}는 정규직교이다.

## 1.5 점 
- 3차원 공간 안의 하나의 위치를 나타내는 벡터를 `위치벡터` 라고 부른다.
- 위치벡터는 점과 같은 의미로 사용된다.
- 점을 벡터로 표현하는 방식은, 기하적으로 벡터연산을 적용할 수 없는 부분이 있다. (EX. 두 점의 합)

## 1.6 DirectXMath 라이브러리의 벡터
- `DirectXMath` 라이브러리를 사용한다.
- 벡터를 다루기 위해 `XMVECTOR` 형식을 사용한다.
- 이는 SIMD(single instruction multiple data)연산을 이용해 효율적으로 처리한다.
- 클래스 자료 멤버에는 `XMFLOAT2`, `XMFLOAT3`, `XMFLOAT4` 를 사용하지만, 필요에 따라 load,store 함수를 이용해 XMVECTOR로 변환한다. 
- 초기화구문으로 const 벡터를 정의할 때는 `XMVECTORF32` 형식을 사용해야 한다.

- XMVECTOR를 인수로 하는 함수를 호출할 때, 효율을 위해 스택이 아닌 SSE/SSE2 레지스터를 통해야 한다. 이를 플랫폼 독립방식으로 사용하기 위해서 
  - 3번째 인수까지는 FXMVECTOR, 4번째는 GXMVECTOR, 5~6번째 HMXVECTOR, 그 이상은 CXMVECTOR을 사용한다.

### DirectXMath 벡터 연산함수들
- XMVector3Length(FXMVECTOR V); // 길이
- XMVector3LengthSq(FXMVECTOR V); //길이 제곱
- XMVector3Dot(FXMVECTOR V1, FXMVECTOR V2); // V1,V2 를 내적
- XMVector3Cross(FXMVECTOR V1, FXMVECTOR V2); // V1,V2를 외적
- XMVector3Normalize(FXMVECTOR V); // 정규화

- XMVectorSet(float,float,float,float); // 벡터 값 세팅
- XMVectorAbs(FXMVECTOR V); // 절댓값
- XMVectorCos(FXMVECTOR V); // 라디안 V를 넣으면 cos값을 구해줌 
- XMVectorPow(FXMVECTOR V1, FXMVECTOR V2); // V의 각성분을 P의 성분별로 제곱한다. 
- XMVectorSqrt(FXMVECTOR V); // 제곱근 
- XMVectorSaturate(FXMVECTOR V); // V의 성분을 0~1로 제한






