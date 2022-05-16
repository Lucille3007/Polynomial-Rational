#include <iostream>
#include <assert.h>
#include "Polynomial.h"


int Polynomial::_Max_Degree = 0;
int Polynomial::ArraySize = 2;
int Polynomial::DinSize = 0;


int* Polynomial::_arr_Max_Degree = new int[ArraySize] { 0 };

void Polynomial::checkSizeArr()
{
	if (ArraySize == DinSize)
	{
		int* temp = _arr_Max_Degree;
		ArraySize *= 2;
		_arr_Max_Degree = new int[ArraySize] { 0 };

		for (int i = 0; i < (ArraySize / 2); i++)
		{
			_arr_Max_Degree[i] = temp[i];
		}
		delete[] temp;
	}
}

void Polynomial::initPolinom(int degree)
{
	this->_maxDegree = degree;
	this->_coeff = new double[_maxDegree + 1]{ 0 };
	this->_degree = 0;
	if (_arr_Max_Degree == NULL)
		_arr_Max_Degree = new int[ArraySize] { 0 };
	checkSizeArr();
}

Polynomial::Polynomial()
{
	initPolinom(0);
	_arr_Max_Degree[DinSize++] = 0;
}


Polynomial::Polynomial(int degree)
{
	initPolinom(degree);
	_arr_Max_Degree[DinSize++] = 0;
}

Polynomial::Polynomial(double c[], int deg)
{
	initPolinom(deg);

	for (int i = 0; i <= _maxDegree; i++)
	{
		this->_coeff[i] = c[i];
	}

	setDegree();
	_arr_Max_Degree[DinSize++] = _degree;
}

Polynomial::Polynomial(const Polynomial& other)
	: _degree(other._degree), _maxDegree(other._maxDegree)
{
	_coeff = new double[_maxDegree + 1];

	for (int i = 0; i <= _degree; i++)
		this->_coeff[i] = other._coeff[i];

	checkSizeArr();

	_arr_Max_Degree[DinSize++] = _degree;
}

int Polynomial::findMax(int* arr)
{
	int max = 0;
	for (int i = 0; i < DinSize; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

void Polynomial::updDegree(int* arr, int degree, int coeff)
{
	for (int i = 0; i < DinSize; i++)
	{
		if (arr[i] == _degree)
		{
			if (coeff == 0.0)
			{
				setDegree();
				arr[i] = _degree;

				if (_Max_Degree == degree)
				{
					_Max_Degree = findMax(_arr_Max_Degree);
				}
			}
			else
				arr[i] = degree;
		}

	}
}

void Polynomial::setDegree()
{
	this->_degree = _maxDegree;

	for (int i = _maxDegree; i > 0; i--)
	{
		if (_coeff[i] == 0.0)
			_degree--;
		else
			break;
	}
	if (_degree > _Max_Degree)
		this->_Max_Degree = _degree; //עדכון החזקה המקסימלית
}


int Polynomial::getDegree(bool what) const
{
	if (what)
		return(this->_degree);
	else
		return(this->_maxDegree);
}

int Polynomial::getMaxDegree()
{
	return (_Max_Degree);
}

void Polynomial::setCoeff(int degree, double coeff)
{
	if (degree >= 0)
	{
		if (degree > this->_maxDegree)
		{
			this->_maxDegree = degree;

			double* temp = new double[this->_maxDegree + 1]{ 0 };

			for (int i = 0; i <= this->_degree; i++)
				temp[i] = this->_coeff[i];

			this->_coeff = new double[this->_maxDegree + 1]{ 0 };

			this->_degree = degree;

			for (int i = 0; i <= _degree; i++)
				this->_coeff[i] = temp[i];

			delete[] temp;
		}
		_coeff[degree] = coeff;

		if (degree >= _degree)
			updDegree(_arr_Max_Degree, degree, coeff);

		setDegree();
	}
}

double Polynomial::getCoeff(int index) const
{
	if (index < 0 || index >_maxDegree)
		return (-1234.56);
	else
		return this->_coeff[index];
}

void Polynomial::print() const
{
	cout << "polynomial = " << this->_coeff[0];

	for (int i = 1; i <= this->_degree; i++)
	{
		cout << "+(" << this->_coeff[i] << ")*X^" << i;
	}
	cout << endl;
}

Polynomial:: ~Polynomial()
{
	int max = _degree;
	int i = 0;
	for (i = 0; i < DinSize; i++)
	{
		if (_arr_Max_Degree[i] == max)
			break;
	}
	_arr_Max_Degree[i] = _arr_Max_Degree[DinSize - 1];
	DinSize--;

	if (DinSize == 0)
	{
		delete[] _arr_Max_Degree;
		_arr_Max_Degree = NULL;
		ArraySize = 2;
	}
	else
		_Max_Degree = findMax(_arr_Max_Degree);

	delete[] _coeff;

	//cout << "Polynomial destructor" << endl;
}




// *************************************** operators ***************************************

ostream& operator<<(ostream& output, const Polynomial& p1)
{
	p1.print();
	return output;
}

Polynomial& Polynomial::operator= (const Polynomial& p2)
{
	updDegree(_arr_Max_Degree, this->_degree, p2._degree);

	this->_degree = p2._degree;
	this->_maxDegree = p2._maxDegree;

	_coeff = new double[_maxDegree + 1];

	for (int i = 0; i <= _degree; i++)
		this->_coeff[i] = p2._coeff[i];

	_arr_Max_Degree[DinSize++] = this->_degree;
	return *this;
}

Polynomial Polynomial::operator+ (const Polynomial& p2)
{
	int maxDeg, max, min, flag;
	int i;

	if (this->_maxDegree > p2._maxDegree)
	{
		maxDeg = this->_maxDegree;
		max = this->_degree;
		min = p2._degree;
		flag = 1;
	}
	else
	{
		maxDeg = p2._maxDegree;
		max = p2._degree;
		min = this->_degree;
		flag = 0;
	}

	double* c = new double[maxDeg + 1]{ 0 };
	for (i = 0; i <= min; i++)
	{
		c[i] = this->_coeff[i] + p2._coeff[i];
	}
	for (; i <= max; i++)
	{
		if (flag)
			c[i] = this->_coeff[i];
		else
			c[i] = p2._coeff[i];
	}

	Polynomial result(c, max);
	return result;
}

Polynomial Polynomial::operator+ (double d)
{
	Polynomial result(this->_coeff, this->_degree);
	result._coeff[0] += d;
	return result;
}

//Polynomial operator+(double d, Polynomial& p2)
//{
//	p2._coeff[0] += d;
//	return p2 + d;
//}

Polynomial Polynomial::operator- (const Polynomial& p2)
{
	int max, min, flag;
	int i;
	(_maxDegree > p2._maxDegree) ? max = _maxDegree, min = p2._maxDegree, flag = 1 : max = p2._maxDegree, min = _maxDegree, flag = 0;
	double* c = new double[max + 1]{ 0 };
	for (i = 0; i <= min; i++)
	{
		c[i] = _coeff[i] - p2._coeff[i];
	}
	for (; i <= max; i++)
	{
		if (flag)
			c[i] = _coeff[i];
		else
			c[i] = -1 * (p2._coeff[i]);
	}
	Polynomial result(c, max);
	return result;
}

Polynomial Polynomial::operator- (double d)
{
	Polynomial result(this->_coeff, this->_degree);
	result._coeff[0] -= d;
	return result;
}

//Polynomial operator- (double d, Polynomial& p2)
//{
//	p2._coeff[0] -= d;
//	return p2;
//}

Polynomial Polynomial::operator* (double d)
{
	Polynomial result(_coeff, _degree);
	for (int i = 0; i <= _degree; i++)
	{
		_coeff[i] *= d;
	}
	return result;
}

Polynomial operator* (double d, Polynomial& p2)
{
	return p2 * d;
}

Polynomial Polynomial::operator* (const Polynomial& p2)
{
	int max = (this->_maxDegree) + (p2._maxDegree);
	double* c = new double[max + 1]{ 0 };

	for (int i = 0; i <= this->_degree; i++)
	{
		for (int j = 0; j <= p2._degree; j++)
			c[i + j] = (_coeff[i] * (p2._coeff[j])) + c[i + j];
	}

	Polynomial result(c, max);

	return result;
}


const double& Polynomial::operator[](int index) const
{
	return (this->getCoeff(index));
}

double& Polynomial::operator[](int index)
{
	assert((index >= 0) && (index <= _maxDegree));
	return this->_coeff[index];
}


bool Polynomial::operator==(const Polynomial& p2) const
{
	if (this->_degree == p2._degree && this->_maxDegree == p2._maxDegree)
	{
		for (int i = 0; i < this->_maxDegree; i++)
		{
			if (this->_coeff[i] != p2._coeff[i])
				return(false);
		}
		return(true);
	}
	else
		return (false);
}