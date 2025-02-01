#include "object3D.h"

using namespace std;

Mesh* object3D::CreateBox(const std::string& name, glm::vec3 position, glm::vec3 color) {
    std::vector<VertexFormat> vertices = {
        VertexFormat(position + glm::vec3(0, 0, 0), color), // bottom
        VertexFormat(position + glm::vec3(1, 0, 0), color),
        VertexFormat(position + glm::vec3(1, 1, 0), color),
        VertexFormat(position + glm::vec3(0, 1, 0), color),
        VertexFormat(position + glm::vec3(0, 0, 1), color), // top
        VertexFormat(position + glm::vec3(1, 0, 1), color),
        VertexFormat(position + glm::vec3(1, 1, 1), color),
        VertexFormat(position + glm::vec3(0, 1, 1), color),
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 5, 5, 4, 0,
        1, 2, 6, 6, 5, 1,
        2, 3, 7, 7, 6, 2,
        3, 0, 4, 4, 7, 3
    };

    Mesh* box = new Mesh(name);
    box->InitFromData(vertices, indices);
    return box;
}

Mesh* object3D::CreateCone(const std::string& name, glm::vec3 position, float height, float radius, glm::vec3 color, int segments = 36) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.emplace_back(position + glm::vec3(0, height, 0), color);  //* the above part of the cone
    vertices.emplace_back(position + glm::vec3(0), color);             //* the base part of the cone

    for (int i = 0; i < segments; i++) {
        float angle = glm::radians(360.0f * i / segments);
        vertices.emplace_back(position + glm::vec3(radius * cos(angle), 0, radius * sin(angle)), color);
    }

    for (int i = 0; i < segments; i++) {
        indices.push_back(0);
        indices.push_back(2 + i);
        indices.push_back(2 + (i + 1) % segments);
    }

    for (int i = 0; i < segments; i++) {
        indices.push_back(1);
        indices.push_back(2 + (i + 1) % segments);
        indices.push_back(2 + i);
    }

    Mesh* cone = new Mesh(name);
    cone->InitFromData(vertices, indices);
    return cone;
}

Mesh* object3D::CreateCylinder(const std::string& name, glm::vec3 position, float height, float baseRadius, glm::vec3 color, int segments) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.emplace_back(position + glm::vec3(0, height, 0), color);  //* the above part of the cylinder
    vertices.emplace_back(position + glm::vec3(0, 0, 0), color);       //* the base part of the cylinder

    for (int i = 0; i < segments; i++) {
        float angle = glm::radians(360.0f * i / segments);
        vertices.emplace_back(position + glm::vec3(baseRadius * cos(angle), height, baseRadius * sin(angle)), color);
        vertices.emplace_back(position + glm::vec3(baseRadius * cos(angle), 0, baseRadius * sin(angle)), color);
    }

    for (int i = 0; i < segments; i++) {
        indices.push_back(0);
        indices.push_back(2 + 2 * i);
        indices.push_back(2 + 2 * ((i + 1) % segments));
    }

    for (int i = 0; i < segments; i++) {
        indices.push_back(1);
        indices.push_back(3 + 2 * ((i + 1) % segments));
        indices.push_back(3 + 2 * i);
    }

    for (int i = 0; i < segments; i++) {
        indices.push_back(2 + 2 * i);
        indices.push_back(3 + 2 * i);
        indices.push_back(2 + 2 * ((i + 1) % segments));

        indices.push_back(2 + 2 * ((i + 1) % segments));
        indices.push_back(3 + 2 * i);
        indices.push_back(3 + 2 * ((i + 1) % segments));
    }

    Mesh* cylinder = new Mesh(name);
    cylinder->InitFromData(vertices, indices);
    return cylinder;
}
