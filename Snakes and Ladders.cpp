// Snakes and Ladders.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//TO-DO
//User Input for board size, num snakes, and num ladders
//Look into making template for snakes and ladders since basically exactly the same
//Add in checks for all input (if needs int make sure int etc)
//separate into independent files for functions etc
//bug: when land on snake, occupance of previous tile dissapears
//bug: when both on same square, and one moves on, it says it is unoccupied
//making loop for x amounts of players instead of hard coding for certain amount


//SNAKE START = MOUTH
//SNAKE END = TAIL
//LADDER START = BOTTON
//LADDER END = TOP

#include <iostream>
#include <ctime>
#include <random>
#include <list>


using namespace std;

int snake_length = 5;
int ladder_length = 5;

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
		number{ snake_start_ },snake_start(snake_start_), snake_end{ snake_end_ }, occupied{ " " }, type{ "snake" }{};
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
		number{ ladder_start_ }, ladder_start(ladder_start_), ladder_end{ ladder_end_ }, occupied{ " " }, type{ "ladder" }{};
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
			occupance(i, " ");
			tiles[i].set_type("normal");
		}

		/*for (int i=1; i < size; i++) {
			if (i * 11 < size) {
				tiles[i * 11].set_type("snake");
			}
			//make sure ladder does not take to beyond scope of board
			if (((i * 11) +3 - ladder_length) < size) {
				tiles[(i * 11) + 3].set_type("ladder");
			}
		}*/

		//Algorithm for auto inserting snakes and ladders; 
		//  more snakes higher up board, more ladders lower down board
		//  both are evenly spaced with same length

		int number_of_snakes = (size - size % 12) / 12; //e.g. for 6x6 board, 3 snakes
		int number_of_ladders = (size - size % 12) / 12; //e.g. for 6x6 board, 3 ladders

		for (int i=0; i < number_of_snakes; i++) {
			//snake every 10 tiles working back from second to last tile
			int tile_number = size - 1 -(i*10);
			tiles[tile_number-1].set_type("snake");
		}

		for (int i = 0; i < number_of_ladders; i++){
			//ladder every 10 tiles working forward from second tile
			int tile_number = 2 + (i * 10);
			tiles[tile_number-1].set_type("ladder");
		}

		//tiles[14].set_type("snake");
		//tiles[15].set_type("snake");
		//tiles[16].set_type("snake");
		//tiles[17].set_type("snake");
		//tiles[22].set_type("snake");
		//tiles[10].set_type("ladder");
		//tiles[30].set_type("ladder");
				
		for (int i{}; i < size; i++) {
			if (tiles[i].get_type() == "snake") {
				tiles[i] = snake(i+1, i+1 - snake_length);
				tiles[i].set_number(i+1);
				tiles[i].set_occupance(" ");
				tiles[i].set_type("snake");
				cout << "snake from " << i+1 << " to " << i+1 - snake_length << endl;
			}
			else if (tiles[i].get_type() == "ladder") {
				tiles[i] = snake(i + 1, i + 1 + ladder_length);
				tiles[i].set_number(i + 1);
				tiles[i].set_occupance(" ");
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
	//override output operator so prints name of player
	friend ostream& operator<<(ostream& os, const player& p);
protected:
	string name;
	string initial;
	int position;
public:
	player() :
		//counter{}, name{ "player" }{}; undo when make player a type of counter as opposed to tile
		name{ "player" }, position{1}{};

	player(string name_) :
		name{ name_ }{
		set_position(1);
		initial = name_;
		for (int i{}; i < name_.length()-1; i++) {
			initial.pop_back();
		}
	};
	//Copy Constructor used for copying player info to "Winner" player
	player(player& arr);
	string get_name() { return name; }
	string get_initial() { return initial; }
	void set_position(int i) { position = i; };
	int get_position() { return position; }
	bool on_board_check(board& b);

	void move(board& b);
	void snake_move(board& b, snake& s);
	void ladder_move(board& b, ladder& l);
	void print_name() const { cout << name << endl; }
};

ostream& operator<<(ostream& os, const player& p)
{
	cout << "Player made";
	//os << "Name: " << p.print_name() << endl;
	//cout << "cout name : " << p.get_name();
	//cout << p.name;
	return os;
}

//copy constructor
player::player(player& arr) {
	// Copy size and declare new array
	initial = arr.initial; 
	position = arr.position; 
	name = arr.name;
}


bool player::on_board_check(board& b) {
	if (position < b.get_size()) {
		return true;
	}
	else {

		return false;
	}
}

void player::move(board& b) {

	
	//set occupance of original tile to open
	b.occupance(get_position() - 1, " ");

	int move_number = roll_dice();
	cout << "Dice : " << move_number << endl;

	//get type of tile at position+move_number
	string tile_type = b.get_type(get_position());

	//if a normal tile, move to that
	//cout << "normal tile" << endl;
	set_position(move_number + get_position());
	//set occupance of new tile to closed
	b.occupance(get_position() - 1, initial);

}

void player::snake_move(board& b, snake& s) {

	//get start position of snake
	int start = s.get_snake_start();
	int end = s.get_snake_end();

	//set occupance of original tile to open
	b.occupance(get_position() - 1, " ");

	//change occupance accordingly
	set_position(end);

	//set occupance of new tile to closed
	b.occupance(get_position() - 1, initial);
	
	cout << "Landed on a snake! Go from " << start << " to " << end << endl;
	b.display();

}

void player::ladder_move(board& b, ladder& l) {
	//get start position of snake
	int start = l.get_ladder_start();
	int end = l.get_ladder_end();

	//set occupance of original tile to open
	b.occupance(get_position() - 1, " ");

	//change occupance accordingly
	set_position(end);

	//set occupance of new tile to closed
	b.occupance(get_position() - 1, initial);

	cout << "Landed on a ladder! Go from " << start << " to " << end << endl;
	b.display();
}

void print_player_name(const player& p) {
	p.print_name();
}

auto print = [](player& p) { std::cout << " " << p.get_name(); };


int main()
{
	srand((unsigned)time(NULL));

	//Enter the size of the board via cin:
	int num_rows, num_columns, num_players;
	cout << "Board Set Up Options: " << endl;
	cout << "  No. Rows: ";
	cin >> num_rows;
	cout << "  No. Cols: ";
	cin >> num_columns;

	//board gameboard(7, 7);
	board gameboard(num_rows, num_columns);

	//Determine players 
	cout << "How many players are playing? ";
	cin >> num_players;

	list<player*> player_list;
	list<player>::iterator it;

	//iteratively add players to list of players
	for (int i{}; i < num_players; i++) {
		string playername;

		cout << "Name of player " << i + 1 << ": ";
		cin >> playername;
		//create new player and add to list
		player* p = new player(playername);
		//player p(playername);
		player_list.push_back(p);
	}

	//for_each(player_list.begin(), player_list.end(), print);

	for (auto it = player_list.cbegin(); it != player_list.cend(); it++) {
		string name = (*it)->get_name();
		cout << name << endl;
	}

	

	/*string player_name;
	vector<string> player_names;
	for (int i{}; i < num_players; i++) {
		cout << "Name of player " << i << " : ";
		cin >> player_name;
		player_names.push_back(player_name);
	}*/

	/*
	string player_name1;
	string player_name2;
	string player_name3;
	string player_name4;

	if (num_players == 1) {
		cout << "Name of player " << 1 << " : ";
		cin >> player_name1;
	}
	else if (num_players == 2) {
		cout << "Name of player " << 1 << " : ";
		cin >> player_name1;
		cout << "Name of player " << 2 << " : ";
		cin >> player_name2;
	}
	else if (num_players == 3) {
		cout << "Name of player " << 1 << " : ";
		cin >> player_name1;
		cout << "Name of player " << 2 << " : ";
		cin >> player_name2;
		cout << "Name of player " << 3 << " : ";
		cin >> player_name3;
	}
	else if (num_players == 4) {
		cout << "Name of player " << 1 << " : ";
		cin >> player_name1;
		cout << "Name of player " << 2 << " : ";
		cin >> player_name2;
		cout << "Name of player " << 3 << " : ";
		cin >> player_name3;
		cout << "Name of player " << 4 << " : ";
		cin >> player_name4;
	}
	else { cout << "Must enter number between 1 and 4"; }
	cin.ignore();

	player player1(player_name1);
	player player2(player_name2);
	*/
	cout << "Here is the board set up. L stands for ladder, S stands for snake." << endl;
	gameboard.display();

	//player player1("Milly");
	//player player2("Ollie");

	cout << endl;
	/*while (player1.get_position() < gameboard.get_size()) {
		player1.move(gameboard);
		gameboard.display();
		cout << player1.get_name() << " is at square " << player1.get_position() << " a " << gameboard.get_type(player1.get_position()) << " tile" << endl;

		//if on a snake tile, go to start of snake
		if (gameboard.get_type(player1.get_position()) == "snake") {
			int snake_start = player1.get_position();
			snake s1 = snake(player1.get_position(), (player1.get_position() - snake_length));
			player1.snake_move(gameboard, s1);
		}

		else if (gameboard.get_type(player1.get_position()) == "ladder") {
			int ladder_start = player1.get_position();
			ladder l1 = ladder(player1.get_position(), (player1.get_position() + ladder_length));
			player1.ladder_move(gameboard, l1);
		}
		cout << endl;
		cout << endl;

	};*/
	bool loop_until_break = true;

	//while (player1.on_board_check(gameboard) == true && player2.on_board_check(gameboard) == true) {
	/*while (loop_until_break == true) {
		//system("Color 4D");
		string temp;
		cout << "Press enter for " << player1.get_name() << " to roll the dice" << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		player1.move(gameboard);
		gameboard.display();
		cout << player1.get_name() << " is at square " << player1.get_position() << " a " << gameboard.get_type(player1.get_position()) << " tile" << endl;

		//if on a snake tile, go to start of snake
		if (gameboard.get_type(player1.get_position()) == "snake") {
			int snake_start = player1.get_position();
			snake s1 = snake(player1.get_position(), (player1.get_position() - snake_length));
			player1.snake_move(gameboard, s1);
		}

		else if (gameboard.get_type(player1.get_position()) == "ladder") {
			int ladder_start = player1.get_position();
			ladder l1 = ladder(player1.get_position(), (player1.get_position() + ladder_length));
			player1.ladder_move(gameboard, l1);
		}
		cout << endl;
		cout << endl;

		if (player1.on_board_check(gameboard) == false) { 
			cout << player1.get_name() << " won!" << endl;
			break; 
		}


		cout << "Press enter for " << player2.get_name() << " to move" << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		player2.move(gameboard);
		gameboard.display();
		cout << player2.get_name() << " is at square " << player2.get_position() << " a " << gameboard.get_type(player2.get_position()) << " tile" << endl;

		//if on a snake tile, go to start of snake
		if (gameboard.get_type(player2.get_position()) == "snake") {
			int snake_start = player2.get_position();
			snake s1 = snake(player2.get_position(), (player2.get_position() - snake_length));
			player2.snake_move(gameboard, s1);
		}

		else if (gameboard.get_type(player2.get_position()) == "ladder") {
			int ladder_start = player2.get_position();
			ladder l1 = ladder(player2.get_position(), (player2.get_position() + ladder_length));
			player2.ladder_move(gameboard, l1);
		}
		cout << endl;
		cout << endl;
		

		if (player2.on_board_check(gameboard) == false) { 
			cout << player2.get_name() << " won!" << endl;
			break; }

	};*/

	//make a list of player objects, each player in game



	while (loop_until_break == true) {
		for (auto it = player_list.cbegin(); it != player_list.cend(); it++) {

			//system("Color 4D");
			string temp;
			cout << "Press enter for " << (*it)->get_name() << " to roll the dice" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			(*it)->move(gameboard);
			gameboard.display();
			cout << (*it)->get_name() << " is at square " << (*it)->get_position() << " a " << gameboard.get_type((*it)->get_position()) << " tile" << endl;

			//if on a snake tile, go to start of snake
			if (gameboard.get_type((*it)->get_position()) == "snake") {
				int snake_start = (*it)->get_position();
				snake s1 = snake((*it)->get_position(), ((*it)->get_position() - snake_length));
				(*it)->snake_move(gameboard, s1);
			}

			else if (gameboard.get_type((*it)->get_position()) == "ladder") {
				int ladder_start = (*it)->get_position();
				ladder l1 = ladder((*it)->get_position(), ((*it)->get_position() + ladder_length));
				(*it)->ladder_move(gameboard, l1);
			}
			cout << endl;
			cout << endl;

			if ((*it)->on_board_check(gameboard) == false) {
				cout << (*it)->get_name() << " won!" << endl;
				loop_until_break = false;
				break;
			}
			
		}
	}

	//system("Color 3C");

	return 0;
}
