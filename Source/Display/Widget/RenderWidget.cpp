#include "RenderWidget.h"
#include "Compute\ComputeManager.h"
#include "CUDA\RenderWidget.cuh"
#include "Events\EventManager.h"
#include "Raster Engine/RasterManager.h"
#include "Input/InputManager.h"
#include "Compute/ComputeBuffer.h"
#include "Photography/Camera/Camera.h"
#include "Ray Engine/RayEngine.h"

/*
 *    Constructor.
 *    @param [in,out]	cameraIn	If non-null, the camera in.
 */

RenderWidget::RenderWidget(uint& id): 
	buffer(S_BEST_GPU), 
	accumulator(S_BEST_GPU), 
	extraData(S_BEST_GPU),
	time(0)
{
	widgetJob = RasterManager::Instance().CreateJob();

	samples = 1.0f;

	//attach shaders to render a quad and apply a texture
	widgetJob->AttachShaders({
		RasterManager::Instance().CreateShader("Resources/Shaders/vertex-shader[Renderer].glsl",VERTEX_SHADER),
		RasterManager::Instance().CreateShader("Resources/Shaders/fragment-shader[Renderer].glsl",FRAGMENT_SHADER)
	});


	//init all uniform data
	widgetJob->RegisterUniform(std::string("screen"));

	uint indices[6];
	float vertices[6 * 4];

	vertices[0] = -1.0f;
	vertices[1] = -1.0f;
	vertices[2] = 0.0f;
	vertices[3] = 1.0f;


	vertices[4] = 1.0f;
	vertices[5] = 1.0f;
	vertices[6] = 0.0f;
	vertices[7] = 1.0f;


	vertices[8] = -1.0f;
	vertices[9] = 1.0f;
	vertices[10] = 0.0f;
	vertices[11] = 1.0f;


	vertices[12] = 1.0f;
	vertices[13] = -1.0f;
	vertices[14] = 0.0f;
	vertices[15] = 1.0f;

	indices[0] = 0;
	indices[1] = 2;
	indices[2] = 1;
	indices[3] = 0;
	indices[4] = 1;
	indices[5] = 3;

	widgetJob->UploadGeometry(vertices, sizeof(vertices), indices, sizeof(indices));

	iCounter = 1;
	integrate = false;
	currentSize = glm::uvec2(312, 720);

	rayJob = RayEngine::Instance().AddJob(RayCOLOUR, true, samples);

	id = rayJob;
}

/* Draws this object. */
void RenderWidget::Draw() {

	EventManager::Listen("Input", "SPACE", [&integrate = integrate, &time = time](keyState state) {
		double newTime = glfwGetTime();
		if (newTime - time > 0.3f) {
			integrate = !integrate;
			time = newTime;
		}
	});

	if (integrate) {
		Integrate(renderSize.x*renderSize.y, buffer.DataDevice(), accumulator.DataDevice(), extraData.DataDevice(), iCounter);
		iCounter++;
	}
	else {
		iCounter = 1;
	}

	buffer.UnmapResources();
	buffer.BindData(0);
	widgetJob->Draw();

	//add the rayJob back in
	buffer.MapResources();

	//get job values
	widgetJob->SetUniform(std::string("screen"), renderSize);

}

/* Recreate data. */
void RenderWidget::RecreateData() {

	const auto jobsize = size.x*size.y;

	//create the new accumulation Buffer
	accumulator.ResizeDevice(jobsize);
	buffer.ResizeDevice(jobsize);
	extraData.ResizeDevice(jobsize);

	if (currentSize != size) {
		currentSize = size;
		renderSize = size;
		widgetJob->SetUniform(std::string("screen"), renderSize);
	}

	//add the ray job with new sizes
	buffer.MapResources();

	//set job values
	RayJob& job = RayEngine::Instance().GetJob(rayJob);

	job.camera.aspectRatio = static_cast<float>(renderSize.x) / static_cast<float>(renderSize.y);
	job.camera.film.resolution = renderSize;
	job.camera.film.resolutionMax = renderSize;
	job.camera.film.results = buffer.DataDevice();
	job.camera.film.hits = extraData.DataDevice();

}