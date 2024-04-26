#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include<vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>

#include <limits.h>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <limits> 

#include "Mwindow.hpp"
#include "Mdevice.hpp"
#include "Mpipeline.hpp"
#include "mswapchain.hpp"
class Renderer {
  public:
    Renderer();
    ~Renderer();
    void start();

  private:
      Mwindow mwindow{800, 600, "Vulkan"};
      Mdevice mdevice{ &mwindow };
      Mswapchain mswapchain{ &mdevice };
      Mpipeline mpipeline{ &mdevice, &mswapchain };

       void loop();
   
  std::vector<VkCommandBuffer> commandBuffer;
  void createCommandBuffer();
  void drawFrame();

  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
};
