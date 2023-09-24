#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "Machine.cpp"
using namespace std;


void Menu_point(Line& line, Machine& machine) {       //���������� � �������� ����� � main
	while (true) {
		cout << "1 - ������� �����, 2 - �������� �����, 3 - ����������\n";
		string num_choise;
		cin >> num_choise;
		vector <string> logs;
		int c_l;
		if (num_choise == "1") {
			cout << "������� �������: ";
			int pos;
			cin >> pos;
			machine.Add_log();
			c_l = machine.Get_count_logs();
			logs = machine.Get_logs();
			line.Del_point(pos, &c_l, &logs);
			machine.Set_logs(logs);
			//line.Print_points_line();
			continue;
		}
		if (num_choise == "2") {
			cout << "������� �������: ";
			int pos;
			cin >> pos;
			machine.Add_log();
			c_l = machine.Get_count_logs();
			logs = machine.Get_logs();
			line.Add_point(pos, &c_l, &logs);
			machine.Set_logs(logs);
			//line.Print_points_line();
			continue;
		}
		if (num_choise == "3") {
			break;
		}
		else {
			cout << "�� ����� ������������ ��������!\n";
			continue;
		}
	}
	return;
}

bool Go_kd(Machine& machine, string command, string kd_choise, int count, int first_value, int second_value) {
	while (true) {
		cout << "������ ������� �� ���������? (\"y\" - yes, \"n\" - no): ";     //��� ��������� �������� �� �� �������
		cin >> kd_choise;
		if (kd_choise == "y") {
			first_value = count + 1;
			second_value = 0;
			machine.Add_rule(command, first_value, second_value);
			return true;
		}
		if (kd_choise == "n") {
			return false;
		}
		else {
			cout << "������������ ����!\n";
		}
	}
}

void Menu_rule(Machine& machine) {           //���������� ������ � main
	int count = 0;
	while (true) {
		cout << "\n--------------������� �������--------------\n";
		cout << " ������� : " << count + 1 << ". ������� ������� : ";
		string command;
		cin >> command;
		string kd_choise;
		int first_value{};
		int second_value{};
		if ((command == ">") || (command == "<") || (command == "0") || (command == "1")) {
			count++;
			if (!Go_kd(machine, command, kd_choise, count, first_value, second_value)) {
				cout << "������� ������� � ������� � ��������: ";
				cin >> first_value;
				//count++;
				second_value = 0;
				machine.Add_rule(command, first_value, second_value);
			}
			//else {
			//	count++;
			//}
		}
		else if (command == "?") {
			cout << "������� ������� ��� ������ ������: ";
			cin >> first_value;
			cout << "������� ������� ��� ������ ������: ";
			cin >> second_value;
			count++;
			machine.Add_rule(command, first_value, second_value);
		}
		else if (command == ".") {
			first_value = -1;
			second_value = -1;
			count++;
			machine.Add_rule(command, first_value, second_value);
		}
		else {
			cout << "�� ����� ������������ �������!\n";
			continue;
		}
		bool flag = false;
		while (true) {
			cout << "\n-----------------------------\n";
			cout << "\"a\" - �������� �������, \"d\" - ������� �������, \"c\" - ����������: ";
			string choise;
			cin >> choise;
			if (choise == "a") {
				flag = true;
				break;
			}
			if (choise == "d") {
				machine.Del_rule();
				count--;
				flag = true;
				continue;
			}
			if (choise == "c") {
				flag = false;
				break;
			}
			else {
				cout << "�� ����� ������������ �����!\n";
				continue;
			}
		}
		if (flag) {
			continue;
		}
		else {
			break;
		}
	}
	return;
}
