// Assignment 6
// Milly Kinghorn 05/03/20
// OOP in C++
//Writing a class of matrices

#include<iostream>
#include<sstream>

using namespace std;

class matrix
{
    // Friends
    friend ostream& operator<<(ostream& os, const matrix& mat);
    friend istream& operator>>(istream& input, matrix& mat);
private:
    double* matrix_data{ nullptr };
    int rows{ 0 };
    int columns{ 0 };
    int size = rows * columns;
public:
    matrix() = default; // Default constructor
    matrix(size_t m, size_t n); // Parameterized constructor
    matrix(matrix& arr); // Copy constructor
    matrix& operator=(matrix&); //Assignment Operator overload
    matrix(matrix&& arr) noexcept;  // Move constructor
    matrix& operator=(matrix&&) noexcept; //Move assignment

    // Destructor
    ~matrix() {
        delete[] matrix_data;
        std::cout << "Destructor called" << std::endl;
    }

    //remove ith row and jth column
    matrix delete_row(int i, int j);

    // Access functions
    int get_rows() const { return rows; } // Return number of rows
    int get_cols() const { return columns; } // Return number of columns
    int index(int m, int n) const // Return position in array of element (m,n)
    {
        if (m > 0 && m <= rows && n > 0 && n <= columns) return (n - 1) + (m - 1) * columns;
        else { std::cout << "Error: out of range" << endl; exit(1); }
    }

    //() operator to allow access to element of given matrix index
    double& operator()(int m, int n) { return matrix_data[index(m, n)]; }

};

// Member functions defined outside class

//Parametized constructor
matrix::matrix(size_t m, size_t n) {
    cout << "Default constructor called" << std::endl;
    rows = m;
    columns = n;
    //store data in a 1d array
    int size = rows * columns;
    matrix_data = new double[size];

    for (int i{}; i < size; i++) matrix_data[i] = 0;

    //see what's going on
    //cout << "number of elements = " << size << endl;
    //for (int i{}; i < size; i++) cout << matrix_data[i];
    //cout << endl;
}


//Move Copy Constructor
matrix::matrix(matrix &&arr) noexcept{
    cout << "Move constructor!" << endl;
    size = arr.size;
    matrix_data = arr.matrix_data;
    arr.size = 0;
    arr.matrix_data = nullptr;
}

//Move assignment
matrix& matrix::operator=(matrix&& arr) noexcept{
    cout << "Move assignment!" << endl;
    swap(size, arr.size);
    swap(matrix_data, arr.matrix_data);
    return *this;
}

//Copy Constructor
matrix::matrix(matrix& arr){
    // Copy size and declare new array
    matrix_data = nullptr; size = arr.size; rows = arr.rows; columns = arr.columns;
    if (size > 0){
        matrix_data = new double[size];
        // Copy values into new array
        for (size_t i{}; i < size; i++) matrix_data[i] = arr.matrix_data[i];
    }
}

//Copy Assignment Operator
//for copying to objects which already exist
matrix & matrix::operator=(matrix& arr) {
    if (&arr == this) return *this; // no self assignment
    delete[] matrix_data; matrix_data = nullptr; size = 0;
    size = arr.rows * arr.columns;
    if (size > 0) {
        matrix_data = new double[size];
        for (size_t i{}; i < size; i++) matrix_data[i] = arr.matrix_data[i];
    }
    return *this;
}


matrix matrix::delete_row( int i, int j) {

    int cols = get_cols();
    int rows = get_rows();

    //define new matrix to add selected elements to
    matrix removed(rows - 1, cols - 1);

    //index of new matrix
    int index_new = 0;

    cout << *this;

    for (int index_old{}; index_old < size; index_old++) {
        //algorithms I made to only allow elements of the correct index to be put into new matrix
        if ((index_old < (cols * (i - 1)) || index_old >= (cols * i))) {
            if ((index_old - j + 1) % cols != 0) {
                removed.matrix_data[index_new] = matrix_data[index_old];
                //cout << "counter " << index_new << " iterator " << index_old << " " << matrix_data[index_old] << endl;
                index_new++;
            }     
        }
    }
  
    index_new = 0;

    cout << endl <<removed << endl;

    return removed;

}

// Overload output operator
ostream& operator<<(ostream& os, const matrix& mat)
{
    int column_counter = 0;
    for (int i{}; i < mat.rows; i++) {
        for (int i{}; i < mat.columns; i++) {
            cout << mat.matrix_data[column_counter] << " ";
            column_counter++;
        }
        //new line for each row
        cout << endl;
    }
    return os;
}

//Overload input operators
istream& operator>>(istream& input, matrix& mat) {
    mat.size = mat.rows * mat.columns;
    for (int i=0; i < mat.size; i++) {
        input >> mat.matrix_data[i];
    }
    return input;
}

//Other functions

bool dimension_check(matrix mat1, matrix mat2) 
{
    int mat1_columns = mat1.get_cols();
    int mat1_rows = mat1.get_rows();
    int mat2_columns = mat2.get_cols();
    int mat2_rows = mat2.get_rows();

    if ((mat1_columns== mat2_columns) && (mat1_rows == mat2_rows)) {
        return true;
    }
    else {
        return false;
    }
}

bool multiplication_check(matrix mat1, matrix mat2) {
    int mat1_columns = mat1.get_cols();
    int mat1_rows = mat1.get_rows();
    int mat2_columns = mat2.get_cols();
    int mat2_rows = mat2.get_rows();

    if (mat1_columns == mat2_rows) {
        return true;
    }
    else {
        return false;
    }
}

matrix add(matrix mat1, matrix mat2) {
    
    if (dimension_check(mat1, mat2)) { //if same dimension, has same indexing
        
        matrix output{ mat1 };
        for (int i = 1; i < mat1.get_rows()+1; i++) {
            for (int j = 1; j < mat1.get_cols()+1; j++) {
                output(i, j) = mat1(i, j) + mat2(i, j);
            }
        }
        cout << mat1  << "+" << endl << mat2  << "=" <<endl<< output;
        return output;
    }
    else {
        cout << "Matrices not the same dimension";
        return mat1;
    }
}

matrix subtract(matrix mat1, matrix mat2) {

    if (dimension_check(mat1, mat2)) { //if same dimension, has same indexing

        matrix output{ mat1 };
        for (int i = 1; i < mat1.get_rows() + 1; i++) {
            for (int j = 1; j < mat1.get_cols() + 1; j++) {
                output(i, j) = mat1(i, j) - mat2(i, j);
            }
        }
        cout << mat1 << "-" << endl << mat2 << "=" << endl << output;
        return output;
    }
    else {
        cout << "Matrices not the same dimension";
        return mat1;
    }
}

matrix multiply(matrix mat1, matrix mat2) {
    if (multiplication_check(mat1, mat2)) { //if same dimension, has same indexing


        //define as matrix of zeros with correct dimensions
        //mxn * nxk = mxk dimensions of product
        matrix output(mat1.get_rows(), mat2.get_cols());
        //cout << "original matrix: " << endl << output;
        for (int i = 1; i < mat1.get_rows() + 1; i++) {
            for (int j = 1; j < mat1.get_cols() + 1; j++) {
                for (int k = 1; k < mat1.get_cols() + 1; k++) {
                    //cout << mat1(i, k) << " * " << mat2(k, j) <<endl;
                    output(i, j) = output(i, j) + mat1(i, k) * mat2(k, j);
                }
            }
        }
        cout << mat1 << "*" << endl << mat2 << "=" << endl << output;
        return output;
    }
    else {
        cout << "Matrices not the correct dimensions";
        return mat1;
    }

}


// Main program

int main(){

    //declare with no info
    matrix a1;
    
    const int m{ 3 };
    const int n{ 3 };

    //parametized declaration
    matrix a2(m, n);
    
    //enter some elements in rows
    cout << "Please enter values for a " << m << "x" << n << " matrix, separated by a space: ";
    cin >> a2;
    cout << "Original matrix a2 = " << endl;
    cout << a2;
    
    //parametized declaration
    matrix a3(m, n);

    //Demonstrate assignment operator
    cout << "Before copy, a3 = " << endl << a3 <<endl;
    a3 = a2;
    cout << "After copy, a3 =  " << endl << a3 << endl;
    //Modify a2 and show changes are not applied to a3
    a2(1, 1) = 9;
    cout << "Changed element (1,1) of a2 = 9" << endl;
    cout << "a2 = " << endl;
    cout << a2;
    cout << endl<< "a3 = " << endl;
    cout << a3;

    //Demonstrate copy constructor
    matrix a4( a2 );
    cout << "Created new matrix a4 as a copy of a2: " << endl;
    cout << a4;
    //Modify a2 and show changes are not applied to a4
    a2(1, 1) = 0;
    cout << "Changed element (1,1) of a2 = 0" << endl;
    cout << "a2 = " << endl;
    cout << a2;
    cout << endl << "a4 = " << endl;
    cout << a4;
    
    //Move assignmment construction demonstration
    matrix a5(m, n);
    cout << "Demonstration of move assignment conctruction "<<endl<<"Before copy, a5 = " << endl << a5 << endl;
    a5 = move(a2);
    cout << "After copy, a5 =  " << endl << a5 << endl;

    // Addition of 2 matrices
    matrix a7 = add(a3, a4);
    //cout << a7;

    // Subtraction of 2 matrices
    matrix a8 = subtract(a3, a4);

    // Multiplication of 2 matrices
    matrix a9 = multiply(a3, a4);

    //Removing ith row and jth column
    int row_remove;
    int col_remove;

    cout << "Which row would you like to delete? ";
    cin >> row_remove;
    cout << "Which column would you like to delete? ";
    cin >> col_remove;

    matrix a10 = a3.delete_row(row_remove, col_remove);    

    return 0;
}
