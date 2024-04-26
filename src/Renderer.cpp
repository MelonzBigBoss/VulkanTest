#include "Renderer.hpp"

Renderer::Renderer() {
  this->createCommandBuffer();
}
Renderer::~Renderer() {
}

void Renderer::loop() {
  drawFrame();
}

void Renderer::start() {

  while (!mwindow.shouldClose()) {
    mwindow.PollEvents();
    this->loop();
  }

  mdevice.WaitIdle();
}

void Renderer::drawFrame() {
  vkWaitForFences(mdevice.device, 1, &mswapchain.inFlightFences[mswapchain.currentFrame], VK_TRUE, UINT64_MAX);


      uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(mdevice.device, mswapchain.swapChain, UINT64_MAX, mswapchain.imageAvailableSemaphores[mswapchain.currentFrame], VK_NULL_HANDLE, &imageIndex);

  if (result == VK_ERROR_OUT_OF_DATE_KHR) {
      mswapchain.recreateSwapChain();
    return;
  } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
   throw std::runtime_error("failed to aquire swap chain image!"); 
  }

  vkResetFences(mdevice.device, 1, &mswapchain.inFlightFences[mswapchain.currentFrame]);

 vkResetCommandBuffer(commandBuffer[mswapchain.currentFrame], 0);

  recordCommandBuffer(commandBuffer[mswapchain.currentFrame], imageIndex);

  VkSubmitInfo submitInfo{};
submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

VkSemaphore waitSemaphores[] = { mswapchain.imageAvailableSemaphores[mswapchain.currentFrame]};
VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
submitInfo.waitSemaphoreCount = 1;
submitInfo.pWaitSemaphores = waitSemaphores;
submitInfo.pWaitDstStageMask = waitStages;

  submitInfo.commandBufferCount = 1;
submitInfo.pCommandBuffers = &commandBuffer[mswapchain.currentFrame];

  VkSemaphore signalSemaphores[] = {mswapchain.renderFinishedSemaphores[mswapchain.currentFrame]};
submitInfo.signalSemaphoreCount = 1;
submitInfo.pSignalSemaphores = signalSemaphores;

  if (vkQueueSubmit(mdevice.graphicsQueue, 1, &submitInfo, mswapchain.inFlightFences[mswapchain.currentFrame]) != VK_SUCCESS) {
    throw std::runtime_error("failed to submit draw command buffer!");
}

  VkPresentInfoKHR presentInfo{};
presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

presentInfo.waitSemaphoreCount = 1;
presentInfo.pWaitSemaphores = signalSemaphores;

  VkSwapchainKHR swapChains[] = { mswapchain.swapChain};
presentInfo.swapchainCount = 1;
presentInfo.pSwapchains = swapChains;
presentInfo.pImageIndices = &imageIndex;

  presentInfo.pResults = nullptr; // Optional
  
result = vkQueuePresentKHR(mdevice.presentQueue, &presentInfo);

  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || mwindow.frameBuffersResized) {
    mwindow.frameBuffersResized = false;
    mswapchain.recreateSwapChain();
  } else if (result != VK_SUCCESS){
    throw std::runtime_error("failed to present swap chain image!");
  }

  mswapchain.currentFrame = (mswapchain.currentFrame + 1) % Mswapchain::MAX_FRAMES_IN_FLIGHT;
}

void Renderer::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
VkCommandBufferBeginInfo beginInfo{};
beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
beginInfo.flags = 0; // Optional
beginInfo.pInheritanceInfo = nullptr; // Optional

if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
    throw std::runtime_error("failed to begin recording command buffer!");
}

  VkRenderPassBeginInfo renderPassInfo{};
renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
renderPassInfo.renderPass = mswapchain.renderPass;
renderPassInfo.framebuffer = mswapchain.swapChainFramebuffers[imageIndex];
renderPassInfo.renderArea.offset = {0, 0};
renderPassInfo.renderArea.extent = mswapchain.swapChainExtent;

  VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
renderPassInfo.clearValueCount = 1;
renderPassInfo.pClearValues = &clearColor;

  vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

  vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, mpipeline.graphicsPipeline);

  VkViewport viewport{};
viewport.x = 0.0f;
viewport.y = 0.0f;
viewport.width = static_cast<float>(mswapchain.swapChainExtent.width);
viewport.height = static_cast<float>(mswapchain.swapChainExtent.height);
viewport.minDepth = 0.0f;
viewport.maxDepth = 1.0f;
vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

VkRect2D scissor{};
scissor.offset = {0, 0};
scissor.extent = mswapchain.swapChainExtent;
vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

  vkCmdDraw(commandBuffer, 3, 1, 0, 0);

  vkCmdEndRenderPass(commandBuffer);

  if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
    throw std::runtime_error("failed to record command buffer!");
}

}

void Renderer::createCommandBuffer() {
  commandBuffer.resize(Mswapchain::MAX_FRAMES_IN_FLIGHT);
  VkCommandBufferAllocateInfo allocInfo{};
allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
allocInfo.commandPool = mdevice.commandPool;
allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
allocInfo.commandBufferCount = (uint32_t)commandBuffer.size();

if (vkAllocateCommandBuffers(mdevice.device, &allocInfo, commandBuffer.data()) != VK_SUCCESS) {
    throw std::runtime_error("failed to allocate command buffers!");
}
}

