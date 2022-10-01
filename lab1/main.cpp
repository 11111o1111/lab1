#include<locale>

#include "Matrix.hpp"


double Matrix::_accuracy = 0.15;

int main(){
	setlocale(LC_ALL, "ru");
	Matrix first(5, 5, 7);



	int k = 1;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			first(i, j) = rand()% 100;
		}
	}

	std::cout << first;
	Matrix second = matrix_transformation(first);
	std::cout << second;

	return 0;
}