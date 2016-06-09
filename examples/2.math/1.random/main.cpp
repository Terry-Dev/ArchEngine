#include <iostream>
#include <arch/math.h>

using namespace arch;

int main()
{
	std::cout << random() << std::endl;
	std::cout << random(-1.0, 1.0) << std::endl;
	std::cout << random(1, 3) << std::endl;
	return 0;
}