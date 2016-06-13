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

#pragma once

namespace arch
{

enum class seek_origin
{
	begin,		///< 始端
	current,	///< 現在
	end,		///< 終端
};

enum class open_mode
{
	append,		///< 追加
	truncate,	///< 破棄
};

}