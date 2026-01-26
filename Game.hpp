#pragma once

#include <algorithm>

#include "Sprite.hpp"
#include "Explosion.hpp"

struct Star {
	Vector2 position;
	float size;
};

class Game {
public:
	Game() {
		InitWindow(Config::WIDTH, Config::HEIGHT, "2D Game");
		ImportAssets();

		meteor_timer = Timer(Config::METEOR_TIMER_DURATION, true, true, [this]() {CreateMeteor();});

		player = new Player(assets["player"], Vector2{ Config::WIDTH / 2,Config::HEIGHT / 2 }, [this](Vector2 pos) { this->ShootLaser(pos); });
		sprites.push_back(player);

	}

	~Game() {
		for(auto& [asset, texture] : assets) {
			UnloadTexture(texture);
		}
		for(auto& sprite : sprites) {
			delete sprite;
		}
	}

	void CreateMeteor() { // cant pass this in direction, as it is a part of the class, and needs a "this" keyword. Therefore, you need to either make it static or use a lambda which then calls the function.
		meteors.emplace_back(Meteor(assets["meteor"]));
	}

	void ShootLaser(Vector2 pos) {
		lasers.emplace_back(Laser(assets["laser"], pos)); // in place.
	}

	void Update() {
		float delta_time = GetFrameTime();
		// Update

		meteor_timer.Update();
		for(auto sprite : sprites) {
			sprite->Update(delta_time);
		}

		meteors.erase(
			std::remove_if(meteors.begin(), meteors.end(),
				[](const Meteor& m) { return m.discard; }
			),
			meteors.end()
		);

		for (auto& meteor : meteors) {
			meteor.Update(delta_time);
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

		explosions.erase(
			std::remove_if(explosions.begin(), explosions.end(),
				[](const ExplosionAnimation& e) { return e.discard; }
			),
			explosions.end()
		);

		for(auto& expolosion : explosions) {
			expolosion.Update(delta_time);

		}

		CheckCollision();
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
		for (auto& meteor : meteors) {
			meteor.Draw();
		}
		for (auto& explosion : explosions) {
		    explosion.Draw();
		}

		EndDrawing();
	}

	void CheckCollision() {
		for(auto& laser : lasers) {
			for(auto& meteor: meteors) {
				if(CheckCollisionCircleRec(meteor.GetCenter(),
				meteor.collision_radius,laser.GetRectange())) {
					laser.discard = true;
					meteor.discard = true;
					Vector2 pos{laser.position.x - laser.size.x,laser.position.y};
					explosions.push_back(ExplosionAnimation(pos,explosion_textures));
				}
			}
		}


		// player and meteor
		for(auto& meteor : meteors) {
			if(CheckCollisionCircles(player->GetCenter(),player->collision_radius,
				meteor.GetCenter(),meteor.collision_radius)) {
					CloseWindow();
				}
		}
		

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
		std::vector<ExplosionAnimation> explosions;
		std::vector<Texture2D> explosion_textures;
		std::vector<Laser> lasers;
		std::vector<Meteor> meteors;
		std::vector<Sprite*> sprites;

		std::vector<Star> stars;

		Player* player;

		Timer meteor_timer;

		void ImportAssets() {
			assets["player"]  = LoadTexture("Images/spaceship.png");
            assets["star"] = LoadTexture("Images/star.png");
			assets["laser"] = LoadTexture("Images/laser.png");
			assets["meteor"] = LoadTexture("Images/meteor.png");
            for(int i = 0; i < 100; ++i) {
				Vector2 vec{(float)GetRandomValue(0,Config::WIDTH),(float)GetRandomValue(0,Config::HEIGHT)}; // pos
				float random_size = float(GetRandomValue(5,16)*0.10);
				stars.push_back({vec,random_size});
			}
			for(int i = 1; i<=28; ++i) {
				std::string path = "Images/explosion/" + std::to_string(i) + ".png";
				explosion_textures.push_back(LoadTexture(path.c_str()));
			}
		}

		void DrawStars() {
			for(auto& star : stars) {
				DrawTextureEx(assets["star"],star.position, 0, star.size,WHITE);
			}
		}
};

