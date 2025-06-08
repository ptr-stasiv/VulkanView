#pragma once
#include <memory>
#include "vulkan/Shader.h"

class VulkanApp;

class Engine
{

public:

	Engine();

	~Engine();

	void setup();

	void shutdown();

	void onFrameRun(VkCommandBuffer commandBuffer);

	Shader shader;

	std::shared_ptr<VulkanApp> vulkanApp;
};