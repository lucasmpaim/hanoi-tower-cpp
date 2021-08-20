//
// Created by Lucas Paim on 17/08/21.
//

#include "Tower.h"
#include <iostream>

unsigned short Tower::Piece::getSize() const {
    return this->size;
}

bool Tower::Tower::canPush(Piece* item) {
    if(item == nullptr) return false;
    if(stack->isEmpty()) return true;
    return stack->peek()->getSize() > item->getSize();
}

bool Tower::Tower::push(Piece* item) {
    if(!this->canPush(item)) return false;
    ++this->pushCounts;
    stack->push(item);
    return true;
}

Tower::Piece* Tower::Tower::pop() {
    ++this->popCounts;
    return this->stack->pop();
}

void Tower::Tower::render() {
    std::cout<<this->name<<"  |-";
    std::string stringToPrint = "";
    auto node = this->stack->peekNode();
    while(node != nullptr) {
        stringToPrint.append(std::to_string(node->data->getSize()));
        stringToPrint.append(" ");
        node = node->prox;
    }
    std::reverse(stringToPrint.begin(), stringToPrint.end());
    std::cout<<stringToPrint;
    std::cout<<std::endl;
}

int Tower::Tower::countPieces() {
    int count = 0;
    auto node = this->stack->peekNode();
    while(node != nullptr) {
        ++count;
        node = node->prox;
    }
    return count;
}

bool Tower::Tower::allHere(int expected) {
    return this->countPieces() == expected;
}

Tower::Piece *Tower::Tower::peek() {
    return this->stack->peek();
}

int Tower::Tower::getPopCounts() { return this->popCounts; }
int Tower::Tower::getPushCounts() { return this->pushCounts; }

void Tower::Tower::clearStatistics() {
    this->popCounts = 0;
    this->pushCounts = 0;
}