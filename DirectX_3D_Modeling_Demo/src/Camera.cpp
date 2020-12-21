#include "Camera.h"
#include "imgui/imgui.h"

DirectX::XMVECTOR front;

Camera::Camera()
    :Speed(4.f)
{
    Right = 0.f;
    Up = 0.f;
    Pitch = 0.f;
    Radius = 10.f;
    Roll = 0.f;
    Yaw = 0.f;
}

const DirectX::XMMATRIX& Camera::GetLookAt() const
{
    using namespace DirectX;
    float cosYaw = cos(XMConvertToRadians(Yaw));
    float cosPitch = cos(XMConvertToRadians(Pitch));
    float sinYaw = sin(XMConvertToRadians(Yaw));
    float sinPitch = sin(XMConvertToRadians(Pitch));

    front = XMVector3Normalize(XMVectorSet(cosYaw * cosPitch, sinPitch, sinYaw * cosPitch, 1.f));
    const DirectX::XMVECTOR pos = DirectX::XMVectorSet(Right, Up, Radius, 1.f);
    return XMMatrixLookAtLH(pos, pos + front, XMVectorSet(0.f, 1.f, 0.f, 1.f)) * XMMatrixRotationRollPitchYaw(Roll, -Yaw, Pitch);
}

void Camera::Move(const UINT key, const float deltaTime)
{
    float deltaSpeed = Speed * deltaTime;
    switch (key) {;
    case 'W':
        Up += deltaSpeed;
        break;
    case 'S':
        Up -= deltaSpeed;
        break;
    case 'A':
        Right -= deltaSpeed;
        break;
    case 'D':
        Right += deltaSpeed;
        break;
    case 'E':
        Radius += deltaSpeed;
        break;
    case 'Q':
        Radius -= deltaSpeed;
        break;
    case 'R':
        Reset();
        break;
    }
}

void Camera::ShowControls()
{
    ImGui::Begin("Camera");
    ImGui::Text("Position");
    ImGui::SliderFloat("Radius", &Radius, 0.1f,  80.f, "%.1f");
    ImGui::SliderFloat("Right",  &Right, -20.f,  20.f, "%.1f");
    ImGui::SliderFloat("Up",     &Up,    -20.f,  20.f, "%.1f");
    ImGui::Text("Orientation");
    ImGui::SliderAngle("Roll",   &Roll,  -180.f, 180.f);
    ImGui::SliderAngle("Pitch",  &Pitch, -180.f, 180.f);   
    ImGui::SliderAngle("Yaw",    &Yaw,   -180.f, 180.f);
    ImGui::End();
}

void Camera::ValidateValues()
{
    ValidateConstraints(Radius, 0.1f,  80.f);
    ValidateConstraints(Right, -20.f,  20.f);
    ValidateConstraints(Up,    -20.f,  20.f);
    ValidateConstraints(Roll,  -180.f, 180.f);
    ValidateConstraints(Pitch, -180.f, 180.f);
    ValidateConstraints(Yaw,   -180.f, 180.f);
}

void Camera::ValidateConstraints(float& value, const float min, const float max)
{
    value = (value > max) ? max : value;
    value = (value < min) ? min : value;
}

void Camera::Reset()
{
    Right = 0.f;
    Up = 0.f;
    Yaw = 0.f;
    Pitch = 0.f;
    Radius = 10.f;
    Roll = 0.f;
}



