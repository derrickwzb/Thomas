#pragma once

#include "Thomas.h"


class EditorLayer : public Thomas::Layer
{
public:
	EditorLayer();
	virtual ~EditorLayer() = default;

	virtual void OnAttach()override;
	virtual void OnDetach()override;

	void OnUpdate(Thomas::Timestep ts)override;
	virtual void OnImGuiRender()override;
	void OnEvent(Thomas::Event& e)override;
	
private:

	//camera controller




};

