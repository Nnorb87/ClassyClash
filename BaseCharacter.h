#pragma once

#include "raylib.h"

class BaseCharacter {
public:
	BaseCharacter();
	Vector2 getWorldPos() { return worldPos; }
	void undoMovement();
	Rectangle getCollisionRec();
	virtual void tick(float deltaTime);
	virtual Vector2 getScreenPos() = 0;
	bool getAlive() { return alive; }
	void setAlive(bool isAlive) { alive = isAlive; }

protected:
	const float scale{ 4.f };

	int maxFrames{ 6 };
	float updateTime{ 1.f / 12.f };
	float speed{ 4.f };
	float width{}, height{};
	float rightLeft{ 1.f }; // 1: facing right, -1: facing left

	// anim variables
	float runningTime{};
	int frame{};

	Texture2D texture{LoadTexture("textures/characters/knight_idle_spritesheet.png")};
	Texture2D idle{ LoadTexture("textures/characters/knight_idle_spritesheet.png") };
	Texture2D run{ LoadTexture("textures/characters/knight_run_spritesheet.png") };
	Vector2 worldPos{};
	Vector2 worldPosLastFrame{};
	Vector2 velocity{};
private:
	bool alive{ true };
};