#include "thpch.h"
#include "Framebuffer.h"

namespace Thomas
{
	Framebuffer::Framebuffer(const FramebufferSpec& spec)
		: m_Spec(spec)
	{
		Invalidate();

	}
}