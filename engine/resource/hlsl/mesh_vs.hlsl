cbuffer camera_buffer : register(b0)
{
	matrix view_matrix;
	matrix projection_matrix;
};

struct vs_input
{
	float3 position		: POSITION;
	float3 normal		: NORMAL;
	float4 color		: COLOR;
	float2 texcoord		: TEXCOORD;
	matrix world_matrix	: MATRIX;
};

struct vs_output
{
	float4 projected_position	: SV_POSITION;
	float4 color				: COLOR;
	float2 texcoord				: TEXCOORD0;
	float3 normal				: TEXCOORD1;
	float3 position				: TEXCOORD2;
};

vs_output main(vs_input input)
{
	vs_output output;
	float4 world_position		= mul(float4(input.position, 1.0f), input.world_matrix);
	float4 view_position		= mul(world_position, view_matrix);
	output.projected_position	= mul(view_position, projection_matrix);

	float4 world_normal		= mul(float4(input.normal, 0.0f), input.world_matrix);
	float4 view_normal		= mul(world_normal, view_matrix);

	output.texcoord = input.texcoord;
	output.color	= input.color;
	output.normal	= world_normal.xyz;
	output.position	= world_position.xyz;
	return output;
}