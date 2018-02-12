#pragma once
#include <glm/glm.hpp>
#include "Compute/ComputeBuffer.h"

namespace Filter {

	void IterativeBicubic(glm::vec4* data, glm::uvec2 originalSize, glm::uvec2 desiredSize);
	void Nearest(glm::vec4* data, glm::uvec2 originalSize, glm::uvec2 desiredSize);
}
