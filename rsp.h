/*
 *  rsp.h
 *  RockPaperScissors
 *
 *  Created by Charlie Melbye on 1/17/13.
 */

#define CHOICE_ROCK     100
#define CHOICE_PAPER    101
#define CHOICE_SCISSORS 102
#define CHOICE_QUIT     103

#define RESULT_WIN  100
#define RESULT_LOSE 101
#define RESULT_TIE  102

void displayUsage();
int getUserChoice();
int didUserWin(int userChoice, int computerChoice);
int getComputerChoice();
void displayComputerChoice(int computerChoice);
void displayRoundResult(int resultCode);
double findWinPercentage(int winCount, int loseCount, int tieCount);
const char * pluralize(int count, const char *plural, const char *singular);
char *fgets_wrapper(char *buffer, int buflen, FILE *fp);
void test_cases(void);