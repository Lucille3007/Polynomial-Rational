#pragma once
#include <iostream>
#include "Polynomial.h"
using namespace std;


class Rational
{
private:
	Polynomial _nom;
	Polynomial _denom;

public:

	Rational();													//constructor
	Rational(const Polynomial& p1, const Polynomial& p2);		//constructor

	Polynomial getNom() const;
	Polynomial getDenom() const;
	void print() const;

	//operators

	//print
	friend ostream& operator<<(ostream& output, const Rational& p1); //printing using cout

	//addition
	Rational operator+ (double d); //adding a number
	Rational operator+ (const Rational& p2); //adding two Rationals

	//subtraction
	Rational operator- (double d); //subtracting a number
	Rational operator- (const Rational& p2); //subtracting two Rationals

	//multiplication
	Rational operator* (double d); //multiplying by a number
	Rational operator* (const Rational& p2); //multiplying two Rationals - not defined yet
	friend Rational operator* (double d, Rational& p2); //multiplying by a number, number is on the right

	//implementation
	Rational& operator= (const Rational& p2);


	~Rational();		//destructor
};