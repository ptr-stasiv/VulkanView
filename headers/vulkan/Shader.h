#pragma once
#include "VulkanApp.h"

class Shader
{
public:

	void initializeStages(const std::shared_ptr<VulkanApp>& app);

	void cleanup();

	void addStage(const std::string& shaderPath, const VkShaderStageFlagBits type);

	void createGraphicsPipeline();

	VkPipeline getGraphicsPipeline() const 
	{
		return graphicsPipeline; 
	}

private:

	VkShaderModule createShaderModule(const std::vector<char>& code);

	VkPipeline graphicsPipeline;
	VkPipelineLayout graphicsPipelineLayout;

	std::shared_ptr<VulkanApp> vulkanApp;

	std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
};