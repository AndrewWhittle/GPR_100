
#include <stdio.h>
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

void drawBoard(gs_battleship game)
{
	cout << "  A|B|C|D|E|F|G|H|I|J|" << endl;
	for (int i = 1; i < 10; i++)
	{
		cout << i << " ";
		for (int j = 0; j < 10; j++)
		{
			cout << gs_battleship_getSpaceState(game, 1, i, j) << "|";
		}
		cout << "\n  --------------------" << endl;
	}

}

void setUpGame(gs_battleship game, int player)
{
	char shipToBePlaced;
	int column, row;
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
		break;
	case 'D':
		break;
	case 'B':
		break;
	case 'C':
		break;
	}
}

int launchBattleship()
{
	gs_battleship game = { 0 };

	gs_battleship_reset(game);

	int column, row, player = 0;

	drawBoard(game);

	setUpGame(game, player);

	drawBoard(game);

	/*
	cout << "Enter a column: ";
	cin >> column;
	cout << "Enter a row: ";
	cin >> row;
	*/


	return 0;
}


//-----------------------------------------------------------------------------
