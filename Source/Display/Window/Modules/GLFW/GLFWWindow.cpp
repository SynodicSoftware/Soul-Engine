#include "GLFWWindow.h"

#include "Rasterer/Modules/Vulkan/VulkanRasterBackend.h"
#include "Rasterer/Modules/Vulkan/VulkanSwapChain.h"

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

GLFWWindow::GLFWWindow(const WindowParameters& params,
	GLFWmonitor* monitor,
	std::shared_ptr<RasterModule> rasterModule,
	bool master):
	Window(params),
	rasterModule_(std::static_pointer_cast<VulkanRasterBackend>(rasterModule)),
	master_(master)
{

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	//TODO Cleanup and implement more features

	//defaulted params
	GLFWmonitor* fullscreenMonitor = nullptr;

	//specific window type creation settings, each setting is global, so all should be set in each possibility
	if (windowParams_.type == WindowType::FULLSCREEN) {

		glfwWindowHint(GLFW_RESIZABLE, false);
		glfwWindowHint(GLFW_DECORATED, false);

		fullscreenMonitor = monitor;

	}
	else if (windowParams_.type == WindowType::WINDOWED) {

		glfwWindowHint(GLFW_RESIZABLE, true);
		glfwWindowHint(GLFW_DECORATED, true);

	}
	else if (windowParams_.type == WindowType::BORDERLESS) {

		glfwWindowHint(GLFW_RESIZABLE, false);
		glfwWindowHint(GLFW_DECORATED, false);

	}
	else {

		glfwWindowHint(GLFW_RESIZABLE, false);
		glfwWindowHint(GLFW_DECORATED, true);

	}

	context_ = glfwCreateWindow(windowParams_.pixelSize.x, windowParams_.pixelSize.y, windowParams_.title.c_str(), fullscreenMonitor, nullptr);
	assert(context_);

	//context related settings
    //TODO: enable when relevant
	//glfwSetInputMode(context_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//GLFW guarantees Vulkan support.
	VkSurfaceKHR castSurface;

	//guaranteed to use GLFW if using Vulkan
	const VkResult error = glfwCreateWindowSurface(
		static_cast<VkInstance>(rasterModule_->GetInstance()),
		context_,
		nullptr,
		&castSurface
	);

	assert(error == VK_SUCCESS);

	//surface_ = static_cast<vk::SurfaceKHR>(castSurface);
	//swapChain_ = rasterModule_->RegisterSurface(surface_, windowParams_.pixelSize);

}

GLFWWindow::~GLFWWindow() {

	//swapChain_.reset();
	//rasterModule_->RemoveSurface(surface_);

	glfwDestroyWindow(context_);

}

void GLFWWindow::Draw()
{

	//swapChain_->Present();

}

void GLFWWindow::FrameBufferResize(int x, int y)
{

	//windowParams_.pixelSize = { x,y };
	//auto newSwapChain = rasterModule_->RegisterSurface(surface_, windowParams_.pixelSize, swapChain_.get());
	//swapChain_.swap(newSwapChain);

}

GLFWwindow* GLFWWindow::Context() const
{

	return context_;

}

bool GLFWWindow::Master() const
{
	
	return master_;

}

