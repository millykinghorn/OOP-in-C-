// Assignment 2: Millikans Oil drop 
//Read in data from 2 different files
//find Mean, Standard Deviation, and standard error on the mean

//TO DO LIST
// - error message for not being able to open file
// - check requirements of task

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include <string>
#include <windows.h>


using namespace std;


double mean(int num_elements, double *my_array) {
   
    double mean;
    double sum = 0;

    for (int i=0; i < num_elements; i++) {
        
        sum = sum + my_array[i];
    }

    mean = sum / num_elements;

    return mean;

}

double standard_dev(int num_elements, double *my_array) {
    
    
    double standard_dev;
    double mean;
    double sum = 0;
    double difference_sq{};

    for (int i = 0; i < num_elements; i++) {
        sum = sum + my_array[i];
    }

    mean = sum / num_elements;

    for (int i = 0; i < num_elements; i++) {
        difference_sq += pow((my_array[i] - mean),2);
    }

    //to solve issue of difference byte sizes in denomincator of standard dev formula
    //use static cast for number of elements
    standard_dev = sqrt((difference_sq) / (static_cast<double>(num_elements) - 1));

    return standard_dev;
}


bool number_check(string line) {

    //cout << line << endl;

    //const int n = line.length();
    const int n = 14;
    //const n;
    // declaring character array 
    char char_array[n + 1];

    // copying the contents of the 
    // string to char array 
    strcpy_s(char_array, line.c_str());
    //cout << "char array = "<<char_array << endl;

    //allows space, dot and digit entries
    for (int i=0; i < n; i++) {
        
        //cout << char_array[i] << endl;

        if (char_array[i] == ' ') {
            //cout << "space" << endl;
        }
        else if (char_array[i] == '.') {
            //cout << "dot" << endl;
        }
        else if (isdigit(char_array[i])) {
            //cout << "digit" << endl;
        }
        else {
            //cout << "letter detected" << endl;
            return false;
        }
        
    }
    return true;

}

int main()
{

    //read in file
    fstream my_file("C:\\Users\\milly\\source\\repos\\ConsoleApplication2\\millikan.txt"); // Check file opened successfully
    string line;

    //initiate iterators for counting number of lines and for the main loop adding to array
    int counter = 0;
    int lines=0;

    //open and close file separately from rest of file
    while(!my_file.eof()){
        (getline(my_file, line));
        lines++;
        //cout << "numner of lines = " << lines << endl;
    }
    cout << "number of lines = " << lines << endl;

    //close and open again to restart getline
    my_file.close();

    my_file.open("C:\\Users\\milly\\source\\repos\\ConsoleApplication2\\millikan.txt");


    //define array 
    int N = lines;
    double* my_array{ new double[N] };

    //while not at the end of the file
    while(!my_file.eof()){

        getline(my_file, line);

        if (number_check(line) == true) {

            my_array[counter] = stod(line);

            ++counter;

            cout << line << "  "<<counter << endl;

        }

        else {

            cout << "non-numerical input detected: ";

            cout << line << endl;

        }
    }
    
    cout << "counter =  " << counter << endl;

    my_file.close();

    //compute mean 
    double mean_value = mean(counter, my_array);
    cout << "mean = "<< mean_value << endl;
        
    //compute standard deviation
    double standard_dev_value = standard_dev(counter, my_array);

    //compute standard error on mean
    double standard_dev_error = standard_dev_value / sqrt(counter);
    cout << "standard deviation = " << standard_dev_value << " +- " << standard_dev_error <<endl;

    delete[] my_array;


    return 0;
}


