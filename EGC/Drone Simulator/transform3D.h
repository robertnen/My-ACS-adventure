#pragma once

#include "utils/glm_utils.h"


namespace transform3D
{
    // Translate matrix
    inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
    {
        return glm::mat4(
            1, 0, 0, 0,     // coloana 1 in memorie 
            0, 1, 0, 0,     // coloana 2 in memorie 
            0, 0, 1, 0,     // coloana 3 in memorie 
            translateX, translateY, translateZ, 1);    // coloana 4 in memorie 
    }

    // Scale matrix
    inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
    {
        // TODO(student): Implement the scaling matrix
        return glm::transpose(
            glm::mat4(scaleX, 0, 0, 0,
                0, scaleY, 0, 0,
                0, 0, scaleZ, 0,
                0, 0, 0, 1));
    }

    // Rotate matrix relative to the OZ axis
    inline glm::mat4 RotateOZ(float radians)
    {
        // TODO(student): Implement the rotation matrix
        return glm::transpose(
            glm::mat4(cos(radians), -sin(radians), 0, 0,
                sin(radians), cos(radians), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1));
    }

    // Rotate matrix relative to the OY axis
    inline glm::mat4 RotateOY(float radians)
    {
        // TODO(student): Implement the rotation matrix
        return glm::transpose(
            glm::mat4(cos(radians), 0, sin(radians), 0,
                0, 1, 0, 0,
                -sin(radians), 0, cos(radians), 0,
                0, 0, 0, 1));
    }

    // Rotate matrix relative to the OX axis
    inline glm::mat4 RotateOX(float radians)
    {
        return glm::transpose(
            glm::mat4(1, 0, 0, 0,
                0, cos(radians), -sin(radians), 0,
                0, sin(radians), cos(radians), 0,
                0, 0, 0, 1));
    }
}   // namespace transform3D
