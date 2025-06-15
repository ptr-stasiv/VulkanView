#pragma once
#include <memory>
#include "vulkan/Shader.h"
#include <glm/glm.hpp>

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

	VertexBuffer<glm::vec2> vb;

	std::shared_ptr<VulkanApp> vulkanApp;
};