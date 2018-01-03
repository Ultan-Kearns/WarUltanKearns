#include <stdio.h>
#include <stdlib.h>

void newGame();
void game(const p);
int exitGame();
void saveGame(const p);
void loadGame();

//global variables
int playerPoints[10];
int player = 0;
int load = 0;

void main()
{
	//menu
	int option;
	printf("1 Start New Game\t2 Load Previous Game\t3 Exit Program\n");
	printf("\nPlease enter a number for option: ");
	scanf("%d", &option);
	switch (option)
	{
	case 1:
			newGame();
			break;
	case 2:
			loadGame();
			break;
	case 3:
			exitGame();
			break;
	default:
		printf("\nNot an option\n");
		main();
	}
}
void newGame()
{
	/*
	*newGame function asks for number of players and then calls game function
	*players passed to game as parameter
	*/

	//make sure that the player enters the correct number of players
	while (player < 2 || player > 10)
	{
		printf("\nPlease enter number of players: ");
		scanf("%d", &player);
		//inform if not the correct number
		if (player < 2 || player > 10)
		{
			printf("Number of players must be between 2 & 10\n");
		}
	}
	game(player,0);
}
void game(const p, int round)
{
	/*
	*Game function holds game logic
	*/

	//declare variables
	const players = p;
	int cardPlayed = 0, points = 0, highestCard = 0, winningPlayer = 0, cardInDeck = 0;
	int deck[] = {14,13,12,11,10,9,8,7,6,5,4,3,2};
	int rounds = round;
	int cardsPlayed[10];
	//initialize hand for each player
	int playerHand[10][10];
	//set player points to zero
	if (load != 1)
	{
		for (int i = 0; i < 10; i++)
		{
			playerPoints[i] = 0;
		}
	}
	//rounds
	for (int i = rounds; i < 13; i++)
	{

		int tie = 0;
		highestCard = 0;
		//Cards Played = 0
		for (int cnt = 0; cnt < 10; cnt++)
		{
			cardsPlayed[i] = 0;
		}
		//players
		for (int j = 0; j < players; j++)
		{
			printf("\nPlayer %d Hand: ", j + 1);
			for (int k = 0; k < 13; k++)
			{
				int random = rand() % 13;
				playerHand[j][k] = deck[random];
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
			//fix input incase character inserted
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
			cardsPlayed[j] = cardPlayed;
			points += cardPlayed;
			if (cardPlayed > highestCard)
			{
				highestCard = cardPlayed;
				winningPlayer = j;
				tie = 0;
			}		
			//Tie not working  count function is wrong what if cnt is 10 which is ! less than play
		}
		for (int cnt = 0; cnt < players; cnt++)
		{
			//count down instead of up here
			for (int cnt1 = cnt; cnt1 > 0; cnt1--)
			{
				if (cardsPlayed[cnt] == highestCard && cnt != winningPlayer)
				{
					tie = 1;
					highestCard = 0;
				}
				else if (cardsPlayed[cnt] > highestCard)
				{
					tie = 0;
					highestCard = cardsPlayed[cnt];
					winningPlayer = cnt;
				}
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
		char response;
		printf("Would you like to save y/n? ");
		scanf(" %c", &response);
		switch (response)
		{
		case 'y' | 'Y':
			saveGame(players, i);
			exitGame();
			break;
		case 'N' | 'n':
			break;
		default:
			printf("Invalid input");
		}
	}
	for (int i = 0; i < players; i++)
	{
		if (playerPoints[i] > playerPoints[i + 1])
		{
			winningPlayer = i;
		}
	}
	if (playerPoints[winningPlayer] > 0)
	{
		printf("\nWinner of game player:%d with a score of: %d\n\n", winningPlayer + 1, playerPoints[winningPlayer]);
	}
	else
	{
		printf("\nGame tied\n\n");
	}
	main();
}
//may include points from tied games
void saveGame(p,round)
{
	int players = p;
	int roundPlayed = round;
	FILE* fptr = fopen("Saves.dat","w");
	fprintf(fptr,"%d\n", player);
	fprintf(fptr,"%d\n", roundPlayed);
	for (int i = 0; i < players; i++)
	{
		fprintf(fptr,"%d\n",playerPoints[i]);
	}
	fclose(fptr);
	printf("\nGame Saved\n");
}
int exitGame()
{
	return 0;
}
void loadGame()
{
	load = 1;
	FILE* fptr = fopen("Saves.dat", "r");
	if (fptr == NULL)
	{
		printf("No records starting new game");
		newGame();
	}
	int i = 0, roundNo, response;
	int prevPlayerPoints[10];
	int player = fscanf(fptr, "%d", &player);
	fscanf(fptr, "%d", &roundNo);
	do
	{
		fscanf(fptr,"\n%d",&prevPlayerPoints[i]); 
		playerPoints[i] = prevPlayerPoints[i];
		printf("\nPlayer: %d, Points %d", i + 1, prevPlayerPoints[i]);
		i++;
	} while (i < player + 1);
	printf("\nPlease enter option below\n");
	printf("\n1.Start New Round\t2.Save Game\t3.Output game status\n4.Exit game without saving\n");
	scanf("%d", &response);
	switch(response)
	{
		case 1:
			game(i - 1, roundNo);
			break;
		case 2:
			saveGame(i - 1, roundNo);
			loadGame();
			break;
		case 3:
			printf("Game Status");
			for (int cnt = 0; cnt < player + 1; cnt++)
			{
				printf("\nPlayer: %d\n Points %d\n", cnt + 1, prevPlayerPoints[cnt]);		
			}
			printf("Round: %d\n\n",roundNo + 1);
			loadGame();
			break;
		case 4:
			main();
			break;
		default:
			printf("\nInvalid type\n");
			loadGame();
	}
	fclose(fptr);
}
