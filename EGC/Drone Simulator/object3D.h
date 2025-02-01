#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "core/engine.h"
#include "core/gpu/mesh.h"
#include "utils/gl_utils.h"
#include "utils/glm_utils.h"
#include "components/simple_scene.h"


namespace object3D {
    Mesh* CreateBox(const std::string& name, glm::vec3 position, glm::vec3 color);
    Mesh* CreateCone(const std::string& name, glm::vec3 position, float height, float baseRadius, glm::vec3 color, int segments);
    Mesh* CreateCylinder(const std::string& name, glm::vec3 position, float height, float baseRadius, glm::vec3 color, int segments);
}
