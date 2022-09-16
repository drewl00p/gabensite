/*
	Written By Andrew Goldberg
	Febuary 2022
	This program converts a number of any base(2-36) to another base(2-36)
	Language: C++ (g++ target)

*/


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int convertLetter(char in_case);
int convertToDecimal(int base, string value);
int convertFromDecimal(int value, int base);
int getOutput(int input);



int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Provide a single filename." << endl;
		exit(EXIT_FAILURE);
	}

	ifstream f(argv[1]);

	if (!f.is_open()) {
		cout << "The file didn't open correctly" << endl;
		exit(EXIT_FAILURE);
	}

	int inbase = 0;
	int outbase = 0;
	int outvalue;
	string term;
	string line;
	string value;

	while (getline(f, line)) {
		stringstream ssline(line);
		unsigned int cnt = 0;

		while (ssline >> term) {  // Checks for lines starting w/ '@'
			stringstream ssterm(term);
			ssterm.str(term);

			if (cnt == 0) {
				ssterm >> inbase;
				cnt++;
			} else if (cnt == 1) {
				ssterm >> value;
				outvalue = convertFromDecimal(convertToDecimal(inbase, value),2);

				getOutput(outvalue);
			}
		}
	}
	f.close();
	exit(EXIT_SUCCESS);

	return 0;
}

int getOutput(int input) {
	int unsigned_value = 0;
	int signed_value = 0;
	int ones_value = 0;
	int twos_value = 0;

	int ones_temp = 0;

	//unsigned
	unsigned_value = convertToDecimal(2,to_string(input));

	//signed
	if (input / 100000.0 >= 1) {
		signed_value = -1 * convertToDecimal(2,to_string(input % 100000));		
	} 
	else {
		signed_value = convertToDecimal(2,to_string(input % 100000));
	}


	//one's comp
	ones_temp = input;
	int digit = 1;
	for (int i=0; i<to_string(ones_temp).length(); i++) {
		if (ones_temp % (10 * digit) >= digit) {
			ones_temp -= digit;
		} else {
			ones_temp += digit;
		}

		digit *= 10;
	}


	ones_value = convertToDecimal(2,to_string(ones_temp));

	

	cout << unsigned_value << " " << showpos << signed_value << " " << ones_value << noshowpos << endl;
}


int convertLetter(char in_case) {
	int out_case;
		
	if (in_case > '9') {
		if (in_case > 'Z') {
			in_case = in_case - 'a' + 'A'; //Convert uppercase to lower
		}
		out_case = in_case - 'A' + 10; //Subtract 'A' and add 10 to convert A to 10, B to 11, etc..
	} else {
		out_case = in_case - '0';
	}
	return out_case;
}

int convertToDecimal(int base, string value) {
	int length = value.length();
	int power = 1;
	int result = 0;

	//To decimal
	for (int i = length - 1; i >= 0; i--) {

		result += convertLetter(value[i]) * power;
		power *= base;
	}
	return result;		
}

int convertFromDecimal(int value, int base) {
	char key[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	int index = 0;
	int int_result;
	string result;

	if (value == 0) {
		result = "0";
	}

	while (value > 0) {
		result += key[value % base];
		value /= base;
		index++;
	}

	for (int i = 0; i < result.length() / 2; i++) {
		char j = result[i];
		result[i] = result[result.length() - i - 1];
		result[result.length() - i - 1] = j;
	}

	stringstream ss(result);
	ss >> int_result;


	return int_result;
}