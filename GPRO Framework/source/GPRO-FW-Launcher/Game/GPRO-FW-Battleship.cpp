
#include <stdio.h>
#include <ctime>
#include <iostream>
using namespace std;


//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_BATTLESHIP_PLAYERS				2
#define GS_BATTLESHIP_BOARD_WIDTH			10
#define GS_BATTLESHIP_BOARD_HEIGHT			10

enum gs_battleship_space_state
{
	// invalid space state
	gs_battleship_space_invalid = -1,

	// states visible to both players
	gs_battleship_space_open,			// space is open and unguessed
	gs_battleship_space_miss,			// space was guessed and missed
	gs_battleship_space_hit,			// space was guessed and hit

	// states hidden from opponent player
	gs_battleship_space_patrol2,		// 2-unit patrol boat
	gs_battleship_space_submarine3,		// 3-unit submarine
	gs_battleship_space_destroyer3,		// 3-unit destroyer
	gs_battleship_space_battleship4,	// 4-unit battleship
	gs_battleship_space_carrier5,		// 5-unit carrier
};
#ifndef __cplusplus
typedef		enum gs_battleship_space_state	gs_battleship_space_state;
#endif	// !__cplusplus

// battleship game state
typedef		unsigned char					gs_battleship_index;
typedef		gs_battleship_space_state		gs_battleship[GS_BATTLESHIP_PLAYERS][GS_BATTLESHIP_BOARD_WIDTH][GS_BATTLESHIP_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,z,w,h,d)		(x < w && y < h && z < d)
#define GS_BATTLESHIP_VALID(p,x,y)				GS_VALIDATE_COORDINATE(x,y,p,GS_BATTLESHIP_BOARD_WIDTH,GS_BATTLESHIP_BOARD_HEIGHT,GS_BATTLESHIP_PLAYERS)


inline gs_battleship_space_state gs_battleship_getSpaceState(gs_battleship const game, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos]);
	return gs_battleship_space_invalid;
}

inline gs_battleship_space_state gs_battleship_setSpaceState(gs_battleship game, gs_battleship_space_state const state, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos] = state);
	return gs_battleship_space_invalid;
}

inline gs_battleship_index gs_battleship_reset(gs_battleship game)
{
	gs_battleship_index player, xpos, ypos, total;
	for (player = 0; player < GS_BATTLESHIP_PLAYERS; ++player)
		for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos)
			for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos)
				game[player][xpos][ypos] = gs_battleship_space_open;
	total = (player * xpos * ypos);
	return total;
}


//-----------------------------------------------------------------------------
// DEFINITIONS


//couts board by line
void drawBoard(gs_battleship game, int player)
{
	cout << "  0|1|2|3|4|5|6|7|8|9|" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << " ";
		for (int j = 0; j < 10; j++)
		{
			cout << gs_battleship_getSpaceState(game, player, i, j) << "|";
		}
		cout << "\n  --------------------" << endl;
	}

}

//
void setUpGame(gs_battleship game, int player)
{
	char shipToBePlaced;
	int column, row;

	srand(time(NULL));
	/*
	for (int i = 0; i < 5; i++)
	{
		int shipX, shipY;
		shipX = rand() % 9 + 1;
		gs_battleship_setSpaceState(game, gs_battleship_space_patrol2, 0, shipX, shipY);
		gs_battleship_setSpaceState(game, gs_battleship_space_patrol2, 0, shipX + 1, shipY + 1);
	}

	
	cout << "What ship would you like to place, (P)atrol, (S)ubmarine, (D)estroyer, (B)attleship, (C)arrier?:";
	cin >> shipToBePlaced;
	cout << "Enter the spots to be taken by your ships";

	switch (shipToBePlaced)
	{
	case 'P':
		for (int i = 0; i < 2; i++)
		{
			cout << "Enter a column: ";
			cin >> column;
			cin.ignore();
			cout << "Enter a row: ";
			cin >> row;
			gs_battleship_setSpaceState(game, gs_battleship_space_patrol2, player, column, row);
		}
		break;
	case 'S':
		for (int i = 0; i < 3; i++)
		{
			cout << "Enter a column: ";
			cin >> column;
			cin.ignore();
			cout << "Enter a row: ";
			cin >> row;
			gs_battleship_setSpaceState(game, gs_battleship_space_submarine3, player, column, row);
		}
		break;
	case 'D':
		for (int i = 0; i < 3; i++)
		{
			cout << "Enter a column: ";
			cin >> column;
			cin.ignore();
			cout << "Enter a row: ";
			cin >> row;
			gs_battleship_setSpaceState(game, gs_battleship_space_destroyer3, player, column, row);
		}
		break;
	case 'B':
		for (int i = 0; i < 4; i++)
		{
			cout << "Enter a column: ";
			cin >> column;
			cin.ignore();
			cout << "Enter a row: ";
			cin >> row;
			gs_battleship_setSpaceState(game, gs_battleship_space_battleship4, player, column, row);
		}
		break;
	case 'C':
		for (int i = 0; i < 5; i++)
		{
			cout << "Enter a column: ";
			cin >> column;
			cin.ignore();
			cout << "Enter a row: ";
			cin >> row;
			gs_battleship_setSpaceState(game, gs_battleship_space_carrier5, player, column, row);
		}
		break;
		
	}*/
}

//player goes through a single turn
void playersTurn(gs_battleship game, int player)
{
	int column, row;
	cout << "Player " << player << " turn" << endl;//diaplsy player whos turn it is
	cout << "Enter a place to attack" << endl;

	//recieve attack coordinates
	cout << "Column: ";
	cin >> column;

	cout << "Row: ";
	cin >> row;

	//if , space is open, cout: miss, else: hit!
	if (gs_battleship_getSpaceState(game, player, column, row) == gs_battleship_space_open)
	{
		cout << "Miss" << endl;
		gs_battleship_setSpaceState(game, gs_battleship_space_miss, player, column, row);
	}
	else if (gs_battleship_getSpaceState(game, player, column, row) >= 1)
	{
		cout << "Hit!" << endl;
		gs_battleship_setSpaceState(game, gs_battleship_space_hit, player, column, row);
	}
}

int launchBattleship()
{
	gs_battleship game = { 0 };

	gs_battleship_reset(game);

	int column, row, player = 0;
	bool t = false, setup = true;

	while (t == false)
	{
		drawBoard(game, player);

		for(int i = 0; i < 10; i++)
		{
			if (i == 4)
			{
				player = 1;
			}
			setUpGame(game, player);
		}

		playersTurn(game, player);
	}
	return 0;
}


//-----------------------------------------------------------------------------
