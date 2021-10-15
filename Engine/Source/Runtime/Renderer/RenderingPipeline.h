// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Math/VMath.h"

namespace Iceblur
{
    struct ICE_API RenderingPipeline
    {
        virtual std::string GetName() = 0;

        virtual enum class Dimension GetDimension() = 0;

    protected:
        virtual void Initialize() = 0;

        virtual void Update(double deltaTime) = 0;

        virtual void Shutdown() = 0;

        friend class Renderer;
    };

    struct ICE_API SimpleRenderer : public RenderingPipeline
    {
        std::string GetName() override
        {
            return "2D Renderer";
        }

        enum class Dimension GetDimension() override
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

    };
}
