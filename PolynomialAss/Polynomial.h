#pragma once
#include <iostream>
using namespace std;

class Polynomial
{
private:
	int _degree;  // The actual degree of this Polynom
	int _maxDegree;  // The max degree could be in this Polynom
	double* _coeff;
	static int _Max_Degree; // The max degree of all Polynoms
	static int* _arr_Max_Degree; // array of max defree of all Polynoms
	static int ArraySize;
	static int DinSize;		// the actual size of _arr_Max_Degree

public:
	void initPolinom(int degree);

	Polynomial();								//constructor
	Polynomial(int degree);						//constructor
	Polynomial(double c[], int deg);			//constructor
	Polynomial(const Polynomial& other);		//copy constructor

	void setDegree();
	int getDegree(bool what) const;
	void checkSizeArr();
	int findMax(int* arr);
	void updDegree(int* arr, int degree, int coeff);
	void setCoeff(int degree, double coeff);
	double getCoeff(int index) const;
	void print() const;
	static int getMaxDegree();

	//operators

	//print
	friend ostream& operator<<(ostream& output, const Polynomial& p1); //printing using cout

	//addition
	Polynomial operator+ (double d); //adding a number
	Polynomial operator+ (const Polynomial& p2); //adding two polinoms
	//friend Polynomial operator+ (double d, Polynomial& p2); //adding a number, number is on the right

	//subtraction
	Polynomial operator- (double d); //subtracting a number
	Polynomial operator- (const Polynomial& p2); //subtracting two polinoms
	//friend Polynomial operator- (double d, Polynomial& p2); //adding a number, number is on the right

	//multiplication
	Polynomial operator* (double d); //multiplying by a number
	Polynomial operator* (const Polynomial& p2); //multiplying two polinoms - not defined yet
	friend Polynomial operator* (double d, Polynomial& p2); //multiplying by a number, number is on the right

	//implementation
	Polynomial& operator= (const Polynomial& p2);

	//return the "index" coefficient  
	const double& operator[](int index) const;
	double& operator[](int index);

	// Equallity
	bool operator==(const Polynomial& p2) const;

	~Polynomial();			//destructor
};
