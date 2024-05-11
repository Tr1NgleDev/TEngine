#pragma once

#include <string>
#include "../glm/glm.hpp"

namespace TEngine
{
	struct Color
	{
        struct Simple
        {
            const Color* color;
            bool bytes;
            std::string to_string() const;
        };
		float r, g, b, a;
		glm::vec3 rgb();
		glm::vec4 rgba();

        Color();
        Color& operator=(const Color& other);
        Color& operator=(Color&& other) noexcept;
        Color operator*(const Color& other) const;
        Color operator*(float v) const;
        Color(const Color& other);
        Color(Color&& other) noexcept;
        Color(float r, float g, float b, float a);
        Color(int r, int g, int b, int a);
        Color(float r, const glm::vec3& gba);
        Color(float r, const glm::vec2& gb, float a);
        Color(const glm::vec2& rg, float b, float a);
        Color(const glm::vec2& rg, const glm::vec2& ba);
        Color(float r, float g, const glm::vec2& ba);
        Color(const glm::vec3& rgb, float a);
        Color(const glm::vec4& rgba);
        int toARGB() const;
        bool operator==(const Color& other) const;
        bool equals(const Color& other) const;
        std::size_t hash() const;
        std::string to_string() const;
        // for simplified to_string()
        Color::Simple to_simple(bool bytes = true) const;
        static Color fromSrgb(const Color& srgb);
        static Color toSrgb(const Color& rgb);

        // Colors

        inline static Color Transparent() { return Color(255, 255, 255, 0); }
        inline static Color AliceBlue() { return Color(240, 248, 255, 255); }
        inline static Color AntiqueWhite() { return Color(250, 235, 215, 255); }
        inline static Color Aqua() { return Color(0, 255, 255, 255); }
        inline static Color Aquamarine() { return Color(127, 255, 212, 255); }
        inline static Color Azure() { return Color(240, 255, 255, 255); }
        inline static Color Beige() { return Color(245, 245, 220, 255); }
        inline static Color Bisque() { return Color(255, 228, 196, 255); }
        inline static Color Black() { return Color(0, 0, 0, 255); }
        inline static Color BlanchedAlmond() { return Color(255, 235, 205, 255); }
        inline static Color Blue() { return Color(0, 0, 255, 255); }
        inline static Color BlueViolet() { return Color(138, 43, 226, 255); }
        inline static Color Brown() { return Color(165, 42, 42, 255); }
        inline static Color BurlyWood() { return Color(222, 184, 135, 255); }
        inline static Color CadetBlue() { return Color(95, 158, 160, 255); }
        inline static Color Chartreuse() { return Color(127, 255, 0, 255); }
        inline static Color Chocolate() { return Color(210, 105, 30, 255); }
        inline static Color Coral() { return Color(255, 127, 80, 255); }
        inline static Color CornflowerBlue() { return Color(100, 149, 237, 255); }
        inline static Color Cornsilk() { return Color(255, 248, 220, 255); }
        inline static Color Crimson() { return Color(220, 20, 60, 255); }
        inline static Color Cyan() { return Color(0, 255, 255, 255); }
        inline static Color DarkBlue() { return Color(0, 0, 139, 255); }
        inline static Color DarkCyan() { return Color(0, 139, 139, 255); }
        inline static Color DarkGoldenrod() { return Color(184, 134, 11, 255); }
        inline static Color DarkGray() { return Color(169, 169, 169, 255); }
        inline static Color DarkGreen() { return Color(0, 100, 0, 255); }
        inline static Color DarkKhaki() { return Color(189, 183, 107, 255); }
        inline static Color DarkMagenta() { return Color(139, 0, 139, 255); }
        inline static Color DarkOliveGreen() { return Color(85, 107, 47, 255); }
        inline static Color DarkOrange() { return Color(255, 140, 0, 255); }
        inline static Color DarkOrchid() { return Color(153, 50, 204, 255); }
        inline static Color DarkRed() { return Color(139, 0, 0, 255); }
        inline static Color DarkSalmon() { return Color(233, 150, 122, 255); }
        inline static Color DarkSeaGreen() { return Color(143, 188, 139, 255); }
        inline static Color DarkSlateBlue() { return Color(72, 61, 139, 255); }
        inline static Color DarkSlateGray() { return Color(47, 79, 79, 255); }
        inline static Color DarkTurquoise() { return Color(0, 206, 209, 255); }
        inline static Color DarkViolet() { return Color(148, 0, 211, 255); }
        inline static Color DeepPink() { return Color(255, 20, 147, 255); }
        inline static Color DeepSkyBlue() { return Color(0, 191, 255, 255); }
        inline static Color DimGray() { return Color(105, 105, 105, 255); }
        inline static Color DodgerBlue() { return Color(30, 144, 255, 255); }
        inline static Color Firebrick() { return Color(178, 34, 34, 255); }
        inline static Color FloralWhite() { return Color(255, 250, 240, 255); }
        inline static Color ForestGreen() { return Color(34, 139, 34, 255); }
        inline static Color Fuchsia() { return Color(255, 0, 255, 255); }
        inline static Color Gainsboro() { return Color(220, 220, 220, 255); }
        inline static Color GhostWhite() { return Color(248, 248, 255, 255); }
        inline static Color Gold() { return Color(255, 215, 0, 255); }
        inline static Color Goldenrod() { return Color(218, 165, 32, 255); }
        inline static Color Gray() { return Color(128, 128, 128, 255); }
        inline static Color Green() { return Color(0, 128, 0, 255); }
        inline static Color GreenYellow() { return Color(173, 255, 47, 255); }
        inline static Color Honeydew() { return Color(240, 255, 240, 255); }
        inline static Color HotPink() { return Color(255, 105, 180, 255); }
        inline static Color IndianRed() { return Color(205, 92, 92, 255); }
        inline static Color Indigo() { return Color(75, 0, 130, 255); }
        inline static Color Ivory() { return Color(255, 255, 240, 255); }
        inline static Color Khaki() { return Color(240, 230, 140, 255); }
        inline static Color Lavender() { return Color(230, 230, 250, 255); }
        inline static Color LavenderBlush() { return Color(255, 240, 245, 255); }
        inline static Color LawnGreen() { return Color(124, 252, 0, 255); }
        inline static Color LemonChiffon() { return Color(255, 250, 205, 255); }
        inline static Color LightBlue() { return Color(173, 216, 230, 255); }
        inline static Color LightCoral() { return Color(240, 128, 128, 255); }
        inline static Color LightCyan() { return Color(224, 255, 255, 255); }
        inline static Color LightGoldenrodYellow() { return Color(250, 250, 210, 255); }
        inline static Color LightGreen() { return Color(144, 238, 144, 255); }
        inline static Color LightGray() { return Color(211, 211, 211, 255); }
        inline static Color LightPink() { return Color(255, 182, 193, 255); }
        inline static Color LightSalmon() { return Color(255, 160, 122, 255); }
        inline static Color LightSeaGreen() { return Color(32, 178, 170, 255); }
        inline static Color LightSkyBlue() { return Color(135, 206, 250, 255); }
        inline static Color LightSlateGray() { return Color(119, 136, 153, 255); }
        inline static Color LightSteelBlue() { return Color(176, 196, 222, 255); }
        inline static Color LightYellow() { return Color(255, 255, 224, 255); }
        inline static Color Lime() { return Color(0, 255, 0, 255); }
        inline static Color LimeGreen() { return Color(50, 205, 50, 255); }
        inline static Color Linen() { return Color(250, 240, 230, 255); }
        inline static Color Magenta() { return Color(255, 0, 255, 255); }
        inline static Color Maroon() { return Color(128, 0, 0, 255); }
        inline static Color MediumAquamarine() { return Color(102, 205, 170, 255); }
        inline static Color MediumBlue() { return Color(0, 0, 205, 255); }
        inline static Color MediumOrchid() { return Color(186, 85, 211, 255); }
        inline static Color MediumPurple() { return Color(147, 112, 219, 255); }
        inline static Color MediumSeaGreen() { return Color(60, 179, 113, 255); }
        inline static Color MediumSlateBlue() { return Color(123, 104, 238, 255); }
        inline static Color MediumSpringGreen() { return Color(0, 250, 154, 255); }
        inline static Color MediumTurquoise() { return Color(72, 209, 204, 255); }
        inline static Color MediumVioletRed() { return Color(199, 21, 133, 255); }
        inline static Color MidnightBlue() { return Color(25, 25, 112, 255); }
        inline static Color MintCream() { return Color(245, 255, 250, 255); }
        inline static Color MistyRose() { return Color(255, 228, 225, 255); }
        inline static Color Moccasin() { return Color(255, 228, 181, 255); }
        inline static Color NavajoWhite() { return Color(255, 222, 173, 255); }
        inline static Color Navy() { return Color(0, 0, 128, 255); }
        inline static Color OldLace() { return Color(253, 245, 230, 255); }
        inline static Color Olive() { return Color(128, 128, 0, 255); }
        inline static Color OliveDrab() { return Color(107, 142, 35, 255); }
        inline static Color Orange() { return Color(255, 165, 0, 255); }
        inline static Color OrangeRed() { return Color(255, 69, 0, 255); }
        inline static Color Orchid() { return Color(218, 112, 214, 255); }
        inline static Color PaleGoldenrod() { return Color(238, 232, 170, 255); }
        inline static Color PaleGreen() { return Color(152, 251, 152, 255); }
        inline static Color PaleTurquoise() { return Color(175, 238, 238, 255); }
        inline static Color PaleVioletRed() { return Color(219, 112, 147, 255); }
        inline static Color PapayaWhip() { return Color(255, 239, 213, 255); }
        inline static Color PeachPuff() { return Color(255, 218, 185, 255); }
        inline static Color Peru() { return Color(205, 133, 63, 255); }
        inline static Color Pink() { return Color(255, 192, 203, 255); }
        inline static Color Plum() { return Color(221, 160, 221, 255); }
        inline static Color PowderBlue() { return Color(176, 224, 230, 255); }
        inline static Color Purple() { return Color(128, 0, 128, 255); }
        inline static Color Red() { return Color(255, 0, 0, 255); }
        inline static Color RosyBrown() { return Color(188, 143, 143, 255); }
        inline static Color RoyalBlue() { return Color(65, 105, 225, 255); }
        inline static Color SaddleBrown() { return Color(139, 69, 19, 255); }
        inline static Color Salmon() { return Color(250, 128, 114, 255); }
        inline static Color SandyBrown() { return Color(244, 164, 96, 255); }
        inline static Color SeaGreen() { return Color(46, 139, 87, 255); }
        inline static Color SeaShell() { return Color(255, 245, 238, 255); }
        inline static Color Sienna() { return Color(160, 82, 45, 255); }
        inline static Color Silver() { return Color(192, 192, 192, 255); }
        inline static Color SkyBlue() { return Color(135, 206, 235, 255); }
        inline static Color SlateBlue() { return Color(106, 90, 205, 255); }
        inline static Color SlateGray() { return Color(112, 128, 144, 255); }
        inline static Color Snow() { return Color(255, 250, 250, 255); }
        inline static Color SpringGreen() { return Color(0, 255, 127, 255); }
        inline static Color SteelBlue() { return Color(70, 130, 180, 255); }
        inline static Color Tan() { return Color(210, 180, 140, 255); }
        inline static Color Teal() { return Color(0, 128, 128, 255); }
        inline static Color Thistle() { return Color(216, 191, 216, 255); }
        inline static Color Tomato() { return Color(255, 99, 71, 255); }
        inline static Color Turquoise() { return Color(64, 224, 208, 255); }
        inline static Color Violet() { return Color(238, 130, 238, 255); }
        inline static Color Wheat() { return Color(245, 222, 179, 255); }
        inline static Color White() { return Color(255, 255, 255, 255); }
        inline static Color WhiteSmoke() { return Color(245, 245, 245, 255); }
        inline static Color Yellow() { return Color(255, 255, 0, 255); }
        inline static Color YellowGreen() { return Color(154, 205, 50, 255); }
	};
}

// some std implements
namespace std
{
    inline std::string to_string(const TEngine::Color& color) noexcept
    {
        return color.to_string();
    }
    inline std::string to_string(const TEngine::Color::Simple& sColor) noexcept
    {
        return sColor.to_string();
    }

    template <>
    struct hash<TEngine::Color>
    {
        inline std::size_t operator()(const TEngine::Color& color) const noexcept
        {
            return color.hash();
        }
    };
}