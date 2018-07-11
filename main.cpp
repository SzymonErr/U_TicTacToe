/*
 * main.cpp
 *
 *  Created on: May 31, 2018
 *      Author: szymon
 */

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include "Board.h"
#include "Opponent.h"

using namespace std;


int main(){
	Opponent Harnas;
	Board game;
	game.prepare_board();
	game.print_board();
	Harnas.copy_board(game);
	Harnas.play();
	//game.play();
	return 0;
}


