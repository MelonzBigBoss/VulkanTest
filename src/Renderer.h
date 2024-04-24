#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include<vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <optional>
#include <set>
#include <limits> 
#include <algorithm>
#include <cstring>
#include <fstream>
class Renderer {
  public:
    Renderer();
    ~Renderer();
    void start();

  private:
    void loop();
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    int rateDeviceSuitability(VkPhysicalDevice device);
   
    void createInstance();
    void createDebugMessenger();

    const std::vector<const char*> validationLayers = {
      "VK_LAYER_KHRONOS_validation"
    };

  
    #ifdef NDEBUG
      const bool enableValidationLayers = false;
    #else
      const bool enableValidationLayers = true;
    #endif
    const int MAX_FRAMES_IN_FLIGHT = 2;
    VkDebugUtilsMessengerEXT debugMessenger;

    bool checkValidationLayers();
    std::vector<const char*> getRequiredExtensions();
    void createLogicalDevice();
    void createSwapChain();
    void recreateSwapChain();
    void cleanupSwapChain();
    void pickPhysicalDevice();
    void createSurface();
    void createImageViews();
    void createRenderPass();
    void createFrameBuffers();
    void createGraphicsPipeline();
  void createCommandPool();
  std::vector<VkCommandBuffer> commandBuffer;
  void createCommandBuffer();
  void drawFrame();
  void createSyncObjects();

  std::vector<VkFramebuffer> swapChainFramebuffers;

  VkCommandPool commandPool;

  std::vector<VkImageView> swapChainImageViews;

  struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
      return graphicsFamily.has_value() && presentFamily.has_value();
    }
  };

  struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
  };
  SwapChainSupportDetails querySwapChainSupportDetails(VkPhysicalDevice device);
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
 
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
  GLFWwindow* window;
  static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

  VkInstance instance;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device;
  VkQueue graphicsQueue;
  VkSurfaceKHR surface;
  VkQueue presentQueue;
  VkSwapchainKHR swapChain;
  std::vector<VkImage> swapChainImages;
  VkPipelineLayout pipelineLayout;
  VkRenderPass renderPass;
  uint32_t currentFrame = 0;

  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;

  bool frameBuffersResized = false;

  VkPipeline graphicsPipeline;

  VkFormat swapChainImageFormat;
VkExtent2D swapChainExtent;

  const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
  };


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

  VkShaderModule createShaderModule(const std::vector<char>& code);

  static std::vector<char> readFile(const std::string& filename);
};
