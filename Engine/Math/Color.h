#pragma once
#include <fstream>

namespace glds
{
	struct Color
	{
		float r, g, b;

		Color() : r{}, g{}, b{} {}
		Color(float red, float green, float blue) : r{ red }, g{ green }, b{ blue } {}
		Color(std::uint32_t rgb) // DWORD( x | b | g | r )
		{
			r = (rgb & 0xFF) / 255.0f;			//0 - 255
			g = ((rgb >> 8) & 0xFF) / 255.0f;	//0 - 255	
			b = ((rgb >> 16) & 0xFF) / 255.0f;	//0 - 255
		}

		Color operator + (const Color color) { return { r + color.r, g + color.g, b + color.b }; }
		Color operator - (const Color color) { return { r - color.r, g - color.g, b - color.b }; }
		Color operator * (const float s) const { return { r * s, g * s, b * s }; }
		operator std::uint32_t() const { return toRGB(); }
		operator bool() const { return false; }
		
		std::uint32_t toRGB() const
		{
			std::uint8_t red = static_cast<std::uint8_t>(r * 255), green = static_cast<std::uint8_t>(g * 255), blue = static_cast<std::uint8_t>(b * 255);

			return (red | (green << 8) | (blue << 16));
		}

		friend std::istream& operator >> (std::istream& stream, Color& v);

		static const Color black;
		static const Color white;
		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color purple;
		static const Color cyan;
		static const Color orange;
		static const Color yellow;
	};
}