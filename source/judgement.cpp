#include<iostream>
#include "judgement.h"
#include "structures.h"
using namespace std;

//The function below is used to check if cards in pyramid can be eliminated. The input array will be changed to atore the newest status.
//Nothing will be returned by this function.
void set_status(card pyramid[])
{
	for (int i = 0; i < 21; i++){
                if (pyramid[i].status != 0)
                        pyramid[i].status = 1;
        }
	if( (pyramid[0].status==1) && (pyramid[1].status==0) && (pyramid[2].status==0) ) pyramid[0].status=2; 
	if( (pyramid[1].status==1) && (pyramid[3].status==0) && (pyramid[4].status==0) ) pyramid[1].status=2;
	if( (pyramid[2].status==1) && (pyramid[4].status==0) && (pyramid[5].status==0) ) pyramid[2].status=2;
	if( (pyramid[3].status==1) && (pyramid[6].status==0) && (pyramid[7].status==0) ) pyramid[3].status=2;
	if( (pyramid[4].status==1) && (pyramid[7].status==0) && (pyramid[8].status==0) ) pyramid[4].status=2;
	if( (pyramid[5].status==1) && (pyramid[8].status==0) && (pyramid[9].status==0) ) pyramid[5].status=2;
	if( (pyramid[6].status==1) && (pyramid[10].status==0) && (pyramid[11].status==0) ) pyramid[6].status=2;
	if( (pyramid[7].status==1) && (pyramid[11].status==0) && (pyramid[12].status==0) ) pyramid[7].status=2;
	if( (pyramid[8].status==1) && (pyramid[12].status==0) && (pyramid[13].status==0) ) pyramid[8].status=2;
	if( (pyramid[9].status==1) && (pyramid[13].status==0) && (pyramid[14].status==0) ) pyramid[9].status=2;
	if( (pyramid[10].status==1) && (pyramid[15].status==0) && (pyramid[16].status==0) ) pyramid[10].status=2;
	if( (pyramid[11].status==1) && (pyramid[16].status==0) && (pyramid[17].status==0) ) pyramid[11].status=2;
	if( (pyramid[12].status==1) && (pyramid[17].status==0) && (pyramid[18].status==0) ) pyramid[12].status=2;
	if( (pyramid[13].status==1) && (pyramid[18].status==0) && (pyramid[19].status==0) ) pyramid[13].status=2;
	if( (pyramid[14].status==1) && (pyramid[19].status==0) && (pyramid[20].status==0) ) pyramid[14].status=2;
	if( (pyramid[15].status==1) ) pyramid[15].status=2;
	if( (pyramid[16].status==1) ) pyramid[16].status=2;
	if( (pyramid[17].status==1) ) pyramid[17].status=2;
	if( (pyramid[18].status==1) ) pyramid[18].status=2;
	if( (pyramid[19].status==1) ) pyramid[19].status=2;
	if( (pyramid[20].status==1) ) pyramid[20].status=2;
	
	return;
}
//This function is used to detect if any elimination can be done after the opportunities to use the deck below is used up. The input is the arrays records all the cards.
bool can_move(card pyramid[])
{
	bool judge1 = 0;
	for (int i = 0; i < 21; i++)
	{
		if (pyramid[i].status == 2 && pyramid[i].num == 9) return 1;
		for (int j = i + 1; j < 21; j++)
		{
			if (pyramid[i].status == 2 && pyramid[j].status == 2 && pyramid[i].num + pyramid[j].num == 9) return 1;
		}
	}
	return 0;
}
