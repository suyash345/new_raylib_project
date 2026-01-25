#pragma once

#include "Config.h"

class Sprite {
	public:
		Sprite(Texture2D texture, Vector2 position, float speed, Vector2 direction)  : texture(texture), position(position), speed(speed), direction(direction), 
															size{float(texture.width),float(texture.height)} {
			collision_radius = size.y/2.0f;
		}
		virtual ~Sprite() = default;

		virtual void Update(float delta_time) = 0;
		virtual void Draw() = 0;
		virtual void Move(float delta_time) {
			position.x += direction.x * delta_time * speed;
			position.y += direction.y * delta_time * speed;
		}

		virtual void Discard() {
			if (position.x < 0 || position.x > Config::WIDTH || position.y < 0 || position.y > Config::HEIGHT) {
				discard = true;
			}
		}

		Vector2 GetCenter() {
			return Vector2 {position.x + size.x /2,
							position.y + size.y/2};
		}

		bool discard = false;
		float collision_radius = 0.0f;

	protected:
		Vector2 direction;
		Texture2D texture;
		Vector2 position = {100.0f,100.0f};
		float speed;
		Vector2 size = {0.0f,0.0f};
};


class Player : public Sprite {
public:
	Player(Texture2D texture, Vector2 position, std::function<void(Vector2)>shoot_laser) : Sprite (texture, position,500,{0.0f,0.0f}), call_back(shoot_laser){

	}
	virtual ~Player() = default;
	void Input() {
		direction.x = int(IsKeyDown(KEY_D)) - int(IsKeyDown(KEY_A));
		direction.y = int(IsKeyDown(KEY_S)) - int(IsKeyDown(KEY_W));
		if (Vector2Length(direction) > 0.0f) {
    		direction = Vector2Normalize(direction);
		}
		if(IsKeyPressed(KEY_SPACE)) {
			call_back({position.x + size.x/2, position.y - 50});
		}

	}
	void Update(float delta_time) {
		Input();
		Move(delta_time);
		Constriant();
	}
	void Draw() {
		DrawTexture(texture, position.x, position.y, WHITE);
	}
	void Constriant() {
		position.x = Clamp(position.x,0,Config::WIDTH-size.x);
		position.y = Clamp(position.y,0,Config::HEIGHT-size.y);
	}

	

	private:
		std::function<void(Vector2)> call_back;	
};


class Laser : public Sprite {
	public:
		Laser(Texture2D texture, Vector2 pos) : Sprite(texture,pos,Config::LASER_SPEED,{0,-1}) 
		{
			size = { float(texture.width), float(texture.height) };
		}
		void Update(float delta_time) {
			Move(delta_time);
			Discard();
		}
		void Draw() {
			DrawTexture(texture, position.x - texture.width /2 , position.y, WHITE);
		} 
		Rectangle GetRectange() {
			return Rectangle{position.x,position.y,size.x,size.y};
		}

};


class Meteor : public Sprite{
public:
	Meteor(Texture2D texture)
		: Sprite(texture,
			{ float(GetRandomValue(0, Config::WIDTH)), float(GetRandomValue(-150, -50)) },
			float(GetRandomValue(300, 400)),
			{ 0.1f * float(GetRandomValue(-5,5)), 1.0f })
	{
	}

	void Update(float delta_time) {
		Move(delta_time);
		Discard();
		rotation += GetRandomValue(10,100) * delta_time;
	}

	void Draw() {
		Rectangle target_rect = Rectangle{position.x,position.y,size.x,size.y};
		DrawTexturePro(texture,rec,target_rect,Vector2{size.x/2,size.y/2},rotation,WHITE);
	}

	virtual void Discard() {
		if (position.x > Config::WIDTH  || position.y > Config::HEIGHT) {
			discard = true;
		}
	}
	virtual Vector2 GetCenter() {
		return position;
	}


	private:
		float rotation = 0;
		Rectangle rec{0,0,size.x,size.y};
};