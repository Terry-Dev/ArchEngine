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

struct vs_output
{
	float4 position : SV_Position;
	float2 texcoord : TEXCOORD;
};

vs_output main(uint vertex_id : SV_VertexID)
{
	vs_output output;

	//
	// vertex id
	//
	// No.0: position (-1.0f, -1.0f), texcoord (0.0f, 1.0f)
	// No.1: position (-1.0f, +1.0f), texcoord (0.0f, 0.0f)
	// No.2: position (+1.0f, -1.0f), texcoord (1.0f, 1.0f)
	// No.3: position (+1.0f, +1.0f), texcoord (1.0f, 0.0f)
	// 
	//  0 ------ 1
	//  |        |
	//  |        |
	//  |        |
	//  2 ------ 3

	output.position.x = (vertex_id / 2 == 0) ? -1.0f : 1.0f;
	output.position.y = (vertex_id % 2 == 0) ? -1.0f : 1.0f;
	output.position.z = 0.0f;
	output.position.w = 1.0f;
	output.texcoord.x = (vertex_id / 2 == 0) ? 0.0f : 1.0f;
	output.texcoord.y = (vertex_id % 2 == 0) ? 1.0f : 0.0f;
	
	return output;
}