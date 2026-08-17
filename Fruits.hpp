#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
using namespace sf;
class Fruits {
    private:
        Vector2f pos_f;
        Sprite sprite;
        Sprite sprite_gold;
    public:
        Fruits () :  sprite(getTexture()), sprite_gold(getTexture_gold()) {
            sprite.setOrigin({8.f, 8.f});
            sprite.setScale({3.75f, 3.75f});
            sprite_gold.setOrigin({8.f, 8.f});
            sprite_gold.setScale({3.75f, 3.75f});
        }
        static sf::Texture& getTexture() {
            static sf::Texture texture;
            static bool loaded = false;
            if (!loaded) {
                if (!texture.loadFromFile("textures/apple.png")) {
                    std::cout << "Текстура яблока загружена";
                }
                loaded = true;  // ← loaded становится true в любом случае
            }
            return texture;
        }
        static sf::Texture& getTexture_gold() {
            static sf::Texture texture;
            static bool loaded = false;
            if (!loaded) {
                if (!texture.loadFromFile("textures/apple_gold.png")) {
                    std::cout << "Текстура яблока загружена";
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
        void AddGoldFruit(float x, float y) {
            pos_f.x = x;
            pos_f.y = y;
            sprite_gold.setPosition(pos_f);
        }
        float get_x() {return pos_f.x;}
        float get_y() {return pos_f.y;}
        void Draw(RenderWindow& window) {
            window.draw(sprite);
        }
        void Draw_Gold(RenderWindow& window) {
            window.draw(sprite_gold);
        }

};
