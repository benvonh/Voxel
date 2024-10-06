#include "world.hpp"
#include "player.hpp"

#include "raylib.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.hpp"

#include<chrono>
#include<iostream>

using namespace std::chrono_literals;

static bool IN_GAME = false;

int main()
{
	World world;
	Player player;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_WINDOW_MAXIMIZED);
	InitWindow(1280, 720, "Minecraft");

	Shader shader = LoadShader(R"(C:\Users\Ben\CLionProjects\Voxel\vertex_shader.txt)", R"(C:\Users\Ben\CLionProjects\Voxel\fragment_shader.txt)");
	shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
	int ambientLocation = GetShaderLocation(shader, "ambient");
	float shaderValue[4] = { 0.1f, 0.1f, 0.1f, 0.1f };
	SetShaderValue(shader, ambientLocation, shaderValue, SHADER_UNIFORM_VEC4);

	Light lights[MAX_LIGHTS] = { 0 };
	lights[0] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, -2 }, Vector3Zero(), YELLOW, shader);
	lights[1] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, 2 }, Vector3Zero(), RED, shader);
	lights[2] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, 2 }, Vector3Zero(), GREEN, shader);
	lights[3] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, -2 }, Vector3Zero(), BLUE, shader);
	lights[0].enabled = true;
	lights[1].enabled = true;
	lights[2].enabled = true;
	lights[3].enabled = true;

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_TAB))
		{
			IN_GAME = false;
			EnableCursor();
		}
		else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			IN_GAME = true;
			DisableCursor();
		}

		if (IN_GAME)
		{
			player.Update();
		}

		float cameraPos[3] = { player.GetCamera().position.x, player.GetCamera().position.y, player.GetCamera().position.z };
		SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
		for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(shader, lights[i]);

		BeginDrawing();
		{
			ClearBackground(SKYBLUE);
			BeginMode3D(player.GetCamera());
			{
				BeginShaderMode(shader);
				{
					DrawGrid(100, 1.0f);

					for (const auto &block : world.GetBlocks())
					{
						DrawCube(block.position, 1.0f, 1.0f, 1.0f, block.colour);
					}
				}
			}
			EndMode3D();
			DrawFPS(10, 10);
		}
		EndDrawing();
	}

	UnloadShader(shader);
	CloseWindow();
	return EXIT_SUCCESS;
}