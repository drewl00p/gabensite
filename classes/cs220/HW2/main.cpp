#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int convertLetter(int in_case);
int convertToDecimal(int base, string value);
string convertFromDecimal(int value, int base);



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

	unsigned int line_no = 1;
	int inbase = 0;
	int outbase = 0;
	string outvalue;
	string term;
	string line;
	string value;
	// int x = (int)*0x123456;

	while (getline(f, line)) {
		stringstream ssline(line);
		unsigned int cnt = 0;

		while (ssline >> term && term[0] != '@' && cnt < 3) {  // Checks for lines starting w/ '@'
			stringstream ssterm(term);
			ssterm.str(term);

			if (cnt == 0) {
				ssterm >> inbase;
				cnt++;
			} else if (cnt == 1) {
				ssterm >> value;
				cnt++;
			} else if (cnt == 2) {
				ssterm >> outbase;

				outvalue = convertFromDecimal(convertToDecimal(inbase, value),outbase);
				cout << line_no << ": "<< outvalue << endl;
				cnt++;
			}
			
		}
		line_no++;
	}
	f.close();
	exit(EXIT_SUCCESS);
}

int convertLetter(int in_case) {
	int out_case;
	
	if (in_case > '9') {
		if (in_case > 'Z') {
			in_case = in_case - 'a' + 'A'; //Convert uppercase to lower
		}
		out_case = in_case - 'A' + 10; //Subtract 'A' and add 10 to convert A to 10, B to 11, etc..
	} else {
		out_case = in_case;
	}
	return (int)out_case;
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

string convertFromDecimal(int value, int base) {
	char key[] = "01234556789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int index = 0;
	char* output[20];
	string result;

	while (value > 0) {
		output[index] += key[value % base];
		value /= base;
		cout <<"\n"<< output << endl;
	}

	stringstream ss;
	ss << output;
	ss >> result;

	for (int i = 0; i < result.length() / 2; i++) {
		char j = result[i];
		result[i] = result[result.length() - i - 1];
		result[result.length() - i - 1] = j;
	}

	return result;
}
