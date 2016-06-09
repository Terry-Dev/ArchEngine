Texture2D DiffuseMap		: register(t0);
Texture2D SpecularMap		: register(t1);
Texture2D EmissiveMap		: register(t2);
SamplerState InputSampler	: register(s0);

struct PS_INPUT
{
	float4 ProjPosition	: SV_POSITION;
	float4 Color		: COLOR;
	float2 Texcoord		: TEXCOORD0;
	float3 Normal		: TEXCOORD1;
	float3 Position		: TEXCOORD2;
};

cbuffer MaterialBuffer : register(b0)
{
	float4	MaterialDiffuse;
	float4	MaterialAmbient;
	float4	MaterialSpecular;
	float4	MaterialEmissive;
};

cbuffer LightBuffer : register(b1)
{
	float4	LightPosition;
	float4	LightDirection;
	float4	LightColor;
};

float4 PS(PS_INPUT Input) : SV_Target
{
	float3 NormalVector	= normalize(Input.Normal);
	float3 LightVector	= -normalize(LightDirection.xyz);
	float3 HarfVector	= normalize(LightVector - normalize(Input.Position));

	float DiffuseRate	= max(0.0f, dot(NormalVector, LightVector));
	float SpecularRate	= pow(max(0.0f, dot(NormalVector, HarfVector)), MaterialSpecular.a);

	float4 Diffuse		= DiffuseMap.Sample(InputSampler, Input.Texcoord) * MaterialDiffuse * Input.Color;
	float3 Ambient		= MaterialAmbient.rgb;
	float3 Specular		= SpecularMap.Sample(InputSampler, Input.Texcoord).rgb * MaterialSpecular.rgb;
	float3 Emissive		= EmissiveMap.Sample(InputSampler, Input.Texcoord).rgb * MaterialEmissive.rgb;

	Diffuse.rgb			*= LightColor.rgb * DiffuseRate;
	Specular			*= LightColor.rgb * SpecularRate;

	return float4(Diffuse.rgb + Ambient + Specular + Emissive, Diffuse.a);
}