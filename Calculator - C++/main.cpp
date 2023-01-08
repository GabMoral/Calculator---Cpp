#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.14159265
//Checks for valid operator input
int opCheck(char* op) {
	switch (*op) {
	case 'c':
	case 's':
	case 't':
	case 'C':
	case 'S':
	case 'T':
		return 3;
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '^':
		return 2;
	case '[':
	case ']':
		return 1;
	default:
		return 0;
	}
}
//Calculates single operand operations
void calculate(char* op, float* result, float num1) {
	switch (*op) {
	case '[':
		*result = sqrt(num1);
		break;
	case ']':
		*result = cbrt(num1);
		break;
	}
}
//Calculates double operand operations
void calculate(char* op, float* result, float num1, float num2) {
	int isNum1Int, isNum2Int;
	switch (*op) {
	case '+':
		*result = num1 + num2;
		break;
	case '-':
		*result = num1 - num2;
		break;
	case '*':
		*result = num1 * num2;
		break;
	case '/':
		*result = num1 / num2;
		break;
	case '%':
		isNum1Int = ((int)num1 == num1);
		isNum2Int = ((int)num2 == num2);
		if (isNum1Int && isNum2Int)
			*result = (int)num1 % (int)num2;
		else
			*op = 'M';
		break;
	case '^':
		*result = pow(num1, num2);
		break;
	}
}
//Calculates trig operations
void calculate(char* op, float* result, float num1, char mode) {
	switch (*op) {
	case 'c':
		if (mode == 'D') num1 = num1 * PI / 180;
		*result = cos(num1);
		break;
	case 's':
		if (mode == 'D') num1 = num1 * PI / 180;
		*result = sin(num1);
		break;
	case 't':
		if (mode == 'D') num1 = num1 * PI / 180;
		*result = tan(num1);
		break;
	case 'C':
		if (mode == 'D') num1 = num1 * PI / 180;
		*result = acos(num1);
		break;
	case 'S':
		if (mode == 'D') num1 = num1 * PI / 180;
		*result = asin(num1);
		break;
	case 'T':
		if (mode == 'D') num1 = num1 * PI / 180;
		*result = atan(num1);
		break;
	}
}
//Gets one number from user
void getNum(float* num1) {
	int tryAgain;
	do {
		cout << "Enter number: ";
		cin >> *num1;
		tryAgain = cin.fail();
		if (tryAgain)
			cout << "Invalid entry!!!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	//clear buffer
	} while (tryAgain);
}
//Gets two number from user
void getNum(float* num1, float* num2) {
	int tryAgain;
	do {
		cout << "Enter 2 numbers: ";
		cin >> *num1 >> *num2;
		tryAgain = cin.fail();
		if (tryAgain)
			cout << "Invalid entry!!!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	//clear buffer
	} while (tryAgain);
}
//Gets one number in degrees or radians mode
void getNum(float* num1, char mode) {
	int tryAgain;
	do {
		tryAgain = 0;
		if (mode == 'D') {
			cout << "Enter number in degrees: ";
			cin >> *num1;
			tryAgain = cin.fail();
			if (tryAgain)
				cout << "Invalid entry!!!\n";
		}
		else if (mode == 'R') {
			cout << "Enter number in radians: ";
			cin >> *num1;
			tryAgain = cin.fail();
			if (tryAgain)
				cout << "Invalid entry!!!\n";
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	//clear buffer
	} while (tryAgain);

}
//Determines mode: degree or radians
char degreeOrRadian() {
	char mode;
	int tryAgain;
	do {
		tryAgain = 0;
		cout << "Degrees (D) or Radians (R): ";
		cin >> mode;
		if (mode != 'D' && mode != 'R') {
			tryAgain = 1;
			cout << "Invalid entry!!!\n";
		}
		else tryAgain = 0;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	//clear buffer
	} while (tryAgain);
	return mode;
}
//Gets operator from user
void getOp(int* opRead, char* op) {
	do {
		cout << "Enter operation: ";
		cin >> *op;
		*opRead = opCheck(op);
		if (*opRead == 0)
			cout << "Invalid entry!!!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	//clear buffer
	} while (*opRead == 0);
}
//Prints result
void print(char error, float result) {
	switch (error) {
	case 'M':
		cout << "Error: (" << error << ")Cannot mod floats.\n";
		return;
	}
	cout << "Result: " << result << endl;
}
//Prints calculator menu options
void menu() {
	cout << "\tOperators Menu: \n";
	cout << "\tc: Cosine\tC: Arc Cosine\n";
	cout << "\ts: Sine\t\tS: Arc Sine\n";
	cout << "\tt: Tangent\tT: Arc Tangent\n";
	cout << "\t+: Addition\t*: Multiplication\n";
	cout << "\t-: Subtraction\t/: Division\n";
	cout << "\t%: Remainder\t^: Power\n";
	cout << "\t[: Square Root\t]: Cube Root\n";
}
int main() {
	float num1 = 0, num2 = 0;
	float result = 0;
	char op;
	int opRead;
	char mode;
	do {
		menu();

		getOp(&opRead, &op);

		if (opRead == 3) {
			mode = degreeOrRadian();
			getNum(&num1, mode);
			calculate(&op, &result, num1, mode);
		}
		else if (opRead == 2) {
			getNum(&num1, &num2);
			calculate(&op, &result, num1, num2);
		}
		else if (opRead == 1) {
			getNum(&num1);
			calculate(&op, &result, num1);
		}

		print(op, result);

		system("pause");
		system("cls");
	} while (1);
	return 0;
}