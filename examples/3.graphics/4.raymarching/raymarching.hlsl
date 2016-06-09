struct ps_input
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

cbuffer raymarching_buffer : register(b0)
{
	float3 camera_position : packoffset(c0);
	float time : packoffset(c0.w);
	float3 camera_direction : packoffset(c1);
	float forcus : packoffset(c1.w);
	float3 camera_up : packoffset(c2);
	int steps : packoffset(c2.w);
	float2 screen_size : packoffset(c3);
	float2 dummy : packoffset(c3.z);
};

float3 mod(float3 x, float3 y)
{
	return x - y * floor(x / y);
}

float plane(float3 p, float3 n)
{
	return dot(p, normalize(n));
}

float signed_sphere(float3 p, float s)
{
	return length(p) - s;
}

float signed_box(float3 p, float3 s)
{
	float3 d = abs(p) - s;
	return min(max(d.x, max(d.y, d.z)), 0.0f) + length(max(d, 0.0f));
}

float unsigned_box(float3 p, float3 s)
{
	return length(max(abs(p) - s, 0.0f));
}

float round_box(float3 p, float3 s, float r)
{
	return length(max(abs(p) - s, 0.0f)) - r;
}

float cylinder(float3 p, float3 c)
{
	return length(p.xz - c.xy) - c.z;
}

float object_union(float d1, float d2)
{
	return min(d1, d2);
}

float object_substraction(float d1, float d2)
{
	return max(-d1, d2);
}

float object_intersection(float d1, float d2)
{
	return max(d1, d2);
}

float3 object_repeaition(float3 p, float3 c)
{
	return mod(p, c) - c * 0.5f;
}

float pseudo_kleinian(float3 p)
{
	float3 c_size = float3(0.92436f, 0.90756f, 0.92436f);
	float size = 1.0f;
	float de_factor = 1.0f;
	float3 ap;
	for (int i = 0; i < 10; i++)
	{
		ap = p;
		p = 2.0f * clamp(p, -c_size, c_size) - p;
		float r2 = dot(p, p);
		float k = max(size / r2, 1.0f);
		p *= k;
		de_factor *= k;
	}
	
	return abs(0.5f * abs(p.z) / de_factor);
}

float distance_function(float3 p)
{
	float d1 = signed_sphere(object_repeaition(p, 1.0f), 0.6f);
	float d2 = round_box(object_repeaition(p, 4.0f), 1.0f, 0.01f);
	return object_substraction(d1, d2);
}

float3 compute_normal(float3 p)
{
	const float d = 0.0001f;
	return normalize
		(
			float3
			(
				distance_function(p + float3(d, 0.0f, 0.0f)) - distance_function(p + float3(-d, 0.0f, 0.0f)),
				distance_function(p + float3(0.0f, d, 0.0f)) - distance_function(p + float3(0.0f, -d, 0.0f)),
				distance_function(p + float3(0.0f, 0.0f, d)) - distance_function(p + float3(0.0f, 0.0f, -d))
			)
		);
}

float4 main(ps_input input) : SV_TARGET
{
	float2 uv = (input.texcoord * 2.0f - float2(1.0f, 1.0f)) * float2(screen_size.x / screen_size.y, -1.0f);
	float3 camera_right = cross(camera_direction, camera_up);

	float3 ray_position = camera_position;
	float3 ray_direction = normalize(camera_right * uv.x + camera_up * uv.y + camera_direction * forcus);
	
	float total_distance = 0.0f;
	float distance;
	for (int i = 0; i < steps; i++)
	{
		distance = distance_function(ray_position);
		total_distance += distance;
		ray_position += ray_direction * distance;
		if (distance < 0.0001f)
		{
			break;
		}
	}

	float3 normal = compute_normal(ray_position);

	float3 diffuse_color = float3(0.4f, 0.4f, 0.4f) * max(0.0f, dot(normal, -camera_direction));
	float3 ambient_color = float3(0.1f, 0.1f, 0.1f);
	float3 fog_color = float3(0.02f, 0.02f, 0.04f) * total_distance;

	return float4(diffuse_color + ambient_color + fog_color, 1.0f);
}