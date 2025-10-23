#include<bits/stdc++.h>
using namespace std;

struct GameState{
	vector<vector<int>> board;
	bool whiteToMove;
	bool whiteCanCastleKingSide;
	bool whiteCanCastleQueenSide;
	bool blackCanCastleKingSide;
	bool blackCanCastleQueenSide;
};

void printBoard(const vector<vector<int>> &board){
    cout << "\n   a  b  c  d  e  f  g  h\n";
    cout << "  ------------------------\n";
    for(int i = 0; i < 8; i++){
	cout<<8-i<<" |";
	for(int j = 0; j < 8; j++){
		int piece = board[i][j];
		char symbol;
		switch (abs(piece)) {
			case 1: symbol = 'P'; break;  // Pawn
			case 2: symbol = 'N'; break;  // Knight
			case 3: symbol = 'B'; break;  // Bishop
			case 4: symbol = 'R'; break;  // Rook
			case 5: symbol = 'Q'; break;  // Queen
			case 6: symbol = 'K'; break;  // King
			default: symbol = '.';        // Empty
	    	}
		//use black peices in lower case and white pieces in upper case
		if(piece < 0) symbol = tolower(symbol);
		cout<<" "<<symbol<<" ";
	}
	cout<<"| "<<8-i<<endl;
    }
    cout << "  ------------------------\n";
    cout << "   a  b  c  d  e  f  g  h\n\n";
}

int main(){
	vector<vector<int>> board = {
	    {-4,-2,-3,-5,-6,-3,-2,-4},
	    {-1,-1,-1,-1,-1,-1,-1,-1},
	    { 0, 0, 0, 0, 0, 0, 0, 0},
	    { 0, 0, 0, 0, 0, 0, 0, 0},
	    { 0, 0, 0, 0, 0, 0, 0, 0},
	    { 0, 0, 0, 0, 0, 0, 0, 0},
	    { 1, 1, 1, 1, 1, 1, 1, 1},
	    { 4, 2, 3, 5, 6, 3, 2, 4}
	};
	/* 
	 *Empty	0
	Pawn	1
	Knight	2
	Bishop	3
	Rook	4
	Queen	5
	King	6
	We make white pieces positive and black pieces negative
	 * */
	printBoard(board);
	return 0;	
}
