void print_deck(int &pos1, card deck[], int &oppo1)//pos1 means the position of the left card
{
    if(oppo1==0) cout<<"You have used up all the opportunities to flip the deck!"<<endl;
    if(pos1>=1 && pos1<=14){
        printspace(2);
        printcard_up(2);
	printspace(3);
        printcard_up(2);
        cout << endl;
        printspace(2);
        printcard_mid(2, deck[pos1].suit, deck[pos1].num);
	printspace(3);
        printcard_mid(2, deck[pos1-1].suit, deck[pos1-1].num);
        cout << endl;
        printspace(2);
        printcard_bottom(2);
	printspace(3);
        printcard_bottom(2);  
	cout << endl;
    } 
    else if(pos1==0){
	printspace(2);
        printcard_up(2);
        cout << endl;
        printspace(2);
        printcard_mid(2, deck[0].suit, deck[0].num);
        cout << endl;
        printspace(2);
        printcard_bottom(2);
	cout << endl;
    }
    else{
	printspace(-2);
        printcard_up(2);
        cout << endl;
        printspace(-2);
        printcard_mid(2, deck[14].suit, deck[14].num);
        cout << endl;
        printspace(-2);
        printcard_bottom(2);
	cout << endl;
    }
    pos1++;
    if(pos1==16){
	pos1=0;
	oppo1--;
    }
    return;
}

}

//status 0--removed 1--exist 2--can be moved
