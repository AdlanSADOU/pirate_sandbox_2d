#pragma once

#include <SFML/System.hpp>

namespace utils
{
    float VectorMagnitude(sf::Vector2f vector);
    sf::Vector2f RotatePointAroundCenter(sf::Vector2f point, sf::Vector2f center, float angle_rad);
    sf::Vector2f GetRandomNormalizedVector();
} // namespace utils
