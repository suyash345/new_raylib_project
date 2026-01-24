#pragma once

#include "Config.h"
#include "Sprite.hpp"

class Game {
public:
	Game() {
		InitWindow(Config::WIDTH, Config::HEIGHT, "2D Game");
		ImportAssets();

		Player * p = new Player(assets["player"],Vector2{Config::WIDTH/2,Config::HEIGHT/2});
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
			ClearBackground(Config::BG_COLOR);

			for(auto sprite : sprites) {
				sprite->Draw();
			}
			EndDrawing();
		}
		CloseWindow();
	}
	
	private:
		std::unordered_map<std::string,Texture2D> assets;
		void ImportAssets() {
			assets["player"]  = LoadTexture("Images/spaceship.png");
		}
		std::vector<Sprite*> sprites;
};
