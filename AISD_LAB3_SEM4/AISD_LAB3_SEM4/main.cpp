#include <iostream>
#include <fstream>
#include "String.h"
#include  "FloydWarshallAlgorithm.h"
using namespace std;


int main() {
	setlocale(LC_ALL, "Russian");
	const int buff = 512;
	char* start_text = new char[buff];
	start_text = read_file();
	cout << start_text << endl << endl;

	String only_peaks;
	only_peaks = string_peaks(start_text);

	int matrix_dimension = dimension(only_peaks);
	//matrix creation
	int** matrix = new int* [matrix_dimension];
	for (int i = 0; i < matrix_dimension; i++) {
		matrix[i] = new int[matrix_dimension];
	}
	matrix = initial_matrix(start_text, only_peaks);
	print_matrix(matrix);

	Floyd_Warshall_Algorithm(matrix, only_peaks);

	delete[]start_text;
	for (int i = 0; i < matrix_dimension; i++) {
		delete[]matrix[i];
	}
	delete[]matrix;
}