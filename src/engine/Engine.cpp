#include "engine/Engine.h"
#include "vulkan/VulkanApp.h"

Engine::Engine()
	: vulkanApp(std::make_unique<VulkanApp>())
{
}

Engine::~Engine() = default;

void Engine::setup()
{
	if (vulkanApp)
	{
		vulkanApp->setup();
		vulkanApp->run();
	}
}

void Engine::shutdown()
{
	if (vulkanApp)
	{
		vulkanApp->shutdown();
	}
}