#pragma once

#include "Thomas.h"


class Canvas2D : public Thomas::Layer
{
public:
	Canvas2D();
	virtual ~Canvas2D() = default;

	virtual void OnAttach()override;
	virtual void OnDetach()override;

	void OnUpdate(Thomas::Timestep ts)override;
	virtual void OnImGuiRender()override;
	void OnEvent(Thomas::Event& e)override;
	
private:




};

