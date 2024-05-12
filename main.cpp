#include "raylib.h"
#include "rlimgui.h"
#include "imgui.h"

#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

int main()
{
	InitWindow(1280, 720, "Voxel Game");
	SetTargetFPS(0);
	rlImGuiSetup(true);

	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	Camera camera{
		{ 1.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		90.0f,
		CAMERA_ORTHOGRAPHIC
	};

	RenderTexture2D target = LoadRenderTexture(GetRenderWidth(), GetRenderHeight());
	SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

	unsigned frames = 0U;
	auto time = std::chrono::steady_clock::now();

	while (!WindowShouldClose())
	{
		frames++;
		auto now = std::chrono::steady_clock::now();

		if (now - time > 1s)
		{
			std::cout << "fps: " << frames << '\r' << std::flush;
			frames = 0U;
			time = now;
		}

		BeginDrawing();
		{
			BeginTextureMode(target);
			ClearBackground(SKYBLUE);
			{
				BeginMode3D(camera);
				{
					DrawGrid(100, 1.0f);
					DrawCube(
						{ 0.0f, 0.0f, 0.0f },
						1.0f, 1.0f, 1.0f, GREEN
					);
				}
				EndMode3D();
			}
			EndTextureMode();
		}
		{
			rlImGuiBegin();
			{
				ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
				if (ImGui::Begin("Viewport"))
				{
					rlImGuiImageRenderTexture(&target);
					ImGui::End();
				}
			}
			rlImGuiEnd();
		}
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return EXIT_SUCCESS;
}