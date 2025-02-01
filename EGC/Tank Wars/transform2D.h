#pragma once

#include "utils/glm_utils.h"


namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        return glm::transpose(
            glm::mat3(1, 0, translateX,
                0, 1, translateY,
                0, 0, 1)
        );
    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        return glm::transpose(
            glm::mat3(scaleX, 0, 0,
                0, scaleY, 0,
                0, 0, 1)
        );
    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        return glm::transpose(
            glm::mat3(cos(radians), -sin(radians), 0,
                sin(radians), cos(radians), 0,
                0, 0, 1));
    }

    inline glm::mat3 Shear(glm::vec2 A, glm::vec2 B)
    {
        if (A.x == B.x) return glm::mat3(-1);

        return glm::transpose(
            glm::mat3(1, 0, 0,
                     (B.y - A.y) / (B.x - A.x), 1, 0,
                     0, 0, 1)
        );
    }

}   // namespace transform2D
