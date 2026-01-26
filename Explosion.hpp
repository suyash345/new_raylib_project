#include "Config.h"


class ExplosionAnimation {
    public:
        ExplosionAnimation(Vector2 position, const std::vector<Texture2D> &textures)  
            : pos(position), textures(textures)
        {
            size = Vector2{float(textures[0].width),float(textures[0].height)};
            pos = Vector2{position.x - size.x/2, position.y - size.y/2};
        }

        void Update(float delta_time){
            if(index < textures.size()-1) {
                index +=20 *delta_time;
            }
            else {
                discard = true;
            }
        }

        void Draw() {
            DrawTextureV(textures[int(index)],pos,WHITE);
        }
        bool discard = false;
    private:
        Vector2 pos;
        std::vector<Texture2D> textures;
        Vector2 size;
        float index = 0.0f;
        


};