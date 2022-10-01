#include<iostream>
#include<stdexcept>

#pragma once

class Matrix {
private:
	int _n, _m;
	double** _matrix;

	static Matrix creating_line(const Matrix& source, int number);
	static void combining_vector(const Matrix& source, int number1, const Matrix& destination, int number2);
public:
	

	static double _accuracy;


	static void set_accuracy(double value) {
		_accuracy = value;
	}

	Matrix();
	Matrix(int n, int m, double value);
	Matrix(const Matrix& b);
	~Matrix();
	double& operator()(int n, int m) const;
	Matrix operator+(const Matrix& obj) const;
	Matrix operator-(const Matrix& obj) const;
	Matrix operator*(const Matrix& obj) const;
	Matrix& operator*(double value);
	Matrix& operator/(double value);
	bool operator==(const Matrix& obj) const;
	bool operator!=(const Matrix& obj) const;
	friend std::ostream& operator<<(std::ostream& out, const Matrix& obj);
	double finding_the_trail() const;

	friend Matrix matrix_transformation(const Matrix& obj);
};

std::ostream& operator<<(std::ostream& out, const Matrix& obj);

Matrix matrix_transformation(const Matrix& obj);