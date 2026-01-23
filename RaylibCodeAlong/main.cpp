#include <iostream>
#include "raylib.h"
#include <raymath.h>

class Sprite {
	public:
		virtual void Update(float delta_time) = 0;
		virtual void Draw() = 0;

protected:
	Vector2 direction = {0,0};
	Texture texture;
	Vector2 position = {100,100};
	int speed;
};

class Player : public Sprite {
public:
	Player() {
		texture = LoadTexture("../Images/spaceship.png");
		speed = 500;
	}
	void Update(float delta_time) {
		direction.x = int(IsKeyDown(KEY_D)) - int(IsKeyDown(KEY_A));
		direction.y = int(IsKeyDown(KEY_S)) - int(IsKeyDown(KEY_W));

		position.x += direction.x * delta_time * speed;
		position.y += direction.y * delta_time * speed;

		position += Vector2Normalize(position);
	}
	void Draw() {
		DrawTexture(texture, position.x, position.y, WHITE);
	}

};

class Game {
public:
	Game() {
		InitWindow(WIDTH, HEIGHT, "2D Game");
	}
	void Run() {
		Player p;
		while (!WindowShouldClose()) {
			float delta_time = GetFrameTime();
			// Update
			p.Update(delta_time);
			// Begin Draw
			BeginDrawing();
			ClearBackground(BLACK);
			p.Draw();
			EndDrawing();
		}
		CloseWindow();
	}

	private:
		static constexpr int WIDTH = 1920;
		static constexpr int HEIGHT = 1080;
};


int main() {
	Game game;
	game.Run();

}