#pragma once
#include "VulkanApp.h"
#include "VertexBuffer.h"
#include <cstdint>

class Shader
{
public:

	void initializeStages(const std::shared_ptr<VulkanApp>& app);

	void cleanup();

	void addStage(const std::string& shaderPath, const VkShaderStageFlagBits type);

	void createGraphicsPipeline();

	void bindGraphicsPipeline(VkCommandBuffer commandBuffer) const;

	VkPipeline getGraphicsPipeline() const 
	{
		return graphicsPipeline; 
	}

	template<typename T>
	void addInputVertexBuffer(VertexBuffer<T> vb, const uint32_t bindingId, const uint32_t locationId, const size_t offset, const VkFormat format)
	{
		VkVertexInputBindingDescription bindingDescription = {};

		bindingDescription.binding = bindingId;
		bindingDescription.stride = vb.getStrideSize();
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		VkVertexInputAttributeDescription attributeDescription = {};
		attributeDescription.binding = bindingId;
		attributeDescription.location = locationId;
		attributeDescription.format = format;
		attributeDescription.offset = offset;

		vertexBufferDescriptions.push_back(bindingDescription);
		vertexBufferInputDescriptions.push_back(attributeDescription);
	}

private:

	VkShaderModule createShaderModule(const std::vector<char>& code);

	VkPipeline graphicsPipeline;
	VkPipelineLayout graphicsPipelineLayout;

	std::shared_ptr<VulkanApp> vulkanApp;

	std::vector<VkPipelineShaderStageCreateInfo> shaderStages;

	std::vector<VkVertexInputBindingDescription> vertexBufferDescriptions;
	std::vector<VkVertexInputAttributeDescription> vertexBufferInputDescriptions;
};