#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "core/engine.h"
#include "core/gpu/mesh.h"
#include "utils/gl_utils.h"
#include "utils/glm_utils.h"
#include "lab_m1/lab4/camera.h"
#include "components/simple_scene.h"


namespace m1 {
    class Lab4 : public gfxc::SimpleScene {
     public:
        struct ViewportArea {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x, y, width, height;
        };

        Lab4();
        ~Lab4();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void GenerateGridMesh(int size, std::vector<VertexFormat>& vertices, std::vector<unsigned int>& indices);
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        void RenderMeshMiniMap(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        void RenderTerrain(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        void RenderTerrainMiniMap(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        int CheckCollisionTrunk(glm::vec3 pos);
        void DrawDrone();
        void DrawPacket();
        void DrawDroneMiniMap();
        void DrawTrees();
        void DrawTreesMiniMap();
        void DrawPacketMiniMap();
        void RenderScene();
        void RenderMiniMap();
        void GeneratePacket();
        void GenerateDestination();
        void DrawDestination();
        void DrawDestinationMiniMap();
        void DrawArrow();
        protected:
        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;
        float scaleX, scaleY, scaleZ;
        float angularStepOX, angularStepOY, angularStepOZ;
        GLenum polygonMode;
        ViewportArea miniViewportArea;
    
        //* constants
        const float SPEED = 8.f;
        const float SENSITIVITY = 0.02f;
        const float DIST_FROM_CAMERA = 1.5f;
        const float DIST_FROM_CAMERA_MINI_MAP = 10.f;

        //* camera
        remade::Camera* camera;
        remade::Camera* camera_mini_map;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        //* tress obstacles
        std::vector<glm::vec3> pos = { glm::vec3( 2, 0,  2), glm::vec3(-13, 0, -28), glm::vec3(11, 0,  -2), glm::vec3(-13, 0, 28), glm::vec3(-11, 0,  -2),
                                       glm::vec3(13, 0, 13), glm::vec3(-13, 0,  -7), glm::vec3(23, 0,  -5), glm::vec3(-13, 0,  7), glm::vec3(-23, 0,  -5),
                                       glm::vec3(17, 0, 17), glm::vec3(-17, 0,  -3), glm::vec3(19, 0,   6), glm::vec3(-17, 0,  3), glm::vec3(-19, 0,   6),
                                       glm::vec3(29, 0, 29), glm::vec3(-29, 0, -13), glm::vec3(38, 0, -26), glm::vec3(-29, 0, 13), glm::vec3(-38, 0, -26),
                                       glm::vec3(33, 0, 33), glm::vec3(-33, 0, -17), glm::vec3(45, 0,   6), glm::vec3(-33, 0, 17), glm::vec3(-45, 0,   6) };
        
        std::vector<glm::vec3> obstacles;

        //* colors
        glm::vec3 drone_color = glm::vec3(0.549f, 0.620f, 0.608f);
        glm::vec3 grass_color = glm::vec3(0.368f, 0.615f, 0.203f);
        glm::vec3 leave_color = glm::vec3(0.141f, 0.831f, 0.055f);
        glm::vec3 trunk_color = glm::vec3(0.620f, 0.349f, 0.063f);
        glm::vec3 arrow_color = glm::vec3(0.400f, 0.239f, 0.890f);
        glm::vec3 packe_color = glm::vec3(0.780f, 0.357f, 0.922f);
        glm::vec3 desti_color = glm::vec3(0.369f, 0.349f, 0.341f);

        //* drone's stats
        float angle = 0.f, drone_angle = 0.f;
        float x = 0.f, y = 0.3f, z = 0.f;

        //* terrain variables
        int size = 200;
        const float SPACE_DIST = 1.f;

        //* packet
        glm::vec3 packet_pos;
        bool isGenerated = false;
        bool isPicked = false;

        //* destination
        glm::vec3 dest_pos;

        //* arrow
        glm::vec3 arrow_pos = glm::vec3(0);
        float arrow_angle = 0.f;
    };
}   // namespace m1

