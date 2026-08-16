#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
using namespace sf;
class Fruits {
    private:
        Vector2f pos_f;
        Sprite sprite;
    public:
        Fruits () :  sprite(getTexture()) {
            sprite.setOrigin({8.f, 8.f});
            sprite.setScale({3.75f, 3.75f});
        }
        static sf::Texture& getTexture() {
            static sf::Texture texture;
            static bool loaded = false;
            if (!loaded) {
                if (!texture.loadFromFile("textures/apple.png")) {
                    // Ошибка загрузки — можно вывести сообщение
                    // или оставить текстуру пустой
                }
                loaded = true;  // ← loaded становится true в любом случае
            }
            return texture;
        }
        void AddFruit(float x, float y) {
            pos_f.x = x;
            pos_f.y = y;
            sprite.setPosition(pos_f);
        }
        float get_x() {return pos_f.x;}
        float get_y() {return pos_f.y;}
        void Draw(RenderWindow& window) {
            window.draw(sprite);
        }

};
