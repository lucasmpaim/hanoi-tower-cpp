//
// Created by Lucas Paim on 17/08/21.
//

#ifndef HANOIOFTOWER_GAME_H
#define HANOIOFTOWER_GAME_H

#include "../Tower/Tower.h"

namespace Game {

    class Gui {
    private:
    public:
        enum OPTIONS {
            MOVE=0,
            SHOW_STATISTICS,
            AUTOMATICALLY,
            EXIT
        };

        enum State{
            VALID=0, INVALID
        };
        void clear();
        void renderBoard(Tower::Tower **towers);
        void renderMenu();
        void renderMessage(const std::string& message);
        OPTIONS readMenuOption();
        void waitForKey();
        State readMove(int& from, int& to, int nTowers);
        int readInt(const std::string& message = "Select one option: ");
    };


    class Game {
    private:
        Gui* gui;
        bool isFinished;
        bool madeManualMoves;
        bool exited;
        int piecesNumber;
        int moves;
        Tower::Tower* towers[3];
        void initializePieces();
        void readMenu();
        void move();
        bool move(int from, int to);
        bool allPiecesInCorrectPlace();
        void exit();

        void automaticallyMove(int from, int to);
        void automaticallySolve();
    public:
        enum GameResult {
            NOT_STARTED = 0,
            WINNER,
            QUIT
        };
        explicit Game(int g_piecesNumber) {
            gui = new Gui();
            isFinished = false;
            madeManualMoves = false;
            exited = false;
            moves = 0;
            piecesNumber = g_piecesNumber;
            towers[0] = new Tower::Tower("Tower 1");
            towers[1] = new Tower::Tower("Tower 2");
            towers[2] = new Tower::Tower("Tower 3");
            initializePieces();
        }
        GameResult loop();
        void printStatistics();
    };

}


#endif //HANOIOFTOWER_GAME_H
