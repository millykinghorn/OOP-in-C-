// Snakes and Ladders.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//TO-DO
//User Input for board size, num snakes, and num ladders
//Make a 2 player game
	//Move only when player button is pressed
	//change occupance to p1 p2 p3 etc instead of x, if o leave blank
	//change "win" statement for whoever has won
//Look into making template for snakes and ladders since basically exactly the same

//SNAKE START = MOUTH
//SNAKE END = TAIL
//LADDER START = BOTTON
//LADDER END = TOP

#include <iostream>
#include <ctime>
#include <random>


using namespace std;

int snake_length = 5;
int ladder_length = 7;

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
	int get_snake_end() { return snake_end; };
};

//ladder is a type of tile with a start and end point
class ladder :tile {
protected:
	int number;
	int ladder_start;
	int ladder_end;
	string occupied;
	string type;
public:
	ladder() = default;
	ladder(int ladder_start_, int ladder_end_) :
		number{ ladder_start_ }, ladder_start(ladder_start_), ladder_end{ ladder_end_ }, occupied{ "o" }, type{ "ladder" }{};
	~ladder() {};

	int get_ladder_start() { return ladder_start; };
	int get_ladder_end() { return ladder_end; };

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
		tiles[10].set_type("ladder");
		tiles[30].set_type("ladder");
		
		//UNCOMMENT AND FIX FOR ADDING SNAKE AND LADDER TILES TO BOARD
		
		for (int i{}; i < size; i++) {
			if (tiles[i].get_type() == "snake") {
				tiles[i] = snake(i+1, i+1 - snake_length);
				tiles[i].set_number(i+1);
				tiles[i].set_occupance("o");
				tiles[i].set_type("snake");
				cout << "snake from " << i+1 << " to " << i+1 - snake_length << endl;
			}
			else if (tiles[i].get_type() == "ladder") {
				tiles[i] = snake(i + 1, i + 1 + ladder_length);
				tiles[i].set_number(i + 1);
				tiles[i].set_occupance("o");
				tiles[i].set_type("ladder");
				cout << "ladder from " << i + 1 << " to " << i + 1 + ladder_length << endl;
			}

		}


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
				else if (get_type(tile_number) == "ladder") {
					cout << "L " << " " << tiles[tile_number - 1].get_occupied() << " ";
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
				else if (get_type(tile_number) == "ladder") {
					cout << "L " << " " << tiles[tile_number - 1].get_occupied() << " ";
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
	void snake_move(board& b, snake& s);
	void ladder_move(board& b, ladder& l);
};

void player::move(board& b) {

	//set occupance of original tile to open
	b.occupance(get_position() - 1, "o");

	int move_number = roll_dice();
	cout << "Dice : " << move_number << endl;

	//get type of tile at position+move_number
	string tile_type = b.get_type(get_position());

	//if a normal tile, move to that
	//cout << "normal tile" << endl;
	set_position(move_number + get_position());
	//set occupance of new tile to closed
	b.occupance(get_position() - 1, "x");

}

void player::snake_move(board& b, snake& s) {

	//get start position of snake
	int start = s.get_snake_start();
	int end = s.get_snake_end();

	//set occupance of original tile to open
	b.occupance(get_position() - 1, "o");

	//change occupance accordingly
	set_position(end);

	//set occupance of new tile to closed
	b.occupance(get_position() - 1, "x");
	
	cout << "Landed on a snake! Go from " << s.get_snake_start() << " to " << s.get_snake_end() << endl;
	b.display();

}

void player::ladder_move(board& b, ladder& l) {
	//get start position of snake
	int start = l.get_ladder_start();
	int end = l.get_ladder_end();

	//set occupance of original tile to open
	b.occupance(get_position() - 1, "o");

	//change occupance accordingly
	set_position(end);

	//set occupance of new tile to closed
	b.occupance(get_position() - 1, "x");

	cout << "Landed on a ladder! Go from " << l.get_ladder_start() << " to " << l.get_ladder_end() << endl;
	b.display();
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

		//if on a snake tile, go to start of snake
		if (gameboard.get_type(player1.get_position()) == "snake") {
			//find which snake has been landed on
			int snake_start = player1.get_position();
			snake s1 = snake(player1.get_position(), (player1.get_position() - snake_length));
			//snake_move for that snake
			player1.snake_move(gameboard, s1);
		}

		else if (gameboard.get_type(player1.get_position()) == "ladder") {
			//find which snake has been landed on
			int ladder_start = player1.get_position();
			ladder l1 = ladder(player1.get_position(), (player1.get_position() + ladder_length));
			//snake_move for that snake
			player1.ladder_move(gameboard, l1);
		}
		cout << endl;
		cout << endl;

	};


	cout << player1.get_name() << " won!" << endl;

	return 0;
}
