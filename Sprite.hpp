#include <raylib.h>


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
	Player(Texture2D texture, Vector2 positon) {
		this->texture = texture;
		this->position = positon;
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