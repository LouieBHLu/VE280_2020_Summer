#include "hand.h"

Hand::Hand(){
    this->curValue.count = 0;
    this->curValue.soft = false;
}

void Hand::discardAll(){
    this->curValue.count = 0;
    this->curValue.soft = false;
}

HandValue Hand::handValue() const{
    return this->curValue;
}

void Hand::addCard(Card c){
    
}