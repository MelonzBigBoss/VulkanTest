#include "Mwindow.hpp"

Mwindow::Mwindow(int w, int h, std::string name) : width { w }, height{ h }, windowName{name} {
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(800, 600, windowName.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

Mwindow::~Mwindow() {
	glfwDestroyWindow(window);

	glfwTerminate();
}

VkResult Mwindow::createSurface(VkInstance instance, VkSurfaceKHR* surface) {
	return glfwCreateWindowSurface(instance, window, nullptr, surface);
}


bool Mwindow::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Mwindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	auto currentWindow = reinterpret_cast<Mwindow*>(glfwGetWindowUserPointer(window));
	currentWindow->frameBuffersResized = true;
}

void Mwindow::getFrameBufferSize(int* width, int* height) {
	glfwGetFramebufferSize(window, width, height);
}

void  Mwindow::PollEvents() {
	glfwPollEvents();
}

void  Mwindow::WaitEvents() {
	glfwWaitEvents();
}