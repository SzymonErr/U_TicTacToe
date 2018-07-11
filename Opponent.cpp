/*
 * Opponent.cpp
 *
 *  Created on: Jun 3, 2018
 *      Author: szymon
 */

#include "Opponent.h"

Opponent::Opponent() {
	// TODO Auto-generated constructor stub
	size = 0;
	win_cond = 0;
	result = 0;
	tab = new int[size*size];
	turn = 0;

	depth = 0;
	curent_move = 0;
}

Opponent::~Opponent() {
	// TODO Auto-generated destructor stub
}

int Opponent::make_move(int current_move){
	return current_move;
}

void Opponent::copy_board(Board table){
	size = table.show_size();
	win_cond = table.show_win_cond();
	for (int i = 0; i< size*size; i++){
		tab[i] = table.show_tab(i);
		//std::cout<< "Tab[" << i << "]= " << tab[i] << std::endl;
	}
	std::cout << "SIZE: " << size << " win_cond: " << win_cond << std::endl;
}

/* minmax bez alfa-beta ciec
 *
int Opponent::minmax(int player, int depth, int place){

	int m;
	int score;
	bool tie = true;
	score = (win_check(player, place) || win_check_row(player, place));

	for (int j = 0; j < size*size; j++){
		if(tab[j] == 0) tie = false;
		//if(depth == 0) std::cout << "Tab[" << j << "]=" << tab[j] << "  ";
	}
	//if(depth == 0) std::cout << std::endl;

	if (score != 0) return player;
	else if(tie == true) return 0;

	player *= -1;

	if (player == 1){
		int best = -100;

		for (int i = 0; i < size*size; i++){
			if (tab[i] == 0){
				tab[i] = player;
				m = minmax(player, depth+1, i);
				if (best < m) best = m;
				tab[i] = 0;
			}
		}
	return best;
	}
	else{
		int best = 100;

		for (int i = 0; i < size*size; i++){
			if (tab[i] == 0){
				tab[i] = player;
				m = minmax(player, depth+1, i);
				if (best > m) best = m;
				tab[i] = 0;
			}
		}
	return best;
	}
}

int Opponent::findBestMove(int player){
	int BestVal = 100;
	int bestMove = -1;
	int moveVal;

	for (int i = 0; i < size*size; i++)
		if (tab[i] == 0){
				tab[i] = player;
				moveVal = minmax(player, 0, i);
				tab[i] = 0;
				if (moveVal < BestVal){
					bestMove = i;
					BestVal = moveVal;
				}
		}
	std::cout << "Najlepszy ruch: " << bestMove << std::endl;
	return bestMove;
}

void Opponent::play(){
	int actual_player = 1;
	int place = -1;

	while (result == 0 && turn < size*size){
		if (actual_player == 1){
		place = -1;
		while ((place < 0 || place >> size*size) && tab[place] == 0 && actual_player == 1){
			if(actual_player == 1) std::cout << "(Tura gracza X)" << std::endl;
			else std::cout << "(Tura gracza O)" << std::endl;
			std::cout << "Podaj numer pola: " << std::endl;
			std::cin >> place;
			if (place < 0 || place >= size*size || tab[place] != 0){
				std::cout << "Nieprawdilowe pole!" << std::endl;
				place = -1;
				}
			}
		}
		if (actual_player == -1){
			std::cout << "(Tura gracza O)" << std::endl;
			//place = enemy_move(actual_player);
			place = findBestMove(actual_player);
		}
		//std::cout << "Aktualne place: " << place << std::endl;
		//result = win_check(place);
		//std::cout << "Result: " << result << std::endl;
		if (result != 1){
			tab[place] = actual_player;
			//result = win_check_row(actual_player, place);
			result = win_check(actual_player, place) || win_check_row(actual_player, place);
			std::cout << "Result: " << result << std::endl;
			turn++;
			actual_player *= -1;
			print_board();
			//place = -1;
		}
	}
	std::cout << "Koniec gry!" << std::endl;
	if(result == 1 && actual_player == -1) std::cout << "ZWYCIESTWO GRACZA X!" << std::endl;
	else if(result == 1 && actual_player == 1) std::cout << "ZWYCIESTWO GRACZA O!" << std::endl;
	else std::cout << "REMIS!" << std::endl;
	//print_board();
}

koniec minmaxa bez alfa-beta */

int Opponent::minmax(int player, int depth, int place, int alpha, int beta){

	int m;
	int score;
	bool tie = true;
	score = (win_check(player, place) || win_check_row(player, place));

	for (int j = 0; j < size*size; j++){
		if(tab[j] == 0) tie = false;
		//if(depth == 3) std::cout << "Tab[" << j << "]=" << tab[j] << "  ";
	}
	//if(depth == 3) std::cout << std::endl;

	if (score != 0 || depth == 0) return player;
	else if(tie == true) return 0;

	player *= -1;

	if (player == 1){
		//int best = -100;

		for (int i = 0; i < size*size; i++){
			if (tab[i] == 0){
				tab[i] = player;
				m = minmax(player, depth-1, i, alpha, beta);
				if (m > alpha) alpha = m;
				if (alpha >= beta) {
					tab[i] = 0;
					break;
				}
				tab[i] = 0;
			}
		}
	return alpha;
	}
	else{
		//int best = 100;

		for (int i = 0; i < size*size; i++){
			if (tab[i] == 0){
				tab[i] = player;
				m = minmax(player, depth-1, i, alpha, beta);
				if (m < beta) beta = m;
				if (alpha >= beta) {
					tab[i] = 0;
					break;
				}
				tab[i] = 0;
			}
		}
	return beta;
	}
}

int Opponent::findBestMove(int player){
	int BestVal = 100;
	int bestMove = -1;
	int moveVal;

	for (int i = 0; i < size*size; i++)
		if (tab[i] == 0){
				tab[i] = player;
				moveVal = minmax(player, 7, i, -10000, 10000);
				tab[i] = 0;
				if (moveVal < BestVal){
					bestMove = i;
					BestVal = moveVal;
				}
		}
	std::cout << "Najlepszy ruch: " << bestMove << std::endl;
	return bestMove;
}

void Opponent::play(){
	int actual_player = -1;
	int place = -1;

	while (result == 0 && turn < size*size){
		if (actual_player == 1){
		place = -1;
		while ((place < 0 || place >> size*size) && tab[place] == 0 && actual_player == 1){
			if(actual_player == 1) std::cout << "(Tura gracza X)" << std::endl;
			else std::cout << "(Tura gracza O)" << std::endl;
			std::cout << "Podaj numer pola: " << std::endl;
			std::cin >> place;
			if (place < 0 || place >= size*size || tab[place] != 0){
				std::cout << "Nieprawdilowe pole!" << std::endl;
				place = -1;
				}
			}
		}
		if (actual_player == -1){
			std::cout << "(Tura gracza O)" << std::endl;
			//place = enemy_move(actual_player);
			place = findBestMove(actual_player);
		}
		//std::cout << "Aktualne place: " << place << std::endl;
		//result = win_check(place);
		//std::cout << "Result: " << result << std::endl;
		if (result != 1){
			tab[place] = actual_player;
			//result = win_check_row(actual_player, place);
			result = win_check(actual_player, place) || win_check_row(actual_player, place);
			std::cout << "Result: " << result << std::endl;
			turn++;
			actual_player *= -1;
			print_board();
			//place = -1;
		}
	}
	std::cout << "Koniec gry!" << std::endl;
	if(result == 1 && actual_player == -1) std::cout << "ZWYCIESTWO GRACZA X!" << std::endl;
	else if(result == 1 && actual_player == 1) std::cout << "ZWYCIESTWO GRACZA O!" << std::endl;
	else std::cout << "REMIS!" << std::endl;
	//print_board();
}
