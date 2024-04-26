#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.h>

#include <iostream>
class Mwindow {
	public:
		Mwindow(int w, int h, std::string name);
		~Mwindow();

		VkResult createSurface(VkInstance instance, VkSurfaceKHR* surface);

		bool shouldClose();
		void getFrameBufferSize(int* width, int* height);
		void PollEvents();
		void WaitEvents();

		bool frameBuffersResized = false;
	private:
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

		const int width;
		const int height;

		std::string windowName;
		GLFWwindow* window;
};