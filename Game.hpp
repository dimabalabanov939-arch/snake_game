#pragma once
#include "Snake.hpp"
#include "Fruits.hpp"
#include <ctime>
#include "sound.hpp"
class Game {
    private:
        sound sounds;
        Snake snake;
        Fruits fruit;
        Clock clock;
        Text finalText;
        Text scoreText;
        Font font;
        int score = 0;
        float moveDelay = 0.15f;
        float timer = 0.f;
        void SpawnFruits() {
            int ch = 1;
            while (ch == 1) {
                float x = 30 + (rand() % 31) * 60;
                float y = 30 + (rand() % 19) * 60;
                ch = snake.CheckPosFruit(x, y);
                if (ch == 0) {
                    if (score == 14) {
                        fruit.AddGoldFruit(x, y);
                    } else {
                        fruit.AddFruit(x, y);
                    }
                }

            }
        }
        void Action(RenderWindow& window) {
            while (auto event = window.pollEvent()) {
                if (event->is<Event::Closed>()) window.close();
                if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                    if (key->code == Keyboard::Key::Escape) window.close();
                }
            }
        }
        bool moveSnake () {
            snake.Moving();
            bool alive = true;
            int ch = snake.CheckColision(fruit.get_x(), fruit.get_y());
            switch (ch) {
                case 0:
                    snake.TailDelete();
                    break;
                case 1:
                    sounds.playEat();
                    score++;
                    scoreText.setString("Score: " + std::to_string(score));
                    if (score == 15) {
                        finalText.setFillColor(Color::Green);
                        finalText.setString("You win!!!");
                        sounds.playWin();
                        return false;
                    }
                    SpawnFruits();
                    break;
                case 2:
                    sounds.playLost();
                    alive = false;
                    break;
            }
            return alive;
        }
        void waitForEnter(RenderWindow& window) {
            while (true) {
                // ← pollEvent() возвращает optional
                while (auto event = window.pollEvent()) {
                    if (event->is<sf::Event::KeyPressed>()) {
                        auto key = event->getIf<sf::Event::KeyPressed>();
                        if (key->code == sf::Keyboard::Key::Enter) {
                            return;
                        }
                    }
                    if (event->is<sf::Event::Closed>()) {
                        window.close();
                        return;
                    }
                }
            }
        }
        void Rendering(RenderWindow& window, bool alive) {
            Color background{255, 255, 172};
            window.clear(background);
            if (!alive) {
                sounds.stopMusic();
                window.draw(finalText);
                window.display();
                waitForEnter(window);
                window.close();
            } else {
                snake.Draw(window);
                window.draw(scoreText);
                if (score != 14) fruit.Draw(window);
                else fruit.Draw_Gold(window);
                window.display();
            }
        }
    public:
        Game () : finalText(font), scoreText(font) {
            if (!font.openFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf")) {
                if (!font.openFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf")) {
                }
            }
            scoreText.setFont(font);
            scoreText.setCharacterSize(20);
            scoreText.setFillColor(Color::White);
            scoreText.setPosition({10.f, 10.f});
            scoreText.setString("Score: 0");
            finalText.setFont(font);
            finalText.setCharacterSize(100);
            finalText.setFillColor(Color::Red);
            finalText.setString("You lost!!!");
            finalText.setPosition({860.f, 540.f});
        }
        void run() {
            RenderWindow window(VideoMode({1920, 1200}), "Snake");
            snake.StartAdd();
            SpawnFruits();
            bool alive = true;
            while (window.isOpen()) {
                float dt = clock.restart().asSeconds();
                timer += dt;
                Action(window);
                if (timer >= moveDelay) {
                    timer = 0.f;
                    alive = moveSnake();
                }
                Rendering(window, alive);
            }
        }
};
