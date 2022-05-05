#pragma once
#pragma warning(disable : 4996)
#include <iostream>
using namespace std;

//Claas "String"
class String {
private:
	char* str;
public:
	int length;
	static const int limit = 90;
	//Constructor without parameters
	String() {
		length = 0;
		str = new char[1];
		str[0] = '\0';
	}
	//Constructors with parameters
	String(char* simv) {
		length = std::strlen(simv);
		str = new char[length + 1];
		std::strcpy(str, simv);
	}
	String(const String& stroka) {
		length = stroka.length;
		str = new char[length + 1];
		std::strcpy(str, stroka.str);
	}
	//Destructor
	~String() {
		delete[] str;
	}
	//Returns the length of a string
	int function_length() {
		return length;
	}
	//Checking if a string is empty
	bool empty() {
		if (function_length() > 0)
			return true;
		else return false;
	}
	//Returns the last character
	char last_simv(String stroka) {
		char simv = stroka[length - 1];
		return simv;
	}
	//Removes the last character
	void pop_last_simv() {
		str[length - 1] = '\0';
		length--;
	}
	//Working with an array
	char& operator[](int i) {
		return str[i];
	}
	//Overloading the assignment operator when 2 objects of a class
	String& operator=(const String& stroka) {
		delete[] str;
		length = stroka.length;
		str = new char[length + 1];
		std::strcpy(str, stroka.str);
		return *this;
	}
	//Overloading the assignment operator when 1 is an object of a class and the other is a variable of type char
	String& operator=(const char simv) {
		delete[] str;
		length = std::strlen(&simv);
		str = new char[length + 1];
		std::strcpy(str, &simv);
		return *this;
	}
	//Overloading the assignment operator when 1 is a class object and the other is quoted directly
	String& operator=(const char* simv) {
		delete[] str;
		length = std::strlen(simv);
		str = new char[length + 1];
		std::strcpy(str, simv);
		return *this;
	}
	//Overloading the sum operator when 2 class objects
	friend String operator+(const String& str1, const String& str2) {
		String temp;
		delete[] temp.str;
		temp.length = str1.length + str2.length;
		temp.str = new char[temp.length + 1];
		std::strcpy(temp.str, str1.str);
		std::strcpy(temp.str + str1.length, str2.str);
		return temp;
	}
	//Overloading the summation operator when 1 is an object of a class and the other is a variable of type char
	friend String operator+(const String& str1, const char simv) {
		String temp;
		delete[] temp.str;
		temp.length = str1.length + sizeof(simv);
		temp.str = new char[temp.length + 1];
		std::strcpy(temp.str, str1.str);
		std::strcpy(temp.str + str1.length, &simv);
		return temp;
	}
	//Overloading the sum operator when 1 is a class object and the other is quoted directly
	friend String operator+(const String& str1, const char* simv) {
		String temp;
		delete[] temp.str;
		temp.length = str1.length + sizeof(simv);
		temp.str = new char[temp.length + 1];
		std::strcpy(temp.str, str1.str);
		std::strcpy(temp.str + str1.length, simv);
		return temp;
	}
	//Overloading the inference statement
	friend ostream& operator<<(ostream& stream, const String& stroka) {
		stream << stroka.str;
		return stream;
	}
	//Input Operator Overload
	friend istream& operator>>(istream& stream, String& stroka) {
		char temp[limit];
		stream.get(temp, limit);
		if (stream)
			stroka = temp;
		while (stream && stream.get() != '\n')
			continue;
		return stream;
	}

	friend bool operator==(const String& st1, const String& st2){
		return (std::strcmp(st1.str, st2.str) == 0);
	}

};