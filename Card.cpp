#include "Card.h"
#include <string>
#include <cassert>
using namespace std;


//constructor
Card::Card(Suit s, Rank r){
	suit_ = s;
	rank_ = r;
}


//getters
Card::Suit Card::getSuit() const{
	return suit_;
}

Card::Rank Card::getRank() const{
	return rank_;
}


//comparison overloads
bool operator==(const Card &a, const Card &b){
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

bool operator<(const Card &a, const Card &b) {
	if(a.getSuit()<b.getSuit())
		return true;
	else if(a.getSuit() == b.getSuit() && a.getRank() < b.getRank())
		return true;
	else
		return false;
}

//output stream overload
ostream &operator<<(ostream &out, const Card &c){
	string suits[Card::SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[Card::RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
		
	out << ranks[c.getRank()] << suits[c.getSuit()];
	
	return out;
}

//input stream overload
istream &operator>>(istream &in, Card &c){
	string suits = "CDHS", ranks = "A234567891JQK";
	
	string str;
	in >> str;
	assert ( !in.fail() );
	
	//Read in the rank, make sure it's valid
	c.rank_ = (Card::Rank)ranks.find( str.at(0) );
	assert ( c.rank_ != string::npos );
	
	//If it's a 10, make sure the 2nd character is a 0
	if ( c.rank_ == Card::TEN ){
		assert(str.at(1) == '0');
		str.at(1) = str.at(2);
	}
	
	//Read in the suit, make sure it's valid
	c.suit_ = (Card::Suit)suits.find( str.at(1) );
	assert ( c.suit_ != string::npos );
	
	return in;
}
