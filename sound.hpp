#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;

class sound {
    private:
        SoundBuffer eatBuf;
        SoundBuffer lostBuf;
        Sound eat{eatBuf};
        Sound lost{lostBuf};
        public:
            sound () : eatBuf(), lostBuf() {
                if (!eatBuf.loadFromFile("resorce/eat.wav")) {
                    std::cout << "Ошибка: eat.wav не найден!" << std::endl;
                }
                if (!lostBuf.loadFromFile("resorce/lost.wav")) {
                    std::cout << "Ошибка: lost.wav не найден!" << std::endl;
                }
                eat.setBuffer(eatBuf);
                lost.setBuffer(lostBuf);
            }
            void playEat(){eat.play();}
            void playLost(){lost.play();}
};
