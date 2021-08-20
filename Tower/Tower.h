//
// Created by Lucas Paim on 17/08/21.
//

#ifndef HANOIOFTOWER_TOWER_H
#define HANOIOFTOWER_TOWER_H


#include "../Stack/Stack.h"
#include <string>
#include <utility>

namespace Tower {
    class Piece {
    private:
        unsigned short int size;
    public:
        explicit Piece(unsigned short int p_size) {
            size = p_size;
        }
        unsigned short int getSize() const;
    };
    class Tower {
    private:
        std::string name;
        Stack::Stack<Piece>* stack;
        int pushCounts = 0;
        int popCounts = 0;
        int countPieces();
    public:
        explicit Tower(std::string t_name) {
            name  = std::move(t_name);
            stack = new Stack::Stack<Piece>();
        }

        bool canPush(Piece* item);
        bool push(Piece* item);
        Piece* pop();
        void render();
        bool allHere(int expected);
        Piece* peek();

        int getPushCounts();
        int getPopCounts();
        void clearStatistics();
    };
}


#endif //HANOIOFTOWER_TOWER_H
