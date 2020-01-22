#include <algorithm>
#include <iostream>
#include <array>
#include <ctime>
#include <random>
#include "cardInformation.h" //for Rank and Suit enums and Card struct

using deck_type = std::array<Card, 52>;

//forward declare functions in createDeck.cpp
deck_type createDeck();

void printCard(const Card& card);

void printDeck(const deck_type& deck);

void shuffleDeck(deck_type& deck)
{
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(const Card& card)
{
	if (card.rank <= Rank::RANK_10)					//number cards are worth their nummber
		return (static_cast<int>(card.rank) + 2);
	if (card.rank == Rank::RANK_ACE)				//by default make Aces worth 11
		return 11;
	else											//Jacks/Queens/Kings are worth 10
		return 10;
}

void dealPlayerCard(const deck_type& deck, int& total, int& topCard, int& aceCount)
{
	int cardValue{ getCardValue(deck[topCard]) };

	total = total + cardValue;
	if (cardValue == 11)
	{
		std::cout << "You got an Ace! it can be worth 1 or 11.\n";
		aceCount++;
	}
	else
		std::cout << "Your card is worth " << cardValue << '\n';

	topCard++;
}

void dealDealerCard(const deck_type& deck, int& total, int& topCard, int& aceCount)
{
	int cardValue{ getCardValue(deck[topCard]) };

	total = total + cardValue;

	if (cardValue == 11)
		aceCount++;
	topCard++;
}

void askPlayerHitOrStick(char& hitOrStick)
{
	std::cout << "Hit or stick? (h or s)\n";
	std::cin >> hitOrStick;
	hitOrStick = tolower(hitOrStick);

	while (hitOrStick != 'h' && hitOrStick != 's')  //ensure the player has chosen a valid answer
	{
		std::cin.ignore(999999, '\n');
		std::cout << "Invalid answer. Hit or stick? (h or s)\n";
		std::cin >> hitOrStick;
	}
}

bool playBlackjack(const deck_type& deck)
{
	int playerTotal{ 0 };
	int dealerTotal{ 0 };

	int topCard{ 0 };		//index of top card. Will increment each time a card is drawn
	//keep track of the number of aces each player is holding
	int dealerAces{ 0 };	
	int playerAces{ 0 };

	dealDealerCard(deck, dealerTotal, topCard, dealerAces);		//dealer starts with a card face down so only one card
	dealPlayerCard(deck, playerTotal, topCard, playerAces);		//deal player two cards
	dealPlayerCard(deck, playerTotal, topCard, playerAces);
	std::cout << "Your total is " << playerTotal << " and the dealer is showing " << dealerTotal <<'\n';
	dealDealerCard(deck, dealerTotal, topCard, dealerAces);		//dealer looks at face down card
	
	char hitOrStick{};
	askPlayerHitOrStick(hitOrStick);

	while (hitOrStick == 'h')
	{
		dealPlayerCard(deck, playerTotal, topCard, playerAces);

		std::cout << "Your total is " << playerTotal << '\n';
		if (playerTotal > 21)
		{
			if (playerAces)
			{
				playerTotal = playerTotal - 10;
				std::cout << "You would be bust, but have an ace! It's now worth 1.\nYour new total is " << playerTotal << '\n';
				playerAces--;
			}
			else
			{
				std::cout << "\nBust!";
				return 0;
			}
		}
		askPlayerHitOrStick(hitOrStick);
	}

	while (dealerTotal < 17) //dealer will stick if it gets a good enough score
	{
		dealDealerCard(deck, dealerTotal, topCard, dealerAces);
		if (dealerTotal > 21)
		{
			if (dealerAces)
			{
				dealerTotal = playerTotal - 10;
				dealerAces--;
			}
			else
			{
				std::cout << "\nDealer is bust!";
				return 1;
			}
		}
	}
	
	std::cout << "\nThe dealer's total is " << dealerTotal << '\n';

	return playerTotal > dealerTotal;
}

void askToPlayAgain(char& playAgain)
{
	std::cout << "\nWould you like to play again? (y/n)\n";
	std::cin >> playAgain;

	playAgain = tolower(playAgain);

	while (playAgain != 'y' && playAgain != 'n')
	{
		std::cin.ignore(999999, '\n');
		std::cout << "Invalid answer. Would you like to play again? (y/n)\n";
		std::cin >> playAgain;
	}
	std::cout << "--------------------\n";
}

int main()
{
	auto deck{ createDeck() };

	//Print the deck to check deck has been created correctly
	//Can remove for final version
	printDeck(deck);

	int playerPoints{};
	int dealerPoints{};

	char play{ 'y' };
	while (play == 'y')
	{
		shuffleDeck(deck);
		 
		if (playBlackjack(deck))
		{
			std::cout << "\nYou win!\n";
			playerPoints++;
		}
		else
		{
			std::cout << "\nYou lose.\n";
			dealerPoints++;
		}
		askToPlayAgain(play);	
	}	

	std::cout << "Final score is " << playerPoints << " to " << dealerPoints << '\n';
	
	return 0;
}