#pragma once

#include "Thomas/Core/Core.h"

namespace Thomas
{

	struct FramebufferSpec
	{
		uint32_t Width, Height;

		uint32_t Samples = 1;

		//rendering to screen
		bool SwapChainTarget = false;

	};

	class Framebuffer
	{
	public:
		std::shared_ptr<Framebuffer> Create(const FramebufferSpec& spec);
		virtual ~Framebuffer();

		const FramebufferSpec& GetSpec() const { return m_Spec; }
		uint32_t GetColorAttachmentID() const { return m_ColorAttachment; }

		void Invalidate();

		void Bind();
		void Unbind();

		Framebuffer(const FramebufferSpec& spec);
		/*	:m_Spec(spec)
		{
			Invalidate();
		}*/

		//static std::shared_ptr<Framebuffer> Create(const FramebufferSpec& spec);
		
	private:
		

		FramebufferSpec m_Spec;
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
	};

}


