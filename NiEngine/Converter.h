#pragma once

#include <math_functions.h>

#include <numbers>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Angle.hpp>

namespace converter
{
	constexpr float PIXELS_PER_METERS = 32.0;

	template<typename T>
	constexpr T PixelsToMeters(const T& x) { return x / PIXELS_PER_METERS; };

	template<typename T>
	constexpr T MetersToPixels(const T& x) { return x * PIXELS_PER_METERS; };

	template<typename T>
	constexpr T DegToRad(const T& x) { return std::numbers::pi * x / 180.0; };

	template<typename T>
	constexpr T RadToDeg(const T& x) { return 180.0 * x / std::numbers::pi; }

	inline sf::Vector2f MetersToPixels(const b2Vec2& v) 
	{
		return sf::Vector2f(v.x * PIXELS_PER_METERS, v.y * PIXELS_PER_METERS);
	}

	inline b2Vec2 PixelsToMeters(const sf::Vector2f& v)
	{
		return b2Vec2(v.x / PIXELS_PER_METERS, v.y / PIXELS_PER_METERS);
	}

	inline b2Vec2 PixelsToMeters(const sf::Vector2i& v)
	{
		return b2Vec2(v.x / PIXELS_PER_METERS, v.y / PIXELS_PER_METERS);
	}

	inline sf::Angle RotToAngle(const b2Rot& v)
	{
		return sf::Angle(sf::radians(b2Rot_GetAngle(v)));
	}
}
