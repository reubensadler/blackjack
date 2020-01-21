# Blackjack game

Lets single player play blackjack against the computer.

Features  
The dealer (the computer) follows simple rule to to decide to hit or sitck: if it has under 17 total, hit. 17+, stick.  
Aces are worth 11, unless you/dealer would go bust, in which case they become worth 1.
The deck is shuffled randomly before each new game.  

Ranks and suits are set in enums, and the Card struct keeps track of the rank and suit for each card. Placed in a header file, so they can be easily added to any future card game.

Currently the deck is printed after creation to check it has been properly created. Would remove in future.
