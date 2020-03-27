// Assignment 8
//Milly Kinghorn 27/03/20
//Abstract base class with derived classes

#include <iostream>

using namespace std;

double pi = 3.14159265359;

//define general base class for all shapes
class shape {
protected:
	double area{};
	double volume{};
	string type{};
public:
	shape() {};
	//virtual destructor so as not to be called when destroying instances of shapes
	virtual ~shape() {};
	//pure virtual functions which will be overridden in derived classes
	virtual void print_info()=0;
	virtual const double get_area() const =0;
	virtual const double get_volume() const =0;
	//to be used when creating a prism
	virtual const string get_type() const { return type; };
};

//demonstrate inheritance through heirarchy in structure of classes
class twodim : public shape {
//class twodim is a shape
public:
	twodim() {};
	virtual ~twodim() {};
};

class threedim : public shape {
public:
	threedim() {};
	virtual ~threedim() {};
	const double get_area() const { return area; };
	const double get_volume() const { return volume; };
};

//2D shapes

class square : public twodim {
private:
	double width{};
	double area{};
	string type{"Square"};
public:
	//constructor for square specifically including width only
	square(const double width_) :
		width{ width_ }, area{width_*width_}{};
	~square() { cout << "Square destroyed" << endl; };
	const double get_area() const { return area; };
	const double get_volume() const { return 0; };
	const string get_type() const { return type; };
	void print_info() {
		//cout << "Square width = " << width << endl;
		cout << "Sqauare area = " << area << endl;
	}
};

class circle :public twodim {
private:
	double radius{};
	double area{};
	string type{"Circle"};
public:
	circle(const double radius_) :
		radius{ radius_ }, area{ pi * pow(radius_,2)}{};
	~circle() { cout << "Circle destroyed" << endl; };
	const double get_area() const { return area; };
	const double get_volume() const { return 0; };
	const string get_type() const { return type; };
	void print_info() {
		//cout << "Circle radius = " << radius << endl;
		cout << "Circle area = " << area << endl;
	}
};

class rectangle : public twodim {
private:
	double width{};
	double height{};
	double area{};
	string type{"Rectangle"};
public:
	rectangle(const double width_, const double height_) :
		width{ width_ }, height{ height_ }, area{ width_ * height_ }{};
	~rectangle() { cout << "Rectangle destroyed" << endl; };
	const double get_area() const { return area; };
	const double get_volume() const { return 0; };
	const string get_type() const { return type; };
	void print_info() {
		//cout << "Rectangle width = " << width << endl;
		//cout << "Rectangle height = " << height << endl;
		cout << "Rectangle area = " << area << endl;
	}
};

class ellipse : public twodim {
private:
	double radius_major{};
	double radius_minor{};
	double area{};
	string type{"Ellipse"};
public:
	ellipse(const double radius_minor_, const double radius_major_) :
		radius_major{ radius_major_ }, radius_minor{ radius_minor_ }, area{ radius_major_ * radius_minor_ * pi }{};
	~ellipse() { cout << "Ellipse destroyed" << endl; };
	const string get_type() const { return type; };
	const double get_area() const { return area; };
	const double get_volume() const { return 0; };
	void print_info() {
		//cout << "Ellipse major radius = " << radius_major << endl;
		//cout << "Ellipse minor radius = " << radius_minor << endl;
		cout << "Ellipse area = " << area << endl;
	}
};

//3D shapes

class cube : public threedim {
private:
	double width{};
	double area{};
	double volume{};
public:
	cube(const double width_) :
		width{ width_ }, area{ 6 * pow(width_ ,2)}, volume{ pow(width_ ,3)}{};
	~cube() { cout << "Cube destroyed" << endl; };
	void print_info() {
		//cout << "Cube width = " << width << endl;
		cout << "Cube area = " << area << endl;
		cout << "Cube volume = " << volume << endl;
	}
};

class cuboid : public threedim {
private:
	double width{};
	double height{};
	double depth{};
	double area{};
	double volume{};
public:
	cuboid(const double width_, const double height_, const double depth_) :
		width{ width_ }, height{ height_ }, depth{ depth_ }, area{ 2 * width_ * height_ + 2 * width_ * depth_ + 2 * depth_ * height_ }, volume{ width_ * height_ * depth_ }{};
	~cuboid() { cout << "Cuboid destroyed" << endl; };
	void print_info() {
		//cout << "Cuboid width = " << width << endl;
		//cout << "Cuboid height = " << height << endl;
		//cout << "Cuboid depth = " << depth << endl;
		cout << "Cuboid area = " << area << endl;
		cout << "Cuboid volume = " << volume << endl;
	}
};
class sphere : public threedim {
private:
	double radius{};
	double area{};
	double volume{};
public:
	sphere(const double radius_) :
		radius{ radius_ }, area{ 4 * pi * pow(radius_,2)}, volume{ (4*pi*pow(radius_,3))/3}{};
	~sphere() { cout << "Sphere destroyed" << endl; };
	void print_info() {
		//cout << "Sphere radius = " << radius << endl;
		cout << "Sphere area = " << area << endl;
		cout << "Sphere volume = " << volume << endl;
	}
};

class ellipsoid: public threedim {
private:
	double semi_axis_a{};
	double semi_axis_b{};
	double semi_axis_c{};
	double area{};
	double volume{};
public:
	ellipsoid(const double a, const double b, const double c) :
		semi_axis_a{ a }, semi_axis_b{ b }, semi_axis_c{ c }, volume{ (4 * pi * a * b * c )/3 }{
		//Knud Thomsen's formula for SA
		double p = 1.6075; //choice of const has max error of 1.061%
		double term = pow(a, p) * pow(b, p) + pow(a, p) * pow(c, p) + pow(b, p) * pow(c, p);
		area = 4 * pi * pow(term / 3, 1 / p);
	};
	~ellipsoid() { cout << "Ellipsoid destroyed" << endl; };
	void print_info() {
		//cout << "Ellisoid semi axis a = " << semi_axis_a << endl;
		//cout << "Ellisoid semi axis b = " << semi_axis_b << endl;
		//cout << "Ellisoid semi axis c = " << semi_axis_c << endl;
		cout << "Ellisoid area = " << area << endl;
		cout << "Ellisoid volume = " << volume << endl;
	}
};

class prism : public threedim {
private:
	twodim* face{};
	double depth{};
	double area{};
	double volume{};
public:
	prism(const double depth_, twodim* shape_) :
		depth{ depth_ }, face{ shape_ }, area{ shape_->get_area() }, volume{ shape_->get_area() * depth }{};
	~prism() { cout << "Prism destroyed" << endl; };
	void print_info() {
		//cout << "Prism depth = " << depth << endl;
		cout << "Prism face shape = " << face->get_type() << endl;
		cout << "Prism volume = " << volume << endl;
	}
};



int main()
{

	//implement array of 8 base class pointers, each pointing to a different shape
	int N{ 8 };
	shape** shape_array = new shape*[N];

	shape_array[0] = new square(2);
	shape_array[1] = new circle(2);
	shape_array[2] = new rectangle(2,3);
	shape_array[3] = new ellipse(2, 3);
	shape_array[4] = new cube(2);
	shape_array[5] = new cuboid(2, 3, 4);
	shape_array[6] = new sphere(2);
	shape_array[7] = new ellipsoid(2, 3, 4);
	

	//print out info for all shapes
	for (int i{}; i < N; i++) {
		shape_array[i]->print_info();
	}
	
	//clean up
	for (int i{}; i < N; i++) {
		delete shape_array[i];
	}

	delete[] shape_array;

	//define face of prism as a 2D shape
	circle face(2);
	prism prism1(3, &face);
	cout << endl; //separate from other info printed out
	prism1.print_info();

	return 0;
}
