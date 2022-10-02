#include<iomanip>
#include<iostream>

#include "Matrix.hpp"

Matrix::Matrix() : _n(0), _m(0) {
	_matrix = new double* [_n];
	for (int i = 0; i < _n; i++) {
		_matrix[i] = new double[_m];
	}
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _m; j++) {
			_matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(int n, int m, double value) {
	if (n <= 0 || m <= 0)
		throw(std::logic_error("incorrect dimensions of the matrix"));
	_n = n;
	_m = m;
	_matrix = new double* [_n];
	for (int i = 0; i < _n; i++) {
		_matrix[i] = new double[_m];
	}
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _m; j++) {
			_matrix[i][j] = value;
		}
	}
}

Matrix::Matrix(const Matrix& b) : Matrix(b._n, b._m, 0) {
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _m; j++) {
			_matrix[i][j] = b._matrix[i][j];
		}
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < _n; i++) {
		delete[] _matrix[i];
	}
	delete[] _matrix;
}

double& Matrix::operator()(int n, int m) const {
	if (n < 0 || n > _n || m < 0 || m > _m)
		throw std::out_of_range("invalid index");
	return _matrix[n][m];
}

Matrix Matrix::operator+(const Matrix& obj) const {
	if (_n != obj._n || _m != obj._m)
		throw std::logic_error("size mismatch");
	Matrix temp_matrix(*this);
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _m; j++) {
			temp_matrix(i,j) += obj._matrix[i][j];
		}
	}
	return temp_matrix;
}

Matrix Matrix::operator-(const Matrix& obj) const {
	if (_n != obj._n || _m != obj._m)
		throw std::logic_error("size mismatch");
	Matrix temp_matrix(*this);
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _m; j++) {
			temp_matrix(i, j) -= obj._matrix[i][j];
		}
	}
	return temp_matrix;
}

Matrix Matrix::operator*(const Matrix& obj) const {
	if (_m != obj._n)
		throw std::logic_error("size mismatch");
	Matrix temp_matrix(_n, obj._m, 0);
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < obj._m; j++) {
			for (int k = 0; k < _m; k++) {
				temp_matrix(i, j) += _matrix[i][j] * obj._matrix[i][j];
			}
		}
	}
	return temp_matrix;
}

Matrix& Matrix::operator*(double value) {
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _m; j++) {
			_matrix[i][j] *= value;
		}
	}
	return *this;
}

Matrix& Matrix::operator/(double value) {
	if (value == 0)
		throw std::logic_error("division by zero");
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _m; j++) {
			_matrix[i][j] /= value;
		}
	}
	return *this;
}

bool Matrix::operator==(const Matrix& obj) const {
	if (_n != obj._n || _m != obj._m)
		return false;
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _m; j++) {
			
			if(fabs(_matrix[i][j] - obj._matrix[i][j]) > _accuracy)
				return false;
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& obj) const {
	if (*this == obj)
		return false;
	return true;
}

std::ostream& operator<<(std::ostream& out, const Matrix& obj){
	for (int i = 0; i < obj._n; i++) {
		for (int j = 0; j < obj._m; j++) {
			out << std::fixed;
			out << std::setprecision(2);
			out << "\t" << obj._matrix[i][j];
		}
		out << "\n";
	}
	system("pause");
	return out;
}

double Matrix::finding_the_trail() const {
	if (_n != _m)
		throw std::logic_error("the matrix is not square");
	double temp = 0;
	for (int i = 0; i < _n; i++) {
		temp += _matrix[i][i];
	}
	return temp;
}

Matrix Matrix::creating_line(const Matrix& source, int number) {
	Matrix temp(1, source._m, 0);
	for (int i = 0; i < source._m; ++i) {
		temp(0, i) = source(number, i);
	}
	return temp;
}

void Matrix::combining_vector(const Matrix& source, int number1, const Matrix& destination, int number2) {
	for (int i = 0; i < source._m; ++i) {
		destination(number2, i) = source(number1, i);
	}
}

Matrix matrix_transformation(const Matrix& obj) {
	if (obj._m != obj._n)
		throw std::logic_error("not a square matrix");

	Matrix new_matrix(obj);
	for (int j = obj._m - 1; j > 0; --j) {
		for (int i = 0; i < j; ++i) {
			if (new_matrix(i, j) != 0) {
				int k = j;
				if (new_matrix(k, j) == 0) {
					while (new_matrix(k, j) == 0) {
						++k;
					}
					Matrix temp_arr_3 = Matrix::creating_line(new_matrix, j);
					Matrix::combining_vector(new_matrix, k, new_matrix, j);
					Matrix::combining_vector(temp_arr_3, 0, new_matrix, k);
				}
				double temp = new_matrix(i, j) / new_matrix(j, j);
				Matrix temp_arr_1 = Matrix::creating_line(new_matrix, i);
				Matrix temp_arr_2 = Matrix::creating_line(new_matrix, j);
				Matrix result = temp_arr_1 - (temp_arr_2 * temp);
				Matrix::combining_vector(result, 0, new_matrix, i);
			}
		}
	}
	return new_matrix;
}