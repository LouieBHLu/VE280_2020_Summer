#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "rand.h"
using namespace std;

void initial_shuffle(Deck &deck, Player *player){
    cout << "Shuffuling the deck\n";
    int cut = 0;
    for (int i = 0; i < 7; i++)
    {
        cut = get_cut();
        deck.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
    player->shuffled();
}

Card deal(Deck &deck, Player *player, Hand &hand, string role, bool expose){
    Card new_card = deck.deal();
    hand.addCard(new_card);
    if(expose){
        player->expose(new_card);
        string spot_name = string(SpotNames[new_card.spot]);
        string suit_name = string(SuitNames[new_card.suit]);
        cout << role << " dealt " << spot_name << " of " << suit_name << endl;
    }
    return new_card;
}

int main(int argc, char const *argv[])
{
    unsigned int mini_bet = 5;
    unsigned int bankroll = 100;
    int hands = 3;
    string player_type = "simple";
    //string player_type = "counting";
    // unsigned int bankroll = atoi(argv[1]);
    // int hands = atoi(argv[2]);
    // string player_type = argv[3];
    Deck deck;
    Player *player;

    if(player_type == "simple"){
        player = get_Simple(); 
    }
    else
    {
        player = get_Counting();
    }
    
    initial_shuffle(deck, player);
    //EFFECT: shuffle seven times before beginning the game

    int thishand = 0;
    Hand dealer_hand, player_hand;
    while(bankroll >= mini_bet && thishand < hands){
        thishand++;
        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        if(deck.cardsLeft() < 20) initial_shuffle(deck, player);
        int wager = player->bet(bankroll,mini_bet);
        cout << "Player bets " << wager << endl;
        //discard?
        string role = "Player";
        deal(deck,player,player_hand,role,true);
        role = "Dealer";
        Card dealer_card = deal(deck,player,dealer_hand,role,true);
        role = "Player";
        deal(deck,player,player_hand,role,true);
        role = "Dealer";
        Card down_card = deal(deck,player,dealer_hand,role,false);
        
        
    }
    return 0;
}
