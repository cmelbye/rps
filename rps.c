//
//  main.c
//  RockPaperScissors
//
//  Created by Charlie Melbye on 1/17/13.
//  Copyright (c) 2013 Charlie Melbye. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rps.h"

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
    
    displayUsage();
    
    // Main game loop
    while (playing) {
        userChoice = getUserChoice();
        
        if (userChoice == CHOICE_QUIT) {
            finalGameCount = winCount + loseCount + tieCount;
            
            printf("\nYou played %s. You won %s, lost %s, and tied %s. Your win percentage is %.1lf%%.\n",
                   pluralize(finalGameCount, "game", "games"),
                   pluralize(winCount, "game", "games"),
                   pluralize(loseCount, "game", "games"),
                   pluralize(tieCount, "game", "games"),
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
    printf("Welcome to the dog-eat-dog world of Rock Paper Scissors.\n");
    printf("Type quit when you're ready to stop playing.\n");
    printf("Press any key to start.\n");
    getchar();
}

int getUserChoice()
{
    int i; // used in for statement
    char choice[81];
    
    int inputIsGood = 0;
    int userChoice = 0;
    
    printf("Rock, paper, or scissors? ");
    
    while (!inputIsGood) {
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
            printf("I don't understand your choice. Try again? ");
        }
    }
    
    return userChoice;
}

int didUserWin(int userChoice, int computerChoice)
{
    if((userChoice > computerChoice) || (userChoice == CHOICE_ROCK && computerChoice == CHOICE_SCISSORS))
    {
        // User wins.
        return RESULT_WIN;
    }
    else if(userChoice == computerChoice)
    {
        // It's a tie.
        return RESULT_TIE;
    }
    else
    {
        // The user loses (computer won).
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
            printf("Error generating computer choice, exiting.\n");
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
            printf("Unable to parse result code, exiting.\n");
            exit(1);
            break;
    }
}

double findWinPercentage(int winCount, int loseCount, int tieCount)
{
    return ((double)winCount / (winCount + loseCount + tieCount)) * 100;
}

const char * pluralize(int count, const char *singular, const char *plural)
{
    int numberOfDigits = 0;
    char *buffer;
    
    if (count > 0) {
        numberOfDigits = floor(log10(abs(count))) + 1; // From StackOverflow: http://bit.ly/aZuDzx
    }
    
    if (count == 1) {
        buffer = malloc(numberOfDigits + 1 + strlen(singular) + 1); // The number + a space + the singular + \0
        sprintf(buffer, "%d %s", count, singular);
    } else {
        buffer = malloc(numberOfDigits + 1 + strlen(plural) + 1); // The number + a space + the plural + \0
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
    
}
