#pragma once
#include <memory>

class VulkanApp;

class Engine
{

public:

	Engine();

	~Engine();

	void setup();

	void shutdown();

private:
	
	std::unique_ptr<VulkanApp> vulkanApp;
};