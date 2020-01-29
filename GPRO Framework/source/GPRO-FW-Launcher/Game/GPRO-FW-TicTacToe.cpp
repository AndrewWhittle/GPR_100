
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_TICTACTOE_PLAYERS					2
#define GS_TICTACTOE_BOARD_WIDTH				3
#define GS_TICTACTOE_BOARD_HEIGHT				3

enum gs_tictactoe_space_state
{
	// invalid space state
	gs_tictactoe_space_invalid = -1,

	// states visible to both players
	gs_tictactoe_space_open,	// space is open
	gs_tictactoe_space_o,		// space is taken by O player
	gs_tictactoe_space_x,		// space is taken by X player
};
#ifndef __cplusplus
typedef		enum gs_tictactoe_space_state		gs_tictactoe_space_state;
#endif	// !__cplusplus

// tic-tac-toe game state
typedef		unsigned char						gs_tictactoe_index;
typedef		gs_tictactoe_space_state			gs_tictactoe[GS_TICTACTOE_BOARD_WIDTH][GS_TICTACTOE_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,w,h)			(x < w && y < h)
#define GS_TICTACTOE_VALID(x,y)					GS_VALIDATE_COORDINATE(x,y,GS_TICTACTOE_BOARD_WIDTH,GS_TICTACTOE_BOARD_HEIGHT)


inline gs_tictactoe_space_state gs_tictactoe_getSpaceState(gs_tictactoe const game, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos]);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_space_state gs_tictactoe_setSpaceState(gs_tictactoe game, gs_tictactoe_space_state const state, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos] = state);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_index gs_tictactoe_reset(gs_tictactoe game)
{
	gs_tictactoe_index xpos, ypos, total;
	for (xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos)
		for (ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos)
			game[xpos][ypos] = gs_tictactoe_space_open;
	total = (xpos * ypos);
	return total;
}


//-----------------------------------------------------------------------------
// DEFINITIONS

void drawBoard(vector<char> changes)
{
	int i = 0;
	while (i <= 8)
	{
		cout << "  " << i << "     " << i + 1 << "     " << i + 2 << endl;
		cout << "  " << changes[i] << "  |  " << changes[i + 1] << "  |  " << changes[i + 2] << "  \n" << "-------------------" << endl;
		i += 3;
	}
}

bool testForWinner(vector<char> changes)
{
	int i = 0;
	while (i <= 8)
	{
		if (changes[0] == 'X' || changes[0] == 'O')
		{
			if (changes[0] == changes[1] && changes[1] == changes[2])
			{
				cout << "this one";
				return true;
			}
			else if (changes[0] == changes[3] && changes[3] == changes[6])
			{
				cout << "this four";
				return true;
			}
			else if (changes[0] == changes[4] && changes[4] == changes[8])
			{
				cout << "this two";
				return true;
			}
			else
			{
				return false;
			}
		}
		if (changes[4] == 'X' || changes[4] == 'O')
		{
			if (changes[1] == changes[4] && changes[4] == changes[7])
			{
				cout << "this one";
				return true;
			}
			else if (changes[3] == changes[4] && changes[4] == changes[5])
			{
				cout << "this four";
				return true;
			}
			else if (changes[0] == changes[4] && changes[4] == changes[8])
			{
				cout << "this two";
				return true;
			}
			else
			{
				return false;
			}
		}
		i += 3;
	}
}

int launchTicTacToe()
{
	gs_tictactoe game = { 0 };

	gs_tictactoe_reset(game);

	srand(time(0));

	char turn = 'X';
	char t = 'y';
	vector<char> changes;
	int spaceChosen = 0;
	int rounds = 1;
	changes.resize(9);

	while (t == 'y')
	{
		cout << "Round " << rounds << endl;
		drawBoard(changes);

		cout << "Player " << turn << " turn" << endl;
		cout << "Chose a space" << endl;
		cin >> spaceChosen;

		if (spaceChosen >= 0 && spaceChosen <= 8 && changes[spaceChosen] != 'X' && changes[spaceChosen] != 'O')
		{
			if (turn == 'X')
			{
				changes[spaceChosen] = 'X';
				turn = 'O';
			}
			else if (turn == 'O')
			{
				changes[spaceChosen] = 'O';
				turn = 'X';
			}
			rounds++;
		}
		else
		{
			cout << "Invalid space entered" << endl;
		}
		
		if (testForWinner(changes) == true)
		{
			cout << "Player " << turn << " Wins!" << endl;
			cout << "Would you like to play again?(y for yes, n for no)" << endl;
			cin >> t;
			rounds = 1;
		}
		if (rounds == 9)
		{
			cout << "Tie game!" << endl;
			cout << "Would you like to play again?(y for yes, n for no)" << endl;
			cin >> t;
			rounds = 1;
		}
	}
	return 0;
}


//-----------------------------------------------------------------------------
