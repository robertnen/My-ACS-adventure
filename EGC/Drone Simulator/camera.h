#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"

namespace remade {
    class Camera {
    public:
        Camera(glm::vec3 start_pos) {
            position = start_pos;
            forward  = glm::vec3( 0,  0, -1);
            up       = glm::vec3( 0,  1,  0);
            right    = glm::vec3( 1,  0,  0);
            distanceToTarget = 0;
        }

        Camera(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up) { Set(position, center, up); }
        ~Camera() { }

        void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up) {
            this->position = position;
            forward = glm::normalize(center - position);
            right = glm::cross(forward, up);
            this->up = glm::cross(right, forward);
        }

        void MoveForward(float distance) {
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }

        void TranslateForward(float distance) { position += glm::normalize(forward) * distance; }
        void TranslateUpward(float distance) { position += glm::normalize(up) * distance; }
        void TranslateRight(float distance) { position += glm::normalize(glm::vec3(right.x, 0, right.z)) * distance; }

        void RotateFirstPerson_OX(float angle) {
            glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.f), glm::radians(angle), right);
            forward = glm::normalize(glm::vec3(rotMatrix * glm::vec4(forward, 1.f)));
            up = glm::normalize(glm::vec3(rotMatrix * glm::vec4(up, 1.f)));
        }

        void RotateFirstPerson_OY(float angle) {
            glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.f), glm::radians(angle), glm::vec3(0, 1, 0));
            forward = glm::normalize(glm::vec3(rotMatrix * glm::vec4(forward, 1.f)));
            right = glm::normalize(glm::vec3(rotMatrix * glm::vec4(right, 1.f)));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateFirstPerson_OZ(float angle) {
            glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.f), glm::radians(angle), forward);
            up = glm::normalize(glm::vec3(rotMatrix * glm::vec4(up, 0.f)));
            right = glm::normalize(glm::cross(forward, up));
        }

        void RotateThirdPerson_OX(float angle) {
            glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.f), glm::radians(angle), right);
            forward = glm::normalize(glm::vec3(rotMatrix * glm::vec4(forward, 0.f)));
            up = glm::normalize(glm::cross(right, forward));

            position = GetTargetPosition() - forward * distanceToTarget;
        }

        void RotateThirdPerson_OY(float angle) {
            glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.f), glm::radians(angle), up);
            forward = glm::normalize(glm::vec3(rotMatrix * glm::vec4(forward, 0.f)));
            right = glm::normalize(glm::vec3(rotMatrix * glm::vec4(right, 0.f)));

            position = GetTargetPosition() - forward * distanceToTarget;
        }

        void RotateThirdPerson_OZ(float angle) {
            glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.f), glm::radians(angle), forward);
            up = glm::normalize(glm::vec3(rotMatrix * glm::vec4(up, 0.f)));
            right = glm::normalize(glm::cross(forward, up));
        }

        glm::mat4 GetViewMatrix() { return glm::lookAt(position, position + forward, up); }
        glm::vec3 GetTargetPosition() { return position + forward * distanceToTarget; }

    public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}   // namespace remade
