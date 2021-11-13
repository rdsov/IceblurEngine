// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Math/VMath.h"

namespace Iceblur
{
	struct RenderingAPIProps
	{
		RenderingAPIProps(const std::string apiName = "", int major = 1, int minor = 0)
				: name(apiName), versionMinor(minor), versionMajor(major)
		{
		}

		std::string name;
		int versionMinor;
		int versionMajor;
	};

	//-------------Rendering Pipeline Base Class-------------------//

	class SpectatorCameraComponent;

	struct ICE_API RenderingPipeline
	{
		virtual std::string GetName() = 0;

		virtual enum Dimension GetDimension() = 0;

		virtual const struct ShaderProgram* GetShaderProgram() const
		{
			return m_ShaderProgram;
		}

		//Returns the current global spectator camera.
		virtual SpectatorCameraComponent* GetSpectatorCamera() const
		{
			return m_Spectator;
		}

		//Sets the active spectator camera. This is global and not scene-dependent.
		virtual void SetSpectatorCamera(SpectatorCameraComponent* camera)
		{
			m_Spectator = camera;
		}

		virtual void Refresh() = 0;

	protected:
		virtual void Initialize() = 0;

		virtual void Update(double deltaTime) = 0;

		virtual void Shutdown() = 0;

	protected:
		ShaderProgram* m_ShaderProgram;

		SpectatorCameraComponent* m_Spectator;

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

		void Refresh() override;

	private:
		void Initialize() override;

		void Update(double deltaTime) override;

		void ClearColor();

		void Shutdown() override;

	private:
		Color m_ClearColor;

		struct Shader* m_VertexShader = nullptr;
		struct Shader* m_FragmentShader = nullptr;
	};
}
