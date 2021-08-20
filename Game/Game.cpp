//
// Created by Lucas Paim on 17/08/21.
//

#include "Game.h"
#include <iostream>
#include <sstream>

/**********************
 *      GUI
 *********************/

void Game::Gui::renderMenu() {
    const char *options[] = {
            "1 - MOVE",
            "2 - STATISTICS FOR NERDS ;)",
            "3 - AUTOMATICALLY",
            "4 - EXIT"
    };
    for (auto option: options) {
        std::cout<<option<<std::endl;
    }
}

Game::Gui::OPTIONS Game::Gui::readMenuOption() {
    int selected = this->readInt();
    switch (selected) {
        case 1: return MOVE;
        case 2: return SHOW_STATISTICS;
        case 3: return AUTOMATICALLY;
        default: return EXIT;
    }
}

void Game::Gui::clear() {
    system("clear");
}

void Game::Gui::waitForKey() {
    this->renderMessage("\nPress enter to continue...\n");
    getchar();
}

int Game::Gui::readInt(const std::string& message) {
    this->renderMessage(message);
    int aux;
    std::cin>>aux;
    return aux;
}

Game::Gui::State Game::Gui::readMove(int &from, int &to, int nTowers) {
    int rFrom = this->readInt("Select the from tower: ");
    if(rFrom > nTowers || rFrom < 1) return INVALID;

    int rTo = this->readInt("Select the to tower: ");
    if(rTo > nTowers || rTo < 1) return INVALID;

    if(rFrom == rTo) return INVALID;

    from = rFrom;
    to = rTo;
    return VALID;
}

void Game::Gui::renderBoard(Tower::Tower **towers) {
    std::cout<<"-------------------------------"<<std::endl;
    for (size_t i = 0; i < 3; ++i) {
        towers[i]->render();
    }
    std::cout<<"-------------------------------"<<std::endl;
}

void Game::Gui::renderMessage(const std::string &message) {
    std::cout<<message;
}

/**********************
 *      Game
 *********************/

void Game::Game::initializePieces() {
    for (int i = this->piecesNumber; i > 0 ; --i) {
        towers[0]->push(new Tower::Piece(i));
    }
    towers[0]->clearStatistics();
}

Game::Game::GameResult Game::Game::loop() {
    do {
        this->gui->clear();
        this->gui->renderBoard(this->towers);
        this->readMenu();
        this->gui->waitForKey();
    } while (!this->isFinished);
    if(this->allPiecesInCorrectPlace())
        return WINNER;
    return this->exited ? QUIT : NOT_STARTED;
}

void Game::Game::readMenu() {
    this->gui->renderMenu();
    switch (this->gui->readMenuOption()) {
        case Gui::EXIT:
            this->isFinished = true;
            this->exit();
            break;
        case Gui::MOVE:
            this->move();
            break;
        case Gui::AUTOMATICALLY:
            this->automaticallySolve();
            break;
        case Gui::SHOW_STATISTICS:
            this->printStatistics();
            break;
    }
}

bool Game::Game::allPiecesInCorrectPlace() {
    return this->towers[2]->allHere(this->piecesNumber);
}

void Game::Game::move() {
    int from = 0;
    int to = 0;
    if(this->gui->readMove(from, to, 3) == Gui::VALID) {
        --from; --to;
        if(this->move(from, to)) {
            this->madeManualMoves = true;
        } else {
            this->gui->renderMessage("Invalid Move!");
        }
    }
}

bool Game::Game::move(int from, int to) {
    bool canMove = this->towers[to]->canPush(this->towers[from]->peek());
    if(canMove) {
        auto piece = this->towers[from]->pop();
        this->towers[to]->push(piece);
        ++this->moves;
        if(this->allPiecesInCorrectPlace())
            this->isFinished = true;
    }
    return canMove;
}

void Game::Game::exit() {
    this->exited = true;
}


void Game::Game::automaticallySolve() {
    if(this->madeManualMoves) {
        this->gui->renderMessage("Can't automatically solve after made manual moves!\n");
        return;
    }
    if(this->piecesNumber == 3) {
        this->automaticallyMove(0, 2);
        this->automaticallyMove(0, 2); // try an invalid move
        this->automaticallyMove(0, 1);
        this->automaticallyMove(2, 1);
        this->automaticallyMove(0, 2);
        this->automaticallyMove(1, 0);
        this->automaticallyMove(1, 2);
        this->automaticallyMove(0, 2);
    } else if(this->piecesNumber == 5) {
        this->automaticallyMove(0, 2);
        this->automaticallyMove(0, 2); // try an invalid move
        this->automaticallyMove(0, 1);
        this->automaticallyMove(2, 1);
        this->automaticallyMove(0, 2);
        this->automaticallyMove(1, 0);
        this->automaticallyMove(1, 2);
        this->automaticallyMove(0, 2);
        this->automaticallyMove(0, 1);
        this->automaticallyMove(2, 1);
        this->automaticallyMove(2, 0);
        this->automaticallyMove(1, 0);
        this->automaticallyMove(2, 1);
        this->automaticallyMove(0, 2);
        this->automaticallyMove(0, 1);
        this->automaticallyMove(2, 1);
        this->automaticallyMove(0, 2);
        this->automaticallyMove(1, 0);
        this->automaticallyMove(1, 2);
        this->automaticallyMove(0, 2);
        this->automaticallyMove(1, 0);
        this->automaticallyMove(2, 1);
        this->automaticallyMove(2, 0);
        this->automaticallyMove(1, 0);
        this->automaticallyMove(1, 2);
        this->automaticallyMove(0, 2);
        this->automaticallyMove(0, 1);
        this->automaticallyMove(2, 1);
        this->automaticallyMove(0, 2);
        this->automaticallyMove(1, 0);
        this->automaticallyMove(1, 2);
        this->automaticallyMove(0, 2);
    } else {
        this->gui->renderMessage("Automatically solve is only for 3 and 5 pieces");
    }
}

void Game::Game::automaticallyMove(int from, int to) {
    std::stringstream message;
    message << "Move from " << from + 1 << " to " << to + 1 <<std::endl;
    this->gui->renderMessage(message.str());
    if(!this->move(from, to)) {
        this->gui->renderMessage("Invalid Move!\n");
    }
    this->gui->renderBoard(this->towers);
}

void Game::Game::printStatistics() {
    std::cout<<"-------------------------------"<<std::endl;
    int totalPopCounts = 0;
    int totalPushCounts = 0;
    for (int i = 0; i < 3; ++i) {
        auto tower = this->towers[i];
        totalPopCounts += tower->getPopCounts();
        totalPushCounts += tower->getPushCounts();
        std::cout << "Torre "<<i+1<<":"<<std::endl;
        std::cout << "      |- push: "<< tower->getPushCounts() << std::endl;
        std::cout << "      |- pop : "<< tower->getPopCounts() << std::endl;
    }
    int all = totalPopCounts + totalPopCounts;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Total :"<<std::endl;
    std::cout << "      |- push: "<< totalPushCounts << std::endl;
    std::cout << "      |- pop : "<< totalPopCounts << std::endl;
    std::cout << "      |- all : "<< all << std::endl;
    std::cout << "      |- mov : "<< this->moves << std::endl;
    std::cout << "-------------------------------"<<std::endl;
    this->gui->waitForKey();
    this->gui->clear();
}