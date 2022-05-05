#pragma once
#include <iostream>
#include <fstream>
#include "String.h"
using namespace std;

char* read_file() {
	const int buff = 512;
	char* start_text = new char[buff];
	//input from file
	std::ifstream filein("Чтение.txt"); 	// open file for reading
	filein.unsetf(ios::skipws);
	if (!filein.is_open()) //if file not found
		std::cout << "Ошибка открытия файла!";
	while (!filein.eof()) {
		filein.getline(start_text, buff, '.'); //until end of file
	}
	filein.close();
	
	return start_text;
}

String string_peaks(char* start_text) {
	//select all paths
	int number = 0;
	int check = 0;
	char space = ' ';
	String all_way;
	String only_peaks;
	while (start_text[number] != '.') {
		if (check == 2) break;
		while (start_text[number] != ';') {
			if (check == 1) {
				check++;
				break;
			}
			all_way = all_way + start_text[number];
			number++;
			if (start_text[number] == ';') {
				all_way = all_way + space;
				number++;
			}
			if (start_text[number] == 'N' && start_text[number + 1] == '/' && start_text[number + 2] == 'A') {
				while (start_text[number] != ';') {
					number++;
				}
				number++;
			}
			if (start_text[number] >= 48 && start_text[number] <= 57) {
				while (start_text[number] != '\n') {
					if (start_text[number] == '\0') {
						check++;
						break;
					}
					number++;
				}
				number++;
			}
		}
	}

	//definition of vertices in a single instance
	number = 0;
	while (number != all_way.length) {
		if (only_peaks.length == 0) {
			while (all_way[number] != space) {
				only_peaks = only_peaks + all_way[number];
				number++;
			}
			only_peaks = only_peaks + space;
			number++;
		}
		else {
			String city_from_list;
			//take a city from the whole list
			while (all_way[number] != space) {
				city_from_list = city_from_list + all_way[number];
				number++;
			}
			//compare it with the main
			for (int i = 0; i < only_peaks.length; i++) {
				String city_for_comparison;
				while (only_peaks[i] != space) {
					city_for_comparison = city_for_comparison + only_peaks[i];
					i++;
				}
				if (city_for_comparison == city_from_list) {
					number++;
					break;
				}
				if (i + 1 == only_peaks.length) {
					only_peaks = only_peaks + city_from_list;
					only_peaks = only_peaks + space;
					number++;
					while (city_for_comparison.empty()) {
						city_for_comparison.pop_last_simv();
					}
					while (city_from_list.empty()) {
						city_from_list.pop_last_simv();
					}
					break;
				}
				else {
					while (city_for_comparison.empty()) {
						city_for_comparison.pop_last_simv();
					}
				}
			}
		}

	}
	return only_peaks;
}

int dimension(String only_peaks) {
	int number = 0, matrix_dimension = 0;
	char space = ' ';
	while (number != only_peaks.length) {
		if (only_peaks[number] == space) matrix_dimension++;
		number++;
	}
	return matrix_dimension;
}

int** initial_matrix(char* start_text, String only_peaks) {
	int matrix_dimension = dimension(only_peaks);
	char space = ' ';
	int inf = 0;
	//matrix creation
	int** matrix = new int* [matrix_dimension];
	for (int i = 0; i < matrix_dimension; i++) {
		matrix[i] = new int[matrix_dimension];
	}
	//matrix initialization
	for (int i = 0; i < matrix_dimension; i++) {
		for (int j = 0; j < matrix_dimension; j++) {
			matrix[i][j] = 0;
		}
	}

	//matrix filling
	int number = 0;
	while (start_text[number] != '\0') {
		String departure_point;
		String place_of_arrival;
		int city1 = 0, city2 = 0;
		int price1 = 0, price2 = 0;
		//read the cities from the first line
		while (start_text[number] != ';') {
			departure_point = departure_point + start_text[number];
			number++;
		}
		number++;
		while (start_text[number] != ';') {
			place_of_arrival = place_of_arrival + start_text[number];
			number++;
		}
		number++;
		//determine the cost
		//from 1 city to 2
		if (start_text[number] >= 48 && start_text[number] <= 57) {
			while (start_text[number] != ';') {
				price1 += start_text[number] - '0';
				if (start_text[number + 1] == ';') {
					number++;
				}
				else {
					price1 *= 10;
					number++;
				}
			}
			number++;
			inf += price1;
		}
		else {
			while (start_text[number] != ';') number++;
			number++;
		}
		//from 2 cities to 1
		if (start_text[number] >= 48 && start_text[number] <= 57) {
			while (start_text[number] != '\n') {
				price2 += start_text[number] - '0';
				if (start_text[number + 1] == '\0') {
					number++;
					break;
				}
				if (start_text[number + 1] == '\n') {
					number++;
				}
				else {
					price2 *= 10;
					number++;
				}
			}
			inf += price2;
		}
		else {
			while (start_text[number] != '\n') {
				if (start_text[number + 1] == '\0') {
					number++;
					break;
				}
				number++;
			}
		}
		//filling cells
		if (start_text[number] == '\n' || start_text[number] == '\0') {
			// work with 1 city
			for (int i = 0; i < only_peaks.length; i++) {
				String city_for_comparison;
				while (only_peaks[i] != space) {
					city_for_comparison = city_for_comparison + only_peaks[i];
					i++;
				}
				city1++;
				if (city_for_comparison == departure_point) {
					while (city_for_comparison.empty()) {
						city_for_comparison.pop_last_simv();
					}
					break;
				}
				else {
					while (city_for_comparison.empty()) {
						city_for_comparison.pop_last_simv();
					}
				}
			}
			// work with 2 city
			for (int i = 0; i < only_peaks.length; i++) {
				String city_for_comparison;
				while (only_peaks[i] != space) {
					city_for_comparison = city_for_comparison + only_peaks[i];
					i++;
				}
				city2++;
				if (city_for_comparison == place_of_arrival) {
					while (city_for_comparison.empty()) {
						city_for_comparison.pop_last_simv();
					}
					break;
				}
				else {
					while (city_for_comparison.empty()) {
						city_for_comparison.pop_last_simv();
					}
				}
			}

			matrix[city1 - 1][city2 - 1] = price1;
			matrix[city2 - 1][city1 - 1] = price2;
			if (start_text[number] == '\0') {
				break;
			}
			else number++;
		}

	}
	//infinity filling
	for (int i = 0; i < matrix_dimension; i++) {
		for (int j = 0; j < matrix_dimension; j++) {
			if (matrix[i][j] == 0 && i != j) {
				matrix[i][j] = inf;
			}
		}
	}
	return matrix;
}

void print_matrix(int** matrix) {
	int matrix_dimension = dimension(string_peaks(read_file()));
	//output matrix
	for (int i = 0; i < matrix_dimension; i++) {
		for (int j = 0; j < matrix_dimension; j++) {
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}

void Floyd_Warshall_Algorithm(int** matrix, String only_peaks) {
	////////////////////////////////////////////////////////////////////
	int matrix_dimension = dimension(string_peaks(read_file()));
	char space = ' ';
	//path matrix
	int** ways = new int* [matrix_dimension];
	for (int i = 0; i < matrix_dimension; i++) {
		ways[i] = new int[matrix_dimension];
	}
	for (int i = 0; i < matrix_dimension; i++) {
		for (int j = 0; j < matrix_dimension; j++) {
			ways[i][j] = 0;
		}
	}
	////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////
	//Floyd-Warshall algorithm
	for (int i = 0; i < matrix_dimension; i++) {
		for (int j = 0; j < matrix_dimension; j++) {
			for (int k = 0; k < matrix_dimension; k++) {
				if (matrix[j][i] + matrix[i][k] < matrix[j][k]) {
					matrix[j][k] = matrix[j][i] + matrix[i][k];
					//path change
					if (ways[j][k] == 0) {
						ways[j][k] = ways[j][k] + i + 1;
					}
					else {
						ways[j][k] = ways[j][k] * 10 + i + 1;
					}
				}
			}
		}
	}

	//matrix output
	for (int i = 0; i < matrix_dimension; i++) {
		for (int j = 0; j < matrix_dimension; j++) {
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
	////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////
	//output of the shortest path
	String city_one;
	String city_two;
	cout << "Enter departure route" << endl;
	cin >> city_one;
	cout << "Enter the way of arrival" << endl;
	cin >> city_two;

	//definition of indexes
	int index1 = -1, index2 = -1;
	for (int i = 0; i < only_peaks.length; i++) {
		String city_for_comparison;
		while (only_peaks[i] != space) {
			city_for_comparison = city_for_comparison + only_peaks[i];
			i++;
		}
		index1++;
		if (city_for_comparison == city_one) {
			while (city_for_comparison.empty()) {
				city_for_comparison.pop_last_simv();
			}
			break;
		}
		else {
			while (city_for_comparison.empty()) {
				city_for_comparison.pop_last_simv();
			}
		}
	}
	for (int i = 0; i < only_peaks.length; i++) {
		String city_for_comparison;
		while (only_peaks[i] != space) {
			city_for_comparison = city_for_comparison + only_peaks[i];
			i++;
		}
		index2++;
		if (city_for_comparison == city_two) {
			while (city_for_comparison.empty()) {
				city_for_comparison.pop_last_simv();
			}
			break;
		}
		else {
			while (city_for_comparison.empty()) {
				city_for_comparison.pop_last_simv();
			}
		}
	}
	if (ways[index1][index2] == 0) {
		cout << "Is that a direct flight. The cost will be: " << matrix[index1][index2] << endl << endl;
	}
	else {
		int num_space = 1;
		int number = 0;
		while (num_space != ways[index1][index2]) {
			if (only_peaks[number] == space) num_space++;
			number++;
		}
		String city3;
		while (only_peaks[number] != space) {
			city3 = city3 + only_peaks[number];
			number++;
		}
		cout << "The cheapest way will be with a transfer in the city: " << city3 << endl;
		cout << "The cost will be: " << matrix[index1][index2] << endl << endl;
	}
	////////////////////////////////////////////////////////////////////
}
