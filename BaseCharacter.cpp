#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {
}

void BaseCharacter::undoMovement() {
	worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec() {
	return Rectangle{ getScreenPos().x, getScreenPos().y, width * scale, height * scale };
}

void BaseCharacter::tick(float deltaTime) {
	worldPosLastFrame = worldPos;

	// update animation
	runningTime += deltaTime;
	if (runningTime >= updateTime) {
		frame++;
		runningTime = 0.f;
		if (frame > maxFrames) frame = 0;
	}

	if (Vector2Length(velocity) != 0.f) {
		// set worldPos = worldPos + direction
		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
		rightLeft = velocity.x < 0.f ? -1.f : 1.f;
		texture = run;
	}
	else {
		texture = idle;
	}
	velocity = {};

	// draw character
	DrawTexturePro(
		texture,
		Rectangle{ frame * (float)texture.width / 6, 0.f, rightLeft * width, height },
		Rectangle{ getScreenPos().x, getScreenPos().y, scale * width, scale * height },
		Vector2{},
		0.f,
		WHITE);
}
