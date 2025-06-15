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

		std::vector<glm::vec2> vertices =
		{
			{ 0.0, -0.5 },
			{ 0.5, 0.5 },
			{ -0.5, 0.5 }
		};

		vb.setup(vulkanApp, vertices);

		shader.addInputVertexBuffer(vb, 0, 0, 0, VK_FORMAT_R32G32_SFLOAT);

		shader.createGraphicsPipeline();

        vulkanApp->onFrameRun = std::bind(&Engine::onFrameRun, this, std::placeholders::_1);

		vulkanApp->run();
	}
}

void Engine::shutdown()
{
	shader.cleanup();

	vb.cleanup();

	if (vulkanApp)
	{
		vulkanApp->shutdown();
	}
}

void Engine::onFrameRun(VkCommandBuffer commandBuffer)
{
	shader.bindGraphicsPipeline(commandBuffer);

	vb.bind(commandBuffer);

    vkCmdDraw(commandBuffer, 3, 1, 0, 0);
}