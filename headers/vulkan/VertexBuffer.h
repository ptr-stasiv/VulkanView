#pragma once
#include "VulkanApp.h"

template<typename T>
class VertexBuffer
{
public:

	VertexBuffer()
	{

	}

	void setup(std::shared_ptr<VulkanApp> app, const std::vector<T>& verticesData)
	{
		vulkanApp = app;

		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = sizeof(T) * verticesData.size();
		bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(app->device, &bufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS)
		{
			std::cout << "Failed to create vertex buffer!" << std::endl;
		}

		VkMemoryRequirements memoryRequirements;
		vkGetBufferMemoryRequirements(app->device, vertexBuffer, &memoryRequirements);

		VkMemoryAllocateInfo allocateInfo = {};
		allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocateInfo.allocationSize = memoryRequirements.size;
		allocateInfo.memoryTypeIndex = findMemoryType(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	
	
		if (vkAllocateMemory(app->device, &allocateInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS)
		{
			std::cout << "Failed to allocate vertex buffer memory!" << std::endl;
		}

		vkBindBufferMemory(app->device, vertexBuffer, vertexBufferMemory, 0);

		void* data;
		vkMapMemory(app->device, vertexBufferMemory, 0, bufferInfo.size, 0, &data);

		memcpy(data, verticesData.data(), bufferInfo.size);

		vkUnmapMemory(app->device, vertexBufferMemory);
	}

	void cleanup()
	{
		vkDestroyBuffer(vulkanApp->device, vertexBuffer, nullptr);
		vkFreeMemory(vulkanApp->device, vertexBufferMemory, nullptr);
	}

	void bind(VkCommandBuffer commandBuffer)
	{
		VkBuffer buffers[] = { vertexBuffer };
		VkDeviceSize offsets[] = { 0 };

		vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
	}

	size_t getStrideSize() const
	{
		return sizeof(T);
	}

	VkBuffer getBufferHandler() const
	{
		return vertexBuffer;
	}

private:

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) 
	{
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(vulkanApp->physicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) 
			{
				return i;
			}
		}
	}

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;

	std::shared_ptr<VulkanApp> vulkanApp;
};