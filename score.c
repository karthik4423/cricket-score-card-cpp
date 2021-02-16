#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

char venue[60] = "";
char team1[60] = "";
char team2[60] = "";
char toss[60] = "";
char decision[20] = "";
int overs;
char batsmen[2][11][25];
char bowlers[2][11][25];
int batsmanNo[2];
int bowlerNo[2];
int spells[2][11][3];
int totalFirstInnings = 0;
struct firstInningsScore
{
    int event;
    int balls;
    struct firstInningsScore *next;
} * firstInnings[11];
char inningsOf[2][60];

void matchDetailTemplate()
{
    printf("\n VENUE : ");
    gets(venue);
    printf("\n Team 1 : ");
    gets(team1);
    printf("\n Team 2 : ");
    gets(team2);
    printf("\n Toss Won By : ");
    gets(toss);
    printf("\n Chose to (Bat/Bowl) : ");
    gets(decision);
    printf("\n Overs : ");
    scanf("%d", &overs);
    //printf("\n\nInnings of : (%s/%s) : ",team1,team2);
}

void matchDetail()
{
    system("cls");
    printf("\n\t\t VENUE : %s", venue);
    printf("\n\t\t %s VERSUS %s", team1, team2);
    printf("\n\t\t Toss Won By : %s", toss);
    printf(" Chose to (Bat/Bowl) : %s", decision);
    printf("\n\t\t %d Overs Match", overs);
}

printInnings(int innings, int number)
{
    if (innings == 0)
    {
        struct firstInningsScore *temp;
        temp = firstInnings[number];
        printf("\t");
        while (temp != NULL)
        {
            printf("%d->", temp->event);
            temp = temp->next;
        }
    }
}

void batsmenDetail(int innings)
{
    int i = 0;
    for (i = 0; i < batsmanNo[innings]; i++)
    {
        printf("\n Batsman %d : %s", i + 1, batsmen[innings][i]);
        printInnings(innings, i);
    }
}

printSpell(int innings, int bowlerID)
{
    printf("\t%d/%d (%d.%d)", spells[innings][bowlerID][1], spells[innings][bowlerID][2], spells[innings][bowlerID][0] / 6, spells[innings][bowlerID][0] % 6);
}

void bowlerDetail(int innings)
{
    int i = 0;
    for (i = 0; i < bowlerNo[innings]; i++)
    {
        printf("\n Bowler %d : %s", i + 1, bowlers[innings][i]);
        printSpell(innings, i);
    }
}
void playerDetailTemplate(int innings)
{
    int i = 0;
    matchDetail();
    printf("\n Innings of : ");
    scanf("%s", inningsOf[innings]);
    printf("\n Batsmen 1 : ");
    scanf("%s", &batsmen[innings][0]);
    printf("\n Batsmen 2 : ");
    scanf("%s", &batsmen[innings][1]);
    batsmanNo[innings] = 2;
    printf("\n Bowler 1 : ");
    scanf("%s", &bowlers[innings][0]);
    bowlerNo[innings] = 1;
}

void addRun(int innings, int batsmanID, int run)
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

void countSpell(int innings, int bowlerID, int run)
{
    spells[innings][bowlerID][0]++;
    spells[innings][bowlerID][1] = spells[innings][bowlerID][1] + run;
}

void addNewBatsman(int innings, int batsmanID)
{
    batsmanNo[innings]++;
    printf("\n\n New Batsman Name : ");
    scanf("%s", &batsmen[innings][batsmanNo[innings] - 1]);
}

void addNewBowler(int innings, int bowlerID)
{
    bowlerNo[innings]++;
    printf("\n\n New Bowler Name : ");
    scanf("%s", &bowlers[innings][bowlerNo[innings] - 1]);
}
void scoreDetail(int innings)
{
    int outcome, temp = 0;
    int i, balls = 0;
    int strikerID = 0, nonStrikerID = 1, bowlerID = 0;
    int totalRuns = 0;
    if (innings == 0)
    {
        for (i = 0; i < overs * 6; i++)
        {
            system("cls");
            matchDetail();
            printf("\n Innings of %s", inningsOf[innings]);
            printf("\n\n");
            batsmenDetail(innings);
            printf("\n\n");
            bowlerDetail(innings);
            printf("\n ===============================================================================================");
            printf("\n Total Runs : %d/%d \t Overs : %d.%d", totalRuns, batsmanNo[innings] - 2, balls / 6, balls % 6);
            printf("\n\n Enter Current Ball Outcome (0,1,2,3,4,6,9 for wicket) : ");
            scanf("%d", &outcome);

            balls += 1;
            if (outcome == 9)
            {
                spells[innings][bowlerID][2]++;
                int maxBatID = strikerID > nonStrikerID ? strikerID : nonStrikerID;
                if (maxBatID < 11)
                {
                    addNewBatsman(innings, maxBatID + 1);
                    strikerID = maxBatID + 1;
                }
                else
                {
                    printf("\n Innings over.\nTotal Runs = %d", totalRuns);
                }
            }
            else
            {
                addRun(innings, strikerID, outcome);
                countSpell(innings, bowlerID, outcome);
                totalRuns += outcome;
            }
            //addRun(innings[inningsNumber - 1].strikerID, outcome);
            //printf("Current Innings of Batsman %d is : ",innings[inningsNumber-1].strikerID);
            //printRun(innings[inningsNumber-1].strikerID);
            if (outcome == 1 && balls % 6 != 0 || outcome == 3 && balls % 6 != 0)
            {
                temp = strikerID;
                strikerID = nonStrikerID;
                nonStrikerID = temp;
            }
            else if (outcome == 2 && balls % 6 == 0 || outcome == 4 && balls % 6 == 0 || outcome == 6 && balls % 6 == 0)
            {
                temp = strikerID;
                strikerID = nonStrikerID;
                nonStrikerID = temp;
            }
            if (balls % 6 == 0)
            {
                addNewBowler(innings, ++bowlerID);
            }
        }
        system("cls");
        matchDetail();
        printf("\n Innings of %s", inningsOf[innings]);
        printf("\n\n");
        batsmenDetail(innings);
        printf("\n\n");
        bowlerDetail(innings);
        printf("\n ===============================================================================================");
        printf("\n Total Runs : %d/%d \t Overs : %d.%d", totalRuns, batsmanNo[innings] - 2, balls / 6, balls % 6);
        totalFirstInnings = totalRuns;
    }

    else
    {
        for (i = 0; i < overs * 6 && totalRuns <= totalFirstInnings; i++)
        {
            system("cls");
            matchDetail();
            printf("\n Innings of %s", inningsOf[innings]);
            printf("\n\n");
            batsmenDetail(innings);
            printf("\n\n");
            bowlerDetail(innings);
            printf("\n ===============================================================================================");
            printf("\n Total Runs : %d/%d \t Overs : %d.%d", totalRuns, batsmanNo[innings] - 2, balls / 6, balls % 6);
            printf("\n To win : %d from %d Balls", totalFirstInnings - totalRuns, overs * 6 - balls);
            printf("\n\n Enter Current Ball Outcome (0,1,2,3,4,6,9 for wicket) : ");
            scanf("%d", &outcome);

            balls += 1;
            if (outcome == 9)
            {
                spells[innings][bowlerID][2]++;
                int maxBatID = strikerID > nonStrikerID ? strikerID : nonStrikerID;
                if (maxBatID < 11)
                {
                    addNewBatsman(innings, maxBatID + 1);
                    strikerID = maxBatID + 1;
                }
                else
                {
                    printf("\n Innings over.\nTotal Runs = %d", totalRuns);
                }
            }
            else
            {
                addRun(innings, strikerID, outcome);
                countSpell(innings, bowlerID, outcome);
                totalRuns += outcome;
            }
            //addRun(innings[inningsNumber - 1].strikerID, outcome);
            //printf("Current Innings of Batsman %d is : ",innings[inningsNumber-1].strikerID);
            //printRun(innings[inningsNumber-1].strikerID);
            if (outcome == 1 && balls % 6 != 0 || outcome == 3 && balls % 6 != 0)
            {
                temp = strikerID;
                strikerID = nonStrikerID;
                nonStrikerID = temp;
            }
            else if (outcome == 2 && balls % 6 == 0 || outcome == 4 && balls % 6 == 0 || outcome == 6 && balls % 6 == 0)
            {
                temp = strikerID;
                strikerID = nonStrikerID;
                nonStrikerID = temp;
            }
            if (balls % 6 == 0)
            {
                addNewBowler(innings, ++bowlerID);
            }
        }
        system("cls");
        matchDetail();
        printf("\n Innings of %s", inningsOf[innings]);
        printf("\n\n");
        batsmenDetail(innings);
        printf("\n\n");
        bowlerDetail(innings);
        printf("\n ===============================================================================================");
        printf("\n Total Runs : %d/%d \t Overs : %d.%d", totalRuns, batsmanNo[innings] - 2, balls / 6, balls % 6);
        //totalFirstInnings = totalRuns;
    }
    if (totalFirstInnings < totalRuns)
    {
        printf("\n\n %s wins the match", inningsOf[1]);
    }
    else if (totalFirstInnings > totalRuns)
    {
        printf("\n\n %s wins the match", inningsOf[0]);
    }
    else
    {
        printf("\n\n Match Tied");
    }
}
int main()
{
    int i, j;
    matchDetailTemplate();
    playerDetailTemplate(0);
    scoreDetail(0);
    playerDetailTemplate(1);
    scoreDetail(1);
    return (0);
}