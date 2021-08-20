#include <iostream>
#include "Game/Game.h"

void runGameWith(int pieces = 3) {
    auto game = new Game::Game(pieces);
    switch(game->loop()) {
        case Game::Game::WINNER:
            std::cout<<"Parabéns! Você conseguiu!!!"<<std::endl;
            break;
        case Game::Game::QUIT:
            std::cout<<"Você precisa treinar mais, pequeno gafanhoto!"<<std::endl;
            break;
        default:
            break;
    }
    game->printStatistics();
}


int main() {
    runGameWith();
    runGameWith(5);
    return 0;
}

