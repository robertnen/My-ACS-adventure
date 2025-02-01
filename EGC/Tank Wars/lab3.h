#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Lab3 : public gfxc::SimpleScene
    {
     public:
        Lab3();
        ~Lab3();

        void Init() override;

        class Bullet {
        public:
            Bullet() {}
            glm::vec2 getPos() { return glm::vec2(x, y); }
            float getTime() { return time; }
            float getAngle() { return angle; }
            std::vector<glm::vec2> getTrajPts() { return trajPts; }

            void setPos(float x, float y) { this->x = x; this->y = y; }
            void setTime(float time) { this->time = time; }
            void setAngle(float angle) { this->angle = angle; }
            void setTrajPts(std::vector<glm::vec2>& trajPts) { this->trajPts = trajPts; }
        private:
            float x = 0, y = 0, time = 0, angle = 0;
            std::vector<glm::vec2> trajPts = std::vector<glm::vec2>(15, glm::vec2(0));
        };

        class Tank {
        public:
            Tank() {}
            glm::vec2 getPos() { return glm::vec2(x, y); }
            float getAngleTank() { return angleTank; }
            float getAngleBarrel() { return angleBarrel; }
            int getId() { return id; }
            glm::vec3 getPtPos() { return pos; }
            std::vector<Bullet>& getBullets() { return bullets; }
            int getActiveBullet() { return activeBullet; }
            std::vector<glm::vec2> getTrajPts() { return trajPts; }
            bool isAlive() { return hp > 0; }
            int getHp() { return hp; }

            void setPos(float x, float y) { this->x = x; this->y = y; }
            void setAngleTank(float angleTank) { 
                if (angleTank > 7 * glm::pi<float>() / 18) angleTank = 7 * glm::pi<float>() / 18;
                if (angleTank < - glm::pi<float>() / 6) angleTank = -glm::pi<float>() / 6;
                this->angleTank = angleTank; }
            void setAngleBarrel(float angleBarrel) { this->angleBarrel = angleBarrel; }
            void setId(int id) { this->id = id; }
            void setPtPos(glm::vec3 pos) { this->pos = pos; }
            void setBullets(std::vector<Bullet>& bullets) { this->bullets = bullets; }
            void setActiveBullet(int activeBullet) { this->activeBullet = activeBullet; }
            void setTrajPts(std::vector<glm::vec2>& trajPts) { this->trajPts = trajPts; }
            void giveDamage() { if (hp > 0) hp -= 10; }
        private:
            float x = 0, y = 0;
            int id = 0;
            float angleTank = 0, angleBarrel = 0;
            glm::vec3 pos;

            std::vector<Bullet> bullets;
            int activeBullet = 0;

            std::vector<glm::vec2> trajPts = std::vector<glm::vec2>(15, glm::vec2(0));

            int hp = 100;
        };

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

        void computeHeights();
        float generateValue(float x);
        void generateTerrain();
        void generateTanks(Tank& tank);
        void getY(glm::vec2& A, glm::vec2& B);
        void getTankY(Tank& tank);
        void GetTrajectory(Tank& tank);
        void DrawTrajectory(std::vector<glm::vec2> trajPts, float angleTank, float angleBarrel);
        void DrawBullets(Tank& tank);
        
        void Ending1();
        void Ending2();
        void Ending3();

        void DrawStars();
        void DrawClouds();
        void getMoonY();
        void DrawMoon();

     protected:
        glm::mat3 modelMatrix;
        float squareSide = 50, no_parts = 5000.f;

        glm::vec3 bkgColor = glm::vec3(37./255, 150./255, 190./255);
        glm::vec3 terColor = glm::vec3(8. / 255, 140. / 255, 4. / 255);
        glm::vec3 hpColor = glm::vec3(255. / 255, 100. / 255, 100. / 255);
        glm::vec3 hpBarColor = glm::vec3(255. / 255, 228. / 255, 228. / 255);
        glm::vec3 cloudsColor = glm::vec3(107. / 255, 107. / 255, 107. / 255);

        glm::vec3 tankColor1 = glm::vec3(147. / 255, 13. / 255, 12. / 255);
        glm::vec3 tankColor2 = glm::vec3(230. / 255, 162. / 255, 58. / 255);

        glm::vec3 projectileColor = glm::vec3(171. / 255, 100. / 255, 13. / 255);

        //* f(x) = 0.2f * sin(0.008f * x) + 0.6f * sin(0.02f * x + 1.5f) +
        //*                             0.1f * sin(0.006f * x + 1.0f) + 2.5
        float no_terrain;  // distance between two points when generating

        const int SIZE = 4; 
        const std::vector<float> AMPLITUDES = { 0.2f, 0.6f, 0.1f, 2.5f };
        const std::vector<float> FREQS = { 0.008f, 0.02f, 0.006f, 0.f };
        const std::vector<float> PHASES = { 0.f, 1.5f, 1.0f, glm::pi<float>() / 2 };
        const float Base = 80, base = 40, height = 20;
        float time = 0;
        Tank p1, p2;

        glm::vec2 A, B;
        glm::ivec2 resolution;

        std::vector<std::pair<float, float>> heights;
        const float GRAVITY = -9.8f, INIT_VELOCITY = 70.f;
        const int MAX_PTS = 30;
        const int MAX_BULLET = 2;

        const float DIST = 50.f;
        const int NEIGH = 100;
        const float MAX_DEPTH = .1f;

        bool isEnding1 = false;
        bool isEnding2 = false;
        bool isEnding3 = false;

        bool isLocked1 = false;
        bool isLocked2 = false;
        bool isLocked3 = false;

        //* ending
        float tick = 0;
        std::vector<glm::vec2> particles;
        std::vector<float> angles;

        //* creeper firework effect
        glm::vec2 startPos;
        std::vector<std::pair<int, int>> dirParticles = { {1, 0}, {4, 0},
                                                          {1, 1}, {2, 1}, {3, 1}, {4, 1},
                                                          {1, 2}, {2, 2}, {3, 2}, {4, 2},
                                                          {2, 3}, {3, 3},
                                                          {0, 4}, {1, 4}, {4, 4}, {5, 4},
                                                          {0, 5}, {1, 5}, {4, 5}, {5, 5} };

        //* stars
        std::vector<glm::vec2> startStars = { glm::vec2(870, 750), glm::vec2(950, 820), glm::vec2(1280, 700), glm::vec2(800, 790),
                                              glm::vec2(1100, 1000), glm::vec2(1002, 920), glm::vec2(720, 730), glm::vec2(1210, 770),
        };
        float starTime = .0f;

        glm::vec2 nextPosition = startStars[rand() % 8];

        //* moon
        glm::vec2 moon = glm::vec2(300, 700);

        //* clouds
        std::vector<glm::vec2> clouds = { glm::vec2(150, 580), glm::vec2(400, 580), glm::vec2(750, 580), glm::vec2(1100, 580) };
    };
}   // namespace m1
