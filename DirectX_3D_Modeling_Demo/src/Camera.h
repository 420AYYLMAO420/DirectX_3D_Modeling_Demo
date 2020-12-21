#pragma once
#include "Demo_Windows.h"
#include <DirectXMath.h>

class Camera {
public:
	Camera();
	const DirectX::XMMATRIX& GetLookAt() const;
	void Move(const UINT key, const float deltaTime);
	void ShowControls();
	void ValidateValues();
private:
	void ValidateConstraints(float& value, const float min, const float max);
	void Reset();
private:
	float Radius;
	float Right;
	float Up;
	float Yaw;
	float Pitch;
	float Roll;
	float Speed;
};