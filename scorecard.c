#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct currentInnings
{
	int strikerID;
	int nonStrikerID;
	int bowlerID;
	int totalRuns;
	int currentOver;
} innings[2];

struct matchDetails
{
	char venue[60];
	char team1Name[60];
	char team2Name[60];
	int overs;

} match;

struct teams
{
	char name[60];
	char players[11][50];
} team[2];

struct firstInningsScore
{
	int event;
	int balls;
	struct firstInningsScore *next;
} * firstInnings[11];

struct secondInningsScore
{
	int event;
	int balls;
	struct secondInningsScore *next;
} * secondInnings[11];

void loadMatchDetails();
struct matchDetails getMatchDetails();
void loadTeamDetails();
void delay(int numberOfSeconds);
void firstBatting(int batting, int bowling, int inningsNumber);
void secondBatting(int batting, int bowling, int inningsNumber);
void printPlayerList(int option);
//void loadTeam2Details();

void main()
{
	loadMatchDetails();
	system("cls");
	loadTeamDetails();
	system("cls");
	//loadTeam2Details();
	//startMatch();//call with batting team,bowling team - startMatch(rcb,csk) and startMatch(csk,rcb)
}
void trimTrailing(char *str)
{
	int index, i;
	index = -1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			index = i;
		}
		i++;
	}
	str[index + 1] = '\0';
}
void loadMatchDetails()
{
	printf("\nMatch details\n");
	printf("\nEnter Venue : ");
	fgets(match.venue, 60, stdin);
	trimTrailing(match.venue);
	match.venue[strcspn(match.venue, "\n")] == '\0';
	printf("\nEnter Team Name 1 : ");
	fgets(match.team1Name, 60, stdin);
	trimTrailing(match.team1Name);
	match.team1Name[strcspn(match.team1Name, "\n")] == '\0';
	printf("\nEnter Team Name 2 : ");
	fgets(match.team2Name, 60, stdin);
	trimTrailing(match.team2Name);
	match.team2Name[strcspn(match.team2Name, "\n")] == '\0';
	printf("\nEnter Total Number of overs : ");
	scanf("%d", &match.overs);
}

struct matchDetails getMatchDetails()
{
	struct matchDetails thisMatch;
	strcpy(thisMatch.venue, match.venue);
	strcpy(thisMatch.team1Name, match.team1Name);
	strcpy(thisMatch.team2Name, match.team2Name);
	thisMatch.overs = match.overs;
	return (thisMatch);
}

void printPlayerList(int option)
{
	struct matchDetails currentMatch;
	currentMatch = getMatchDetails();
	int j = 0;
	if (option == 0)
	{
		printf("\n\n\tPlayers List of %s", currentMatch.team1Name);
		for (j = 0; j < 11; j++)
		{
			printf("\n%d. %s", j + 1, team[0].players[j]);
		}
	}
	if (option == 1)
	{
		printf("\n\n\tPlayers List of %s", currentMatch.team2Name);
		for (j = 0; j < 11; j++)
		{
			printf("\n%d. %s", j + 1, team[1].players[j]);
		}
	}
	if (option == 2)
	{
		printf("\n%s\t%s", currentMatch.team1Name, currentMatch.team2Name);
		for (j = 0; j < 11; j++)
		{
			printf("\n%d. %s\t\t%d. %s", j + 1, team[0].players[j], j + 1, team[1].players[j]);
		}
	}
}

void loadTeamDetails()
{
	struct matchDetails currentMatch;
	currentMatch = getMatchDetails();
	int i, j, tossSelection;
	//matchDetails currentMatch = getMatchDetails();
	printf("\n\t\t %d Over match Between %s and %s at %s", currentMatch.overs, currentMatch.team1Name, currentMatch.team2Name, currentMatch.venue);
	printf("\n---------------------------------------------------------------------------");
	strcpy(team[0].name, currentMatch.team1Name);
	strcpy(team[1].name, currentMatch.team2Name);
	for (i = 0; i < 2; i++)
	{

		printf("\n Enter player names of %s", team[i].name);
		for (j = 0; j < 11; j++)
		{
			printf("\n Enter name of player %d : ", j + 1);
			fgets(team[i].players[j], 30, stdin);
			trimTrailing(team[i].players[j]);
			team[i].players[j][strcspn(team[i].players[j], "\n")] == '\0';
		}
	}

	system("cls");
	printf("\n\t\t %d Over match Between %s and %s at %s", currentMatch.overs, currentMatch.team1Name, currentMatch.team2Name, currentMatch.venue);
	printf("\n---------------------------------------------------------------------------");

	//printPlayerList(2);
	printPlayerList(0);
	printPlayerList(1);

	printf("\n\t\t\t%s is calling the toss", team[0].name);
	printf("\n\t\t\tSelect 1 for Heads and 2 for Tails : ");
	scanf("%d", &tossSelection);

	int random = rand();
	int toss = random % 2 == 0 ? 0 : 1;
	char tossWinner[60];

	printf("\n\n\t\t\tTossing the Coin");
	int threshold = rand() % 5;
	for (i = 0; i < threshold; i++)
	{
		delay(750);
		printf(".");
	}

	if (toss == 0)
	{
		printf("\n\t\tThe toss is : Heads");
	}
	else
	{
		printf("\n\t\tThe toss is : Tails");
	}

	tossSelection == toss + 1 ? strcpy(tossWinner, team[0].name) : strcpy(tossWinner, team[1].name);
	printf("\n\t\tToss is won by %s", tossWinner);
	printf("\n\t\t%s chooses to (1. Bat 2. Field) : ", tossWinner);
	int decision;
	scanf("%d", &decision);

	char chooses[10];
	decision == 1 ? strcpy(chooses, "Bat") : strcpy(chooses, "Bowl");
	printf("\n\t\t%s chooses to %s first.", tossWinner, chooses);

	printf("\n\n\nLoading the Match..");
	threshold = rand() % 9;
	for (i = 0; i < threshold; i++)
	{
		delay(750);
		printf(".");
	}

	int tossWinnerID = strcmpi(tossWinner, currentMatch.team1Name) == 0 ? 0 : 1;
	int firstBattingTeam = (tossWinnerID + decision) == 2 ? 1 : 0;
	int firstBowlingTeam = (tossWinnerID + decision) == 2 ? 0 : 1;

	firstBatting(firstBattingTeam, firstBowlingTeam, 1);
	secondBatting(firstBowlingTeam, firstBattingTeam, 2);

	getch();
}

void delay(int numberOfSeconds)
{
	clock_t startTime = clock();
	while (clock() < startTime + numberOfSeconds)
		;
}
void addFBRun(int batsmanID, int run)
{

	struct firstInningsScore *temp;

	if (firstInnings[batsmanID] == NULL)
	{
		temp = (struct firstInningsScore *)malloc(sizeof(struct firstInningsScore));
		temp->event = run;
		temp->next = NULL;
		firstInnings[batsmanID] = temp;
	}
	else
	{
		temp->next = (struct firstInningsScore *)malloc(sizeof(struct firstInningsScore));
		temp = temp->next;
		temp->event = run;
		temp->next = NULL;
		struct firstInningsScore *cur;
		cur = firstInnings[batsmanID];
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = temp;
	}
}
void addSBRun(int batsmanID, int run)
{

	struct secondInningsScore *temp;

	if (secondInnings[batsmanID] == NULL)
	{
		temp = (struct secondInningsScore *)malloc(sizeof(struct secondInningsScore));
		temp->event = run;
		temp->next = NULL;
		secondInnings[batsmanID] = temp;
	}
	else
	{
		temp->next = (struct secondInningsScore *)malloc(sizeof(struct secondInningsScore));
		temp = temp->next;
		temp->event = run;
		temp->next = NULL;
		struct secondInningsScore *cur;
		cur = secondInnings[batsmanID];
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = temp;
	}
}
void printFBRun(int batsmanID)
{
	struct firstInningsScore *temp;
	temp = firstInnings[batsmanID];
	while (temp != NULL)
	{
		printf("%d->", temp->event);
		temp = temp->next;
	}
}
void printSBRun(int batsmanID)
{
	struct secondInningsScore *temp;
	temp = secondInnings[batsmanID];
	while (temp != NULL)
	{
		printf("%d->", temp->event);
		temp = temp->next;
	}
}
void firstBatting(int batting, int bowling, int inningsNumber)
{
	system("cls");
	struct matchDetails currentMatch = getMatchDetails();
	int currentOver = 0, totalBalls = currentMatch.overs * 6, balls = 0, temp, i = 0, j = 0;
	printf("\n\t\t %d Over match Between %s and %s at %s", currentMatch.overs, currentMatch.team1Name, currentMatch.team2Name, currentMatch.venue);
	printf("\n\t\t Innings of %s", team[batting].name);
	innings[inningsNumber - 1].strikerID = 0;
	innings[inningsNumber - 1].nonStrikerID = 1;
	innings[inningsNumber - 1].bowlerID = 0;
	int totalRuns = 0, currentRuns = 0;
	for (i = 0; i < currentMatch.overs; i++)
	{
		for (j = 0; j < 6; j++)
		{
			system("cls");
			printf("\n\t\t %d Over match Between %s and %s at %s", currentMatch.overs, currentMatch.team1Name, currentMatch.team2Name, currentMatch.venue);
			printf("\n\t\t Innings of %s", team[batting].name);
			printf("\nIn Strike : %s", team[batting].players[innings[inningsNumber - 1].strikerID]);
			printf("\nNon Striker : %s", team[batting].players[innings[inningsNumber - 1].nonStrikerID]);
			printf("\n Bowler : %s", team[bowling].players[innings[inningsNumber - 1].bowlerID]);
			//totalRuns+=currentRuns;
			printf("\n\n\t\tOver : %d.%d\tTotal : %d", i, j, totalRuns);
			printf("\n\n\t\tCurrent Innings of Batsman %d is : ", innings[inningsNumber - 1].strikerID);
			printFBRun(innings[inningsNumber - 1].strikerID);
			printf("\nEnter runs Scored (0 for dot, 1, 2, 3, 4, 6, 9 for Wicket) : ");
			scanf("%d", &currentRuns);
			balls += 1;
			if (currentRuns == 9)
			{
				int maxBatID = innings[inningsNumber - 1].strikerID > innings[inningsNumber - 1].nonStrikerID ? innings[inningsNumber - 1].strikerID : innings[inningsNumber - 1].nonStrikerID;
				if (maxBatID < 11)
				{
					innings[inningsNumber - 1].strikerID = maxBatID + 1;
				}
				else
				{
					printf("\n Innings over.\nTotal Runs = %d", totalRuns);
				}
			}
			else{
				addFBRun(innings[inningsNumber - 1].strikerID, currentRuns);
				totalRuns += currentRuns;
			}
			//addFBRun(innings[inningsNumber - 1].strikerID, currentRuns);
			//printf("Current Innings of Batsman %d is : ",innings[inningsNumber-1].strikerID);
			//printRun(innings[inningsNumber-1].strikerID);
			if (currentRuns == 1 && balls % 6 != 0 || currentRuns == 3 && balls % 6 != 0)
			{
				temp = innings[inningsNumber - 1].strikerID;
				innings[inningsNumber - 1].strikerID = innings[inningsNumber - 1].nonStrikerID;
				innings[inningsNumber - 1].nonStrikerID = temp;
			}
			else if (currentRuns == 2 && balls % 6 == 0 || currentRuns == 4 && balls % 6 == 0 || currentRuns == 6 && balls % 6 == 0)
			{
				temp = innings[inningsNumber - 1].strikerID;
				innings[inningsNumber - 1].strikerID = innings[inningsNumber - 1].nonStrikerID;
				innings[inningsNumber - 1].nonStrikerID = temp;
			}

			
			//getch();
		}
	}
	printf("\n The Total runs scored in this innings is : %d", totalRuns);
	for (i = 0; i < 11; i++)
	{
		printf("\n i = %d : ", i);
		printFBRun(i);
	}
	getch();
}

void secondBatting(int batting, int bowling, int inningsNumber)
{
	system("cls");
	struct matchDetails currentMatch = getMatchDetails();
	int currentOver = 0, totalBalls = currentMatch.overs * 6, balls = 0, temp, i = 0, j = 0;
	printf("\n\t\t %d Over match Between %s and %s at %s", currentMatch.overs, currentMatch.team1Name, currentMatch.team2Name, currentMatch.venue);
	printf("\n\t\t Innings of %s", team[batting].name);
	innings[inningsNumber - 1].strikerID = 0;
	innings[inningsNumber - 1].nonStrikerID = 1;
	innings[inningsNumber - 1].bowlerID = 0;
	int totalRuns = 0, currentRuns = 0;
	for (i = 0; i < currentMatch.overs; i++)
	{
		for (j = 0; j < 6; j++)
		{
			system("cls");
			printf("\n\t\t %d Over match Between %s and %s at %s", currentMatch.overs, currentMatch.team1Name, currentMatch.team2Name, currentMatch.venue);
			printf("\n\t\t Innings of %s", team[batting].name);
			printf("\nIn Strike : %s", team[batting].players[innings[inningsNumber - 1].strikerID]);
			printf("\nNon Striker : %s", team[batting].players[innings[inningsNumber - 1].nonStrikerID]);
			printf("\n Bowler : %s", team[bowling].players[innings[inningsNumber - 1].bowlerID]);
			//totalRuns+=currentRuns;
			printf("\n\n\t\tOver : %d.%d\tTotal : %d", i, j, totalRuns);
			printf("Current Innings of Batsman %d is : ", innings[inningsNumber - 1].strikerID);
			printSBRun(innings[inningsNumber - 1].strikerID);
			printf("\nEnter runs Scored (0 for dot, 1, 2, 3, 4, 6, 9 for Wicket) : ");
			scanf("%d", &currentRuns);
			balls += 1;
			addSBRun(innings[inningsNumber - 1].strikerID, currentRuns);
			//printf("Current Innings of Batsman %d is : ",innings[inningsNumber-1].strikerID);
			//printRun(innings[inningsNumber-1].strikerID);
			if (currentRuns == 1 && balls % 6 != 0 || currentRuns == 3 && balls % 6 != 0)
			{
				temp = innings[inningsNumber - 1].strikerID;
				innings[inningsNumber - 1].strikerID = innings[inningsNumber - 1].nonStrikerID;
				innings[inningsNumber - 1].nonStrikerID = temp;
			}
			else if (currentRuns == 2 && balls % 6 == 0 || currentRuns == 4 && balls % 6 == 0 || currentRuns == 6 && balls % 6 == 0)
			{
				temp = innings[inningsNumber - 1].strikerID;
				innings[inningsNumber - 1].strikerID = innings[inningsNumber - 1].nonStrikerID;
				innings[inningsNumber - 1].nonStrikerID = temp;
			}
			totalRuns += currentRuns;
			//getch();
		}
	}
	printf("\n The Total runs scored in this innings is : %d", totalRuns);
	for (i = 0; i < 2; i++)
	{
		printf("\n i = %d : ", i);
		printSBRun(i);
	}
	getch();
}
