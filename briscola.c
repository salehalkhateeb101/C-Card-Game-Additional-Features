#include "briscola.h"

/* cards owned by the players
 * E.g. The suit and rank of the third card of the second players are stored in:
 *      suit[1][2] and rank[1][2]
 * NOTE: to indicate that a card has been played (and is unavailable) assign value '\0' to the corresponding suit.
 */
char suit[PLAYERS][CARDS_PER_PLAYER];
char rank[PLAYERS][CARDS_PER_PLAYER];

int lead;    // lead player
int partner; // partner (i.e., teammate of lead player)

/**********************************************************/
/*         HELPER FUNCTIONS DECLARATION                   */
/**********************************************************/

/* returns true if players p1 and p2 are teammates,
 * and false otherwise */
bool teammates(int p1, int p2);

/* returns the highest-ranked card of a given player, where:
 * - suit = target_suit if equal = true
 * - suit <> target_suit if equal = false
 * The value returned is the index of the card within suit[player]/rank[player]
 * If such a card is unavailable, it returns -1.
 * If target_suit == 0, it returns the highest-ranked card of player (independent of the suit).
 * In this case, the value of equal is irrelevant.
 */
int find_max(int player, char target_suit, bool equal);

/* returns the lowest-ranked card of a given player, where:
 * - suit = target_suit if equal = true
 * - suit <> target_suit if equal = false
 * The value returned is the index of the card within suit[player]/rank[player]
 * If such a card is unavailable, it returns -1.
 * If target_suit == 0, it returns the lowest-ranked card of player (independent of the suit).
 * In this case, the value of equal is irrelevant.
 */
int find_min(int player, char target_suit, bool equal);

/*  returns a card of a given player with suit=target_suit,
 *  and rank equal to the lowest rank available greater than target_rank.
 *  The value returned is the index of the card within suit[player]/rank[player]
 *  If such card is not available, returns -1
 */
int find_relative_min(int player, char target_suit, char target_rank);

/**********************************************************/
/*         HELPER FUNCTIONS DEFINITION                    */
/**********************************************************/

char get_value(char rank) {
    if (rank == 'J')
        return 8;
    if (rank == 'Q')
        return 9;
    if (rank == 'K')
        return 10;
    if (rank == 'A')
        return 11;
    return (rank - '0');
}

bool teammates(int p1, int p2) {
    if ((p1 == lead && p2 == partner) || (p1 == partner && p2 == lead))
        return true;
    if (p1 == lead || p1 == partner || p2 == lead || p2 == partner)
        return false;
    return true;
}

int find_max(int player, char target_suit, bool equal) {
    int index = -1;
    for (int i = 0; i < CARDS_PER_PLAYER; i++) {
        if (suit[player][i]!=0 && (target_suit == 0 || (equal && suit[player][i]==target_suit) || (!equal && suit[player][i]!=target_suit))) {
            if (index == -1 || get_value(rank[player][i]) > get_value(rank[player][index]))
                index = i;
        }
    }
    return index;
}

int find_min(int player, char target_suit, bool equal) {
    int index = -1;
    for (int i = 0; i < CARDS_PER_PLAYER; i++) {
        if (suit[player][i]!=0 && (target_suit == 0 || (equal && suit[player][i]==target_suit) || (!equal && suit[player][i]!=target_suit))) {
            if (index == -1 || get_value(rank[player][i]) < get_value(rank[player][index]))
                index = i;
        }
    }
    return index;
}

int find_relative_min(int player, char target_suit, char target_rank) {
    int index = -1;
    for (int i = 0; i < CARDS_PER_PLAYER; i++) {
        if (suit[player][i]!=0 && (suit[player][i]==target_suit) && (get_value(rank[player][i]) > get_value(target_rank))) {
            if (index == -1 || get_value(rank[player][i]) < get_value(rank[player][index]))
                index = i;
        }
    }
    return index;
}

/**********************************************************/
/*         CORE   FUNCTIONS                               */
/**********************************************************/

/* COMPLETE THESE FUNCTIONS */

void deal_cards() {
    char userInput[200] = "";
    // userInput used to scanf through the code
    int i=0;
    int m=0; // keeps track of which card number
    int count=8;
    // count designated for the 8 cards per player
    while (userInput[i] != 'E') { // till it reaches end of deck
        scanf("%s", userInput);
        if (userInput[i] == 'E') {
            break; // break whenever it gets to E check
        }
        suit[0][m] = userInput[i];
        rank[0][m] = userInput[i+1]; // give cards to player0
        
        scanf("%s", userInput);
        if (userInput[i] == 'E') {
            break; // another E check
        }
        suit[1][m] = userInput[i];
        rank[1][m] = userInput[i+1]; // give cards to player1

        scanf("%s", userInput);
        if (userInput[i] == 'E') {
            break; // another E check
        }
        suit[2][m] = userInput[i];
        rank[2][m] = userInput[i+1]; // give cards to player2

        scanf("%s", userInput);
        if (userInput[i] == 'E') {
            break; // another E check
        }
        suit[3][m] = userInput[i];
        rank[3][m] = userInput[i+1]; // give cards to player3

        scanf("%s", userInput);
        if (userInput[i] == 'E') {
            break; // another E check
        }
        suit[4][m] = userInput[i];
        rank[4][m] = userInput[i+1]; // give cards to player4
        ++m;
    }
    printf("player 0:: ");
    while (count != 0) { // sets up a loop that prints all 8 cards in a row of the player0
        printf("%c%c ", suit[0][i], rank[0][i]);
        ++i;
        --count;
    }
    printf("\n"); // set a new line
    i=0;
    count=8; // reset the count to 8 for 8 cards
    printf("player 1:: ");
    while (count != 0) { // repeat same loop for player1
        printf("%c%c ", suit[1][i], rank[1][i]);
        ++i;
        --count;
    }
    printf("\n");
    i=0;
    count=8;
    printf("player 2:: ");
    while (count != 0) { // repeat same loop for player2
        printf("%c%c ", suit[2][i], rank[2][i]);
        ++i;
        --count;
    }
    printf("\n");
    i=0;
    count=8;
    printf("player 3:: ");
    while (count != 0) { // repeat same loop for player3
        printf("%c%c ", suit[3][i], rank[3][i]);
        ++i;
        --count;
    }
    printf("\n");
    i=0;
    count=8;
    printf("player 4:: ");
    while (count != 0) { // repeat same loop for player 4
        printf("%c%c ", suit[4][i], rank[4][i]);
        ++i;
        --count;
    }
    printf("\n");
}

char find_briscola() {
    int counter = 0;
    int clubsmax = 0;
    int diamondsmax = 0;
    int heartsmax = 0;
    int spadesmax = 0;
    char briscolamax[6];
    int playermax[6];
    int battle = 0;
    char briscola;
    int check;
    int checkpoint = 0;
    int m = 2;
    int tempfix;
    while (counter != 5) { // counter is at 5 to loop through player count
        for (int i=0; i < 8; ++i) {
            tempfix = get_value(rank[counter][i]); // gets value of card
            if (suit[counter][i] == 'C') {
                clubsmax = clubsmax + tempfix; // adds that specific value to clubs if it is club
            }
            if (suit[counter][i] == 'D') { // adds specific value to diamonds if diamond
                diamondsmax = diamondsmax + tempfix;
            }
            if (suit[counter][i] == 'H') { // adds specific value to hearts if heart
                heartsmax = heartsmax + tempfix;
            }
            if (suit[counter][i] == 'S') { // adds specific value to spades if spade
                spadesmax = spadesmax + tempfix;
            }
        } // this loop essentially tallies an individual players count for each suit which then below will decide what is the highest suit of that player
        playermax[counter] = clubsmax;
        briscolamax[counter] = 'C'; // this sets a starting comparison value
        if (playermax[counter] < diamondsmax) {
            playermax[counter] = diamondsmax; // compares with diamonds to see if that is their briscola canidate
            briscolamax[counter] = 'D';
        }
        if (playermax[counter] < heartsmax) {
            playermax[counter] = heartsmax; // compares with hearts to see if that is thier briscola canidate
            briscolamax[counter] = 'H';
        }
        if (playermax[counter] < spadesmax) {
            playermax[counter] = spadesmax; // compares with spades to see if taht is their briscola canidate
            briscolamax[counter] = 'S';
        }
        clubsmax = 0; // reset the suit checks for next player
        diamondsmax = 0; // value of players max is already stored in the loop via playermax and briscolamax
        heartsmax = 0;
        spadesmax = 0;
        ++counter; // next player
    }
    for (int i=0; i < 5; ++i) {
        if (battle < playermax[i]) {
            battle = playermax[i];
            lead = i;
        }
    } // loops through the players to decide who has the highest briscola canidate and designates them as lead
    briscola = briscolamax[lead]; // takes lead and what their briscola canidate was to be briscola
    
    // Below is finding the partner
    counter = 0;
    tempfix = 0;
    while (counter < 9) { // loops through cards to find the smallest missing card for the specific briscola
        for (int i=0; i < 8; ++i) {
            if (suit[lead][i] == briscola) {
                tempfix = tempfix + 1; // gets a count of their briscola cards
            }
            check = get_value(rank[lead][i]);
            if (suit[lead][i] == briscola && check != m) {
                ++checkpoint; // checks cards in increment from 0-K to check for the smallest value it doesnt have
            }
        }
        if (checkpoint == tempfix) {
            break; // get out of loop 
        }
        ++m;
        checkpoint = 0;
        tempfix = 0;
        ++counter;
    }
    counter = 0;
    checkpoint = 0;
    tempfix = 0; // when the loop above is done the smallest card amount is designated in m
    while (counter != 5) { // go through all players
        for (int i=0; i < 8; ++i) { // go through entire deck of player
            tempfix = get_value(rank[counter][i]);
            if (suit[counter][i] == briscola && tempfix == m) {
                partner = counter; // compare to see who has card m that is briscola and whoever has it is partner
            }
        }
        ++counter;
    }
    return briscola;
}

int first_player_strategy(int player, char briscola) {
    int check;
    check = find_min(player, briscola, false); // player looks for lowest ranked non briscola card
    if (check != -1) {
        return check;
    }
    if (check == -1) { // if they don't have that specific card then look for lowest ranked card in hand
        check = find_min(player, 0, true);
        return check;
    }

}

int middle_player_strategy(int player, int winner, char win_suit, char win_rank, char briscola) {
    int check2;
    if (win_suit == briscola) { // if the winning suit is briscola
        if (teammates(winner, player) == true) { // and they are teammates with winner
            // printf("These players are teammates.\n"); Just a check for code
            check2 = find_max(player, briscola, false); // then find the max card that isn't briscola in their deck
            if (check2 != -1) {
                return check2;
            }
        }
        if (teammates(player, winner) == false) { // and they are not teammates with winner
            check2 = find_relative_min(player, briscola, win_rank); // find the lowest ranked briscola that outranks the winners card
            if (check2 != -1) {
                return check2;
            }
        }
    }
    if (win_suit != briscola) { // if the winning card is not briscola
        check2 = find_min(player, briscola, true); // play the minimum briscola card in deck
        if (check2 != -1) {
            return check2;
        }
    }
    if (check2 == -1) { // if none of the conditions above work
        check2 = find_min(player, briscola, false); // find the minimum ranked non-briscola card to play
        if (check2 != -1) {
            return check2;
        }
        if (check2 == -1) {
            check2 = find_min(player, briscola, true); // if none find the minimum briscola card to play
            return check2;
        }
    }
}

int last_player_strategy(int player, int winner, char win_suit, char win_rank, char briscola) {
    int check3;
    if (teammates(player, winner) == true) { // if they are teammates
        // printf("these guys are teammates.\n"); Just a code check
        check3 = find_max(player, briscola, false); // find the highest ranked non briscola card
        if (check3 != -1) {
            // printf("checkpoint 1\n"); Just a code check
            return check3;
        }
        if (check3 == -1) {
            check3 = find_min(player, briscola, true); // If none find the smallest ranked briscola card to play
            // printf("checkpoint 2\n"); Just a code check
            return check3;
        }
    }
    if (teammates(player, winner) == false) { // if they are not teammates
        if (win_suit != briscola) { // and the card is not briscola
            check3 = find_max(player, win_suit, true); // take the biggest card that is of the same winning suit
            if (get_value(rank[player][check3]) < get_value(win_rank)) { // if it is less than the winning cards rank
                check3 = find_relative_min(player, win_suit, win_rank); // find the lowest rank card of that winning suit that outranks that card
                if (check3 != -1) {
                    return check3;
                }
            }
            if (check3 != -1) {
                return check3;
            }
            if (check3 == -1) {
                check3 = find_min(player, briscola, true); // find the lowest ranked briscola card if the above conditions are not met
                if (check3 != -1) {
                    return check3;
                }
            }
        }
        if (win_suit == briscola) { // if the win suit is briscola
            check3 = find_relative_min(player, briscola, win_rank); // find the lowest ranking briscola card that outranks the winning card
            if (check3 != -1) {
                return check3;
            }
        }
        if (check3 == -1) {
            check3 = find_min(player, briscola, false); // if no conditions are met find the minimum non ranked briscola card
            if (check3 != -1) {
                return check3;
            }
            if (check3 == -1) {
                check3 = find_min(player, briscola, true); // if only briscola cards find the smallest one to play
                return check3;
            }
        }
    }
}


