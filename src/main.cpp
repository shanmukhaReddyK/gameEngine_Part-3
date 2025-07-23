#include<SFML/Graphics.hpp>

#include "GameEngine.h"

int main() {
    GameEngine g("assests.txt");
    g.run();
}