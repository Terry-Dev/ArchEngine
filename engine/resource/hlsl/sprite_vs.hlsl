//=================================================================================//
//                                                                                 //
//  ArchEngine                                                                     //
//                                                                                 //
//  Copyright (C) 2011-2016 Terry                                                  //
//                                                                                 //
//  This file is a portion of the ArchEngine. It is distributed under the MIT      //
//  License, available in the root of this distribution and at the following URL.  //
//  http://opensource.org/licenses/mit-license.php                                 //
//                                                                                 //
//=================================================================================//

cbuffer camera_buffer : register(b0)
{
	matrix g_transform;
};

struct vs_input
{
	uint vertex_id			: SV_VertexID;
	matrix transformation	: MATRIX;
	float2 uv_offset		: UV_OFFSET;
	float2 uv_size			: UV_SIZE;
};

struct vs_output
{
	float4 projected_position	: SV_Position;
	float4 color				: COLOR;
	float2 texcoord				: TEXCOORD0;
	float3 world_normal			: TEXCOORD1;
	float3 world_position		: TEXCOORD2;
};

vs_output main(vs_input input)
{
	vs_output output;

	//
	// vertex id
	//
	// No.0: position (-0.5f, -0.5f), texcoord (0.0f, 1.0f)
	// No.1: position (-0.5f, +0.5f), texcoord (0.0f, 0.0f)
	// No.2: position (+0.5f, -0.5f), texcoord (1.0f, 1.0f)
	// No.3: position (+0.5f, +0.5f), texcoord (1.0f, 0.0f)
	// 
	//  0 ------ 1
	//  |        |
	//  |        |
	//  |        |
	//  2 ------ 3

	float4 local_position;
	local_position.x = (input.vertex_id / 2 == 0) ? -0.5f : 0.5f;
	local_position.y = (input.vertex_id % 2 == 0) ? -0.5f : 0.5f;
	local_position.z = 0.0f;
	local_position.w = 1.0f;

	float2 texcoord;
	texcoord.x = (input.vertex_id / 2 == 0) ? 0.0f : 1.0f;
	texcoord.y = (input.vertex_id % 2 == 0) ? 1.0f : 0.0f;

	float4 world_position = mul(local_position, input.transformation);
	output.projected_position = mul(world_position, g_transform);

	float4 world_normal = mul(float4(0.0f, 0.0f, 1.0f, 0.0f), input.transformation);
	float4 view_normal = mul(world_normal, g_transform);

	output.texcoord = texcoord;
	output.color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	output.world_normal = world_normal.xyz;
	output.world_position = world_position.xyz;
	
	return output;
}