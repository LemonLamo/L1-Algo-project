#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h> 

#define ANIMATION_DELAY 100000 // delay between characters in microseconds

// ANSI color codes
#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

struct team {
    char name[20];
    int score;
    int rank;
  
};

int num_teams() {
    int n;
    printf(CYAN "\t\t \t Enter the number of teams: " RESET);
    scanf("%d", &n);
    return n;
}

void name_teams(struct team teams[], int nbteams) {
    int i;
    printf("\n \t\t \t" CYAN "Enter the names of the teams:\n" RESET);
    for (i = 0; i < nbteams; i++) {
        printf(CYAN "Team %d: " RESET, i+1);
        scanf("%s", teams[i].name);
        teams[i].score = 0;
    }
}

// this function is supposed to ensure that the position of the teams get shuffled which means no 
//matches get repeated since the teams keep changing their position in the array i created
void shuffle(int *array, int n) {
	int i, j;
    for (i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

void match_simulator(struct team teams[], int nbteams, int num_days) {
    int i, j, k, team1_score, team2_score, first_team, second_team, score_choice, press;
    struct team X;
    srand(time(NULL));
    
    // creating a 2D array to keep track of pairs of teams that have already played against each other
    int played[nbteams][nbteams];
    for (i = 0; i < nbteams; i++) {
        for (j = 0; j < nbteams; j++) {
            played[i][j] = 0;
        }
    }
    
    printf("\n" YELLOW"Do you want to let the program randomize the scores or enter them manually?\n" RESET);
    printf ("\n Enter");
    printf( RED " 1 " RESET);
    printf("for randomization");
    printf ("\n Enter");
    printf( RED " 2 " RESET);
    printf("for manual input: \n");
    scanf("%d", &score_choice);

    if (score_choice == 1) {
        printf("\n" YELLOW "Simulating the matches...\n" RESET);
        for (k = 0; k < num_days; k++) {
            printf("\n" MAGENTA "Day %d matches:\n" RESET, k+1);

            // creating a randomized list of team indices for this day
    int team_indices[nbteams];
    for (i = 0; i < nbteams; i++) {
        team_indices[i] = i;
    }
    //shuffling that array so that positions change
    shuffle(team_indices, nbteams);

     // matching teams against their respective opponents
    for (i = 0; i < nbteams / 2; i++) {
        first_team = team_indices[i];
        second_team = team_indices[nbteams - 1- i];

        // checking if these teams have already played against each other
        while (played[first_team][second_team] == 1 || played[second_team][first_team] == 1) {
            shuffle(team_indices, nbteams);
            first_team = team_indices[i];
            second_team = team_indices[nbteams - 1-  i];
        }

        // marking these teams as having played against each other
        played[first_team][second_team] = 1;
        played[second_team][first_team] = 1;
                // scores randomization
                team1_score = rand() % 6;
                team2_score = rand() % 6;
                
                printf("%s [%d-%d] %s\n", teams[first_team].name, team1_score, team2_score, teams[second_team].name);

                // update scores based on match results
                if (team1_score > team2_score) {
                    teams[first_team].score += 3;
                } else if (team2_score > team1_score) {
                    teams[second_team].score += 3;
                } else if (team2_score == team1_score) {
                    teams[first_team].score += 1;
                    teams[second_team].score += 1;
                }
            }

            // sorting teams based on scores for this day
            for (i = 0; i < nbteams - 1; i++) {
                for (j = i + 1; j < nbteams; j++) {
                    if (teams[i].score < teams[j].score) {
                        // permutation between teams[i] et teams[j]
                        X = teams[i];
                        teams[i] = teams[j];
                        teams[j] = X;
                    }
                }
            }

            // assigning ranks based on scores for this day
            for (i = 0; i < nbteams; i++) {
                teams[i].rank = i + 1;
            }

            // prompt user to show results for this day
            printf("\nEnter 1 to show results for Day %d \n: ", k+1);
            scanf("%d", &press);
            if (press == 1) {
                // print results for this day
                printf("\n" MAGENTA "Day %d results:\n" RESET, k+1);
               // displaying results for this day
printf("\n" CYAN "Results for day %d:\n" RESET, k+1);
printf("+----------------------------------+--------+\n");
printf("| Team                             | Score |\n");
printf("+----------------------------------+--------+\n");
for (i = 0; i < nbteams; i++) {
printf("| %-32s| %6d |\n", teams[i].name, teams[i].score);
}
printf("+----------------------------------+--------+\n");
}
}
}


    else if (score_choice ==2) {
    	
     printf("\n" YELLOW "Manually inputing the scores...\n" RESET);
        for (k = 0; k < num_days; k++) {
            printf("\n" MAGENTA "Day %d matches:\n" RESET, k+1);

           
            // creating a randomized list of team indices for this day
    int team_indices[nbteams];
    for (i = 0; i < nbteams; i++) {
        team_indices[i] = i;
    }
    //shuffling that array so that positions change
    shuffle(team_indices, nbteams);

     // matching teams against their respective opponents
    for (i = 0; i < nbteams / 2; i++) {
        first_team = team_indices[i];
        second_team = team_indices[nbteams - 1- i];

        // checking if these teams have already played against each other
        while (played[first_team][second_team] == 1 || played[second_team][first_team] == 1) {
            shuffle(team_indices, nbteams);
            first_team = team_indices[i];
            second_team = team_indices[nbteams - 1-  i];
        }

        // marking these teams as having played against each other
        played[first_team][second_team] = 1;
        played[second_team][first_team] = 1;
               //manual input of the score
                    printf("Enter the score for %s:", teams[first_team].name);
                   scanf("%d", &team1_score);
                   printf("Enter the score for %s :", teams[second_team].name);
                    scanf("%d", &team2_score); 
                
                printf("%s [%d-%d] %s\n", teams[first_team].name, team1_score, team2_score, teams[second_team].name);

                // update scores based on match results
                if (team1_score > team2_score) {
                    teams[first_team].score += 3;
                } else if (team2_score > team1_score) {
                    teams[second_team].score += 3;
                } else if (team2_score == team1_score) {
                    teams[first_team].score += 1;
                    teams[second_team].score += 1;
                }
            }

            // sorting teams based on scores for this day
            for (i = 0; i < nbteams - 1; i++) {
                for (j = i + 1; j < nbteams; j++) {
                    if (teams[i].score < teams[j].score) {
                        // permutation between teams[i] et teams[j]
                        X = teams[i];
                        teams[i] = teams[j];
                        teams[j] = X;
                    }
                }
            }

            // assigning ranks based on scores for this day
            for (i = 0; i < nbteams; i++) {
                teams[i].rank = i + 1;
            }

            // prompt user to show results for this day
            printf("\nEnter 1 to show results for Day %d: ", k+1);
            scanf("%d", &press);
           if (press == 1) {
                // print results for this day
                printf("\n" MAGENTA "Day %d results:\n" RESET, k+1);
               // displaying results for this day
printf("\n" CYAN "Results for day %d:\n" RESET, k+1);
printf("+----------------------------------+--------+\n");
printf("| Team                             | Score |\n");
printf("+----------------------------------+--------+\n");
for (i = 0; i < nbteams; i++) {
printf("| %-32s| %6d |\n", teams[i].name, teams[i].score);
}
printf("+----------------------------------+--------+\n");
}
}
 } else  {
	  printf("\n" RED "Invalid choice, please try again.\n" RESET);
      match_simulator(teams, nbteams, num_days);
   }
}



void print_results(struct team teams[], int nbteams) {
    int i;
    printf("\n" YELLOW "+---------------------------------------+\n");
    printf("|           Final Results:               |\n");
    printf("+----+---------------------+------------+\n");
    printf("|Rank|        Name         |   Score    |\n");
    printf("+----+---------------------+------------+\n");
    for (i = 0; i < nbteams; i++) {
        printf("|%-4d|%-21s|%-12d|\n", teams[i].rank, teams[i].name, teams[i].score);
        printf("+----+---------------------+------------+\n");
    }
}


int main() {
    int nbteams, num_days;
    int terminal_width = 80;  // changing to match terminal width
    char message[] = "WELCOME TO THE CHAMPIONSHIP SIMULATOR !";
    int message_length = strlen(message);
    int padding_size = (terminal_width - message_length) / 2;
    int i, j;

    // displaying animation for message
    printf(YELLOW);
    for (i = 0; i < padding_size; i++) {
        printf(" ");
    }
    for (i = 0; i < message_length; i++) {
        printf("%c", message[i]);
        fflush(stdout);
        usleep(100000);  // wait for 0.1 seconds between each character
    }
    printf(RESET "\n\n");

    nbteams = num_teams();
    num_days = nbteams - 1;
    struct team teams[nbteams];
    name_teams(teams, nbteams);
    match_simulator(teams, nbteams, num_days);
    print_results(teams, nbteams);

    // asking the user if they want to reveal the winner
    printf("\nDo you want to reveal the winner(s)? (1 for yes, 0 for no): ");
    int choice;
    scanf("%d", &choice);

if (choice == 1) {
    // updating winning team based on highest score
    int max_score = teams[0].score;
    int winning_team_indices[nbteams];
    int num_winners = 0;
    for (i = 1; i < nbteams; i++) {
        if (teams[i].score > max_score) {
            max_score = teams[i].score;
        }
    }
    for (i = 0; i < nbteams; i++) {
        if (teams[i].score == max_score) {
            winning_team_indices[num_winners++] = i;
        }
    }

    // display animation for revealing the winner(s)
    char* message = "AND THE WINNER IIIS.... ";
    int message_length = strlen(message);
    for (i = 0; i < message_length; i++) {
        printf(CYAN"%c" RESET, message[i]);
        fflush(stdout);
        usleep(100000);  // wait for 0.1 seconds
    }

    for (i = 0; i < num_winners; i++) {
        printf("%s , CONGRATULATIONS TO ", teams[winning_team_indices[i]].name);
        fflush(stdout);
        int winner_length = strlen(teams[winning_team_indices[i]].name);
        for (j = 0; j < winner_length; j++) {
            printf("%c !", teams[winning_team_indices[i]].name[j]);
            fflush(stdout);
            usleep(100000);  // waiting for 0.1 seconds
        }        
        printf("\n");
         char message2[] = "This is a project made by Lamia Koucem.";
           int message2_length = strlen(message2);
           for (i = 0; i < message2_length; i++) {
        printf("%c", message2[i]);
        fflush(stdout);
        usleep(100000);  // wait for 0.1 seconds between each character
    }
      
    }
} else {
	printf("Okay then..");
}


    return 0;
}

