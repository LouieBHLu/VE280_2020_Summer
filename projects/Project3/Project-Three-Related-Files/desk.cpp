#include "deck.h"

Deck::Deck(){
    this->reset();
}

void Deck::reset(){
    this->next = 0;
    for(int suits = SPADES; suits <= DIAMONDS; suits++){
        for(int spots = TWO; spots <= ACE; spots++){
            int order = suits * 13 + spots;//the position of the card in a "newly opened" deck of cards.
            this->deck[order].spot = Spot(spots);
            this->deck[order].suit = Suit(suits);
        }
    }
}

void Deck::shuffle(int n){
    
}