#include <iostream>
#include <arch/math.h>

using namespace arch;

int main()
{
	vector2<float> v2;
	vector3<float> v3;
	vector4<float> v4;

	int2 iv2 = int2::zero();
	uint3 uiv3 = int3::one();
	double4 dv4 = double4::unit_x();

	std::cout << float2::zero() << std::endl;
	std::cout << float2::one() << std::endl;
	std::cout << float2::unit_x() << std::endl;
	std::cout << float2::unit_y() << std::endl;

	float3 vector = { -3.0f, 3.0f, 0.0f };
	std::cout << vector << std::endl;
	std::cout << vector.absoluted() << std::endl;
	std::cout << vector.normalized() << std::endl;
	std::cout << vector.all() << std::endl;
	std::cout << vector.any() << std::endl;
	std::cout << vector.length() << std::endl;
	std::cout << vector.distance(float3::zero()) << std::endl;
	std::cout << vector.saturated() << std::endl;

	return 0;
}