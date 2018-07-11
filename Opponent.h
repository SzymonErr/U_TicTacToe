/*
 * Opponent.h
 *
 *  Created on: Jun 3, 2018
 *      Author: szymon
 */

#ifndef OPPONENT_H_
#define OPPONENT_H_
#include "Board.h"
#include <iostream>

class Opponent
		: public Board {
	int curent_move;
	int depth;
public:
	Opponent();
	virtual ~Opponent();
	int make_move(int);
	void copy_board(Board);
	//int minmax(int, int);
	void play();
	/*int enemy_move(int);
	int minmax(int player, int depth, int);
	int findBestMove(int player);
	 */
	int enemy_move(int);
	int minmax(int player, int depth, int, int, int);
	int findBestMove(int player);
};

#endif /* OPPONENT_H_ */
