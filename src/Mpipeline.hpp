#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WIN 1
#include <windows.h>
#undef min
#undef max
#else
#include <unistd.h>
#endif

#include <vulkan/vulkan.h>

#include <limits.h>
#include <fstream>
#include <vector>

#include "Mdevice.hpp"
#include "Mswapchain.hpp"
class Mpipeline {
public:
	Mpipeline(Mdevice* m, Mswapchain* s);
	~Mpipeline();

	VkPipeline graphicsPipeline;
private:
	VkShaderModule createShaderModule(const std::vector<char>& code);

	static std::vector<char> readFile(const std::string& filename);

	void createGraphicsPipeline();

	static std::string getexepath();
	std::string exepath = "";

	Mdevice* mdevice;
	Mswapchain* mswapchain;
};
