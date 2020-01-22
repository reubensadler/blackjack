#include <iostream>
#include <array>
#include "cardInformation.h" //for Rank and Suit enums and Card struct


using deck_type = std::array<Card, 52>;

deck_type createDeck()
{
	deck_type deck;

	int cardCount{ 0 };		//this will increase from 0 to 51, repesenting each card in the deck
	int suitCount{ 0 };		//this will increase from 0 to 3, representing each suit

	while (cardCount < 52)
	{
		deck[cardCount].suit = static_cast<Suit>(suitCount);
		deck[cardCount].rank = static_cast<Rank>(cardCount % 13); //when cardCount reaches 13 (ie an Ace), start again at 0 (ie a 2) 
		cardCount++;

		//if cardCount is a multiple of 13, a suit has just been finished 
		//so increment suitCount to move to the next suit
		if ((cardCount % 13) == 0)
			suitCount++;
	}

	return deck;
}

void printCard(const Card& card)
{
	switch (card.rank)
	{
	case RANK_2:
		std::cout << "2";
		break;
	case RANK_3:
		std::cout << "3";
		break;
	case RANK_4:
		std::cout << "4";
		break;
	case RANK_5:
		std::cout << "5";
		break;
	case RANK_6:
		std::cout << "6";
		break;
	case RANK_7:
		std::cout << "7";
		break;
	case RANK_8:
		std::cout << "8";
		break;
	case RANK_9:
		std::cout << "9";
		break;
	case RANK_10:
		std::cout << "10";
		break;
	case RANK_JACK:
		std::cout << "J";
		break;
	case RANK_QUEEN:
		std::cout << "Q";
		break;
	case RANK_KING:
		std::cout << "K";
		break;
	case RANK_ACE:
		std::cout << "A";
		break;
	}

	switch (card.suit)
	{
	case SUIT_SPADE:
		std::cout << "S";
		break;
	case SUIT_HEART:
		std::cout << "H";
		break;
	case SUIT_DIAMOND:
		std::cout << "D";
		break;
	case SUIT_CLUB:
		std::cout << "C";
		break;
	}
}

void printDeck(const deck_type& deck)
{
	for (auto card : deck)
	{
		printCard(card);
		std::cout << " ";
	}

	std::cout << "\n\n";
}