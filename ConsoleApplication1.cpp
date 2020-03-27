// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.

//TO DO LIST//////////////////////
// add checks for integers: if integer, allow to coontinue

#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <math.h>

//#include <bits/stdc++.h> 

using namespace std;


//define energy funtion outside main function
//nj = final energy level, ni = initial energy level
double energy(int z, int ni, int nj) {
	
	float result;

	result = 13.6*z*z*(pow(nj,-2) - pow(ni,-2));

	return result;

}

double ev_to_joules(float a) {
	
	float result;

	float constant = 1.602 * pow(10, -19);

	result = a * constant;

	return result;
}

//unused for the moment
string convert_to_lowercase(string a) {


	for (int i = 0; i < a.size(); i++) {
		putchar(tolower(a[i]));
			}
	cout << a << endl;
	
	//cout << a << endl;
	return a;
	//return 0;

}

//check in input is either ev or joules

bool unit_check(string input) {
	if (input == "ev"){
		return true;
	}
	else if (input == "joules") {
		return true;
	}
	else{

		cout << "PLease enter \"ev\" or \"joules\" in lower case letters." << endl;
		return false;
	}
}

//needs to be ain integer greater than 0
bool integer_check(float x) {

	float fractpart, intpart;

	fractpart = modf(x, &intpart);
	
	//check is not string
	if (!x) {
		return false;
	}

	else if (x>0){
		cout << intpart <<" + " << fractpart << endl;
		return true;
	}

	else {

		return false;
	}

}


//calculate energy of transition for bhor model of electron
int main()
{
	int z;
	int ni;
	int nj;
	string unit;
	bool answerable;
	string again;

	again = "y";

	do {
		do {
			cout << "Please enter a valid atomic number" << endl;
			cin >> z;
		} while (integer_check(z) == false);

		do {
			cout << "Please enter the initial energy state" << endl;
			cin >> ni;
		} while (integer_check(ni) == false);

		do {
			cout << "Please enter the final energy state" << endl;
			cin >> nj;
		} while (integer_check(nj) == false);

		do {
			cout << "Would you like the answer in eV or Joules? PLease enter in lowercase." << endl;
			cin >> unit;
		} while (unit_check(unit) == false);

		float energy_value = energy(z, ni, nj);

		if (unit == "joules") {


			energy_value = ev_to_joules(energy_value);

			cout << "Value for energy is E = " << energy_value << " J" << endl;

			//answerable = true;
		}

		else if (unit == "ev") {

			cout << "Value for energy is E = " << energy_value << " eV" << endl;

			//answerable = true;
		}

		cout << "Would you like to go again? (y/n)" << endl;
		cin >> again;

		
	} while (again == "y");
		
}
