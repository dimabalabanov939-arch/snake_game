#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;

class sound {
    private:
        SoundBuffer eatBuf;
        SoundBuffer lostBuf;
        SoundBuffer winBuf;
        Music backgroundMusic;
        Sound eat{eatBuf};
        Sound lost{lostBuf};
        Sound win{winBuf};
        public:
            sound () : eatBuf(), lostBuf(), winBuf() {
                if (!eatBuf.loadFromFile("resorce/eat.wav")) {
                    std::cout << "Ошибка: eat.wav не найден!" << std::endl;
                }
                if (!lostBuf.loadFromFile("resorce/lost.wav")) {
                    std::cout << "Ошибка: lost.wav не найден!" << std::endl;
                }
                if (!winBuf.loadFromFile("resorce/win.wav")) {
                    std::cout << "Ошибка: lost.wav не найден!" << std::endl;
                }
                eat.setBuffer(eatBuf);
                lost.setBuffer(lostBuf);
                win.setBuffer(winBuf);
                if (!backgroundMusic.openFromFile("resorce/fon_music.wav")) {
                    std::cout << "Ошибка: fon_music.wav не найден!" << std::endl;
                } else {
                    backgroundMusic.setVolume(30.f);
                    backgroundMusic.setLooping(true);
                    backgroundMusic.play();
                }
            }
            void playEat(){eat.play();}
            void playLost(){lost.play();}

            void playWin(){win.play();}

            void stopMusic() {
                backgroundMusic.stop();
            }
};
