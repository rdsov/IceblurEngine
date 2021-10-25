// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"

#define RES_INVALID_RETURN_VAL 1

namespace Iceblur
{
	enum class Dimension
	{
		ONE,
		TWO,
		THREE,
		FOUR
	};

	struct ICE_API Resolution
	{
		Resolution(int x, int y, bool canBeZero = false)
		{
			canBeNull = canBeZero;
			if (canBeNull)
			{
				m_Width = x;
				m_Height = y;
			}
			else
			{
				if (x > 0 && y > 0)
				{
					m_Width = x;
					m_Height = y;
				}
				else
				{
					ResolutionNullError();
				}
			}
		}

		NODISCARD inline int GetWidth() const
		{
			if (canBeNull)
			{
				return m_Width;
			}
			else
			{
				if (m_Width > 0)
				{
					return m_Width;
				}
			}

			ResolutionNullError();
			return RES_INVALID_RETURN_VAL;
		}

		NODISCARD inline int SetWidth(int value)
		{
			if (canBeNull)
			{
				m_Width = value;
				return m_Width;
			}
			else
			{
				if (value > 0)
				{
					m_Width = value;
					return m_Width;
				}
			}

			ResolutionNullError();
			return RES_INVALID_RETURN_VAL;
		}

		NODISCARD inline int GetHeight() const
		{
			if (canBeNull)
			{
				return m_Height;
			}
			else
			{
				if (m_Height > 0)
				{
					return m_Height;
				}
			}

			ResolutionNullError();
			return RES_INVALID_RETURN_VAL;
		}

		NODISCARD inline int SetHeight(int value)
		{
			if (canBeNull)
			{
				m_Height = value;
				return m_Height;
			}
			else
			{
				if (value > 0)
				{
					m_Height = value;
					return m_Height;
				}
			}

			ResolutionNullError();
			return RES_INVALID_RETURN_VAL;
		}

		//Should an error be thrown once m_Width or m_Height are zero or negative?
		bool canBeNull = false;

		NODISCARD inline int GetAspectRatio() const
		{
			if (m_Width > 0 && m_Height > 0)
			{
				return m_Width / m_Height;
			}

			ResolutionNullError();
			return RES_INVALID_RETURN_VAL;
		}

	private:
		static void ResolutionNullError();

	private:
		int m_Width = 1;
		int m_Height = 1;
	};

#define RGB_CHANNELS(var) (var).red, (var).green, (var).blue
#define ALL_COLOR_CHANNELS(var) var.red, (var).green, (var).blue, (var).alpha

	struct Color
	{
		Color()
				: red(0), green(0), blue(0), alpha(0)
		{
		}

		Color(float rgb, float alpha = 0)
				: red(rgb), green(rgb), blue(rgb), alpha(alpha)
		{
		}

		Color(float r, float g, float b, float a = 1)
				: red(r), green(g), blue(b), alpha(a)
		{
		}

		float red = 0;
		float green = 0;
		float blue = 0;
		float alpha = 0;
	};
}
