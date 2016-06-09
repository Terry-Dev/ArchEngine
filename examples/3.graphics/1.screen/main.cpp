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

	while (update())
	{
		if (!main_screen.is_visible())
		{
			break;
		}
	}
}