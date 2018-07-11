/*
 * Board.cpp
 *
 *  Created on: Jun 2, 2018
 *      Author: szymon
 */

#include <iostream>
#include "Board.h"
#include <cmath>

Board::Board() {
	// TODO Auto-generated constructor stub
	size = 0;
	win_cond = 0;
	result = 0;
	tab = new int[size*size];
	turn = 0;
}

Board::~Board() {
	//delete [] tab;
	// TODO Auto-generated destructor stub
}

/*
Board::Board(const Board &board){
	size = board.size;
	win_cond = board.win_cond;
	tab = new int[size*size];
}*/

void Board::prepare_board(){
	read_size();
	read_win_cond();
	for(int i = 0; i < size*size; i++) tab[i] = 0;
	print_help();
}

char Board::x_or_o(int value){
		if (value > 0) return 'X';
		else if (value < 0) return 'O';
		else return ' ';
}

void Board::print_board(){
	int i = 0;
	/*
	for (int j = 0; j < size*size; j++)
		std::cout << tab[j] << " ";
	std::cout << std::endl;
*/
	for (int height = 1; height <= size; height++){
		for (int width = 0; width < size; width++){
			std::cout << " " << x_or_o(tab[i]) << " ";
			if ((i+1) % size) std::cout << "|";
			i++;
		}
		std::cout << std::endl;
		if(height % size)
			for (int j = 1; j <= size; j++){
				std::cout << "---";
				if (j % size) std::cout << "+";
			}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::print_help(){
	int i = 0;

	for (int height = 1; height <= size; height++){
		for (int width = 0; width < size; width++){
			std::cout << " " << i << " ";
			if ((i+1) % size) std::cout << "|";
			i++;
		}
		std::cout << std::endl;
		if(height % size)
			for (int j = 1; j <= size; j++){
				std::cout << "---";
				if (j % size) std::cout << "+";
			}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::read_size(){
	while(size <= 0){
		std::cout << "Podaj rozmiar planszy: " << std::endl;
		std::cin >> size;
		if(size <= 0) std::cout << "Nieprawidlowy rozmiar planszy!" << std::endl;
	}
}

void Board::read_win_cond(){
	while (win_cond == 0){
		std::cout << "Podaj warunek zwyciestwa: " << std::endl;
		std::cin >> win_cond;
		if (win_cond <= 0 || win_cond > size){
			std::cout << "Nieprawidlowy warunek zwyciestwa!" << std::endl;
			win_cond = 0;
		}
	}
}

bool Board::count_limiter(int med, int place, int condition){
	if(condition == 0 && place/size != med){
	return 0;
	}
	else return 1;
}

bool Board::check_if_include(int place){
	if (place >= 0 && place < size*size)
	return 1;
	else return 0;
}


bool Board::win_check_row(int actual_player, int place){
	int counter = 1;
	int act = place, next = place+1;
	int med = place / size;

			while(next >= 0 && next < size*size && tab[next] == actual_player && next/size == med && counter < win_cond){
				//std::cout << "Next: " << tab[next] << std::endl;
				counter++;
				act = next;
				next = act+1;
			}

		//std::cout << "Counter1: " << counter << std::endl;
		act = place;
		next = act-1;
			while(next >= 0 && next < size*size && tab[next] == actual_player && next/size == med && counter < win_cond){
				counter++;
				act = next;
				next = act-1;
			}

		//std::cout << "Counter2: " << counter << std::endl;
		if (counter == win_cond) return 1;
		else return 0;

}

bool Board::win_check(int actual_player, int place){
	int counter = 1;
	int act = place, next;
	int gap = size;

	for (int i = 0; i < 3; i++){
		switch(i){
		case 0: gap = size;
		break;
		case 1: gap = size - 1;
		break;
		case 2: gap = size + 1;
		break;
		}
		act = place;
		next = act+gap;
			while(next >= 0 && next < size*size && tab[next] == actual_player && counter < win_cond && (act/size - next/size) == -1){
				//std::cout << "Next: " << tab[next] << std::endl;
				counter++;
				act = next;
				next = act+gap;
			}

		//std::cout << "Counter1: " << counter << std::endl;
		act = place;
		next = act-gap;
			while(next >= 0 && next < size*size && tab[next] == actual_player && counter < win_cond && (act/size - next/size) == 1 ){
				counter++;
				act = next;
				next = act-gap;
			}
		if (counter == win_cond) break;
		else counter = 1;
	}
		//std::cout << "Counter2: " << counter << std::endl;
		if (counter == win_cond) return 1;
		else return 0;
}


void Board::play(){
	int actual_player = 1;
	int place = -1;

	while (result == 0 && turn < size*size){
		while (place < 0 || place >> size*size){
			if(actual_player == 1) std::cout << "(Tura gracza X)" << std::endl;
			else std::cout << "(Tura gracza O)" << std::endl;
			std::cout << "Podaj numer pola: " << std::endl;
			std::cin >> place;
			if (place < 0 || place >= size*size || tab[place] != 0){
				std::cout << "Nieprawdilowe pole!" << std::endl;
				place = -1;
			}

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
			place = -1;
		}
	}
	std::cout << "Koniec gry!" << std::endl;
	if(result == 1 && actual_player == -1) std::cout << "ZWYCIESTWO GRACZA X!" << std::endl;
	else if(result == 1 && actual_player == 1) std::cout << "ZWYCIESTWO GRACZA O!" << std::endl;
	else std::cout << "REMIS!" << std::endl;
	//print_board();
}
