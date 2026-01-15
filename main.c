// ECE 209, Spring 2025
// Simulator of Briscola Chiamata card game
// (1) User enters expression: <tricks> [<card>]x40 E, where <card> = <suit><value>
// (2) Print outcome of the game.

#include "briscola.h"

// cards owned
extern char suit[PLAYERS][CARDS_PER_PLAYER];
extern char rank[PLAYERS][CARDS_PER_PLAYER];

// lead player and partner
extern int lead;
extern int partner;

/* COMPLETE THE MAIN FUNCTION */
int main(void) {
    int turns[10] = {0, 1, 2, 3, 4, 0, 1, 2, 3};
    // the way the turns array works is it takes the winning cards posistion which will match up and loops 4 more times
    int trick = 0; // keeps count of tricks
    int numtrick; // scans for how many tricks are being asked for
    int team0score = 0; // keeps track of team scores
    int team1score = 0;
    char team0cards[200] = " "; // team card arrays and posistion in deck
    int team0deck = 1;
    char team1cards[200] = " ";
    int team1deck = 1;
    printf("Enter the number of tricks and the cards in the deck (terminated by 'E'):\n");
    scanf("%d", &numtrick); // scan for number of tricks
    deal_cards(); // our created deal card function
    char briscola = find_briscola(); // assigning our created find briscola function to have briscola
    int winner = lead; // winner starts as lead
    int winnercard; // used later for winner checks
    int first = turns[winner]; // uses the turn array to designate starting player posistion
    int middle1 = turns[first+1]; // depending on first person which is next player
    int middle2 = turns[middle1+1]; // same thing and so on
    int middle3 = turns[middle2+1];
    int last = turns[middle3+1];
    int firstwin; // which card did first player play
    int middle1win; // which card did first middle player play
    int middle2win; // which card did second middle player play
    int middle3win; // which card did third middle player play
    int lastwin; // which card did last player play
    // char space = " "; no longer used, was used to test code
    printf("briscola = %c, lead player = %d, partner = %d \n", briscola, lead, partner);
    while (trick != numtrick) { // keep loop going until tricks match how many tricks were asked
        firstwin = first_player_strategy(first, briscola); // designates first players card
        winner = first;
        winnercard = firstwin;
        
        middle1win = middle_player_strategy(middle1, first, suit[first][firstwin], rank[first][firstwin], briscola); // designates second players cards
        if (suit[winner][winnercard] == briscola) { // if the winning card is briscola
            if (suit[middle1][middle1win] == briscola) { // and second players card is briscola
                if (get_value(rank[middle1][middle1win]) > get_value(rank[winner][winnercard])) {
                    winner = middle1; // if the value of 2nd players briscola is greater they are new winner
                    winnercard = middle1win;
                }
            }
        }
        if (suit[winner][winnercard] != briscola) { // if winning card isn't briscola
            if (suit[middle1][middle1win] == briscola) {
                winner = middle1; // if the 2nd players card is briscola then they are the new winning card
                winnercard = middle1win;
            }
            if (suit[middle1][middle1win] == suit[winner][winnercard]) { // if they have the same suit as the winners card when winners card is not briscola
                if (get_value(rank[middle1][middle1win]) > get_value(rank[first][firstwin])) {
                    winner = middle1; // then whoever has the higher value card is the new winner
                    winnercard = middle1win;
                }
            }
        }

        middle2win = middle_player_strategy(middle2, winner, suit[winner][winnercard], rank[winner][winnercard], briscola); // designates third card played
        if (suit[winner][winnercard] == briscola) { // same if statement as before when briscola but for third turn taker and updated winner
            if (suit[middle2][middle2win] == briscola) {
                if (get_value(rank[middle2][middle2win]) > get_value(rank[winner][winnercard])) {
                    winner = middle2;
                    winnercard = middle2win;
                }
            }
        }
        if (suit[winner][winnercard] != briscola) { // same if statement as before when not briscola but for third turn taker and updated winner
            if (suit[middle2][middle2win] == briscola) {
                winner = middle2;
                winnercard = middle2win;
            }
            if (suit[middle2][middle2win] == suit[winner][winnercard]) {
                if (get_value(rank[middle2][middle2win]) > get_value(rank[winner][winnercard])) {
                    winner = middle2;
                    winnercard = middle2win;
                }
            }
        }
        
        middle3win = middle_player_strategy(middle3, winner, suit[winner][winnercard], rank[winner][winnercard], briscola); // designates fourth players played card
        if (suit[winner][winnercard] == briscola) { // same if statement as before when briscola but for fourth player and updated winner
            if (suit[middle3][middle3win] == briscola) {
                if (get_value(rank[middle3][middle3win]) > get_value(rank[winner][winnercard])) {
                    winner = middle3;
                    winnercard = middle3win;
                }
            }
        }
        if (suit[winner][winnercard] != briscola) { // same if statement as before when not briscola but for fourth player and updated winner
            if (suit[middle3][middle3win] == briscola) {
                winner = middle3;
                winnercard = middle3win;
            }
            if (suit[middle3][middle3win] == suit[winner][winnercard]) {
                if (get_value(rank[middle3][middle3win]) > get_value(rank[winner][winnercard])) {
                    winner = middle3;
                    winnercard = middle3win;
                }
            }
        }

        lastwin = last_player_strategy(last, winner, suit[winner][winnercard], rank[winner][winnercard], briscola); // designates the last turn or fifth players played card
        if (suit[winner][winnercard] == briscola) { // same if statement as before when not briscola but for fifth player and updated winner
            if (suit[last][lastwin] == briscola) {
                if (get_value(rank[last][lastwin]) > get_value(rank[winner][winnercard])) {
                    winner = last;
                    winnercard = lastwin;
                }
            }
        }
        if (suit[winner][winnercard] != briscola) { // same if statement as before but for when not briscola but for fifth player and updated winner
            if (suit[last][lastwin] == briscola) {
                winner = last;
                winnercard = lastwin;
            }
            if (suit[last][lastwin] == suit[winner][winnercard]) {
                if (get_value(rank[last][lastwin]) > get_value(rank[winner][winnercard])) {
                    winner = last;
                    winnercard = lastwin;
                }
            }
        }
        // print out the trick and cards played plus winner
        printf("trick %d:: cards played: [ %c%c %c%c %c%c %c%c %c%c ], winner: %d\n", trick, suit[first][firstwin], rank[first][firstwin], suit[middle1][middle1win], rank[middle1][middle1win], suit[middle2][middle2win], rank[middle2][middle2win], suit[middle3][middle3win], rank[middle3][middle3win], suit[last][lastwin], rank[last][lastwin], winner);

        if (winner == lead || winner == partner) { // this loop essentially goes through for the winner if they are team 0 and updates their point value and winning cards
            team0cards[team0deck] = suit[first][firstwin];
            ++team0deck;
            team0cards[team0deck] = rank[first][firstwin];
            team0score = team0score + get_value(rank[first][firstwin]);
            ++team0deck;
            team0cards[team0deck] = ' ';
            ++team0deck;
            team0cards[team0deck] = suit[middle1][middle1win];
            ++team0deck;
            team0cards[team0deck] = rank[middle1][middle1win];
            team0score = team0score + get_value(rank[middle1][middle1win]);
            ++team0deck;
            team0cards[team0deck] = ' ';
            ++team0deck;
            team0cards[team0deck] = suit[middle2][middle2win];
            ++team0deck;
            team0cards[team0deck] = rank[middle2][middle2win];
            team0score = team0score + get_value(rank[middle2][middle2win]);
            ++team0deck;
            team0cards[team0deck] = ' ';
            ++team0deck;
            team0cards[team0deck] = suit[middle3][middle3win];
            ++team0deck;
            team0cards[team0deck] = rank[middle3][middle3win];
            team0score = team0score + get_value(rank[middle3][middle3win]);
            ++team0deck;
            team0cards[team0deck] = ' ';
            ++team0deck;
            team0cards[team0deck] = suit[last][lastwin];
            ++team0deck;
            team0cards[team0deck] = rank[last][lastwin];
            team0score = team0score + get_value(rank[last][lastwin]);
            ++team0deck;
            team0cards[team0deck] = ' ';
            ++team0deck;
        }
        if (winner != lead && winner != partner) { // same thing but for team 1 when the winner is not lead or partner it updates their point value and winning cards
            team1cards[team1deck] = suit[first][firstwin];
            ++team1deck;
            team1cards[team1deck] = rank[first][firstwin];
            team1score = team1score + get_value(rank[first][firstwin]);
            ++team1deck;
            team1cards[team1deck] = ' ';
            ++team1deck;
            team1cards[team1deck] = suit[middle1][middle1win];
            ++team1deck;
            team1cards[team1deck] = rank[middle1][middle1win];
            team1score = team1score + get_value(rank[middle1][middle1win]);
            ++team1deck;
            team1cards[team1deck] = ' ';
            ++team1deck;
            team1cards[team1deck] = suit[middle2][middle2win];
            ++team1deck;
            team1cards[team1deck] = rank[middle2][middle2win];
            team1score = team1score + get_value(rank[middle2][middle2win]);
            ++team1deck;
            team1cards[team1deck] = ' ';
            ++team1deck;
            team1cards[team1deck] = suit[middle3][middle3win];
            ++team1deck;
            team1cards[team1deck] = rank[middle3][middle3win];
            team1score = team1score + get_value(rank[middle3][middle3win]);
            ++team1deck;
            team1cards[team1deck] = ' ';
            ++team1deck;
            team1cards[team1deck] = suit[last][lastwin];
            ++team1deck;
            team1cards[team1deck] = rank[last][lastwin];
            team1score = team1score + get_value(rank[last][lastwin]);
            ++team1deck;
            team1cards[team1deck] = ' ';
            ++team1deck;
        }
        suit[first][firstwin] = NULL; // these NULL statements are to erase the played card from this trick from the players deck
        rank[first][firstwin] = NULL;
        suit[middle1][middle1win] = NULL;
        rank[middle1][middle1win] = NULL;
        suit[middle2][middle2win] = NULL;
        rank[middle2][middle2win] = NULL;
        suit[middle3][middle3win] = NULL;
        rank[middle3][middle3win] = NULL;
        suit[last][lastwin] = NULL;
        rank[last][lastwin] = NULL;

        first = turns[winner]; // updates the first turn player as the winner
        middle1 = turns[first+1]; // updates the following turns using the winner or first player
        middle2 = turns[middle1+1];
        middle3 = turns[middle2+1];
        last = turns[middle3+1];
        ++trick; // updates to next trick
    }
    if (numtrick != 0) { // if tricks were played then print out team scores
        printf("team 0:: cards won: [%s], score: %d\n", team0cards, team0score);
        printf("team 1:: cards won: [%s], score: %d\n", team1cards, team1score);
    }
    return 0;
}
