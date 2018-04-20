/* Card.h
 * This class defines a card in black jack
 */

#include <string>

class Card
{
    // name of the card
    string name;
    
    // holds the value
    int value;

    // Constructors
    Card();
    Card(string nm, int vl);

    /* int determine_value
     * this function will determine the value of a card if it can have more
     * than one value, such as an ace
     */
    int determine_value();
};
