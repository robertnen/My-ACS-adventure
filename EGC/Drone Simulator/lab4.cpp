#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#include "lab_m1/lab4/transform3D.h"
#include "lab_m1/lab4/object3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab4::Lab4()
{
}


Lab4::~Lab4()
{
}


void Lab4::Init() {
    polygonMode = GL_FILL;

    Shader* shader_terrain = new Shader("terrain");
    shader_terrain->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab4", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
    shader_terrain->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab4", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader_terrain->CreateAndLink();

    shaders[shader_terrain->GetName()] = shader_terrain;

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(resolution.x - 250, resolution.y - 200, resolution.x / 5.f, resolution.y / 5.f);

    Mesh* drone_base = object3D::CreateBox("drone_base", glm::vec3(0, 0, 0), drone_color);
    Mesh* drone_propeller = object3D::CreateBox("drone_propeller", glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

    AddMeshToList(drone_base);
    AddMeshToList(drone_propeller);

    Mesh* cone1 = object3D::CreateCone("cone1", glm::vec3(1, 4, 1), 2.5f, 1.25f, leave_color, 36);
    Mesh* cone2 = object3D::CreateCone("cone2", glm::vec3(1, 3, 1), 2.5f, 1.25f, leave_color, 36);
    Mesh* trunk = object3D::CreateCylinder("trunk", glm::vec3(1, 0, 1), 4.f, .3f, trunk_color, 36);

    AddMeshToList(cone1);
    AddMeshToList(cone2);
    AddMeshToList(trunk);

    Mesh* packet = object3D::CreateBox("packet", glm::vec3(0, 0, 0), packe_color);
    Mesh* destination = object3D::CreateBox("destination", glm::vec3(0, 0, 0), desti_color);
    Mesh* arrow = object3D::CreateCone("arrow", glm::vec3(0), 0.1, 0.03, arrow_color, 36);

    AddMeshToList(packet);
    AddMeshToList(destination);
    AddMeshToList(arrow);

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    GenerateGridMesh(size, vertices, indices);

    camera = new remade::Camera(glm::vec3(0, 0, 0));
    camera->Set(glm::vec3(0, 1, DIST_FROM_CAMERA), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    camera_mini_map = new remade::Camera(glm::vec3(0, 0, 0));
    camera_mini_map->Set(glm::vec3(0, 3, DIST_FROM_CAMERA_MINI_MAP), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    projectionMatrix = glm::perspective(RADIANS(45), window->props.aspectRatio, 0.01f, 200.0f);

    int px, pz;

    for (int i = 0; i < size; i++) {
        px = rand() % size;
        pz = rand() % size;

        if (px > size / 2) { px -= size / 2; px *= -1; }
        if (pz > size / 2) { pz -= size / 2; pz *= -1; }

        bool flag = true;

        for (glm::vec3 o : obstacles)
            if (glm::distance(glm::vec3(px, 0, pz), o) < 3) { flag = false; break; }
    
        if (flag) obstacles.push_back(glm::vec3(px, 0, pz));
    }
}

void Lab4::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.486f, 0.674f, 0.956f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Lab4::GenerateGridMesh(int size, std::vector<VertexFormat>& vertices, std::vector<unsigned int>& indices) {
    float x_pos = -size * SPACE_DIST / 2.f, z_pos = -size * SPACE_DIST / 2.f;

    for (int i = 0; i <= size; i++)
        for (int j = 0; j <= size; j++)
            vertices.push_back(VertexFormat(glm::vec3(x_pos + j * SPACE_DIST, .0f, z_pos + i * SPACE_DIST), grass_color));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            unsigned int topLeft = i * (size + 1) + j;
            unsigned int topRight = topLeft + 1;
            unsigned int bottomLeft = (i + 1) * (size + 1) + j;
            unsigned int bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    std::string name = "terrain";

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
}

void Lab4::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) {
    if (!mesh || !shader || !shader->program) return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    mesh->Render();
}

void Lab4::RenderMeshMiniMap(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) {
    if (!mesh || !shader || !shader->program) return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera_mini_map->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    mesh->Render();
}

void Lab4::DrawDrone() {
    //* base used for half of 'X' (looks like '/')
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(-glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .1f, -.05f);
    modelMatrix *= transform3D::Scale(.5f, .1f, .1f);
    RenderMesh(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    //* next two are cubes used for the propeller
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(-glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .2f, -.05f);
    modelMatrix *= transform3D::Scale(.1f, .1f, .1f);
    RenderMesh(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(-glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(0.15f, .2f, -.05f);
    modelMatrix *= transform3D::Scale(.1f, .1f, .1f);
    RenderMesh(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    //* propellers
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(-glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .3f, -.02f);
    modelMatrix *= transform3D::Translate(0.05f, .0f, .02f);
    modelMatrix *= transform3D::RotateOY(-angle);
    modelMatrix *= transform3D::Translate(-0.05f, .0f, -.02f);
    modelMatrix *= transform3D::Scale(.1f, .05f, .04f);
    RenderMesh(meshes["drone_propeller"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(-glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(0.15f, .3f, -.02f);
    modelMatrix *= transform3D::Translate(0.05f, .0f, .02f);
    modelMatrix *= transform3D::RotateOY(-angle);
    modelMatrix *= transform3D::Translate(-0.05f, .0f, -.02f);
    modelMatrix *= transform3D::Scale(.1f, .05f, .04f);
    RenderMesh(meshes["drone_propeller"], shaders["VertexColor"], modelMatrix);

    //* mirror part
    //* base used for half of 'X' (looks like '\')
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .1f, -.05f);
    modelMatrix *= transform3D::Scale(.5f, .1f, .1f);
    RenderMesh(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    //* next two are cubes used for the propeller
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .2f, -.05f);
    modelMatrix *= transform3D::Scale(.1f, .1f, .1f);
    RenderMesh(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(0.15f, .2f, -.05f);
    modelMatrix *= transform3D::Scale(.1f, .1f, .1f);
    RenderMesh(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    //* propellers
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .3f, -.02f);
    modelMatrix *= transform3D::Translate(0.05f, .0f, .02f);
    modelMatrix *= transform3D::RotateOY(angle);
    modelMatrix *= transform3D::Translate(-0.05f, .0f, -.02f);
    modelMatrix *= transform3D::Scale(.1f, .05f, .04f);
    RenderMesh(meshes["drone_propeller"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(0.15f, .3f, -.02f);
    modelMatrix *= transform3D::Translate(0.05f, .0f, .02f);
    modelMatrix *= transform3D::RotateOY(angle);
    modelMatrix *= transform3D::Translate(-0.05f, .0f, -.02f);
    modelMatrix *= transform3D::Scale(.1f, .05f, .04f);
    RenderMesh(meshes["drone_propeller"], shaders["VertexColor"], modelMatrix);

    angle += .08f;
    if (angle > glm::pi<float>() * 2) angle = 0.f;
}

void Lab4::DrawTrees() {
    for (glm::vec3 p : obstacles) {
        float x = p.x, y = p.y, z = p.z;

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(x, y - .2f, z);
        RenderMesh(meshes["trunk"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(x, y - 1, z);
        RenderMesh(meshes["cone1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(x, y - 1.4f, z);
        RenderMesh(meshes["cone2"], shaders["VertexColor"], modelMatrix);
    }
}

void Lab4::RenderTerrain(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) {
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Lab4::DrawPacket() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(packet_pos.x, packet_pos.y, packet_pos.z);
    modelMatrix *= transform3D::Scale(0.2f, 0.4f, 0.2f);
    RenderMesh(meshes["packet"], shaders["VertexColor"], modelMatrix);
}

void Lab4::DrawPacketMiniMap() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(packet_pos.x, packet_pos.y, packet_pos.z);
    modelMatrix *= transform3D::Scale(0.2f, 0.4f, 0.2f);
    RenderMeshMiniMap(meshes["packet"], shaders["VertexColor"], modelMatrix);
}

void Lab4::DrawArrow() {
    float ax = arrow_pos.x, ay = arrow_pos.y + 0.5f, az = arrow_pos.z;

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(ax, ay, az);
    modelMatrix *= transform3D::RotateOY(arrow_angle + drone_angle + glm::pi<float>() / 2);
    modelMatrix *= transform3D::RotateOZ(-glm::pi<float>() / 2);
    RenderMesh(meshes["arrow"], shaders["VertexColor"], modelMatrix);
}

void Lab4::RenderScene() {
    DrawDrone();
    RenderTerrain(meshes["terrain"], shaders["terrain"], glm::mat4(1));
    DrawTrees();

    if (!isGenerated) GeneratePacket();
    DrawPacket();
    if (isPicked) DrawDestination();
    DrawArrow();
}

int Lab4::CheckCollisionTrunk(glm::vec3 pos) {
    int i = 0;
    for (glm::vec3 o : obstacles) {
        int px = o.x + 1.25f, py = o.y, pz = o.z - .5f;

        if ((px - 0.6f <= pos.x && pos.x <= px + 0.8f) &&
            (py <= pos.y && pos.y <= py + 4.f) &&
            (pz - 0.6f <= pos.z && pos.z <= pz + 0.8f)) {
            
            return i;
        }

        i++;
    }

    return -1; // null
}

void Lab4::DrawDroneMiniMap() {
    //* base used for half of 'X' (looks like '/')
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(-glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .1f, -.05f);
    modelMatrix *= transform3D::Scale(.5f, .1f, .1f);
    RenderMeshMiniMap(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    //* next two are cubes used for the propeller
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(-glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .2f, -.05f);
    modelMatrix *= transform3D::Scale(.1f, .1f, .1f);
    RenderMeshMiniMap(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(-glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(0.15f, .2f, -.05f);
    modelMatrix *= transform3D::Scale(.1f, .1f, .1f);
    RenderMeshMiniMap(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    //* propellers
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(-glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .3f, -.02f);
    modelMatrix *= transform3D::Translate(0.05f, .0f, .02f);
    modelMatrix *= transform3D::RotateOY(-angle);
    modelMatrix *= transform3D::Translate(-0.05f, .0f, -.02f);
    modelMatrix *= transform3D::Scale(.1f, .05f, .04f);
    RenderMeshMiniMap(meshes["drone_propeller"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(-glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(0.15f, .3f, -.02f);
    modelMatrix *= transform3D::Translate(0.05f, .0f, .02f);
    modelMatrix *= transform3D::RotateOY(-angle);
    modelMatrix *= transform3D::Translate(-0.05f, .0f, -.02f);
    modelMatrix *= transform3D::Scale(.1f, .05f, .04f);
    RenderMeshMiniMap(meshes["drone_propeller"], shaders["VertexColor"], modelMatrix);

    //* mirror part
    //* base used for half of 'X' (looks like '\')
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .1f, -.05f);
    modelMatrix *= transform3D::Scale(.5f, .1f, .1f);
    RenderMeshMiniMap(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    //* next two are cubes used for the propeller
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .2f, -.05f);
    modelMatrix *= transform3D::Scale(.1f, .1f, .1f);
    RenderMeshMiniMap(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(0.15f, .2f, -.05f);
    modelMatrix *= transform3D::Scale(.1f, .1f, .1f);
    RenderMeshMiniMap(meshes["drone_base"], shaders["VertexColor"], modelMatrix);

    //* propellers
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(-0.25f, .3f, -.02f);
    modelMatrix *= transform3D::Translate(0.05f, .0f, .02f);
    modelMatrix *= transform3D::RotateOY(angle);
    modelMatrix *= transform3D::Translate(-0.05f, .0f, -.02f);
    modelMatrix *= transform3D::Scale(.1f, .05f, .04f);
    RenderMeshMiniMap(meshes["drone_propeller"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(drone_angle);
    modelMatrix *= transform3D::RotateOY(glm::pi<float>() / 4);
    modelMatrix *= transform3D::Translate(0.15f, .3f, -.02f);
    modelMatrix *= transform3D::Translate(0.05f, .0f, .02f);
    modelMatrix *= transform3D::RotateOY(angle);
    modelMatrix *= transform3D::Translate(-0.05f, .0f, -.02f);
    modelMatrix *= transform3D::Scale(.1f, .05f, .04f);
    RenderMeshMiniMap(meshes["drone_propeller"], shaders["VertexColor"], modelMatrix);

    angle += .08f;
    if (angle > glm::pi<float>() * 2) angle = 0.f;
}

void Lab4::DrawTreesMiniMap() {
    for (glm::vec3 p : obstacles) {
        float x = p.x, y = p.y, z = p.z;

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(x, y - .2f, z);
        RenderMeshMiniMap(meshes["trunk"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(x, y - 1, z);
        RenderMeshMiniMap(meshes["cone1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(x, y - 1.4f, z);
        RenderMeshMiniMap(meshes["cone2"], shaders["VertexColor"], modelMatrix);
    }
}

void Lab4::RenderTerrainMiniMap(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) {
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");
    glm::mat4 viewMatrix = camera_mini_map->GetViewMatrix();
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
    //glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Lab4::RenderMiniMap() {
    DrawDroneMiniMap();
    DrawTreesMiniMap();
    RenderTerrainMiniMap(meshes["terrain"], shaders["VertexColor"], glm::mat4(1));
    DrawPacketMiniMap();
    if (isPicked) DrawDestinationMiniMap();
}

void Lab4::GeneratePacket() {
    bool isDone = false;
    packet_pos.y = 2.2f;

    while (!isDone) {
        isDone = true;

        packet_pos.x = rand() % size;
        packet_pos.z = rand() % size;

        if (packet_pos.x >= size / 2) { packet_pos.x -= size / 2; packet_pos.x *= -1; }
        if (packet_pos.z >= size / 2) { packet_pos.z -= size / 2; packet_pos.z *= -1; }

        for (glm::vec3 o : obstacles)
            if (glm::distance(packet_pos, o) < 4) { isDone = false; break; }
    }

    isGenerated = true;
}

void Lab4::GenerateDestination() {
    bool isDone = false;
    dest_pos.y = 2.2f;

    while (!isDone) {
        isDone = true;

        dest_pos.x = rand() % size;
        dest_pos.z = rand() % size;

        if (dest_pos.x >= size / 2) { dest_pos.x -= size / 2; dest_pos.x *= -1; }
        if (dest_pos.z >= size / 2) { dest_pos.z -= size / 2; dest_pos.z *= -1; }

        for (glm::vec3 o : obstacles)
            if (glm::distance(dest_pos, o) < 4) { isDone = false; break; }
    }
}

void Lab4::DrawDestination() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(dest_pos.x, dest_pos.y, dest_pos.z);
    modelMatrix *= transform3D::Scale(1.f, 0.3f, 1.f);
    RenderMesh(meshes["destination"], shaders["VertexColor"], modelMatrix);
}

void Lab4::DrawDestinationMiniMap() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(dest_pos.x, dest_pos.y, dest_pos.z);
    modelMatrix *= transform3D::Scale(1.f, 0.3f, 1.f);
    RenderMeshMiniMap(meshes["destination"], shaders["VertexColor"], modelMatrix);
}

void Lab4::Update(float deltaTimeSeconds) {
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(resolution.x - 450, resolution.y - 200, resolution.x / 5.f, resolution.y / 5.f);
    glViewport(0, 0, resolution.x, resolution.y);

    glClear(GL_DEPTH_BUFFER_BIT);
    RenderScene();
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);

    glViewport(miniViewportArea.x - 100, miniViewportArea.y - size, 2.5 * size, size);
    RenderMiniMap();
}

void Lab4::FrameEnd() {}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab4::OnInputUpdate(float deltaTime, int mods) {
    glm::vec3 pos;
    camera->TranslateForward(DIST_FROM_CAMERA);
    pos.x = camera->position.x + .5f; pos.y = camera->position.y; pos.z = camera->position.z - 1;
    camera->TranslateForward(-DIST_FROM_CAMERA);

    if (window->KeyHold(GLFW_KEY_W)) {  // front
        pos.z -= deltaTime * SPEED * cos(drone_angle);
        pos.x -= deltaTime * SPEED * sin(drone_angle);

        if (CheckCollisionTrunk(pos) > -1) return;

        z -= deltaTime * SPEED * cos(drone_angle);
        x -= deltaTime * SPEED * sin(drone_angle);
        camera->TranslateForward(deltaTime * SPEED);
        camera_mini_map->TranslateForward(deltaTime * SPEED);
    }

    if (window->KeyHold(GLFW_KEY_A)) {  // left
        z += deltaTime * SPEED * sin(drone_angle);
        x -= deltaTime * SPEED * cos(drone_angle);
        camera->TranslateRight(-deltaTime * SPEED);
        camera_mini_map->TranslateRight(-deltaTime * SPEED);
    }

    if (window->KeyHold(GLFW_KEY_S)) {  // back
        z += deltaTime * SPEED * cos(drone_angle);
        x += deltaTime * SPEED * sin(drone_angle);
        camera->TranslateForward(-deltaTime * SPEED);
        camera_mini_map->TranslateForward(-deltaTime * SPEED);
    }

    if (window->KeyHold(GLFW_KEY_D)) {  // right
        z -= deltaTime * SPEED * sin(drone_angle);
        x += deltaTime * SPEED * cos(drone_angle);
        camera->TranslateRight(deltaTime * SPEED);
        camera_mini_map->TranslateRight(deltaTime * SPEED);
    }

    if (window->KeyHold(GLFW_KEY_Q)) {  // lower
        y -= deltaTime * SPEED;
        if (y < 0.8f) y = 0.8f;
        else {
            camera->TranslateUpward(-deltaTime * SPEED);
        }
    }

    if (window->KeyHold(GLFW_KEY_E)) {  // higher
        y += deltaTime * SPEED;
        if (y > 4.f) y = 4.f;
        else {
            camera->TranslateUpward(deltaTime * SPEED);
        }
    }

    if (window->KeyHold(GLFW_KEY_R)) { // rotate right
        drone_angle -= 0.01;

        camera->TranslateForward(DIST_FROM_CAMERA);
        camera->RotateFirstPerson_OY(-0.573);
        camera->TranslateForward(-DIST_FROM_CAMERA);

        camera_mini_map->TranslateForward(DIST_FROM_CAMERA_MINI_MAP);
        camera_mini_map->RotateFirstPerson_OY(-0.573);
        camera_mini_map->TranslateForward(-DIST_FROM_CAMERA_MINI_MAP);
    }

    if (window->KeyHold(GLFW_KEY_F)) { // rotate left
        drone_angle += 0.01;

        camera->TranslateForward(DIST_FROM_CAMERA);
        camera->RotateFirstPerson_OY(0.573);
        camera->TranslateForward(-DIST_FROM_CAMERA);

        camera_mini_map->TranslateForward(DIST_FROM_CAMERA_MINI_MAP);
        camera_mini_map->RotateFirstPerson_OY(0.573);
        camera_mini_map->TranslateForward(-DIST_FROM_CAMERA_MINI_MAP);
    }

    camera_mini_map->right = camera->right;
    camera_mini_map->forward = camera->forward;

    if (isPicked) packet_pos = glm::vec3(x - 0.15f, y - 0.4f, z - 0.15f);
    else if (glm::distance(glm::vec2(packet_pos.x, packet_pos.z), glm::vec2(x, z)) < 1.f) {
        isPicked = true;
        GenerateDestination();
    }

    if (isPicked && glm::distance(glm::vec2(dest_pos.x, dest_pos.z), glm::vec2(x, z)) < 1.f) {
        isPicked = false;
        GeneratePacket();
    }

    camera->TranslateForward(3.f);
    arrow_pos = camera->position;
    camera->TranslateForward(-3.f);

    glm::vec3 direction = (isPicked ? dest_pos : packet_pos) - camera->position;
    direction = glm::normalize(direction);

    float x_c, z_c;

    x_c = glm::dot(direction, camera->right);
    z_c = glm::dot(direction, camera->forward);

    arrow_angle = glm::atan(-x_c, z_c);
}


void Lab4::OnKeyPress(int key, int mods) {
    // Add key press event
    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }

}


void Lab4::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {

}


void Lab4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab4::OnWindowResize(int width, int height)
{
}
