/* Deck.h
 * This class defines the deck and the ways it can interact with players and 
 * cards
 */

#include "card.h"
#include <vector>

using namespace std;

class Deck
{
    int decksize;
    vector<Card> deck;

    public:

        //Constructor
        Deck();

        /* vector<Card> *generate
         * This function generates the 52 cards in the deck
         */
        vector<Card> *generate();

        /* Card deal
         * This function handles dealing cards
}
