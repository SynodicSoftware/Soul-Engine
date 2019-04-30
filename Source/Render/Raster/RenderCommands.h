#pragma once

#include "Types.h"

class RenderCommand {

public:

	RenderCommand() = default;
	~RenderCommand() = default;

	RenderCommand(const RenderCommand&) = default;
	RenderCommand(RenderCommand &&) noexcept = default;

	RenderCommand& operator=(const RenderCommand&) = default;
	RenderCommand& operator=(RenderCommand &&) noexcept = default;


};

struct DrawCommand : RenderCommand {

	uint elementSize;
	uint indexOffset;
	uint vertexOffset;

};

struct DrawIndirectCommand : RenderCommand {

};

struct UpdateBufferCommand : RenderCommand {

};

struct UpdateTextureCommand : RenderCommand {

};

struct CopyBufferCommand : RenderCommand {

};

struct CopyTextureCommand : RenderCommand {

};