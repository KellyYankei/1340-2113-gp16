bool can_move(card pyramid[],card deck[])//this is a function to judge if any operations can be conducted after the opportunities of flipping the deck below is used up.
{
	bool judge1=0;
	for(int i=0;i<21;i++)
	{
		if(pyramid[i].status==2 && pyramid[i].num==9) return 1;
		for(int j=i+1;j<21;j++)
		{
			if(pyramid[i].status==2 && pyramid[j].status==2 && pyramid[i].num+pyramid[j].num==9) return 1;
		}
	}

//the lines below is unfinished. I tried to also judge the cards in the deck.	
/*	card deck2[20];
	num2=0;
	for(int i=0;i<15;i++) if(deck[i].status!=0) 
	{
		deck2[num2]=deck[i];
		num2++;
	}
	deck2[num2].suit=C;
	deck2[num2].num=100;
	deck2[num2].status=1;

	for(int i=0;i<num2;i++)
	{
		if(deck2[i].num+deck2[i+1].num==9) return 1;
		if(deck2[i].num==9) return 1;
		for(int j=0;j<21;j++)
		{
			if(pyramid[j].status==2 && pyramid[j].num)
		}
	}
	*/
	return 0;
}
