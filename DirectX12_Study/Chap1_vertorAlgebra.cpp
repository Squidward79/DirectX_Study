#include <Windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

#include "../d3d12book/Common/d3dApp.h"
#include "../d3d12book/Common/MathHelper.h"
#include "../d3d12book/Common/UploadBuffer.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

//XMVECTOR 객체를 cout으로 출력하기 위해서 
// << 연산자를 오버로딩한다

ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
{
	XMFLOAT3 dest;
	XMStoreFloat3(&dest, v);

	os << "(" << dest.x << "," << dest.y << "," << dest.z << ")";
	return os;
}

int main()
{
	cout.setf(ios_base::boolalpha);

	//SSES2를 지원하는지 (Pentium4, AMD K8이상) 확인
	if (!XMVerifyCPUSupport())
	{
		cout << "DirectXMath 지원 안함"<<endl;
		return 0;
	}

	XMVECTOR p = XMVectorZero();
	XMVECTOR q = XMVectorSplatOne();
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	XMVECTOR w = XMVectorSplatZ(u);

	cout << p << endl;
	cout << q << endl;
	cout << u << endl;
	cout << w << endl;

	return 0;
}