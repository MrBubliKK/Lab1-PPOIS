#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "WorkFunctions.h"
using namespace std;

int main() {
	system("chcp 1251");
	cout << "Введите позицию каретки: ";
	int tape;
	string log;
	cin >> tape;
	Machine machine(tape);
	Line line;
	Had had;
	vector <string> logs = (machine.Get_logs());
	Menu_point(line, machine);
	Menu_rule(machine);
	machine.Start(had, line);
	cout << "Если вам нужны логи, введите -log: ";
	cin >> log;
	if (log == "-log") {
		machine.Print_logs();
	}

	cout << "\n Выполнение прошло успешно!";
}