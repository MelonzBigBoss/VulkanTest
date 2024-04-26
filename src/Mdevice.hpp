#pragma once

#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <iostream>
#include <unordered_set>
#include <optional>
#include <map>
#include "Mwindow.hpp"
class Mdevice {
public:
	Mwindow* mwindow;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkInstance instance;
	VkDevice device;
	VkSurfaceKHR surface;
	VkQueue graphicsQueue; 
	VkQueue presentQueue;
	VkCommandPool commandPool;

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	SwapChainSupportDetails querySwapChainSupportDetails(VkPhysicalDevice device);

	Mdevice(Mwindow* w);
	~Mdevice();

	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
	#endif

	void WaitIdle();
private:
	VkDebugUtilsMessengerEXT debugMessenger;

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger);

	void DestroyDebugUtilsMessengerEXT(VkInstance instance,
		VkDebugUtilsMessengerEXT debugMessenger,
		const VkAllocationCallbacks* pAllocator);

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	void createInstance();
	void createDebugMessenger();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createCommandPool();

	bool checkValidationLayersSupport();

	std::vector<const char*> getRequiredExtensions();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	int rateDeviceSuitability(VkPhysicalDevice device);

	const std::vector<const char*> validationLayers = {
	  "VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions = {
	 VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};


};