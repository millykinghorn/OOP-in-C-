//Assignment 7 OOP in C++
//Milly Kinghorn 15/02/20

#include <iostream>
#include <string>

using namespace std;

//Vector class, Specialised Minkowski 4-vector class, and Particle class

//Create general vector class
class vector
{
    // Friends
    friend ostream& operator<<(ostream& os, const vector& vec);
    friend istream& operator>>(istream& input, vector& vec);

protected:
    double* vector_data{ nullptr };
    int length{ 0 };
public:
    vector() = default; // Default constructor
    vector(size_t n); // Parameterized constructor
    vector(vector& vec); // Copy constructor
    vector& operator=(vector&); //Assignment Operator overload
    vector(vector&& vec) noexcept;  // Move constructor
    vector& operator=(vector&&) noexcept; //Move assignment

    // Destructor
    ~vector() {
        delete[] vector_data;
        std::cout << "Destructor called" << std::endl;
    }

    //() operator to allow access to element of given vector index
    double& operator()(int n) {
        if (n > 0 || n <= length) return vector_data[n];
        else cout << "Vector out of range";
    }

    //dot product calculation
    double dot_product(vector& v) {
        double answer=0;
        if (length == v.length) {
            for (int i{}; i < length; i++) {
                answer = answer + vector_data[i] * v.vector_data[i];
            }
        }
        else {
            cout << "vector do not have the same length" << endl;
        }
        return answer;
    }
};
//outstream overload
ostream& operator<<(ostream& os, const vector& vec) {
    cout << "vector : (";
    for (int i{}; i < vec.length; i++) {
        cout << vec.vector_data[i];
        if (i != vec.length-1) {
            cout << ",";
        }
    }
    cout << ")" << endl;
    return os;
}

istream& operator>>(istream& input, vector& vec) {
    for (int i = 0; i < vec.length; i++) {
        input >> vec.vector_data[i];
    }
    return input;
}

// Member functions defined outside class

//Parametized constructor
vector::vector(size_t n) {
    cout << "Default constructor called" << std::endl;
    length = n;
    //store data in a 1d array
    vector_data = new double[length];

    for (int i{}; i < length; i++) vector_data[i] = 0;
}


//Move Copy Constructor
vector::vector(vector&& arr) noexcept {
    cout << "Move constructor!" << endl;
    length = arr.length;
    vector_data = arr.vector_data;
    arr.length = 0;
    arr.vector_data = nullptr;
}

//Move assignment
vector& vector::operator=(vector&& arr) noexcept {
    cout << "Move assignment!" << endl;
    swap(length, arr.length);
    swap(vector_data, arr.vector_data);
    return *this;
}

//Copy Constructor
vector::vector(vector& arr) {
    cout << "Copy constructor!" << endl;
    // Copy size and declare new array
    vector_data = nullptr; length = arr.length;
    if (length > 0) {
        vector_data = new double[length];
        // Copy values into new array
        for (int i{}; i < length; i++) vector_data[i] = arr.vector_data[i];
    }
}

//Copy Assignment Operator
//for copying to objects which already exist
vector& vector::operator=(vector& arr) {
    cout << "Assignment operator!" << endl;
    if (&arr == this) return *this; // no self assignment
    delete[] vector_data; vector_data = nullptr; length = 0;
    if (arr.length > 0) {
        length = arr.length;
        vector_data = new double[length];
        for (int i{}; i < length; i++) {
            vector_data[i] = arr.vector_data[i];
        }
    }
    return *this;
}


//Specialised minowski class
//Specialised particle class


int main()
{
    int n{};
    cout << "Please enter length of vector: "; 
    cin >> n;
    vector first(n);
    cout << "please enter values of vector separated by space: ";
    cin >> first;
    cout << "first " << first;

    //demo copy constructor
    vector second(first);
    cout << "second " << second;

    //demo assignment operator
    vector third;
    third = first;
    cout << "third " << third;

    //demo move assignment
    vector fourth;
    fourth = move(third);
    cout << "fourth " << fourth;

    //demo dot product
    double dot_prod;
    dot_prod = first.dot_product(second);
    cout << "dot product of first and second = " << dot_prod << endl;

    return 0;
}
