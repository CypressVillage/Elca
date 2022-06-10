#ifndef _STACK_HPP_
#define _STACK_HPP_

#include <iostream>
#include <string>

using namespace std;

template<class ElementType>
class Stack {
    typedef struct Node{
        ElementType data;
        Node *next;
    } Node;

    Node *top;
    int num;

public:
    Stack<ElementType>();
    ~Stack();

    void push( ElementType );
    ElementType pop( void );
    ElementType topElement();
    void show();
    bool empty();

};

template<class ElementType>
Stack<ElementType>::Stack(): num(0) {
    top = new Node;
}

template<class ElementType>
Stack<ElementType>::~Stack(){

}

template<class ElementType>
void Stack<ElementType>::push( ElementType str ){
    if( num == 0 ){
        top->data = str;
    }else{
        // cout << "push" << str << endl;
        Node *oldTop = new Node;
        oldTop->data = top->data;
        oldTop->next = top->next;
        top ->next = oldTop;
        top -> data = str;
    }
    num ++;
}

template<class ElementType>
ElementType Stack<ElementType>::pop( void ){
    if( num == 1 ){ num = 0; return top->data; }
    if( !num ) cerr << "stack empty" << endl;
    ElementType ans = top->data;
    Node *t = top;
    top = top->next;
    delete t;
    num --;
    // cout << "pop" << ans << endl;
    return ans;
}

template<class ElementType>
ElementType Stack<ElementType>::topElement(){
    if(empty()) return "null";
    return top->data;
}

template<class ElementType>
void Stack<ElementType>::show(){
    cout << "stack:";
    Node *iterator = top;
    for( int i = 0; i < num; ++i ){
        cout << iterator->data << " -> ";
        iterator = iterator->next;
    }
    cout << endl;
}

template<class ElementType>
bool Stack<ElementType>::empty(){
    if(num) return false;
    return true;
}

#endif