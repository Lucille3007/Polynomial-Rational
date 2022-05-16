#include <iostream>
#include "Rational.h"
#include "Polynomial.h"



Rational::Rational() : _nom(0), _denom(0)
{
	_denom.setCoeff(0, 1);
}

Rational::Rational(const Polynomial& p1, const Polynomial& p2)
	: _nom(p1), _denom(p2)
{ }

Polynomial Rational::getNom() const
{
	return this->_nom;
}

Polynomial Rational::getDenom() const
{
	return this->_denom;
}

void Rational::print() const
{
	_nom.print();
	cout << "--------------------------" << endl;
	_denom.print();
}

Rational:: ~Rational()
{
}

// *************************************** operators ***************************************

ostream& operator<<(ostream& output, const Rational& r1)
{
	cout << "numerator=";
	r1._nom.print();
	cout << "--------------------------" << endl;
	cout << "denominator=";
	r1._denom.print();
	return output;
}

//addition
Rational Rational::operator+ (double d)
{
	Rational result(this->_nom, this->_denom);
	result._nom = _nom + d;

	return result;
}

Rational Rational::operator+ (const Rational& p2)
{

	if ((this->_denom) == (p2._denom))
	{
		Rational result((this->_nom) + (p2._nom), (this->_denom));
		return result;
	}
	else
	{
		Polynomial nom1((this->_nom) * (p2._denom));
		Polynomial nom2((this->_denom) * (p2._nom));

		Rational result(nom1 + nom2, (this->_denom) * (p2._denom));

		return result;
	}
}


//subtraction
Rational Rational::operator- (double d)
{
	Rational result(this->_nom, this->_denom);
	result._nom = _nom - d;

	return result;
}

Rational Rational::operator- (const Rational& p2)
{
	if ((this->_denom) == (p2._denom))
	{
		Rational result((this->_nom) - (p2._nom), (this->_denom));
		return result;
	}
	else
	{
		Polynomial nom1((this->_nom) * (p2._denom));
		Polynomial nom2((this->_denom) * (p2._nom));

		Rational result(nom1 - nom2, (this->_denom) * (p2._denom));

		return result;
	}

}


//multiplication
Rational Rational :: operator* (double d)
{
	Rational result(this->_nom * d, this->_denom);
	return result;

}
Rational Rational :: operator* (const Rational& p2)
{
	Rational result(this->_nom * p2._nom, this->_denom * p2._denom);

	return result;
}
Rational operator* (double d, Rational& p2)
{
	return(p2 * d);
}



Rational& Rational::operator= (const Rational& p2)
{
	this->_nom = p2._nom;
	this->_denom = p2._denom;

	return *this;
}
