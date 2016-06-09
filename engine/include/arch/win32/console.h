#pragma once

#include <string>
#include "../arch/types.h"

namespace arch
{

namespace win32
{

namespace console
{

bool open();
void close();
bool is_opened();

}

}

}