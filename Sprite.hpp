#include <raylib.h>


class Sprite {
	public:
		virtual void Update(float delta_time) = 0;
		virtual void Draw() = 0;
		virtual void Move(float delta_time) {
			position.x += direction.x * delta_time * speed;
			position.y += direction.y * delta_time * speed;
		}
		virtual ~Sprite() = default;
protected:
	Vector2 direction = {0.0f,0.0f};
	Texture2D texture;
	Vector2 position = {100.0f,100.0f};
	float speed = 200.0f;
};


class Player : public Sprite {
public:
	Player(Texture2D texture, Vector2 position) {
		this->texture = texture;
		this->position = position;
	}
	virtual ~Player() = default;
	void Input() {
		direction.x = int(IsKeyDown(KEY_D)) - int(IsKeyDown(KEY_A));
		direction.y = int(IsKeyDown(KEY_S)) - int(IsKeyDown(KEY_W));
		if (Vector2Length(direction) > 0.0f) {
    		direction = Vector2Normalize(direction);
		}
		if(IsKeyPressed(KEY_SPACE)) {
			return;
		}

	}
	void Update(float delta_time) {
		Input();
		Move(delta_time);
	}
	void Draw() {
		DrawTexture(texture, position.x, position.y, WHITE);
	}
	void Constriant() {

	}

};