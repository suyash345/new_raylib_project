#pragma once

#include "Config.h"
#include "Sprite.hpp"


struct Asteroid {
	Vector2 position;
	float size;
};

class Game {
public:
	Game() {
		InitWindow(Config::WIDTH, Config::HEIGHT, "2D Game");
		ImportAssets();

		Player* p = new Player(assets["player"], Vector2{ Config::WIDTH / 2,Config::HEIGHT / 2 }, [this](Vector2 pos) { this->ShootLaser(pos); });
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

	void ShootLaser(Vector2 pos) {
		lasers.emplace_back(Laser(assets["laser"], pos)); // in place.
	}

	void Update() {
		float delta_time = GetFrameTime();
		// Update
		for(auto& sprite : sprites) {
			sprite->Update(delta_time);
		}

		lasers.erase(
			std::remove_if(lasers.begin(), lasers.end(),
				[](const Laser& l) { return l.discard; }
			),
			lasers.end()
		);

		for(auto& laser : lasers) {

			laser.Update(delta_time);
		}
	}

	void Draw() {
		// Begin Draw
		BeginDrawing();
		ClearBackground(Config::BG_COLOR);
		DrawStars();
		for(auto& sprite : sprites) {
			sprite->Draw();	
		}
		for(auto& laser : lasers) {
			laser.Draw();
		}
		EndDrawing();
	}

	void Run() {
		while (!WindowShouldClose()) {
			Update();
			Draw();
		}
		CloseWindow();
	}
	
	private:
		std::unordered_map<std::string,Texture2D> assets;
		std::vector<Laser> lasers;

		std::vector<Sprite*> sprites;
		std::vector<Asteroid> asteroids;

		void ImportAssets() {
			assets["player"]  = LoadTexture("Images/spaceship.png");
            assets["star"] = LoadTexture("Images/star.png");
			assets["laser"] = LoadTexture("Images/laser.png");
            for(int i = 0; i < 100; ++i) {
				Vector2 vec{(float)GetRandomValue(0,Config::WIDTH),(float)GetRandomValue(0,Config::HEIGHT)}; // pos
				float random_size = float(GetRandomValue(5,16)*0.10);
				asteroids.push_back({vec,random_size});
			}
		}

		void DrawStars() {
			for(auto star :asteroids) {
				DrawTextureEx(assets["star"],star.position, 0, star.size,WHITE);
			}
		}
};

