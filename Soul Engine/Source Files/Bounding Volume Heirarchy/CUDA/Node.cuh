#pragma once

#include "Utility\CUDAIncludes.h"
#include "BoundingBox.cuh"
#include "Ray Engine\CUDA/Ray.cuh"
class Node : public Managed
{
public:
	Node();
	~Node();

	Node* GetRight();
	Node* GetLeft();

	//CUDA_FUNCTION void TransformRay(Ray&);

private:
	static const uint systemMin = 0;
	static const uint systemMax = 0xffffffff;

	BoundingBox* box;

	Node* childLeft;
	Node* childRight;

};