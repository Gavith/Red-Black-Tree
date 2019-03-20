#define _CRT_SECURE_NO_WARNINGS
#include "RBTree.h"
#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;

void to_lower_char(char* c);
bool isDigit(char *c);

int main()
{
	RBTree t = RBTree();
	char* input = new char(10);
	while (input[0] != 'q') {

		cout << "1) add\n2) read\n3) print\n4) search\n5) remove\n6) quit" << endl << "? ";

		cin >> input;
		cin.ignore(100, '\n');
		to_lower_char(input);
		if (strcmp(input, "add") == 0) {
			REPEAT: //marker so that I don't have to write a while statement cuz im lazy
			cout << "Enter a number" << endl;
			int in;

			cin >> input;
			if (isDigit(input)) { //if the input is a digit
				in = atoi(input); //add it
				t.insert(in);
			}
			else goto REPEAT; //otherwise, go back to the beginning

			
		}
		else if (strcmp(input, "read") == 0) {
			ifstream file;
			cout << "Input your file name:" << endl;
			cin.get(input, 100);
			cin.ignore(100, '\n');
			file.open(input);
			if (file.is_open()) {
				char* l = new char[10000];//big number just so that I can read all the stuff
				file.getline(l, 10000);
				char* i = strtok(l, ",");
				while (i != NULL) {//while there are still entries
					t.insert(atoi(i));//add it
					i = strtok(NULL, ",");
				}	
			}
			file.close();
		}
		else if (strcmp(input, "print") == 0) {
			cout << "Numbers: " << endl;
			t.printTree();
			cout << "Colors: " << endl;
			t.printTreeColor();
		} 
		else if (strcmp(input, "search") == 0) {
			strcpy(input, "placeholder");
			while (!isDigit(input)) {
				cout << "Search for what number?" << endl << "? ";
				cin.get(input, 100);
				cin.ignore(100, '\n');
				if (isDigit(input)) {
					if (t.search(atoi(input))) {
						cout << "The number is in the tree." << endl;
					}
					else {
						cout << "The number is not in the tree." << endl;
					}
				}
			}
		}
		else if (strcmp(input, "remove") == 0) {

		}
	}
}

void to_lower_char(char* c) {
	for (unsigned int i = 0; i < strlen(c); i++)
		c[i] = tolower(c[i]);
}

bool isDigit(char * c)
{
	for (unsigned int i = 0; i < strlen(c); i++)
		if ((int)c[i] < 48 || (int)c[i] > 57) return false;
	return true;
}
