#include <arch_engine.h>

using namespace arch;

void setup()
{
	logging::set_logger(std::make_shared<text_logger>());
}

void shutdown()
{
}

void run()
{
	screen main_screen(640, 480, "ArchEngine");
	main_screen.show();

	hsv_color c(1.0, 1.0, 1.0);

	while (update())
	{
		c.h++;
		c.h = std::fmod(c.h, 360.0);
		main_screen.clear(c.to_vector4<uchar>());

		if (!main_screen.is_visible())
		{
			break;
		}
		main_screen.display();
	}
}