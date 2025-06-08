#pragma once
#include <memory>
#include <vector>
#include <vulkan/vulkan.h>

class VulkanApp;

class Engine
{

public:

	Engine();

	~Engine();

	void setup();

	void shutdown();

	void onFrameRun(VkCommandBuffer commandBuffer);

	void createGraphicsPipeline();
	
	VkShaderModule createShaderModule(const std::vector<char>& code);

	std::unique_ptr<VulkanApp> vulkanApp;

	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
};