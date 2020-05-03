// Snakes and Ladders.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//TO-DO
//Make dice roll random each time
//make snakes link start and end
//change the move to it goes to start of snake if lands on it

//add variables for :
// snake length
// where snakes start

#include <iostream>
#include <ctime>
#include <random>


using namespace std;

int snake_length = 5;

//global function to roll dice and return random number between 1 and 6
int roll_dice() {
	//srand(time(0));
	//srand((unsigned)time(NULL));
	return rand() % 6 + 1;
	//return 5;
}

class tile {
protected:
	int number{};
	string occupied{};
	string type{};
public:
	tile() = default;
	~tile() {};

	void set_number(int i) { number = i; }
	int get_number() { return number; }
	void set_occupance(string x) { occupied = x; }
	string get_occupied() { return occupied; }
	void set_type(string s) { type = s; }
	string get_type() { return type; }

};

//snake is a type of tile with a start and end point
class snake : public tile {
protected:
	int number;
	int snake_start;
	int snake_end;
	string occupied;
	string type;
public:
	snake() = default;
	snake(int snake_start_, int snake_end_) :
		number{ snake_start_ },snake_start(snake_start_), snake_end{ snake_end_ }, occupied{ "o" }, type{ "snake" }{};
	~snake() {};

	int get_snake_start() { return snake_start; };
	int get_snake_send() { return snake_end; };
};

//ladder is a type of tile with a start and end point
class ladder :tile {
protected:
	int ladder_start;
	int ladder_end;
};

//board is an array of tiles of size 25 (5x5) to start
class board: public tile {
protected:
	int rows;
	int columns;
	int size;
	tile* tiles{nullptr};

public:
	board() = default;
	board(int rows_,int columns_) :
		rows{ rows_ }, columns{ columns_ }, size{rows_*columns_} {
		tiles = new tile[size];
		for (int i{}; i < size; i++) {
			tiles[i].set_number(i+1);
			occupance(i, "o");
			tiles[i].set_type("normal");
		}

		tiles[14].set_type("snake");
		//tiles[15].set_type("snake");
		//tiles[16].set_type("snake");
		//tiles[17].set_type("snake");
		tiles[22].set_type("snake");
		
		//UNCOMMENT AND FIX FOR ADDING SNAKE TILES TO BOARD
		/*
		for (int i{}; i < size; i++) {
			if (tiles[i].get_type() == "snake") {
				tiles[i] = snake(i+1, i+1 - snake_length);
				tiles[i].set_number(i+1);
				cout << "snake from " << i+1 << " to " << i+1 - snake_length << endl;
			}

		}
		*/

		//the start tile is occupied
		occupance(0, "x");

	} ;

	~board() { cout << "Game Over"; };


	void display();
	void occupance(int i, string s);
	int get_size() { return size; }
	string get_type(int i) { 
		if (i <= size) {
			return tiles[i - 1].get_type();
		}
		else { return "end of board"; }
	} //check indexing for this
};

void board::display() {
	int column_counter = 1;
	int row_counter = 0;
	//print top row of boxes
	for (row_counter; row_counter <= rows; row_counter++){
		for (column_counter; column_counter <= columns; column_counter++) {
			int i = row_counter*column_counter;
			if (row_counter == 0){
				cout << " _____ ";
			}
			//odd rows increase to the right
			else if ((rows - row_counter) % 2 == 0) {
				int tile_number = size - (columns*row_counter) + column_counter;
				cout << "| ";
				if (tile_number < 10) { cout << " "; };
				if (get_type(tile_number) == "snake") {
					cout << "S " << " " << tiles[tile_number - 1].get_occupied() << " ";
				}
				else {
					cout << tiles[tile_number - 1].get_number() << " " << tiles[tile_number - 1].get_occupied() << " ";
				}
			}
			else {
				int tile_number = size - (columns * row_counter) + (columns+1 - column_counter);
				cout << "| ";
				if (tile_number < 10) { cout << " "; };
				if (get_type(tile_number) == "snake") {
					cout << "S " << " " << tiles[tile_number - 1].get_occupied() << " ";
				}
				else {
					cout << tiles[tile_number - 1].get_number() << " " << tiles[tile_number - 1].get_occupied() << " ";
				}
			}
		}
		column_counter = 1;
		cout << endl;
	}
	//below is display formatting for a straight line
	/*
	for (int i{}; i < size; i++) {
		cout << "| " << tiles[i].get_number() << " " << tiles[i].get_occupied() << " ";
	}
	cout << "|";
	return;*/
}

void board::occupance(int i, string s){
	//find number of tile player is on and make the occupance open
	if ( i < size) {
		tiles[i].set_occupance(s);
		return;
	}
	else {
		return;
	}

}

//acts as player interface
class counter {
protected:
	int position;
public:
	counter()=default;
	counter(int num) : position{ num } {}; //parametized constructor
	virtual ~counter() {};

	virtual void set_position(int i) = 0;
	virtual int get_position()=0;
	virtual void move() = 0;
};


class player : public board {
protected:
	string name;
	int position;
public:
	player() :
		//counter{}, name{ "player" }{}; undo when make player a type of counter as opposed to tile
		name{ "player" }{};

	player(string name_) :
		name{ name_ }{
		set_position(1);
	};

	string get_name() { return name; }
	void set_position(int i) { position = i; };
	int get_position() { return position; }

	void move(board& b);
	void snake_move(board& b);
	void ladder_move(board& b);
};

void player::move(board& b) {

	//set occupance of original tile to open
	b.occupance(get_position() - 1, "o");

	int move_number = roll_dice();
	cout << "Dice : " << move_number << endl;

	//get type of tile at position+move_number
	string tile_type = b.get_type(get_position());

	//if a normal tile, move to that
	if (tile_type == "normal") {
		//cout << "normal tile" << endl;
		set_position(move_number + get_position());
		//set occupance of new tile to closed
		b.occupance(get_position() - 1, "x");
	}
	
	//if a snake tile, move to start of snake 
	//(could have landed on start of snake, doesn't matter)
	else if (tile_type == "snake") {
		//cout << "landed on snake" << endl;
		set_position(move_number + get_position());
		//set occupance of new tile to closed
		b.occupance(get_position() - 1, "x");
	}

}

void player::snake_move(board& b) {

	//get start position of snake

	//if at start of snake, do nothing

	//if at end of snake, move to start

	//change occupance accordingly

}

void player::ladder_move(board& b) {
	//get end position of ladder


	//change occupancy accordingly
}

int main()
{
	srand((unsigned)time(NULL));

	//Enter the size of the board via cin:
	board gameboard(7,7);

	gameboard.display();

	player player1("Milly");
	player player2("Ollie");

	cout << endl;
	while (player1.get_position() < gameboard.get_size()) {
		player1.move(gameboard);
		gameboard.display();
		cout << player1.get_name() << " is at square " << player1.get_position() << " a " << gameboard.get_type(player1.get_position()) << " tile" << endl;
	};


	cout << player1.get_name() << " is at square " << player1.get_position() << endl;
	cout << player1.get_name() << " won!" << endl;

	return 0;
}
