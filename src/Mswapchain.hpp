#pragma once

#include <vulkan/vulkan.h>

#include <vector>
#include <algorithm>
#include <limits>

#include "Mdevice.hpp"
class Mswapchain {
public:
	static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

	Mswapchain(Mdevice* d);

	~Mswapchain();

	void recreateSwapChain();


	void createSwapChain();
	void cleanupSwapChain();
	void createImageViews();
	void createRenderPass();
	void createFrameBuffers();
	void createSyncObjects();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkPipelineLayout pipelineLayout;
	VkRenderPass renderPass;
	uint32_t currentFrame = 0;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	std::vector<VkFramebuffer> swapChainFramebuffers;

	std::vector<VkImageView> swapChainImageViews;

	Mdevice* mdevice;
};
