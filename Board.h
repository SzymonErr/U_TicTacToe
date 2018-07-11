/*
 * Board.h
 *
 *  Created on: Jun 2, 2018
 *      Author: szymon
 */

#ifndef BOARD_H_
#define BOARD_H_

class Board {
protected:
	int size;
	int win_cond;
	int *tab;
	bool result;
	int turn;
public:
	Board();
	virtual ~Board();
	//Board(const Board&);
	int show_size(){ return size;};
	int show_win_cond(){ return win_cond;};
	int show_tab(int i){ return tab[i];};
	void prepare_board();
	char x_or_o(int value);
	void print_board();
	void print_help();
	bool win_check_row(int, int);
	bool win_check(int, int);
	void read_size();
	void read_win_cond();
	void play();

	bool check_if_include(int);
	bool count_limiter(int med, int place, int condition);
};

#endif /* BOARD_H_ */
