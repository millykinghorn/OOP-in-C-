// PHYS 30762 Programming in C++
// Assignment 5 - Milly Kinghorn

#include<iostream>
#include<cmath>
#include<sstream>

using namespace std;

class complex
{
    //operation instertion function
    // Make function to overload operator<< a friend
    friend ostream& operator<<(ostream& os, const complex& z);
    friend istream& operator>>(istream& is, complex& z);

private:
    double re, im;

public:
    // Constructors & destructor
    complex() { re = im = 0; }
    complex(double real_part, double im_part) { re = real_part; im = im_part; }
    ~complex() {}

    // Return real component
    double get_re() const { return re; }

    // Return imaginary component
    double get_im() const { return im; }

    // Return modulus
    double modulus() const { return sqrt((re, 2) + pow(im, 2)); }

    // Return argument in radians
    double argument() const { return sin(im / re); }

    // Return complex conjugate
    complex complex_conjugate() { return { re, -1 * im }; }

    // Overload + operator for addition 
    complex operator+(const complex& v) const {
        complex temp{ re + v.re, im + v.im };
        return temp;
    }

    // Overload - operator for subtraction
    complex operator-(const complex& v) const {
        complex temp{ re - v.re, im - v.im };
        return temp;
    }

    // Overload * operator for multiplication, z1*z2
    complex operator*(const complex& v) const {
        complex temp{ re*v.re - im*v.re, re*v.im + im*v.re };
        return temp;
    }

    // Overload / operator for division, z1/z2
    complex operator/(const complex& v) const {
        //multiply denominator and numberator by complex conjugate
        double denominator = pow(v.re, 2) + pow(v.im, 2);
        double numerator_re = (re*v.re + im*v.im);
        double numerator_im = (-1*re*v.im + im*v.re);
        complex division{numerator_re/denominator, numerator_im/denominator};
        return division;
    }

    //Function to print out data
    void show() const { cout << "(" << re << " + " << im << "i"<<")" << std::endl; }

};


// Function to overload << operator for complex numbers
ostream& operator<<(ostream& os, const complex& z) {
    if (z.im > 0) {
        os << "(" << z.re << " + " << z.im << "i" << ")";
        return os;
    }
    else if (z.im < 0) {
        os << "(" << z.re << " - " << -1*z.im << "i" << ")";
        return os;
    }
    else {
        return os;
    }
}

//Function to overload >> operator
istream& operator>>(istream& input, complex& z) {

    char sign;
    char i;

    input >> z.re >> sign >> z.im >> i;

    if (sign == '-'){
        z.im = -1 * z.im;
    }

    return input;

}

int main()
{

    string input;
    complex a;
    complex b;

    // Create two complex numbers
    cout << "Please enter complex number a: ";
    cin >> a;
    cout << "Please enter complex number b: ";
    cin >> b;

    //complex a{ 3,4 };
    //complex b{ 1,-2 };

    // Get real and imaginary components, modulus and argument
    double a_real = a.get_re();
    double b_real = b.get_re();
    double a_im = a.get_im();
    double b_im = b.get_im();

     // Get conjugates
    complex a_conjugate = a.complex_conjugate();
    complex b_conjugate = b.complex_conjugate();

     // Get sum, difference, product and quotient of a and b
    complex a_b_sum = a.operator+(b);
    complex a_b_quotient = a.operator/(b);

     // Print out results, also demonstrating use of overloaded operator<<
    cout << "a = " << a << endl;
    cout << "a* =  " << a_conjugate << endl;
    cout << "b = " << b <<endl;
    cout << "b* =  " << b_conjugate <<endl;
    cout << "a+b = "<< a_b_sum <<endl;
    cout << "a/b = "<< a_b_quotient <<endl;

}