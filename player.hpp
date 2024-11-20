#pragma once

#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

#include <iostream>

class Player final
{
public:
	Player() : M_camera(
		{ 1.0f, 1.0f, 1.0f },
		{ 0.0f , 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		60.0f, CAMERA_PERSPECTIVE)
	{
	}

	Player(Player &&) = delete;
	Player(const Player &) = delete;
	Player& operator=(Player &&) = delete;
	Player& operator=(const Player &) = delete;

	~Player() = default;

	[[nodiscard]]
	const auto &GetCamera() const
	{
		return M_camera;
	}

	void Update()
	{
		// TODO: How to do physics?
		const float dt = GetFrameTime();

		Vector3 acceleration = { 0 };

		if (IsKeyDown(KEY_W)) acceleration.x = 5.0f;
		if (IsKeyDown(KEY_A)) acceleration.z = -5.0f;
		if (IsKeyDown(KEY_S)) acceleration.x = -5.0f;
		if (IsKeyDown(KEY_D)) acceleration.z = 5.0f;
		if (IsKeyDown(KEY_SPACE)) acceleration.y = 5.0f;
		if (IsKeyDown(KEY_LEFT_SHIFT)) acceleration.y = -5.0f;

//		acceleration.x -= 0.9f * M_velocity.x;
//		acceleration.z -= 0.9f * M_velocity.z;
//		acceleration.y -= 9.81f;

//		M_velocity = Vector3Add(M_velocity, Vector3Scale(acceleration, dt));
//		M_camera.position = Vector3Add(M_camera.position, Vector3Scale(M_velocity, dt));

//		if (M_camera.position.y < 1.1f)
//			M_camera.position.y = std::max(M_camera.position.y, 0.0f);

		CameraMoveForward(&M_camera, acceleration.x * dt, true);
		CameraMoveRight(&M_camera, acceleration.z * dt, true);
		CameraMoveUp(&M_camera, acceleration.y * dt);

		const Vector2 mouseDelta = GetMouseDelta();
		CameraYaw(&M_camera, (float)(-mouseDelta.x * 0.001), false);
		CameraPitch(&M_camera, (float)(-mouseDelta.y * 0.001), true, false, false);
	}

private:
	Camera M_camera;
	Vector3 M_velocity{0};
};