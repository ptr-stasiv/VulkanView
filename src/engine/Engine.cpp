#include "engine/Engine.h"
#include "vulkan/VulkanApp.h"

Engine::Engine()
	: vulkanApp(std::make_shared<VulkanApp>())
{
}

Engine::~Engine() = default;

void Engine::setup()
{
	if (vulkanApp)
	{
		vulkanApp->setup();

		shader.initializeStages(vulkanApp);

		shader.addStage("shaders/shader.vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
		shader.addStage("shaders/shader.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);

		shader.createGraphicsPipeline();

        vulkanApp->onFrameRun = std::bind(&Engine::onFrameRun, this, std::placeholders::_1);

		vulkanApp->run();
	}
}

void Engine::shutdown()
{
	shader.cleanup();

	if (vulkanApp)
	{
		vulkanApp->shutdown();
	}
}

void Engine::onFrameRun(VkCommandBuffer commandBuffer)
{
	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, shader.getGraphicsPipeline());

    vkCmdDraw(commandBuffer, 3, 1, 0, 0);
}