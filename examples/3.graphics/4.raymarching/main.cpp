#include <arch_engine.h>
#include <graphics/renderer.h>

using namespace arch;

struct raymarching_buffer
{
	float3 camera_position;
	float time;
	float3 camera_direction;
	float forcus;
	float3 camera_up;
	uint32_t steps;
	float2 screen_size;
	float2 _dummy;
};

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

	shader pixel_shader("raymarching.cso");
	renderable_texture target(main_screen);
	constant_buffer constant_buffer(sizeof(raymarching_buffer));
	
	raymarching_buffer cbuffer;
	cbuffer.screen_size = float2(640.0f, 480.0f);
	cbuffer.time = 0.0f;
	cbuffer.forcus = 1.8f;
	cbuffer.steps = 64;
	
	while (update())
	{
		main_screen.clear();

		cbuffer.camera_direction = float3::unit_z();
		cbuffer.camera_position.x = 0.0f;
		cbuffer.camera_position.y = 5.0f * cbuffer.time;
		cbuffer.camera_position.z = 5.0f * cbuffer.time;
		cbuffer.camera_up = normalize(float3(arch::sin(cbuffer.time * 0.2f), arch::cos(cbuffer.time * 0.2f), 0.0f));

		if (!main_screen.is_visible())
		{
			break;
		}

		constant_buffer.fill(&cbuffer);

		renderer::set_pixel_shader(pixel_shader);
		renderer::set_constant(shader_type::pixel_shader, 0, constant_buffer);
		renderer::set_target(0, target);
		renderer::set_viewport(0, 0.0f, 0.0f, 0.0f, static_cast<float>(target.width()), static_cast<float>(target.height()), 1.0f);
		renderer::draw_fullscreen_quad();

		main_screen.display();
	
		cbuffer.time += static_cast<float>(delta_time());
	}
}