//----------------------------------------------------------------------------------------
// This cpp file contains the definitions of the following classes:
// 1. Card
// 2. CardsDeck
// This file can be compiled as below:
//     $ g++ DeckOfCards.cpp -o DeckOfCards --std=c++11
//----------------------------------------------------------------------------------------
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

#define MAX_NO_OF_SYMBOLS 4
#define MAX_NO_OF_VALUES  13
#define MAX_CARDS MAX_NO_OF_SYMBOLS * MAX_NO_OF_VALUES

const string cardSymbol[MAX_NO_OF_SYMBOLS] { "CLUBS", "DIAMONDS", "HEARTS", "SPADES" };
const string cardValue[MAX_NO_OF_VALUES]   { "ACE", "TWO", "THREE", "FOUR", "FIVE",  \
		                                     "SIX", "SEVEN", "EIGHT", "NINE", "TEN", \
											 "JACK", "QUEEN", "KING" };

//----------------------------------------------------------------------------------------
// Card class represents one card with a symbol and value.
class Card
{
    private:
        int m_symbol;
        int m_value;

    protected:

    public:
		// Constructors 
		Card() { m_symbol = 0; m_value = 0; }

		Card(int sym, int val):
			m_symbol(sym),
			m_value(val) {}

	    bool operator==(const Card& rhs)
		{	
			return m_symbol == rhs.m_symbol && m_value == rhs.m_value ? true : false;
		}

		// Methods
		string getSymbol(void) const { return cardSymbol[m_symbol]; }
		string getValue(void) const { return cardValue[m_value]; }
};

//----------------------------------------------------------------------------------------
// CardsDeck represents the set of 52 cards.
class CardsDeck
{
	private:
		vector<Card> m_cardsDeck;
		int          m_numOfCards;

	protected:

	public:
		// Constructor 
		CardsDeck() 
		{ 
			// Prepare the Deck with 52 cards.
			for(int sym=0; sym < MAX_NO_OF_SYMBOLS; sym++)
				for(int val=0; val < MAX_NO_OF_VALUES; val++)
					m_cardsDeck.push_back(Card(sym, val));

			m_numOfCards = MAX_CARDS;
		}

		// Restrict copy construction 
		CardsDeck(const CardsDeck&) = delete;
		// Restrict assignment operator 
		CardsDeck& operator=(const CardsDeck&) = delete;

		// Methods
		bool checkForDuplicates(void);
		Card dealOneCard(void);
		void display(void);
		void shuffle(void);
};

//----------------------------------------------------------------------------------------
// Utility method to check for duplicates in the deck.
bool CardsDeck :: checkForDuplicates(void)
{
	cout << ":: CardsDeck :: checkForDuplicates :: " << endl;

	auto it = unique(m_cardsDeck.begin(), m_cardsDeck.end());

	if(it == m_cardsDeck.end())
		return false;
	else
		return true;
}

//----------------------------------------------------------------------------------------
// Method to remove one card from the top of the Deck.
Card CardsDeck :: dealOneCard(void)
{
	cout << ":: CardsDeck :: dealOneCard :: " << endl;

	m_numOfCards--;

	if (m_numOfCards < 0)
		throw "No more cards, Deck is empty.";
	
	Card top_card = m_cardsDeck[0];
	m_cardsDeck.erase(m_cardsDeck.begin());

	return top_card;
}

//----------------------------------------------------------------------------------------
// Utility method to display the remaining cards in the deck i.e. after deal/s.
void CardsDeck :: display(void)
{
	cout << ":: CardsDeck :: displayCardsDeck :: " << endl;

	for(int i=0; i < m_cardsDeck.size(); i++)
	{
		auto card_Obj = m_cardsDeck.at(i);
		cout << " Deck[" << i << "] = " << card_Obj.getSymbol() << " : " << card_Obj.getValue() << endl;
	}
}

//----------------------------------------------------------------------------------------
// We can shuffle only the full deck of cards i.e 52 cards
void CardsDeck :: shuffle(void)
{
	cout << ":: CardsDeck :: shuffle :: " << endl;

	if(m_cardsDeck.size() < MAX_CARDS)
		throw "Can't shuffle: Deck is not full, in the middle of the game.";

	srand(time(0));
	for(int i=0; i < MAX_CARDS; i++)
	{
		int random_index = rand() % MAX_CARDS;
		swap(m_cardsDeck[random_index], m_cardsDeck[i]);
	}

	// Check if the random number generator resulted in any duplicates
	if (checkForDuplicates())
		cout << " Shuffle resulted in duplicates." << endl;
}

//----------------------------------------------------------------------------------------
// Test driver for unit testing the Card and CardsDeck classes.
int main()
{       
    // Create a CardsDeck object that internally creates 52 Cards objects.
	CardsDeck cdObj_1;

	cout << "-----------------------------------------------" << endl;
	// Display the contents of the CardsDeck object.
	cdObj_1.display();

	// Invoke dealOneCard until all cards are exhausted.
	try
	{
		for(int i=0; i < MAX_CARDS + 2; i++)
		{
			Card top_card = cdObj_1.dealOneCard();
			cout << "--Top card = " << top_card.getSymbol() << " : " << top_card.getValue() << endl;
		}
	}
	catch(const char* msg)
	{
		cout << msg << endl;
	}


	cout << "-----------------------------------------------" << endl;
	CardsDeck cdObj_2;

	// Display original Deck
	cdObj_2.display();

	// Shuffle
	try
	{
		cdObj_2.shuffle();
	}
	catch(const char* msg)
	{
		cout << msg << endl;
	}

	cout << "-----------------------------------------------" << endl;
	// Display Deck after shuffle
	cdObj_2.display();
	cout << "-----------------------------------------------" << endl;
	// Deal one card
	cdObj_2.dealOneCard();

	// Display after a Deal
	cdObj_2.display();
	cout << "-----------------------------------------------" << endl;

	// Shuffle after Deal
	try
	{
		cdObj_2.shuffle();
	}
	catch(const char* msg)
	{
		cout << msg << endl;
	}

	if (cdObj_2.checkForDuplicates())
		cout << "There are duplicates." << endl;
}       

