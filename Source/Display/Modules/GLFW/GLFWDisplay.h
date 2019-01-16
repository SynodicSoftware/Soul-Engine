#pragma once

#include "Display/Display.h"

#include "Display/Modules/GLFW/GLFWWindow.h"

#include <vector>

struct GLFWmonitor;
class WindowParameters;
class VulkanRasterBackend;

class GLFWDisplay final : public Display {

public:

	GLFWDisplay();
	~GLFWDisplay() override;

	GLFWDisplay(const GLFWDisplay&) = delete;
	GLFWDisplay(GLFWDisplay&&) noexcept = default;

	GLFWDisplay& operator=(const GLFWDisplay&) = delete;
	GLFWDisplay& operator=(GLFWDisplay&&) noexcept = default;

	void Draw() override;
	bool Active() override;

	std::shared_ptr<Window> CreateWindow(WindowParameters&, std::shared_ptr<RasterBackend>) override;

	std::vector<char const*> GetRequiredExtensions();

private:

	std::shared_ptr<GLFWWindow> masterWindow_;

	//TODO: Replace with std::span as GLFW owns and manages the monitors - C++20
	std::vector<GLFWmonitor*> monitors_;
	std::vector<std::shared_ptr<GLFWWindow>> windows_;

};
