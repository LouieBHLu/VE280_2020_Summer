#include "player.h"

class Simple_Player : public Player{
    public:
    int bet(unsigned int bankroll,unsigned int minimum){
        return minimum;
    }

    bool draw(Card dealer, const Hand &player){
        HandValue current_value = player.handValue();
        if(!current_value.soft){
            if(current_value.count <= 11){
                return true;
            }
            else if(current_value.count == 12){
                if(!(dealer.spot >= FOUR && dealer.spot <= SIX)){
                    return true;
                }
            }
            else if(current_value.count >= 13 && current_value.count <= 16){
                if(!(dealer.spot >= TWO && dealer.spot <= SIX)){
                    return true;
                }
            }
        }
        else
        {
            if(current_value.count <= 17){
                return true;
            }
            else if(current_value.count == 18){
                if(!(dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT)){
                    return true;
                }
            }
        }
        return false;
    }

    void expose(Card c)
    { }
    void shuffled()
    { }
};

Player *get_Simple(){
    Player *SimplePlayer = new Simple_Player();
    return SimplePlayer;
}

class Counting_Player : public Player{
    private:
    int count;

    public:
    int bet(unsigned int bankroll,unsigned int minimum){
        if(count >= 2 && bankroll >= 2*minimum){
            return 2*minimum;
        }
        else
        {
            return minimum;
        }
    }

    void shuffled(){
        this->count = 0;
    }

    void expose(Card c){
        if(c.spot >= TEN){
            count--;
        }
        if(c.spot <= SIX && c.spot >= TWO){
            count++;
        }
    }

    bool draw(Card dealer, const Hand &player){
        Simple_Player simple_player;
        return simple_player.draw(dealer,player);
    }
};

Player *get_Counting(){
    Player *CountingPlayer = new Counting_Player();
    return CountingPlayer;
}