#include<locale>

#include "Matrix.hpp"


double Matrix::_accuracy = 0.15;

int main(){
	setlocale(LC_ALL, "ru");
	int n, m;
	system("cls");
	std::cout << "Введите размеры матрицы:" << std::endl;
	try {
		std::cin >> n >> m;
		Matrix first(n, m, 0);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; j++) {
				std::cout << "Заполните матрицу:" << std::endl;
				std::cout << "a[" << i << "][" << j << "] = ";
				std::cin >> first(i, j);
			}
		}
		system("cls");
		std::cout << first;
		Matrix second = matrix_transformation(first);
		std::cout << second;
	}
	catch (std::logic_error& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}