Texture2D default_texture : register(t0);
SamplerState default_sampler : register(s0);

struct ps_input
{
	float4 projected_position	: SV_POSITION;
	float4 color				: COLOR;
	float2 texcoord				: TEXCOORD0;
	float3 world_normal			: TEXCOORD1;
	float3 world_position		: TEXCOORD2;
};

float4 main(ps_input input) : SV_TARGET
{
	float4 color = default_texture.Sample(default_sampler, input.texcoord) * input.color;
	if (color.a == 0.0f)
	{
		discard;
	}

	return color;
}