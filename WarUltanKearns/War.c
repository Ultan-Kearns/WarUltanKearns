#include <stdio.h>
#include <stdlib.h>

void newGame();
void game(const p);
void exitGame();
void saveGame();
void loadGame();

void main()
{
	//menu
	int option;
	printf("1 Start New Game\t2 Load Previous Game\t3 Exit Program\n");
	printf("\nPlease enter a number for option: ");
	scanf("%d", &option);
	if (option == 1)
	{
		newGame();
	}
	else if (option == 2)
	{
		loadGame();
	}
	else if (option == 3)
	{
		exitGame();
	}
}
void newGame()
{
	/*
	*newGame function asks for number of players and then calls game function
	*players passed to game as parameter
	*/

	//make sure that the player enters the correct number of players
	int players = 0;
	while (players < 2 || players > 10)
	{
		printf("\nPlease enter number of players: ");
		scanf("%d", &players);
		//inform if not the correct number
		if (players < 2 || players > 10)
		{
			printf("Number of players must be between 2 & 10\n");
		}
	}
	game(players);
}
void game(const p)
{
	/*
	*Game function holds game logic
	*/

	//declare variables
	const players = p;
	int round = 0, cardPlayed = 0, points = 0, highestCard = 0, winningPlayer = 0, cardInDeck = 0, lastHighest = 0;
	int deck[] = { 14,13,12,11,10,9,8,7,6,5,4,3,2 };
	//initialize hand for each player
	int playerHand[10][10];
	int playerPoints[10];
	//set player points to zero
	for (int i = 0; i < 10; i++)
	{
		playerPoints[i] = 0;
	}
	//begin round
	for (int i = 0; i < 13; i++)
	{
		int tie = 0;
		highestCard = 0;
		lastHighest = 0;
		for (int j = 0; j < players; ++j)
		{
			printf("\nPlayer %d Hand: ", j + 1);
			for (int k = 0; k < 13; k++)
			{
				//random deck generates random numbers
				int random = rand() % 13;
				playerHand[j][k] = deck[k];
				if (playerHand[j][k] < 11)
				{
					printf("%3d", playerHand[j][k]);
				}
				else if (playerHand[j][k] == 11)
				{
					printf("%3c", 'J');
				}
				else if (playerHand[j][k] == 12)
				{
					printf("%3c", 'Q');
				}
				else if (playerHand[j][k] == 13)
				{
					printf("%3c", 'K');
				}
				else if (playerHand[j][k] == 14)
				{
					printf("%3c", 'A');
				}
			}
			printf("\nPlease choose a card from deck: ");
			scanf("%d", &cardPlayed);
			cardInDeck = 0;
			do
			{
				for (int cnt = 0; cnt < 13; cnt++)
				{
					if (playerHand[j][cnt] == cardPlayed)
					{
						cardInDeck = 1;
						break;
					}
				}
				if (cardInDeck != 1)
				{
					printf("\nCard not in deck\n");
					printf("\nPlease choose a card from deck: ");
					scanf("%d", &cardPlayed);
				}
				else
				{
					break;
				}
			} while (cardInDeck != 1);
			points += cardPlayed;
			if (cardPlayed > highestCard && cardPlayed != lastHighest)
			{
				highestCard = cardPlayed;
				winningPlayer = j;
			}
			else if (cardPlayed == highestCard || cardPlayed == lastHighest)
			{
				lastHighest = highestCard;
				tie = 1;
				highestCard = 0;
			}
		}
		if (tie != 1)
		{
			playerPoints[winningPlayer] += points;
			printf("\nWinning player this round: %d\nWith score this round of: %d\n", winningPlayer + 1, points);
			points = 0;
		}
		else
		{
			printf("\nRound tied points in next round: %d\n",points);
		}
	}
	for (int i = 0; i < players; i++)
	{
		if (playerPoints[i] > playerPoints[i + 1])
		{
			winningPlayer = i;
		}
	}
	printf("\nWinner of game player:%d with a score of: %d\n", winningPlayer + 1, playerPoints[winningPlayer]);
}
void saveGame()
{
	FILE* fptr;
}
void exitGame()
{
	printf("Are you sure you don't want to save? ");
	return 0;
}
void loadGame()
{

}
