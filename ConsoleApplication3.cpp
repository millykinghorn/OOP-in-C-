// Object Orientated Programming Assignment 3
//Reading and storing physics courselist
//Milly Kinghorn 10/02/20

// Simple code to store courses using vectors and strings

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>

using namespace std;

int first_digit(int n)
{
    // Remove last digit from number
    // till only one digit is left
    while (n >= 10)
        n /= 10;

    return n;
}


struct course
{
    int course_number{};
    string course_title{};
};

bool compare_number(course i, course j) {
    return (i.course_number < j.course_number);
}

bool compare_title(course i, course j) {
    return (i.course_title < j.course_title);
}


int main(void)

{
    const string degree_code("PHYS");
    string user_input;
    string full_title_input;
    int counter = 0;

    //try pushing the structure back into a vector as opposed to a string
    vector<course> courses;

    //boolean to judge when to stop allowing user entries
    bool not_finished(true);

    do

    {
        cout << "Please enter the course title (or x to finish): ";

        //need to allow spaces to be inputted so use getline instead of cin
        getline(cin, user_input, '\n');

        //split input into integer and string
        stringstream ss(user_input);

        //define temporary string for each section of input
        string temp;
        string string_temp;

        //integer to test if stringstream is number
        int x;

        //push back each new entry as a new structure to the vector
        courses.push_back(course());

        //only allow 1 numerical entry, e.g. for maths 2 do not start new stringstream 2
        bool is_full(false);

        while (!ss.eof()) {

            //extracting word by word from stream
            ss >> temp;

            //Checking the given word is integer by seeing if can allocate to integer
            if ((stringstream(temp) >> x) && (is_full == false)) {

                //need to ADD to structure, not replace.
                stringstream(temp) >> courses[counter].course_number;

                is_full = true;
            }
            else {
                //concat to previous strings before allocating to this
                string_temp = string_temp + " " + temp;
            }
            //add concated strings to string member of course_title
            courses[counter].course_title = string_temp;

            //save memory
            temp = "";
        }
        counter = counter + 1;

        //if chose to exit, finish loop and remove the "x" course title imput
        if (user_input == "x") {
            not_finished = false;

            //remove last element = "x" from vector
            courses.pop_back();
        }

    } while (not_finished);

    // Print out full list of courses using iterables
    for (size_t i = 0; i < courses.size(); i++) {
        cout << courses[i].course_number << courses[i].course_title << std::endl;
    };

    //choose a year of course codes or sort by title/course number
    string yearChoice;
    string sortOption;
    int year_choice_int;

    cout << "Please enter year: " << endl;
    cin >> yearChoice;

    if (stringstream(yearChoice) >> year_choice_int) {

        for (size_t i = 0; i < courses.size(); i++) {

            //turn first digit into integer
            int first_digit_value = first_digit(courses[i].course_number);

            if (first_digit_value == year_choice_int) {
                cout << "match with year choice:  " << courses[i].course_number << courses[i].course_title << endl;
            }
        }
    }
    else {

        cout << "Please enter integer for year of choice" << endl;
    }

    cout << "Sort by year or title? " << endl;
    cin >> sortOption;

    bool wrong_entry(true);

    if (sortOption == "year") {

        sort(courses.begin(), courses.end(), compare_number);

        for (size_t i{}; i < courses.size(); i++) {
            cout << courses[i].course_number << courses[i].course_title << std::endl;
        }
    }
    else if (sortOption == "title") {

        sort(courses.begin(), courses.end(), compare_title);

        for (size_t i{}; i < courses.size(); i++) {
            cout << courses[i].course_number << courses[i].course_title << std::endl;
        }
    }

    else {
        cout << "please enter either \"title\" or \"year\"" << endl;

    }

    return 0;

}
