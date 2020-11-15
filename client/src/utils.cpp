#include "utils.h"


float utils::VectorMagnitude(sf::Vector2f vector)
{
    float magnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    return (magnitude);
}


sf::Vector2f utils::RotatePointAroundCenter(sf::Vector2f point, sf::Vector2f center, float angle_rad)
{
    float sin_val = sin(angle_rad);
    float cos_val = cos(angle_rad);

    // translate point back to origin:
    point.x -= center.x;
    point.y -= center.y;

    // rotate point
    float xnew = point.x * cos_val - point.y * sin_val;
    float ynew = point.x * sin_val + point.y * cos_val;

    // translate point back:
    point.x = xnew + center.x;
    point.y = ynew + center.y;

    return (point);
}
