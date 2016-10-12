#pragma once

#include "Engine Core/Camera/Camera.h"
#include "Engine Core/BasicDependencies.h"
#include "Bounding Volume Heirarchy/BVH.h"
#include "Ray Engine/RayEngine.h"
#include "Utility\GPUIncludes.h"

class Renderer{
public:

	Renderer(Camera&, glm::uvec2);

	void RenderSetup(const glm::uvec2&, Camera*, double);
	void Render(bool);


private:
	uint iCounter;
	RayJob* RenderJob;
	double frameTime;

	float changeCutoff;
	float samplesMax;
	float samplesMin;
	uint samples;

	float targetFPS;
	float scroll;

	glm::uvec2 originalScreen;
	glm::uvec2 modifiedScreen;

	uint Indices[6];

	float Vertices[6 * 4];
	GLint texUniform;
	GLint screenUniform;
	GLint cameraUniform;
	GLint modelUniform;
	GLint screenModUniform;

	bool debug;
	shading::ShaderSupport* CUDAtoScreen;

	GLuint renderBufferA;
	GLuint renderBufferB;
	struct cudaGraphicsResource *cudaBuffer;
	glm::vec4 *bufferData;
	double newTime;
	std::list<double> fiveFrame;
};
