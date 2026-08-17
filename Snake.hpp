#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Angle.hpp>
#include <iostream>
#define SEGMENT_SIZE 20
using namespace sf;
class segment {
public:
    Sprite sprite_body;
    Sprite sprite_head;
    Sprite angle_right;
    Sprite angle_left;
    //Sprite tail;
    int vec;
    Vector2f pos_s;
    segment * next;
    segment() : sprite_body(getTexture_body()), sprite_head(getTexture_head()), angle_right(getTexture_angle_right()), angle_left(getTexture_angle_left()) /*tail(getTexture_tail())*/ {
        pos_s = Vector2f(0.0f, 0.0f);
        vec = 0;
        sprite_body.setScale({3.75f, 3.75f});
        sprite_head.setScale({3.75f, 3.75f});
        angle_left.setScale({3.75f, 3.75f});
        angle_right.setScale({3.75f, 3.75f});
        /*tail.setScale({3.75f, 3.75f});
        tail.setOrigin({8.f, 8.f});*/
    }
    static sf::Texture& getTexture_body() {
        static sf::Texture texture;
        static bool loaded = false;
        if (!loaded) {
            if (!texture.loadFromFile("textures/boxy_smake.png")) {
                // Ошибка загрузки — можно вывести сообщение
                // или оставить текстуру пустой
                std::cout << "❌ Ошибка: textures/snake_segment.png не найден!" << std::endl;
            }
            else {
            loaded = true;  // ← loaded становится true в любом случае
            std::cout << "тело успешно считано" << std::endl;
            }
        }
        return texture;
    }
    static sf::Texture& getTexture_head() {
        static sf::Texture texture;
        static bool loaded = false;
        if (!loaded) {
            if (!texture.loadFromFile("textures/head_snake.png")) {
                // Ошибка загрузки — можно вывести сообщение
                // или оставить текстуру пустой
                std::cout << "❌ Ошибка: textures/snake_head.png не найден!" << std::endl;
            }
            else {
            loaded = true;  // ← loaded становится true в любом случае
            std::cout << "голова успешно считана" << std::endl;
        }
        }
        return texture;
    }
    static sf::Texture& getTexture_angle_right() {
        static sf::Texture texture;
        static bool loaded = false;
        if (!loaded) {
            if (!texture.loadFromFile("textures/snake_angle_right.png")) {
                // Ошибка загрузки — можно вывести сообщение
                // или оставить текстуру пустой
                std::cout << "❌ Ошибка: textures/snake_angle_right.png не найден!" << std::endl;
            }
            else {
                loaded = true;  // ← loaded становится true в любом случае
                std::cout << "угл вправо успешно считан" << std::endl;
            }
        }
        return texture;
    }
    static sf::Texture& getTexture_angle_left() {
        static sf::Texture texture;
        static bool loaded = false;
        if (!loaded) {
            if (!texture.loadFromFile("textures/snake_angle_left.png")) {
                // Ошибка загрузки — можно вывести сообщение
                // или оставить текстуру пустой
                std::cout << "❌ Ошибка: textures/snake_angle_left.png не найден!" << std::endl;
            }
            else {
                loaded = true;  // ← loaded становится true в любом случае
                std::cout << "угл влево успешно считан!" << std::endl;
            }
        }
        return texture;
    }
    /*static sf::Texture& getTexture_tail() {
        static sf::Texture texture;
        static bool loaded = false;
        if (!loaded) {
            if (!texture.loadFromFile("textures/tail.png")) {
                // Ошибка загрузки — можно вывести сообщение
                // или оставить текстуру пустой
                std::cout << "❌ Ошибка: textures/tail.png не найден!" << std::endl;
            }
            else {
                loaded = true;  // ← loaded становится true в любом случае
                std::cout << "Хвост успешно считан!" << std::endl;
            }
        }
        return texture;
    }*/
};
class Snake {
    private:
        int vec = 1; // up - 0, right - 1, down - 2, left - 3
        segment *Head;
        segment *Tail;
        float offset = 30.f;
        int getSigmentType(segment* curr, segment* prev, segment* next) {
            if (curr == Tail) return 3;
            if (next == nullptr) return 3;
            if (prev == nullptr) return 0;
            int nextVec = next->vec;
            int currVec = curr->vec;

            if ((currVec == 0 && nextVec == 1) || (currVec == 1 && nextVec == 2) || (currVec == 2 && nextVec == 3) || (currVec == 3 && nextVec == 0)) return 2;
            if ((currVec == 0 && nextVec == 3) || (currVec == 1 && nextVec == 0) || (currVec == 2 && nextVec == 1) || (currVec == 3 && nextVec == 2)) return 1;
            return 0;
        }
    public:
        Snake () {
            Head = nullptr;
            Tail = nullptr;
        }
    void StartAdd () {

        Head = new segment;
        Head->pos_s.x = 960 + offset;
        Head->pos_s.y = 600 + offset;
        Head->vec = 1;
        Tail = Head;
        Head->next = nullptr;

        segment* new_segment = new segment;
        Tail->next = new_segment;
        new_segment->pos_s.x = 900 + offset;
        new_segment->pos_s.y = 600 + offset;
        new_segment->vec = 1;
        Tail = new_segment;

        segment* new_s = new segment;
        Tail->next = new_s;
        new_s->pos_s.x = 840 + offset;
        new_s->pos_s.y = 600 + offset;
        new_s->vec = 1;
        Tail = new_s;
    }
    void chekVec() {
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            if(Head->vec != 3) Head->vec = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
            if(Head->vec != 2) Head->vec = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
            if(Head->vec != 0) Head->vec = 2;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
            if(Head->vec != 1) Head->vec = 3;
        }
    }
    void Moving() {
        segment * new_s = new segment;
        new_s->next = Head;
        chekVec();
        switch (Head->vec) {
            case 0:
                new_s->pos_s.y = Head->pos_s.y - 60;
                new_s->pos_s.x = Head->pos_s.x;
                break;
            case 1:
                new_s->pos_s.y = Head->pos_s.y;
                new_s->pos_s.x = Head->pos_s.x + 60;
                break;
            case 2:
                new_s->pos_s.y = Head->pos_s.y + 60;
                new_s->pos_s.x = Head->pos_s.x;
                break;
            case 3:
                new_s->pos_s.y = Head->pos_s.y;
                new_s->pos_s.x = Head->pos_s.x - 60;
                break;
        }
        new_s->vec = Head->vec;
        Head = new_s;
    }
    bool CheckAlive() {
        segment* curr = Head->next;
        while (curr) {
            if (Head->pos_s.x == curr->pos_s.x && Head->pos_s.y == curr->pos_s.y) return false;
            curr = curr->next;
        }
        if (Head->pos_s.x > 1920 - offset || Head->pos_s.x < 0 + offset || Head->pos_s.y > 1200 - offset || Head->pos_s.y < 0 + offset) return false;
        return true;
    }
    int CheckPosFruit(float x, float y) {
        segment* curr = Head;
        while (curr) {
            if(curr->pos_s.x == x && curr->pos_s.y == y) return 1;
            curr = curr->next;
        }
        return 0;
    }
    int CheckColision(float xf, float yf) {
        int ch;
        if (Head->pos_s.x == xf && Head->pos_s.y == yf) {
            ch = 1;
        } else if (!CheckAlive()) {
            ch = 2;
        } else ch = 0;
        return ch;
    }
    void TailDelete () {
        if (Head == nullptr || Head == Tail) return;
        segment* curr = Head;
        while (curr->next != Tail) {
            curr = curr->next;
        }
        delete Tail;
        curr->next = nullptr;
        Tail = curr;
    }
    void Draw(RenderWindow& window) {
        if (Head == nullptr) return;
        if (!Tail) std::cout << "Хвост не существует";
        segment* curr = Head;
        curr->sprite_head.setOrigin({8.f, 8.f});
        curr->sprite_head.setPosition({curr->pos_s.x + 8.f, curr->pos_s.y + 8.f});
        curr->sprite_head.setRotation(sf::degrees(curr->vec * 90.f));

        window.draw(curr->sprite_head);
        segment * prev = Head;
        curr = curr->next;
        while(curr->next) {
            segment* next = curr->next;
            int type = getSigmentType(curr, prev, next);
            Sprite* SpriteToDraw;
            switch (type) {
                case 0:
                    SpriteToDraw = &curr->sprite_body;
                    SpriteToDraw->setRotation(sf::degrees(curr->vec * 90.f));
                    break;
                case 1:
                    SpriteToDraw = &curr->angle_left;
                    SpriteToDraw->setRotation(sf::degrees(curr->vec * 90.f + 180));
                    break;
                case 2:
                    SpriteToDraw = &curr->angle_right;
                    SpriteToDraw->setRotation(sf::degrees(curr->vec * 90.f + 180));
                    break;
                case 3:{
                    std::cout << "Отрисовка хвоста";
                    static sf::Texture tailTexture;
                    static bool loaded = false;
                    if (!loaded) {
                        if (!tailTexture.loadFromFile("textures/tail.png")) {
                            std::cout << "❌ Ошибка: tail.png не найден!" << std::endl;
                        } else {
                            std::cout << "✅ Хвост загружен!" << std::endl;
                        }
                        loaded = true;
                    }
                    sf::Sprite tailSprite(tailTexture);
                    tailSprite.setScale({3.75f, 3.75f});
                    tailSprite.setOrigin({8.f, 8.f});
                    tailSprite.setPosition({Tail->pos_s.x + 8.f, Tail->pos_s.y + 8.f});
                    tailSprite.setRotation(sf::degrees(Tail->vec * 90.f));
                    window.draw(tailSprite);
                    break;
                    prev = curr;
                    curr = curr->next;
                    continue;
                }
                default:
                    SpriteToDraw = &curr->sprite_body;
                    SpriteToDraw->setRotation(sf::degrees(curr->vec * 90.f));
                    break;
            }
            if (SpriteToDraw != nullptr) {
                SpriteToDraw->setOrigin({8.f, 8.f});
                SpriteToDraw->setPosition({curr->pos_s.x + 8.f, curr->pos_s.y + 8.f});
                window.draw(*SpriteToDraw);
            }
            prev = curr;
            curr = curr->next;
        }
        if (Tail != nullptr) {
            static sf::Texture tailTexture;
            static bool loaded = false;
            if (!loaded) {
                if (!tailTexture.loadFromFile("textures/tail.png")) {
                    std::cout << "❌ Ошибка: tail.png не найден!" << std::endl;
                } else {
                    std::cout << "✅ Хвост загружен!" << std::endl;
                }
                loaded = true;
            }
            sf::Sprite tailSprite(tailTexture);
            tailSprite.setScale({3.75f, 3.75f});
            tailSprite.setOrigin({8.f, 8.f});
            tailSprite.setPosition({Tail->pos_s.x + 8.f, Tail->pos_s.y + 8.f});
            tailSprite.setRotation(sf::degrees(Tail->vec * 90.f));
            window.draw(tailSprite);
        }
    }
};
