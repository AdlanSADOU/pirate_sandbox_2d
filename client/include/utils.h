#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace utils
{
    void posDebug(sf::Vector2f pos, sf::RenderWindow &window);
    float DotProduct(sf::Vector2f vector_a, sf::Vector2f vector_b);
    float VectorMagnitude(sf::Vector2f vector);
    sf::Vector2f RotatePointAroundCenter(sf::Vector2f point, sf::Vector2f center, float angle_rad);
    sf::Vector2f VectorNormalize(sf::Vector2f p);
    sf::Vector2f GetRandomNormalizedVector();
} // namespace utils
