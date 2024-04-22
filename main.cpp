#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

const int WINDOW_WIDTH{384};
const int WINDOW_HEIGHT{384};

int main() 
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Classy Clash");
	SetTargetFPS(60);


	Texture2D map= LoadTexture("textures/nature_tileset/OpenWorldMap24x24.png");
	Vector2 mapPos{ 0.f, 0.f };
	const float mapScale{ 4.f };

	Character knight(WINDOW_WIDTH, WINDOW_HEIGHT);

	Prop props[2]{ 
		{ Vector2{600.f, 300.f}, LoadTexture("textures/nature_tileset/Rock.png") }, 
		{ Vector2{400.f, 500.f}, LoadTexture("textures/nature_tileset/Log.png") }
	};

	Enemy goblin{ 
		Vector2{400.f, 400.f}, 
		LoadTexture("textures/characters/goblin_idle_spritesheet.png"), 
		LoadTexture("textures/characters/goblin_run_spritesheet.png") 
	};

	Enemy goblin2{
	Vector2{250.f, 120.f},
	LoadTexture("textures/characters/goblin_idle_spritesheet.png"),
	LoadTexture("textures/characters/goblin_run_spritesheet.png")
	};

	Enemy* enemies[2]{&goblin, &goblin2};

	for (Enemy* enemy : enemies) {
		enemy->SetTarget(&knight);
	}


	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		const float dT = GetFrameTime();

		mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

		// draw map
		DrawTextureEx(map, mapPos, 0.f, mapScale, WHITE);

		// draw the props
		for (Prop prop : props) {
			prop.Render(knight.getWorldPos());
		}

		if (!knight.getAlive()) {
			DrawText("GAME OVER", 55.f, 45.f, 40, RED);
			EndDrawing();
			continue;
		}
		else {
			std::string knightsHealth = "Health: ";
			knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
			DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
		}
		
		knight.tick(dT);

		// check map bounds
		if(knight.getWorldPos().x < 0.f ||
			knight.getWorldPos().y < 0.f ||
			knight.getWorldPos().x + WINDOW_WIDTH > map.width * mapScale ||
			knight.getWorldPos().y + WINDOW_HEIGHT > map.height * mapScale)
		{
			knight.undoMovement();
		}
		
		// check props collision
		for (Prop prop : props) {
			if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRect(knight.getWorldPos()))) {
				knight.undoMovement();
			}
		}


		for (Enemy* enemy : enemies) {
			enemy->tick(dT);
		}


		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			for (Enemy* enemy : enemies) {
				if (CheckCollisionRecs(knight.getWeaponCollisionRec(), enemy->getCollisionRec())) enemy->setAlive(false);
			}
		}


		EndDrawing();
	}


	CloseWindow();
}