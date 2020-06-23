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
    if(c.spot == JACK || c.spot == QUEEN || c.spot == KING){
        this->curValue.count += 10;
    }
    else if(c.spot == ACE){
        if(!this->curValue.soft && this->curValue.count < 21) this->curValue.count++;
        else{
            this->curValue.count += 11;
            this->curValue.soft = true;
        }
    }
    else
    {
        this->curValue.count += (c.spot + 2);
    }
    if (this->curValue.soft && this->curValue.count > 21)
    {
        this->curValue.count -= 10;
        this->curValue.soft = false;
    }
}