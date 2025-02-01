#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(const std::string &name, glm::vec3 leftBottomCorner,
    float length, glm::vec3 color, bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner,
    float width, float height, glm::vec3 color, bool fill) {
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) rectangle->SetDrawMode(GL_LINE_LOOP);
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateTrapezoid(const std::string& name, glm::vec3 leftBottomCorner,
    float length, float height, float B, float b,
    glm::vec3 color, bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(B, 0, 0), color),
        VertexFormat(corner + glm::vec3((B - b) / 2, height, 0), color),
        VertexFormat(corner + glm::vec3((B + b) / 2, height, 0), color)
    };

    Mesh* trapezoid = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        trapezoid->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(1);
        indices.push_back(2);
    }

    trapezoid->InitFromData(vertices, indices);
    return trapezoid;
}

Mesh* object2D::CreateSemicircle(const std::string& name, glm::vec3 leftBottomCorner,
    float radius, glm::vec3 color, bool fill) {
    int segments = 30;
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 position;
    float theta;

    if (fill) {
        vertices.push_back(VertexFormat(leftBottomCorner, color));
    }

    for (int i = 0; i <= segments; i++) {
        theta = glm::pi<float>() * i / segments;
        position = leftBottomCorner + glm::vec3(radius * cos(theta), radius * sin(theta), 0);
        vertices.push_back(VertexFormat(position, color));

        if (!fill && i > 0) {
            indices.push_back(i - 1);
            indices.push_back(i);
        }
    }

    if (fill) {
        for (int i = 1; i <= segments; ++i) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }

    Mesh* semicircle = new Mesh(name);
    semicircle->InitFromData(vertices, indices);

    if (!fill) {
        semicircle->SetDrawMode(GL_LINE_LOOP);
    }

    return semicircle;
}

Mesh* object2D::CreateCircle(const std::string& name, glm::vec3 leftBottomCorner,
    float radius, glm::vec3 color, bool fill) {
    int segments = 30;
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 position;
    float theta;

    if (fill) {
        vertices.push_back(VertexFormat(leftBottomCorner, color));
    }

    for (int i = 0; i <= segments; i++) {
        theta = 2. * glm::pi<float>() * i / segments;
        position = leftBottomCorner + glm::vec3(radius * cos(theta), radius * sin(theta), 0);
        vertices.push_back(VertexFormat(position, color));

        if (!fill && i > 0) {
            indices.push_back(i - 1);
            indices.push_back(i);
        }
    }

    if (fill) {
        for (int i = 1; i <= segments; ++i) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }

    Mesh* semicircle = new Mesh(name);
    semicircle->InitFromData(vertices, indices);

    if (!fill) {
        semicircle->SetDrawMode(GL_LINE_LOOP);
    }

    return semicircle;
}

Mesh* object2D::BgSquare(const std::string& name, glm::vec3 leftBottomCorner,
    float length, bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    glm::vec3 black = glm::vec3(0, 0, 0);
    glm::vec3 purple = glm::vec3(142. / 255, 0, 215. / 255);

    std::vector<VertexFormat> vertices = {
        VertexFormat(corner, purple),
        VertexFormat(corner + glm::vec3(length, 0, 0), purple),
        VertexFormat(corner + glm::vec3(length, length, 0), black),
        VertexFormat(corner + glm::vec3(0, length, 0), black)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (fill) {
        indices.push_back(0);
        indices.push_back(2);
    }
    else {
        square->SetDrawMode(GL_LINE_LOOP);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::Point(const std::string& name, glm::vec3 leftBottomCorner) {
    glm::vec3 corner = leftBottomCorner;

    glm::vec3 white = glm::vec3(1, 1, 1);

    // Define vertices with gradient color
    std::vector<VertexFormat> vertices = {
        VertexFormat(corner, white),
        VertexFormat(corner + glm::vec3(1, 0, 0), white),
        VertexFormat(corner + glm::vec3(1, 1, 0), white)
    };

    Mesh* point = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    point->SetDrawMode(GL_LINE_LOOP);

    point->InitFromData(vertices, indices);
    return point;
}