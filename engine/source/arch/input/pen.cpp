#include <arch/input/pen.h>

using namespace arch;

bool pen::supports = false;
bool pen::supports_pressure = false;
bool pen::supports_tilt = false;
bool pen::is_eraser = false;

double pen::pressure = 0.0;
double pen::altitude = 0.0;
double pen::azimuth = 0.0;