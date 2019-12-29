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

//XMVECTOR ��ü�� cout���� ����ϱ� ���ؼ� 
// << �����ڸ� �����ε��Ѵ�

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

	//SSES2�� �����ϴ��� (Pentium4, AMD K8�̻�) Ȯ��
	if (!XMVerifyCPUSupport())
	{
		cout << "DirectXMath ���� ����"<<endl;
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