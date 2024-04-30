#include "structures.h"

//This is used to define the "==" operator for judging if 2 card variable are totally the same for convenience.
bool operator==(const card& card1, const card& card2) {  
	return (card1.suit == card2.suit && card1.num == card2.num && card1.status == card2.status);
}
