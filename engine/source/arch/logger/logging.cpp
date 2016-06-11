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

#include "arch/logging.h"

using namespace arch;

#ifdef _DEBUG
trace_level logging::m_level = trace_level::debug;
#else
trace_level logging::m_level = trace_level::infomation;
#endif

std::shared_ptr<logger> logging::m_logger;