#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "glm/gtx/string_cast.hpp"

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
    resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, -1, 0);
    float squareSide = 50;

    computeHeights();

    p1.setPos(heights[1000].first, 0);
    p1.setAngleBarrel(glm::pi<float>() / 4);
    p1.setId(1);
    
    p2.setPos(heights[4000].first, 0);
    p2.setAngleBarrel(3 * glm::pi<float>() / 4);
    p2.setId(2);


    //* terrain
    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, terColor, true);
    AddMeshToList(square1);


    //* for tanks
    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, hpColor, true);
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, hpBarColor, true);
    AddMeshToList(square3);

    Mesh* trapezoid1 = object2D::CreateTrapezoid("trapezoid1", corner, squareSide,
                                height, Base, base, tankColor1, true);
    AddMeshToList(trapezoid1);

    Mesh* trapezoid2 = object2D::CreateTrapezoid("trapezoid2", corner, squareSide,
        height, Base, base, tankColor2, true);
    AddMeshToList(trapezoid2);

    Mesh* trapezoid3 = object2D::CreateTrapezoid("trapezoid3", corner, squareSide,
        height, Base, base, glm::vec3(0.5, 0.7, 0.5), true);
    AddMeshToList(trapezoid3);

    Mesh* semicircle1 = object2D::CreateSemicircle("semicircle1", corner, 20, tankColor1, true);
    AddMeshToList(semicircle1);

    Mesh* rect1 = object2D::CreateRectangle("rectangle1", corner, 25, 5, glm::vec3(96. / 255, 82. / 255, 107. / 255), true);
    AddMeshToList(rect1);

    Mesh* semicircle2 = object2D::CreateSemicircle("semicircle2", corner, 20, tankColor2, true);
    AddMeshToList(semicircle2);

    Mesh* rect2 = object2D::CreateRectangle("rectangle2", corner, 25, 5, glm::vec3(96. / 255, 82. / 255, 107. / 255), true);
    AddMeshToList(rect2);


    //* for backgroundd
    Mesh* sqBlack = object2D::CreateSquare("sqBlack", corner, squareSide, glm::vec3(0), true);
    AddMeshToList(sqBlack);

    Mesh* background = object2D::BgSquare("bgSquare", corner, squareSide, true);
    AddMeshToList(background);


    //* point
    Mesh* point = object2D::Point("point", corner);
    AddMeshToList(point);


    //* projectile
    Mesh* circle = object2D::CreateCircle("circle", corner, 3, projectileColor, true);
    AddMeshToList(circle);


    //* ending particles
    Mesh* circle1 = object2D::CreateCircle("circle1", corner, 3, tankColor1, true);
    AddMeshToList(circle1);

    Mesh* circle2 = object2D::CreateCircle("circle2", corner, 3, tankColor2, true);
    AddMeshToList(circle2);


    //* star
    Mesh* square4 = object2D::CreateSquare("square4", corner, 1.f, glm::vec3(1, 1, 1), true);
    AddMeshToList(square4);


    //* moon
    Mesh* circle3 = object2D::CreateCircle("circle3", corner, 3, glm::vec3(.5f, .5f, .5f), true);
    AddMeshToList(circle3);


    //* clouds
    Mesh* circle4 = object2D::CreateCircle("circle4", corner, 25, cloudsColor, true);
    AddMeshToList(circle4);
}


void Lab3::computeHeights() {
    no_terrain = resolution.x / no_parts;

    for (float x = 0; x < resolution.x; x += no_terrain)
        heights.push_back({x, generateValue(x)});
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(bkgColor.x, bkgColor.y, bkgColor.z, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


float Lab3::generateValue(float x) {
    float y = 0;

    for (int i = 0; i < SIZE; i++)
        y += AMPLITUDES[i] * sin(FREQS[i] * x + PHASES[i]);

    return y;
}


void Lab3::generateTerrain() {
    A.x = heights[0].first;
    A.y = heights[0].second;

    for (int i = 1; i < heights.size(); i++) {
        if (heights[i].second < 0.2) heights[i].second = 0.2;
        if (heights[i].second > 4) heights[i].second = 4;
        
        B.x = heights[i].first;
        B.y = heights[i].second;

        modelMatrix = transform2D::Translate(A.x, A.y);
        modelMatrix *= transform2D::Shear(A, B);
        modelMatrix *= transform2D::Scale(B.x - A.x, glm::min(A.y, B.y));

        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        A = B;
    }

        for (int i = 1; i < heights.size() - 2; i++) {
            for (int j = 0; j < 100; j++) {
                heights[i].second = (heights[i - 1].second + heights[i].second + heights[i + 1].second) / 3.f;
            }
        }

        heights[0].second = heights[1].second;
        heights[heights.size() - 2].second = heights[heights.size() - 1].second;
}


void Lab3::getY(glm::vec2& A, glm::vec2& B) {
    modelMatrix = transform2D::Translate(A.x, A.y);
    modelMatrix *= transform2D::Shear(A, B);
    modelMatrix *= transform2D::Scale(B.x - A.x, glm::max(A.y, B.y));

    glm::vec3 topLeft = glm::vec3(0., 50., 1.);
    glm::vec3 topRight = glm::vec3(50., 50., 1.);

    topLeft = modelMatrix * topLeft;
    topRight = modelMatrix * topRight;

    A = glm::vec2(topLeft.x, topLeft.y);
    B = glm::vec2(topRight.x, topRight.y);
}


void Lab3::getTankY(Tank& tank) {
    int index = (int) (tank.getPos().x / no_terrain);

    A = glm::vec2(heights[index].first, heights[index].second);
    B = glm::vec2(heights[index + 1].first, heights[index + 1].second);

    getY(A, B);

    float t = 0;

    t = tank.getPos().x - A.x;
    t = t / (B.x - A.x);

    tank.setPos(tank.getPos().x, A.y + t * (B.y - A.y) - 20);
}


void Lab3::generateTanks(Lab3::Tank& tank) {
    glm::vec2 pos = tank.getPos();
    float cx = Base / 2;
    float cy = base / 2;

    getTankY(tank);

    glm::vec2 C = B - A;

    tank.setAngleTank(50 * atan2(C.y, C.x));

    if (tank.isAlive()) {
        //* upper base
        modelMatrix = transform2D::Translate(pos.x, pos.y + height);
        modelMatrix *= transform2D::Rotate(tank.getAngleTank());
        RenderMesh2D(meshes["trapezoid" + to_string(tank.getId())], shaders["VertexColor"], modelMatrix);

        //* lower base
        modelMatrix = transform2D::Translate(pos.x + 4, pos.y - height + 15);
        modelMatrix *= transform2D::Translate(0, height);
        modelMatrix *= transform2D::Rotate(tank.getAngleTank());
        modelMatrix *= transform2D::Translate(0, -height);
        modelMatrix *= transform2D::Scale(0.9f, 0.6f);
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Rotate(glm::pi<float>());
        modelMatrix *= transform2D::Translate(-cx, -cy);
        RenderMesh2D(meshes["trapezoid3"], shaders["VertexColor"], modelMatrix);

        //* above room
        modelMatrix = transform2D::Translate(pos.x + Base / 2, pos.y + height + Base / 2 - 20);
        modelMatrix *= transform2D::Translate(-Base / 2, -height);
        modelMatrix *= transform2D::Rotate(tank.getAngleTank());
        modelMatrix *= transform2D::Translate(Base / 2, height);
        modelMatrix *= transform2D::Scale(0.8f, 0.5f);
        RenderMesh2D(meshes["semicircle" + to_string(tank.getId())], shaders["VertexColor"], modelMatrix);

        //* shooting thing
        modelMatrix = transform2D::Translate(pos.x + Base / 2, pos.y + height + Base / 2 - 15);
        modelMatrix *= transform2D::Translate(-Base / 2, -height);
        modelMatrix *= transform2D::Rotate(tank.getAngleTank());
        modelMatrix *= transform2D::Translate(Base / 2, height);
        modelMatrix *= transform2D::Rotate(tank.getAngleBarrel());
        RenderMesh2D(meshes["rectangle" + to_string(tank.getId())], shaders["VertexColor"], modelMatrix);

        //* hp bar
        modelMatrix = transform2D::Translate(pos.x + 15, pos.y + height + Base);
        modelMatrix *= transform2D::Scale((float)tank.getHp() / 100, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = transform2D::Translate(pos.x + 10, pos.y + height + Base - 5);
        modelMatrix *= transform2D::Scale(1.2, 0.4);
        RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
    }
}


void Lab3::GetTrajectory(Tank& tank) {
    std::vector<glm::vec2> trajPts;
    float angle = 0, time = 0;

    while (trajPts.size() < MAX_PTS) {
        time += 0.8;

        glm::vec2 tankPos = tank.getPos();
        angle = tank.getAngleBarrel() + tank.getAngleTank();
        glm::vec2 position;

        position.x = tankPos.x + Base / 2 + INIT_VELOCITY * cos(angle) * time;
        position.y = tankPos.y + height + Base / 2 + INIT_VELOCITY * sin(angle) * time + .5f * GRAVITY * time * time;

        trajPts.push_back(position);
    }

    tank.setTrajPts(trajPts);

    DrawTrajectory(trajPts, tank.getAngleTank(), tank.getAngleBarrel());
}


void Lab3::DrawTrajectory(std::vector<glm::vec2> trajPts, float angleTank, float angleBarrel) {
    for (glm::vec2 position : trajPts) {
        if (position.y < 5) continue;
        if (position.x <= 0) continue;
        if (position.x > resolution.x) continue;

        modelMatrix = transform2D::Translate(position.x, position.y);
        modelMatrix *= transform2D::Translate(-Base / 2, -height);
        modelMatrix *= transform2D::Rotate(angleTank);
        modelMatrix *= transform2D::Translate(Base / 2, height);
        modelMatrix *= transform2D::Rotate(angleBarrel);
        modelMatrix *= transform2D::Scale(1, 1);
        RenderMesh2D(meshes["point"], shaders["VertexColor"], modelMatrix);
    }
}


void Lab3::DrawBullets(Tank& tank) {
    std::vector<Bullet>& bullets = tank.getBullets();
    float angleTank = tank.getAngleTank();
    float angleBarrel = tank.getAngleBarrel();

    for (int i = 0; i < bullets.size();) {
        if (i < 0) continue;

        Bullet& b = bullets[i];

        float time = b.getTime();
        float angle = b.getAngle();

        glm::vec2 position = b.getPos();
        std::vector<glm::vec2> trjPts = b.getTrajPts();

        if (time >= MAX_PTS) {
            bullets.erase(bullets.begin() + i);
            continue;
        }

        position = trjPts[(int) time];
        time += 0.5;

        trjPts[(int)time] = glm::vec2(0);

        if (position.y > resolution.y) {
            bullets.erase(bullets.begin() + i);
            continue;
        }

        if (position.y < -15) {
            bullets.erase(bullets.begin() + i);
            continue;
        }

        if (position.x < 0) {
            bullets.erase(bullets.begin() + i);
            continue;
        }

        if (position.x > resolution.x - 20) {
            bullets.erase(bullets.begin() + i);
            continue;
        }

        int index = (int)(position.x / no_terrain);

        A = glm::vec2(heights[index].first, heights[index].second);
        B = glm::vec2(heights[index + 1].first, heights[index + 1].second);

        getY(A, B);

        if (tank.getId() == 1 && glm::distance(p2.getPos() + glm::vec2(Base / 2, 0), position) < 2 * DIST) {
            p2.giveDamage();

            bullets.erase(bullets.begin() + i);
            if (!p2.isAlive() && !isLocked1) { isEnding1 = true; isLocked1 = true; }

            for (int i = 0; i < 21; i++) particles.push_back(p2.getPos() + glm::vec2(Base / 2, 0));
            for (int i = 0; i < 21; i++) angles.push_back(glm::pi<float>() / 20 * i);

            continue;
        }

        if (tank.getId() == 2 && glm::distance(p1.getPos() + glm::vec2(Base / 2, 0), position) < 2 * DIST) {
            p1.giveDamage();

            bullets.erase(bullets.begin() + i);
            if (!p1.isAlive() && !isLocked2) { isEnding2 = true; isLocked2 = true; }

            for (int i = 0; i < 21; i++) particles.push_back(p1.getPos() + glm::vec2(Base / 2, 0));
            for (int i = 0; i < 21; i++) angles.push_back(glm::pi<float>() / 10 * i);

            continue;
        }

        if (glm::distance(tank.getPos() + glm::vec2(Base / 2, 0), position) < 2 * DIST &&
            b.getTime() > 5.f) { 
            tank.giveDamage();

            bullets.erase(bullets.begin() + i);
            if (!tank.isAlive() && !isLocked3) { isEnding3 = true; isLocked3 = true; }
            startPos = tank.getPos() + glm::vec2(Base / 2, 0);
            continue;
        }

        if (glm::distance(A, position) < DIST) {
            for (int i = -NEIGH; i <= NEIGH; i++)
                if (i + index >= 0 && i + index < heights.size()) {
                    float scale = 1 - (float)(.1f * i * i) / (NEIGH * NEIGH);

                    heights[i + index].second -= scale * MAX_DEPTH;
                }


            bullets.erase(bullets.begin() + i);
            continue;
        }

        modelMatrix = transform2D::Translate(position.x, position.y);
        modelMatrix *= transform2D::Translate(-Base / 2, -height);
        modelMatrix *= transform2D::Rotate(angleTank);
        modelMatrix *= transform2D::Translate(Base / 2, height);
        modelMatrix *= transform2D::Rotate(angleBarrel);
        modelMatrix *= transform2D::Scale(3, 3);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

        b.setPos(position.x, position.y);
        b.setTime(time);
        
        i++;
    }

    tank.setBullets(bullets);
}


void Lab3::Ending1() {
    if (tick >= 30.f) { isEnding1 = false; tick = 0; return; }

    tick += 0.1;

    for (int i = 0; i < 21; i++) {
        if (particles[i].x < 0 || particles[i].x > resolution.x ||
            particles[i].y < 15 || particles[i].y > resolution.y - 10) continue;

        particles[i].x += 10 * cos(angles[i]) * tick;
        particles[i].y += 10 * sin(angles[i]) * tick + .5f * GRAVITY * tick * tick;

        modelMatrix = transform2D::Translate(particles[i].x, particles[i].y);
        modelMatrix *= transform2D::Scale(2, 2);
        RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
    }
}


void Lab3::Ending2() {
    if (tick >= 30.f) { isEnding2 = false; tick = 0; return; }

    tick += 0.1;

    for (int i = 0; i < 21; i++) {
        if (particles[i].x < 0 || particles[i].x > resolution.x ||
            particles[i].y < 15 || particles[i].y > resolution.y - 10) continue;

        particles[i].x += 10 * cos(angles[i]) * tick;
        particles[i].y += 10 * sin(angles[i]) * tick + .5f * GRAVITY * tick * tick;

        modelMatrix = transform2D::Translate(particles[i].x, particles[i].y);
        modelMatrix *= transform2D::Scale(2, 2);
        RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);
    }
}


void Lab3::Ending3() {
    if (tick >= 200.f) { isEnding3 = false; isLocked3 = false; tick = 0; return; }

    tick += 1;
    
    for (std::pair<int, int> position : dirParticles) {
        int x, y;
        x = position.first * 10 + startPos.x;
        y = position.second * 10 + startPos.y + 100;

        y += (int) tick;

        modelMatrix = transform2D::Translate(x, y);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
    }
}


void Lab3::DrawStars() {
    if (starTime > 1000.f) {
        starTime = 0.f;
        nextPosition = startStars[rand() % 8];
    }

    starTime += 8.f;

    if (starTime > 800.f) return;

    for (float t = starTime - 64.f; t < starTime; t += 8.f) {
        modelMatrix = transform2D::Translate(nextPosition.x - t, nextPosition.y - t);
        RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = transform2D::Translate(nextPosition.x - starTime, nextPosition.y - starTime);
    RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
}


void Lab3::DrawClouds() {
    for (glm::vec2 cloud : clouds) {
        modelMatrix = transform2D::Translate(cloud.x - 40, cloud.y);
        RenderMesh2D(meshes["circle4"], shaders["VertexColor"], modelMatrix);

        modelMatrix = transform2D::Translate(cloud.x, cloud.y + 10);
        RenderMesh2D(meshes["circle4"], shaders["VertexColor"], modelMatrix);

        modelMatrix = transform2D::Translate(cloud.x + 40, cloud.y);
        RenderMesh2D(meshes["circle4"], shaders["VertexColor"], modelMatrix);

        modelMatrix = transform2D::Translate(cloud.x, cloud.y - 10);
        RenderMesh2D(meshes["circle4"], shaders["VertexColor"], modelMatrix);
    }
}


void Lab3::getMoonY() {
    float x = moon.x * moon.x;
    x /= 1300;
    float y = 1280 - x;
    y *= 360;
    y = sqrt(y);

    moon.y = y;
}


void Lab3::DrawMoon() {
    modelMatrix = transform2D::Translate(moon.x, moon.y);
    modelMatrix *= transform2D::Scale(8, 8);
    RenderMesh2D(meshes["circle3"], shaders["VertexColor"], modelMatrix);

    moon.x += .5f;
    getMoonY();

    if (moon.x < 0) moon.x = resolution.x;
    if (moon.x > resolution.x) moon.x = 0;
    if (moon.y < 20) moon.y = resolution.y;
    if (moon.y > resolution.y) moon.y = 20;
}


void Lab3::Update(float deltaTimeSeconds)
{
    generateTanks(p1);
    generateTanks(p2);

    if (isEnding1) Ending1();
    if (isEnding2) Ending2();
    if (isEnding3) Ending3();
    
    generateTerrain();
    DrawStars();
    DrawClouds();
    DrawMoon();

    if (p1.isAlive()) GetTrajectory(p1);
    if (p2.isAlive()) GetTrajectory(p2);

    if (p1.isAlive()) DrawBullets(p1);
    if (p2.isAlive()) DrawBullets(p2);

    //* background
    modelMatrix = transform2D::Translate(0, 300);
    modelMatrix *= transform2D::Scale(30, 9);
    RenderMesh2D(meshes["sqBlack"], shaders["VertexColor"], modelMatrix);

    modelMatrix = transform2D::Scale(30, 6);
    RenderMesh2D(meshes["bgSquare"], shaders["VertexColor"], modelMatrix);
}

void Lab3::FrameEnd()
{
}


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
    //* tank 1
    if (window->KeyHold(GLFW_KEY_W)) {
        float angle = p1.getAngleBarrel();

        if (angle + 3.f * deltaTime >= glm::pi<float>()) {
            p1.setAngleBarrel(glm::pi<float>());
        }
        else {
            p1.setAngleBarrel(angle + 3.f * deltaTime);
        }
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        float angle = p1.getAngleBarrel();

        if (angle - 3.f * deltaTime < 0) {
            p1.setAngleBarrel(0);
        }
        else {
            p1.setAngleBarrel(angle - 3.f * deltaTime);
        }
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        glm::vec2 pos = p1.getPos();

        if (pos.x - 100 * deltaTime < 0) {
            p1.setPos(0, pos.y);
            getTankY(p1);
        } else {
            p1.setPos(pos.x - 100.f * deltaTime, pos.y);
            getTankY(p1);
        }
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        glm::vec2 pos = p1.getPos();

        if (pos.x + 100 * deltaTime >= resolution.x) {
            p1.setPos(resolution.x - 100.f, pos.y);
            getTankY(p1);
        }
        else {
            p1.setPos(pos.x + 100.f * deltaTime, pos.y);
            getTankY(p1);
        }
    }

    //* tank 1
    if (window->KeyHold(GLFW_KEY_UP)) {
        float angle = p2.getAngleBarrel();

        if (angle + 3.f * deltaTime >= glm::pi<float>()) {
            p2.setAngleBarrel(glm::pi<float>());
        }
        else {
            p2.setAngleBarrel(angle + 3.f * deltaTime);
        }
    }

    if (window->KeyHold(GLFW_KEY_DOWN)) {
        float angle = p2.getAngleBarrel();

        if (angle - 3.f * deltaTime < 0) {
            p2.setAngleBarrel(0);
        }
        else {
            p2.setAngleBarrel(angle - 3.f * deltaTime);
        }
    }

    if (window->KeyHold(GLFW_KEY_LEFT)) {
        glm::vec2 pos = p2.getPos();

        if (pos.x - 100 * deltaTime < 0) {
            p2.setPos(0, pos.y);
            getTankY(p2);
        }
        else {
            p2.setPos(pos.x - 100.f * deltaTime, pos.y);
            getTankY(p2);
        }
    }

    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        glm::vec2 pos = p2.getPos();

        if (pos.x + 100 * deltaTime >= resolution.x) {
            p2.setPos(resolution.x - 100.f, pos.y);
            getTankY(p2);
        }
        else {
            p2.setPos(pos.x + 100.f * deltaTime, pos.y);
            getTankY(p2);
        }
    }
}


void Lab3::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_SPACE && p1.isAlive()) {
        float x, y, angle, time;
        glm::vec2 tankPos = p1.getPos();

        std::vector<glm::vec2> trjPts = p1.getTrajPts();
        std::vector<Bullet> bullets = p1.getBullets();

        if (bullets.size() >= MAX_BULLET) return;

        time = 0.8;

        angle = p1.getAngleBarrel() + p1.getAngleTank();
        glm::vec2 position;

        position = trjPts[0];

        Bullet b;

        b.setPos(position.x, position.y);
        b.setAngle(angle);
        b.setTime(time);
        b.setTrajPts(p1.getTrajPts());

        bullets.push_back(b);

        p1.setBullets(bullets);
    }

    if (key == GLFW_KEY_ENTER && p2.isAlive()) {
        float x, y, angle, time;
        glm::vec2 tankPos = p2.getPos();

        std::vector<glm::vec2> trjPts = p2.getTrajPts();
        std::vector<Bullet> bullets = p2.getBullets();

        if (bullets.size() >= MAX_BULLET) return;

        time = 0.8;

        angle = p2.getAngleBarrel() + p2.getAngleTank();
        glm::vec2 position;

        position = trjPts[0];

        Bullet b;

        b.setPos(position.x, position.y);
        b.setAngle(angle);
        b.setTime(time);
        b.setTrajPts(p2.getTrajPts());

        bullets.push_back(b);

        p2.setBullets(bullets);
    }
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (!p2.isAlive()) return;

    glm::vec2 tankPos = p2.getPos();
    glm::vec2 C = glm::vec2(mouseX, mouseY) - tankPos;

    C = glm::normalize(C);

    p2.setAngleBarrel(glm::clamp(atan2(C.y, C.x), 0.f, glm::pi<float>()));
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
