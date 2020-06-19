#include "deck.h"

Deck::Deck(){
    this->next = 0;
    for(int suits = SPADES; suits <= DIAMONDS; suits++){
        for(int spots = TWO; spots <= ACE; spots++){
            int order = suits * 13 + spots;//the position of the card in a "newly opened" deck of cards.
            this->deck[order].spot = Spot(spots);
            this->deck[order].suit = Suit(suits);
        }
    }

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
    int left_number = n; int right_number = DeckSize - n;
    //Card* left_cards = new Card[left_number]; Card* right_cards = new Card[right_number];
    Card left_cards[left_number]; Card right_cards[right_number];
    for(int i = 0; i < left_number; i++) left_cards[i] = this->deck[i];
    for(int i = 0; i < right_number; i++) right_cards[i] = this->deck[left_number + i];
    int right_order = 0; int left_order = 0; int right_full = 0; int left_full = 0;
    int sum_order = right_order + left_order;
    while(!right_full || !left_full){
        if(!right_full){
            this->deck[sum_order] = right_cards[right_order];
            right_order++;
        }
        if(!left_full){
            this->deck[sum_order] = left_cards[left_order];
            left_order++;
        }
        if(right_order == right_number) right_full++;
        if(left_order == left_number) left_full++;
    }
    this->next = 0;
}

Card Deck::deal(){
    if(this->next < DeckSize){
        int order = this->next;
        this->next++;
        return this->deck[order];
    } 
    else throw DeckEmpty();
}

int Deck::cardsLeft(){
    return DeckSize - this->next;
}