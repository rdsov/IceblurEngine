// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

namespace Iceblur
{
    struct RenderingPipeline;

    class Renderer
    {
    public:
        static void Initialize();

        static void SetActiveRenderingPipeline(RenderingPipeline* pipeline);

        static void Update();

        static void Shutdown();

    private:
        static RenderingPipeline* m_ActivePipeline;
    };
}
