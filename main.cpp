#include <iostream>
#include "raylib.h"
#include <raymath.h>
#include <unordered_map>
#include <string>
#include <vector>

#include "Sprite.hpp"

class Game {
public:
	Game() {
		InitWindow(WIDTH, HEIGHT, "2D Game");
		ImportAssets();

		Player * p = new Player(assets["player"],Vector2{WIDTH/2,HEIGHT/2});
		sprites.push_back(p);
	}

	~Game() {
		for(auto& [asset, texture] : assets) {
			UnloadTexture(texture);
		}
		for(auto& sprite : sprites) {
			delete sprite;
		}
	}
	void Run() {
		while (!WindowShouldClose()) {
			float delta_time = GetFrameTime();
			// Update
			for(auto sprite : sprites) {
				sprite->Update(delta_time);
			}
			
			// Begin Draw
			BeginDrawing();
			ClearBackground(BLACK);

			for(auto sprite : sprites) {
				sprite->Draw();
			}
			EndDrawing();
		}

		CloseWindow();
	}

	private:
		static constexpr int WIDTH = 1920;
		static constexpr int HEIGHT = 1080;
		std::unordered_map<std::string,Texture2D> assets;
		void ImportAssets() {
			assets["player"]  = LoadTexture("Images/spaceship.png");
		}
		std::vector<Sprite*> sprites;
};


int main() {
	Game game;
	game.Run();

}