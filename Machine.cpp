#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "Rule.cpp"
#include "Had.cpp"
#include "Line.cpp"
using namespace std;

// �������� ������
class Machine {
private:
	int counter = 0;
	int log_count{};
	int count_rule = 0;
	string log;
	int count_logs = 0;
	bool is_terminate = true;
	int position;
	vector <string> logs;
	vector <Rule> rules;

public:
	Machine(int position) : position(position) {
	}
	void Add_rule(string command, int first_value, int second_value) {    //��������� ������� � �����
		rules.push_back(Rule(command, first_value, second_value));
		count_rule++;
		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ���������� ������� " +
			command + " " + to_string(first_value) + ", " + to_string(second_value));
		logs.push_back(log);
	}

	void Del_rule() {                              //������� ������� � �����
		if (count_rule > 0) {
			count_logs++;
			log = ("������ " + to_string(count_logs) + ". �������� ������� " +
				rules[(rules.size()) - 1].Get_command() + " " + to_string(rules[(rules.size()) - 1].Get_first_value()) + ", " +
				to_string(rules[(rules.size()) - 1].Get_second_value()));
			logs.push_back(log);
			count_rule--;
			rules.pop_back();
			cout << "������� �������.\n";
		}
		else {
			cout << "������ �� ����������.\n";
			count_logs++;
			log = ("������ " + to_string(count_logs) + ". �������� ������� . ������ ���.");
			logs.push_back(log);
		}
	}

	bool Correct_command(int number) {                       //�������, ����� ������� �� ��������
		//cout << "count_rule: " << count_rule << " rules[number].first_value: " << rules[number].first_value << " rules[number].second_value: " << rules[number].second_value << endl;
		if ((count_rule < rules[number].Get_first_value()) ||      //�� �������
			(count_rule < rules[number].Get_second_value())) {

			count_logs++;
			log = ("������ " + to_string(count_logs) + ". ������� " +
				to_string(number + 1) + ". ����� �� �������. ����������.");
			logs.push_back(log);
			cout << "�� ����� �� ������� ������.\n";
			cout << "��������� ���������.";
			return false;
		}
		return true;
	}

	void Work_command(int number, Had& had, Line& line) {                          //��������� ������ �������
		if (rules[number].Get_command() == "<") {
			Work_less(number, had, line);
			return;
		}
		if (rules[number].Get_command() == ">") {
			Work_more(number, had, line);
			return;
		}
		if (rules[number].Get_command() == "?") {
			Work_ask(number, had, line);
			return;
		}
		if (rules[number].Get_command() == "1") {
			Work_one(number, had, line);
			return;
		}
		if (rules[number].Get_command() == "0") {
			Work_zero(number, had, line);
			return;
		}
		if (rules[number].Get_command() == ".") {
			Work_point(number, had, line);
			return;
		}
	}

	void Work_less_zero_val(int number, Had& had, Line& line) { //��� �������� �� 0 ������ work_less
		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ������� " + to_string(number + 1) + ". ����� �����. ������� "
			+ to_string(had.Get_position()) + ". ������� � �������� �������. ����������.");
		logs.push_back(log);
		cout << "��������� ���������.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_less(int number, Had& had, Line& line) {       //���� ����� <
		had.Reduce_position();  //������� ������� �����
		if (rules[number].Get_first_value() == 0) {  //���� ������� �� 0 ������, �� �������� ����������
			Work_less_zero_val(number, had, line);
			return;
		}

		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ������� "
			+ to_string(number + 1) + ". ����� �����. ������� " + to_string(had.Get_position()) +
			". ������� � ������� " + to_string(rules[number].Get_first_value()) + ".");
		logs.push_back(log);
		if (!Correct_command(number)) {
			is_terminate = false;
			counter = 0;
			return;
		}

		counter = rules[number].Get_first_value() - 1;
		return;
	}

	void Work_more_sero_val(int number, Had& had, Line& line) {  //������� �� 0 work_more
		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ������� " + to_string(number + 1)
			+ ". ����� ������. ������� " + to_string(had.Get_position()) + ". ������� � �������� �������.����������.");
		logs.push_back(log);
		cout << "��������� ���������.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_more(int number, Had& had, Line& line) {      //���� ����� >
		had.Increase_position(); //������� ������� ������
		if (rules[number].Get_first_value() == 0) {  //���� ������� �� 0 ������, �� �������� ����������
			Work_more_sero_val(number, had, line);
			return;
		}

		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ������� " + to_string(number + 1) + ". ����� ������. ������� "
			+ to_string(had.Get_position()) + ". ������� � ������� " + to_string(rules[number].Get_first_value()) + ".");
		logs.push_back(log);
		if (!Correct_command(number)) {
			is_terminate = false;
			counter = 0;
			return;
		}

		counter = rules[number].Get_first_value() - 1;
		return;
	}

	void Work_ask_secodn_zero_val(int number, Had& had, Line& line) {
		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ������� " + to_string(number + 1) + ". �������� ����. ������� "
			+ to_string(had.Get_position()) + ". ����������� ������. ������� � �������� �������. ����������.");
		logs.push_back(log);
		cout << "��������� ���������.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_ask_first_zero_val(int number, Had& had, Line& line) {
		count_logs++;
		log = ("������ " + to_string(count_logs) + ".������ " + to_string(number + 1) +
			". �������� ����. ������� " + to_string(had.Get_position()) + ". ������ ������. ������� � �������� �������.����������.");
		logs.push_back(log);
		cout << "��������� ���������.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_ask(int number, Had& had, Line& line) {       //���� ����� ?
		for (int i = 0; i < line.Get_points_line().size(); i++) {               //����������� ��������
			if (line.Get_points_line()[i] == had.Get_position()) {
				if (rules[number].Get_second_value() == 0) {
					Work_ask_secodn_zero_val(number, had, line);
					return;
				}

				count_logs++;
				log = ("������ " + to_string(count_logs) + ". ������� " + to_string(number + 1) + ". �������� ����. ������� "
					+ to_string(had.Get_position()) + ". ����������� ������. ������� � ������� " + to_string(rules[number].Get_second_value()) + ".");
				logs.push_back(log);
				if (!Correct_command(number)) {
					is_terminate = false;
					counter = 0;
					return;
				}
				counter = rules[number].Get_second_value() - 1;
				return;
			}
		}
		if (rules[number].Get_first_value() == 0) {                              //������ ��������
			Work_ask_first_zero_val(number, had, line);
			return;
		}

		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ������� " + to_string(number + 1) + ". �������� ����. ������� " +
			to_string(had.Get_position()) + ". ������ ������. ������� � ������� " + to_string(rules[number].Get_first_value()) + ".");
		logs.push_back(log);
		if (!Correct_command(number)) {
			is_terminate = false;
			counter = 0;
			return;
		}
		log_count = rules[number].Get_first_value() - 1;
		counter = log_count;
		return;
	}

	void Work_one_zero_val(int number, Had& had, Line& line) {
		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ������� " + to_string(number + 1) +
			". ������� " + to_string(had.Get_position()) + ". ���������� �����. ������� � �������� �������.����������.");
		logs.push_back(log);
		cout << "��������� ���������.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_one(int number, Had& had, Line& line) {               //���� ����� 1
		bool flag = false;
		for (int i = 0; i < line.Get_points_line().size(); i++) {    //���� ����� ������� ����
			if (line.Get_points_line()[i] == had.Get_position()) {         //�� ��������� ������
				flag = true;                                   //����� ������� ���
				break;
			}
			flag = false;
		}
		if (!flag) {
			Add_log();
			line.Add_point(had.Get_position(), &count_logs, &logs);
		}

		if (rules[number].Get_first_value() == 0) {  //���� ������� �� 0 ������, �� �������� ����������
			Work_one_zero_val(number, had, line);
			return;
		}

		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ������� " + to_string(number + 1) + ". ������� " +
			to_string(had.Get_position()) + ". ���������� �����. ������� � ������� " + to_string(rules[number].Get_first_value()) + ".");
		logs.push_back(log);
		if (!Correct_command(number)) {
			is_terminate = false;
			counter = 0;
			return;
		}

		counter = rules[number].Get_first_value() - 1;
		return;
	}

	void Work_zero_zero_val(int number, Had& had, Line& line) {
		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ������� " + to_string(number + 1) +
			". ������� " + to_string(had.Get_position()) + ". �������� �����. ������� � �������� �������. ����������.");
		logs.push_back(log);
		cout << "��������� ���������.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_zero(int number, Had& had, Line& line) {     //���� ����� 0
		bool flag = false;
		for (int i = 0; i < line.Get_points_line().size(); i++) {
			if (line.Get_points_line()[i] == had.Get_position()) {         //���� ����� ������� ����
				Add_log();
				line.Del_point(had.Get_position(), &count_logs, &logs);                  //�� ����� ��� ������
				//line.Print_points_line();
				break;                                         //����� ������
			}
			flag = false;
		}

		if (rules[number].Get_first_value() == 0) {  //���� ������� �� 0 ������, �� �������� ����������
			Work_zero_zero_val(number, had, line);
			return;
		}

		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ������� " + to_string(number + 1) + ". ������� " +
			to_string(had.Get_position()) + ". ������� �����. ������� � ������� " + to_string(rules[number].Get_first_value()) + ".");
		logs.push_back(log);
		if (!Correct_command(number)) {
			is_terminate = false;
			counter = 0;
			return;
		}

		counter = rules[number].Get_first_value() - 1;
		return;
	}

	void Work_point(int number, Had& had, Line& line) {  //���� ����� .
		if (!Correct_command(number)) {
			is_terminate = false;
			counter = 0;
			return;
		}

		count_logs++;
		log = ("������ " + to_string(count_logs) + ". ������� " +
			to_string(number + 1) + ". ������� " + to_string(had.Get_position()) + ". ���������� ���������.");
		logs.push_back(log);
		is_terminate = false;
		counter = 0;
		return;
	}

	void Start(Had& had, Line& line) {               //��������� ������� ������� ������
		had.Set_position(position);
		if (count_rule > 0) {
			while (is_terminate) {
				Work_command(counter, had, line);
			}
		}
	}

	void Print_logs() {
		cout << "\n-----------------����-------------\n";
		for (int i = 0; i < logs.size(); i++) {
			cout << logs[i] << endl;
		}
	}

	int Get_rules_size() {
		return rules.size();
	}

	int Get_count_rule() {
		return count_rule;
	}

	int Get_count_logs() {
		return count_logs;
	}

	void Add_log() {
		count_logs++;
	}

	vector <string> Get_logs() {
		return logs;
	}

	vector <Rule> Get_rules() {
		return rules;
	}

	int Get_counter() {
		return counter;
	}

	void Set_logs(vector <string> logs_v) {
		logs = logs_v;
	}
};