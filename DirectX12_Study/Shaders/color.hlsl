//***************************************************************************************
// color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer cbPerObject : register(b0)
{
	float4x4 gWorldViewProj; 
	float gTime;
};

struct VertexIn
{
	float3 PosL  : POSITION;
    float4 Color : COLOR;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	//정점변환 

	vin.PosL.xy += 0.5f * sin(vin.PosL.x) * sin(3.0f * gTime);
	vin.PosL.z *= 0.6f * 0.4f * sin(2.0f * gTime) + 1;


	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);

	// Just pass vertex color into the pixel shader.
	vin.Color.x = sin(3.0f * gTime);
	vin.Color.y = sin(2.0f * gTime + 0.2f);
    vout.Color = vin.Color;
    
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	//clip -> 해당 색상이 0 이하면 해당 픽셀을 버린다.
	//clip(pin.Color.r - 0.5f);
    return pin.Color;
}


