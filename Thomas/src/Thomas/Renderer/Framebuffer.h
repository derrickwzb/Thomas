/*!*************************************************************************
\file:				Framebuffer.h
\author:			Derrick Woo
\par DP email:		d.woo@digipen.edu
\par Course:		CSD2125
\par Programming:	CSD2400 Game project
\date:				31/10/2022
\brief:
		This file contains the declaration for Framebuffer class.
****************************************************************************/
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

		void Resize(uint32_t width, uint32_t height);

		Framebuffer(const FramebufferSpec& spec);
		
	private:
		FramebufferSpec m_Spec;
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
	};
}


