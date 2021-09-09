// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"

namespace Iceblur
{
    class VMath
    {
    public:
        struct Resolution
        {
            Resolution(float x, float y, bool canBeZeroOrNegative = false)
            {
                canBeNull = canBeZeroOrNegative;
                if (canBeNull)
                {
                    width = x;
                    height = y;
                }
                else
                {
                    if (x > 0 && y > 0)
                    {
                        width = x;
                        height = y;
                    }
                }
            }

            NODISCARD inline float GetWidth() const
            {
                if (canBeNull)
                {
                    return width;
                }
                else
                {
                    if (width > 0)
                    {
                        return width;
                    }

                    //TODO: ERROR
                }

                //TODO: ERROR

                return 0;
            }

            NODISCARD inline float SetWidth(float value)
            {
                if (canBeNull)
                {
                    width = value;
                    return width;
                }
                else
                {
                    if (value > 0)
                    {
                        width = value;
                        return width;
                    }

                    //TODO: ERROR
                }

                return 0;
            }

            NODISCARD inline float GetHeight() const
            {
                if (canBeNull)
                {
                    return height;
                }
                else
                {
                    if (height > 0)
                    {
                        return height;
                    }

                    //TODO: ERROR
                }

                return 0;
            }

            NODISCARD inline float SetHeight(float value)
            {
                if (canBeNull)
                {
                    height = value;
                    return height;
                }
                else
                {
                    if (value > 0)
                    {
                        height = value;
                        return height;
                    }

                    //TODO: ERROR
                }

                return 0;
            }

            //Should an error be thrown once width or height are zero or negative?
            bool canBeNull = false;

            NODISCARD inline float GetAspectRatio() const
            {
                if (width > 0 && height > 0)
                {
                    return width / height;
                }

                //TODO: ERROR

                return 0;
            }

        private:
            float width = 1.0;
            float height = 1.0;
        };
    };
}
