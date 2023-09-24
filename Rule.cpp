#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

//ПРАВИЛО
class Rule {
private:
	string command;
	int number;
	int first_value;
	int second_value;

public:
	Rule(string command = "", int first_value = 0, int second_value = 0) :    //Инициализация класса правила
		command(command),
		first_value(first_value),
		second_value(second_value) {}


	string Get_command() {
		return command;
	}

	int Get_first_value() {
		return first_value;
	}

	int Get_second_value() {
		return second_value;
	}
};