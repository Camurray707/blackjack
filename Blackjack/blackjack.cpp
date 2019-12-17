#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

vector<string> deckOfCards(int numDecks);      //create a deck of cards into a vector
vector<string> shuffleDeck(vector<string>& deck);         //random shuffles deck
void printCard(vector<string> deckOfCards);    //prints current hand |A|...
void dealCards(vector<string>& deck);                   //deal two cards each
void dealerDraw();                  //dealer draws according to rules
void playerDraw();                  //player draws card
int stringToInt(string card, int start, int last);



int main() {


  vector<string> doubleDeck = deckOfCards(2);
  shuffleDeck(doubleDeck);

  while(doubleDeck.size() > 20) {
      dealCards(doubleDeck);

  }

  return 0;
}

vector<string> deckOfCards(int numDecks){

    string value[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    string suit[] = {" of spade", " of club", " of diamond", " of heart"};
    vector<string> cards;

    for (int k = 0; k < numDecks; k++) {
      for (int i = 0; i < 4; i++) {
	    for (int j = 0; j < 13; j++) {
	  cards.push_back(value[j] + suit[i]);
	    }
      }
    }
    return cards;
}

vector<string> shuffleDeck(vector<string>& deck) {

  srand(time(0));
  int test = rand()% 13;
  random_shuffle(deck.begin(), deck.end());

  return deck;
}

void printCard (vector<string> deckOfCards) {

  string answer;
  cout<<"Would you like to play black jack?"<<endl;
  cin>>answer;

    for (int i = 0; i < deckOfCards.size(); i++) {
      while (answer != "no") {

	cout<<deckOfCards.at(i)<<endl;
	cout<<"Another card?"<<endl;
	cin>>answer;
      break;
      }
    }
    cout<<"Continue:(yes/no)"<<endl;
    cin>>answer;
}

void dealCards(vector<string>& deck) {

        int dealerHand = 0;
        int playerHand = 0;
        int discard = 4;
        char action = ' ';

        cout<<setw(25)<<setfill('#')<<'#'<<endl;
        cout<<"______DEALER_HAND______"<<endl<<deck[1]<<endl<<endl;
        cout<<"______PLAYER_HAND______"<<endl<<deck[0]<<" | "<<deck[2]<<endl<<endl;

        dealerHand = stringToInt(deck[1], 0, 10) + stringToInt(deck[3], 0, 10);
        playerHand = stringToInt(deck[0], 0, 10) + stringToInt(deck[2], 0, 10);

        cout<<"Hit(h)/Stay(s): ";
        while (action != 's') {
            cin>>action;

            if (action == 'h') {
                cout<<setw(25)<<setfill('#')<<'#'<<endl;
                cout<<"______DEALER_HAND______"<<endl<<deck[1]<<endl<<endl;
                cout<<"______PLAYER_HAND______"<<endl<<deck[0]<<" | "<<deck[2]<<" | "<<deck[4]<<endl<<endl;
                playerHand += stringToInt(deck[4], 0, 10);
                discard++;
            }
            else if (action == 's') {
                deck.erase(deck.begin(), deck.begin() + discard);
            }
            else {cout<<action<<" is not a valid input. (h/s)";}
        }
}

int stringToInt(string card, int start, int last) {         //converts string to int value

    int value;
    for (int r = start; r < last; r++) {

        if(card[r] == 'A') {value = 1;}
        if(card[r] == '2') {value = 2;}
        if(card[r] == '3') {value = 3;}
        if(card[r] == '4') {value = 4;}
        if(card[r] == '5') {value = 5;}
        if(card[r] == '6') {value = 6;}
        if(card[r] == '7') {value = 7;}
        if(card[r] == '8') {value = 8;}
        if(card[r] == '9') {value = 9;}
        if(card[r] == '1') {value = 10;}
        if(card[r] == 'J') {value = 10;}
        if(card[r] == 'Q') {value = 10;}
        if(card[r] == 'K') {value = 10;}
    }
    return value;
}
