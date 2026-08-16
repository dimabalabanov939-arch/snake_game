#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Game.hpp"

using namespace sf;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    Game game;
    game.run();
    return 0;
}
