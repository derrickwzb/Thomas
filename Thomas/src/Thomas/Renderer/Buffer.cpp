#include "thpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Thomas
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			//can assert here
		case RendererAPI::None: return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices , size);

		}

		//assert here if false
		return nullptr;
	}
	
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			//can assert here
		case RendererAPI::None: return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);

		}

		//assert here if false
		return nullptr;
	}

}