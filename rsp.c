/*
 *  rsp.c
 *  RockPaperScissors
 *
 *  Created by Charlie Melbye on 1/17/13.
 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "checkit.h"

#include "rsp.h"

int main(int argc, const char * argv[])
{
    int playing = 1;
    int userChoice = 0;
    int computerChoice = 0;
    int roundResult = 0;
    
    int winCount = 0;
    int loseCount = 0;
    int tieCount = 0;
    
    int finalGameCount = 0;
    
    srand((unsigned int) time(0));
    
    test_cases();

    displayUsage();
    
    /* Main game loop */
    while (playing) {
        userChoice = getUserChoice();
        
        if (userChoice == CHOICE_QUIT) {
            finalGameCount = winCount + loseCount + tieCount;
            
            printf("\nWe played %s. You won %s, lost %s, and tied %s.\n",
                   pluralize(finalGameCount, "game", "games"),
                   pluralize(winCount, "game", "games"),
                   pluralize(loseCount, "game", "games"),
                   pluralize(tieCount, "game", "games"));
            
            printf("Your win percentage was %.1f%%.\n",
                   findWinPercentage(winCount, loseCount, tieCount));
            
            return 0;
        }
        
        computerChoice = getComputerChoice();
        
        displayComputerChoice(computerChoice);
        
        roundResult = didUserWin(userChoice, computerChoice);
        
        displayRoundResult(roundResult);
        
        switch (roundResult) {
            case RESULT_WIN:
                winCount++;
                break;
            case RESULT_LOSE:
                loseCount++;
                break;
            case RESULT_TIE:
                tieCount++;
                break;
            default:
                break;
        }
    }
    
    return 0;
}

void displayUsage()
{
    printf("Welcome to Rock Paper Scissors.\n");
    printf("Type \"rock\", \"paper\", or \"scissors\" to choose your move.\n");
    printf("Type \"quit\" when you're ready to stop playing.\n\n");
}

int getUserChoice()
{
    int i; /* used in for statement */
    char choice[81];
    
    int inputIsGood = 0;
    int userChoice = 0;

    while (!inputIsGood) {
        printf("Rock, paper, or scissors? ");
        fgets_wrapper(choice, 81, stdin);
        
        /*
         * BEGIN Lowercase code from StackOverflow user Earlz
         * http://stackoverflow.com/questions/2661766/c-convert-a-mixed-case-string-to-all-lower-case
         */
        for(i = 0; choice[i]; i++){
            choice[i] = tolower(choice[i]);
        }
        /* END Lowercase code */
        
        if ((strcmp(choice, "rock") == 0) || (strcmp(choice, "r") == 0)) {
            userChoice = CHOICE_ROCK;
            inputIsGood = 1;
        } else if ((strcmp(choice, "paper") == 0) || (strcmp(choice, "p") == 0)) {
            userChoice = CHOICE_PAPER;
            inputIsGood = 1;
        } else if ((strcmp(choice, "scissors") == 0) || (strcmp(choice, "s") == 0)) {
            userChoice = CHOICE_SCISSORS;
            inputIsGood = 1;
        } else if ((strcmp(choice, "quit") == 0) || (strcmp(choice, "exit") == 0) || (strcmp(choice, "q") == 0) || (strcmp(choice, "e") == 0)) {
            userChoice = CHOICE_QUIT;
            inputIsGood = 1;
        } else {
            printf("I don't understand your choice.\n\n");
        }
    }
    
    return userChoice;
}

int didUserWin(int userChoice, int computerChoice)
{
    if(!(userChoice == CHOICE_SCISSORS && computerChoice == CHOICE_ROCK) &&
        ((userChoice > computerChoice) ||
            (userChoice == CHOICE_ROCK && computerChoice == CHOICE_SCISSORS)))
    {
        /* User wins. */
        return RESULT_WIN;
    }
    else if(userChoice == computerChoice)
    {
        /* It's a tie. */
        return RESULT_TIE;
    }
    else
    {
        /* The user loses (computer won). */
        return RESULT_LOSE;
    }
}

int getComputerChoice()
{
    switch (rand() % 3) {
        case 0:
            return CHOICE_ROCK;
            break;
        case 1:
            return CHOICE_PAPER;
            break;
        case 2:
            return CHOICE_SCISSORS;
            break;
        default:
            printf("ERROR: Error generating computer choice, exiting.\n");
            exit(1);
            break;
    }
}

void displayComputerChoice(int computerChoice)
{
    switch (computerChoice) {
        case CHOICE_ROCK:
            printf("I pick rock.\n");
            break;
        case CHOICE_PAPER:
            printf("I pick paper.\n");
            break;
        case CHOICE_SCISSORS:
            printf("I pick scissors.\n");
            break;
        default:
            break;
    }
}

void displayRoundResult(int resultCode)
{
    switch (resultCode) {
        case RESULT_WIN:
            printf("You win, but if we play again, you won't be as lucky...\n\n");
            break;
        case RESULT_LOSE:
            printf("I win! You lose! Quit while you're ahead.\n\n");
            break;
        case RESULT_TIE:
            printf("Well, we tied. Let's play again!\n\n");
            break;
        default:
            break;
    }
}

double findWinPercentage(int winCount, int loseCount, int tieCount)
{
    int totalRoundCount = 0;

    totalRoundCount = winCount + loseCount + tieCount;

    if (totalRoundCount == 0)
    {
        return 0;
    }

    return ((double)winCount / totalRoundCount) * 100;
}

const char * pluralize(int count, const char *singular, const char *plural)
{
    int numberOfDigits = 0;
    char *buffer;
    
    if (count > 0) {
        numberOfDigits = floor(log10(abs(count))) + 1; /* From StackOverflow: http://bit.ly/aZuDzx */
    }
    
    if (count == 1) {
        buffer = malloc(numberOfDigits + 1 + strlen(singular) + 1); /* The number + a space + the singular + \0 */
        sprintf(buffer, "%d %s", count, singular);
    } else {
        buffer = malloc(numberOfDigits + 1 + strlen(plural) + 1); /* The number + a space + the plural + \0 */
        sprintf(buffer, "%d %s", count, plural);
    }
    
    return buffer;
}

/*
 * By StackOverflow user Jonathan Leffler.
 * http://stackoverflow.com/questions/4309746/safe-alternative-to-gets
 *
 * This function is a wrapper around fgets to make it act more like gets, in
 * that it does not include a newline at the end of the line it's reading.
 */

char *fgets_wrapper(char *buffer, int buflen, FILE *fp)
{
    if (fgets(buffer, buflen, fp) != 0)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n')
            buffer[len-1] = '\0';
        return buffer;
    }
    return 0;
}

/* END fgets_wrapper code */

void test_cases(void)
{
    /* Test didUserWin() */
    checkit_int(didUserWin(CHOICE_ROCK, CHOICE_ROCK), RESULT_TIE);
    checkit_int(didUserWin(CHOICE_ROCK, CHOICE_PAPER), RESULT_LOSE);
    checkit_int(didUserWin(CHOICE_ROCK, CHOICE_SCISSORS), RESULT_WIN);

    checkit_int(didUserWin(CHOICE_PAPER, CHOICE_ROCK), RESULT_WIN);
    checkit_int(didUserWin(CHOICE_PAPER, CHOICE_PAPER), RESULT_TIE);
    checkit_int(didUserWin(CHOICE_PAPER, CHOICE_SCISSORS), RESULT_LOSE);

    checkit_int(didUserWin(CHOICE_SCISSORS, CHOICE_ROCK), RESULT_LOSE);
    checkit_int(didUserWin(CHOICE_SCISSORS, CHOICE_PAPER), RESULT_WIN);
    checkit_int(didUserWin(CHOICE_SCISSORS, CHOICE_SCISSORS), RESULT_TIE);

    /* Test findWinPercentage() */
    checkit_double(findWinPercentage(2, 4, 1), 28.571428);
    checkit_double(findWinPercentage(0, 0, 0), 0.0);
    checkit_double(findWinPercentage(6, 0, 0), 100.0);
    checkit_double(findWinPercentage(2, 2, 2), 33.333333);
}
