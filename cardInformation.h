#ifndef CARD_INFORMATION_H
#define CARD_INFORMATION_H

enum Rank
{
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	RANK_ACE,

	MAX_RANK
};

enum Suit
{
	SUIT_SPADE,
	SUIT_HEART,
	SUIT_DIAMOND,
	SUIT_CLUB,

	MAX_SUIT
};

struct Card
{
	Rank rank{};
	Suit suit{};
};

#endif CARD_INFORMATION_H