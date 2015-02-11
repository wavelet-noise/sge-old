#pragma once
#ifndef Camera_h__
#define Camera_h__

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>
#include "gametimer.h"


class Camera {
public:
    enum CameraType {
        ORTHO, FREE
    };
    enum CameraDirection {
        UP, DOWN, LEFT, RIGHT, FORWARD, BACK
    };
    enum FrustrumPlane {
        RIGHT_PLANE, LEFT_PLANE, BOTTOM_PLANE, TOP_PLANE, BACK_PLANE, FRONT_PLANE
    };

    float m_clipMatrix[16];
    float m_frustum[6][4];
    Camera();
    ~Camera();

    void Reset();
    void Update();

    void Move(CameraDirection dir, GameTimer *gt);
    void ChangePitch(float degrees);
    void ChangeHeading(float degrees);

    void Move2D(int x, int y, GameTimer *gt);

    void SetPosition(glm::vec3 pos);
    void SetLookAt(glm::vec3 pos);
    void SetFOV(double fov);
    void SetViewport(int loc_x, int loc_y, int width, int height);
    void SetClipping(double near_clip_distance, double far_clip_distance);

    void SetDistance(double cam_dist);

    void GetViewport(int &loc_x, int &loc_y, int &width, int &height);
    void GetMatricies(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M) const;
    glm::mat4 VP() const;
    glm::mat4 GetOrthoProjection();
    std::string getFullDebugDescription();
    CameraType camera_mode;

    int viewport_x;
    int viewport_y;

    int window_width;
    int window_height;

    double aspect;
    double field_of_view;
    double near_clip;
    double far_clip;

    float camera_scale;
    float camera_heading;
    float camera_pitch;

    float max_pitch_rate;
    float max_heading_rate;
    bool move_camera;

    glm::vec3 position;
    glm::vec3 position_delta;
    glm::vec3 look_at;
    glm::vec3 direction;

    glm::vec3 up;
    glm::quat rotation_quaternion;
    glm::vec3 mouse_position;

    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 MVP;


    void CalculateFrustum(const glm::mat4 &projectionMatrix, const glm::mat4 &modelViewMatrix);
    bool BoxWithinFrustum(const glm::vec3 &min, const glm::vec3 &max);
};
const glm::mat4 OrthoProjection(float left, float right, float bottom, float top, float zNear, float zFar);
#endif // Camera_h_
