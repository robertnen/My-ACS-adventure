#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

    // Create rectangle with given bottom left corner, width, height and color
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill);

    // Create trapezoid with given bottom left corner, length and color
    Mesh* CreateTrapezoid(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, float B, float b, glm::vec3 color, bool fill = false);

    // Create semicircle with given center, radius and color
    Mesh* CreateSemicircle(const std::string& name, glm::vec3 leftBottomCorner, float radius, glm::vec3 color, bool fill);

    // Create circle with given center, radius and color
    Mesh* CreateCircle(const std::string& name, glm::vec3 leftBottomCorner, float radius, glm::vec3 color, bool fill);

    // Create background square
    Mesh* BgSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, bool fill);

    // Create point for trajectory
    Mesh* Point(const std::string& name, glm::vec3 leftBottomCorner);
}
