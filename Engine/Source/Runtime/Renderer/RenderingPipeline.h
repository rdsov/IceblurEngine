// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Math/VMath.h"

#include "Shader.h"

namespace Iceblur
{

	//-------------Rendering Pipeline Base Class-------------------//


	struct ICE_API RenderingPipeline
	{
		virtual std::string GetName() = 0;

		virtual enum Dimension GetDimension() = 0;

	protected:
		virtual void Initialize() = 0;

		virtual void Update(double deltaTime) = 0;

		virtual void Shutdown() = 0;

		friend class Renderer;
	};


	//-------------------- BASE RENDERER --------------------------//


	struct ICE_API BaseRenderer : public RenderingPipeline
	{
		std::string GetName() override
		{
			return "2D Renderer";
		}

		enum Dimension GetDimension() override
		{
			return Dimension::TWO;
		}

	private:
		void Initialize() override;

		void Update(double deltaTime) override;

		void ClearColor();

		void Shutdown() override;

	private:
		Color m_ClearColor;

		ShaderProgram* m_ShaderProgram = nullptr;
		Shader* m_VertexShader = nullptr;
		Shader* m_FragmentShader = nullptr;
	};
}
