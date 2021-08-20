//
// Created by Lucas Paim on 17/08/21.
//

#ifndef HANOIOFTOWER_STACK_H
#define HANOIOFTOWER_STACK_H


namespace Stack {
    template <typename T>
    class Node {
    public:
        T* data;
        Node* prox;
        explicit Node(T* item) {
            data = item;
            prox = nullptr;
        }
    };

    template <typename T>
    class Stack {
    private:
        Node<T>* head;
    public:
        void push(T* item);
        T* pop();
        T* peek();
        Node<T>* peekNode();
        bool isEmpty();
        Stack() {
            head = nullptr;
        };
    };
}

template <typename T>
void Stack::Stack<T>::push(T* item) {
    auto node = new Node<T>(item);
    if(!this->isEmpty()) {
        node->prox = this->head;
    }
    this->head = node;
}

template <typename T>
T* Stack::Stack<T>::pop() {
    if(this->isEmpty()) return nullptr;
    auto valueToPop = this->head;
    this->head = this->head->prox;
    return valueToPop->data;
}

template <typename T>
bool Stack::Stack<T>::isEmpty() {
    return this->head == nullptr;
}


template <typename T>
T* Stack::Stack<T>::peek() {
    if(this->isEmpty()) return nullptr;
    return this->head->data;
}

template <typename T>
Stack::Node <T> *Stack::Stack<T>::peekNode() {
    if(this->isEmpty()) return nullptr;
    return this->head;
}

#endif //HANOIOFTOWER_STACK_H
