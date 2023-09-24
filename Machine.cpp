#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "Rule.cpp"
#include "Had.cpp"
#include "Line.cpp"
using namespace std;

// ОСНОВНАЯ МАШИНА
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
	void Add_rule(string command, int first_value, int second_value) {    //Добавляет правило в конец
		rules.push_back(Rule(command, first_value, second_value));
		count_rule++;
		count_logs++;
		log = ("Строка " + to_string(count_logs) + ". Добавление команды " +
			command + " " + to_string(first_value) + ", " + to_string(second_value));
		logs.push_back(log);
	}

	void Del_rule() {                              //Удаляет правило с конца
		if (count_rule > 0) {
			count_logs++;
			log = ("Строка " + to_string(count_logs) + ". Удаление команды " +
				rules[(rules.size()) - 1].Get_command() + " " + to_string(rules[(rules.size()) - 1].Get_first_value()) + ", " +
				to_string(rules[(rules.size()) - 1].Get_second_value()));
			logs.push_back(log);
			count_rule--;
			rules.pop_back();
			cout << "Команда удалена.\n";
		}
		else {
			cout << "Правил не сущетсвует.\n";
			count_logs++;
			log = ("Строка " + to_string(count_logs) + ". Удаление команды . Команд нет.");
			logs.push_back(log);
		}
	}

	bool Correct_command(int number) {                       //Смотрит, чтобы правила не выходили
		//cout << "count_rule: " << count_rule << " rules[number].first_value: " << rules[number].first_value << " rules[number].second_value: " << rules[number].second_value << endl;
		if ((count_rule < rules[number].Get_first_value()) ||      //за границу
			(count_rule < rules[number].Get_second_value())) {

			count_logs++;
			log = ("Строка " + to_string(count_logs) + ". Правило " +
				to_string(number + 1) + ". Выход за границу. Завершение.");
			logs.push_back(log);
			cout << "Вы вышли за границы правил.\n";
			cout << "Программа завершена.";
			return false;
		}
		return true;
	}

	void Work_command(int number, Had& had, Line& line) {                          //Выполняет разные команды
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

	void Work_less_zero_val(int number, Had& had, Line& line) { //Для перехода на 0 строку work_less
		count_logs++;
		log = ("Строка " + to_string(count_logs) + ". Правило " + to_string(number + 1) + ". Сдвиг влево. Позиция "
			+ to_string(had.Get_position()) + ". Переход к нулевому правилу. Завершение.");
		logs.push_back(log);
		cout << "Программа завершена.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_less(int number, Had& had, Line& line) {       //Если вызов <
		had.Reduce_position();  //Двигаем каретку влево
		if (rules[number].Get_first_value() == 0) {  //Если переход на 0 строку, то окончить выполнение
			Work_less_zero_val(number, had, line);
			return;
		}

		count_logs++;
		log = ("Строка " + to_string(count_logs) + ". Правило "
			+ to_string(number + 1) + ". Сдвиг влево. Позиция " + to_string(had.Get_position()) +
			". Переход к команде " + to_string(rules[number].Get_first_value()) + ".");
		logs.push_back(log);
		if (!Correct_command(number)) {
			is_terminate = false;
			counter = 0;
			return;
		}

		counter = rules[number].Get_first_value() - 1;
		return;
	}

	void Work_more_sero_val(int number, Had& had, Line& line) {  //Переход на 0 work_more
		count_logs++;
		log = ("Строка " + to_string(count_logs) + ". Правило " + to_string(number + 1)
			+ ". Сдвиг вправо. Позиция " + to_string(had.Get_position()) + ". Переход к нулевому правилу.Завершение.");
		logs.push_back(log);
		cout << "Программа завершена.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_more(int number, Had& had, Line& line) {      //Если вызов >
		had.Increase_position(); //Двигаем каретку вправо
		if (rules[number].Get_first_value() == 0) {  //Если переход на 0 строку, то окончить выполнение
			Work_more_sero_val(number, had, line);
			return;
		}

		count_logs++;
		log = ("Строка " + to_string(count_logs) + ". Правило " + to_string(number + 1) + ". Сдвиг вправо. Позиция "
			+ to_string(had.Get_position()) + ". Переход к команде " + to_string(rules[number].Get_first_value()) + ".");
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
		log = ("Строка " + to_string(count_logs) + ". Правило " + to_string(number + 1) + ". Тенарный знак. Позиция "
			+ to_string(had.Get_position()) + ". Заполненная ячейка. Переход к нулевому правилу. Завершение.");
		logs.push_back(log);
		cout << "Программа завершена.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_ask_first_zero_val(int number, Had& had, Line& line) {
		count_logs++;
		log = ("Строка " + to_string(count_logs) + ".Првило " + to_string(number + 1) +
			". Тенарный знак. Позиция " + to_string(had.Get_position()) + ". Пустая ячейка. Переход к нулевому правилу.Завершение.");
		logs.push_back(log);
		cout << "Программа завершена.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_ask(int number, Had& had, Line& line) {       //Если вызов ?
		for (int i = 0; i < line.Get_points_line().size(); i++) {               //Заполненное значение
			if (line.Get_points_line()[i] == had.Get_position()) {
				if (rules[number].Get_second_value() == 0) {
					Work_ask_secodn_zero_val(number, had, line);
					return;
				}

				count_logs++;
				log = ("Строка " + to_string(count_logs) + ". Правило " + to_string(number + 1) + ". Тенарный знак. Позиция "
					+ to_string(had.Get_position()) + ". Заполненная ячейка. Переход к команде " + to_string(rules[number].Get_second_value()) + ".");
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
		if (rules[number].Get_first_value() == 0) {                              //Пустое значение
			Work_ask_first_zero_val(number, had, line);
			return;
		}

		count_logs++;
		log = ("Строка " + to_string(count_logs) + ". Правило " + to_string(number + 1) + ". Тенарный знак. Позиция " +
			to_string(had.Get_position()) + ". Пустая ячейка. Переход к команде " + to_string(rules[number].Get_first_value()) + ".");
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
		log = ("Строка " + to_string(count_logs) + ". Правило " + to_string(number + 1) +
			". Позиция " + to_string(had.Get_position()) + ". Добавление точки. Переход к нулевому правилу.Завершение.");
		logs.push_back(log);
		cout << "Программа завершена.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_one(int number, Had& had, Line& line) {               //Если вызов 1
		bool flag = false;
		for (int i = 0; i < line.Get_points_line().size(); i++) {    //Если такой элемент есть
			if (line.Get_points_line()[i] == had.Get_position()) {         //Мы перестаем искать
				flag = true;                                   //Иначе добавим его
				break;
			}
			flag = false;
		}
		if (!flag) {
			Add_log();
			line.Add_point(had.Get_position(), &count_logs, &logs);
		}

		if (rules[number].Get_first_value() == 0) {  //Если переход на 0 строку, то окончить выполнение
			Work_one_zero_val(number, had, line);
			return;
		}

		count_logs++;
		log = ("Строка " + to_string(count_logs) + ". Правило " + to_string(number + 1) + ". Позиция " +
			to_string(had.Get_position()) + ". Добавление точки. Переход к команде " + to_string(rules[number].Get_first_value()) + ".");
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
		log = ("Строка " + to_string(count_logs) + ". Правило " + to_string(number + 1) +
			". Позиция " + to_string(had.Get_position()) + ". Удаление точки. Переход к нулевому правилу. Завершение.");
		logs.push_back(log);
		cout << "Программа завершена.";
		is_terminate = false;
		counter = 0;
		return;
	}

	void Work_zero(int number, Had& had, Line& line) {     //Если вызов 0
		bool flag = false;
		for (int i = 0; i < line.Get_points_line().size(); i++) {
			if (line.Get_points_line()[i] == had.Get_position()) {         //Если такой элемент есть
				Add_log();
				line.Del_point(had.Get_position(), &count_logs, &logs);                  //Мы сразу его удалим
				//line.Print_points_line();
				break;                                         //Иначе ничего
			}
			flag = false;
		}

		if (rules[number].Get_first_value() == 0) {  //Если переход на 0 строку, то окончить выполнение
			Work_zero_zero_val(number, had, line);
			return;
		}

		count_logs++;
		log = ("Строка " + to_string(count_logs) + ". Правило " + to_string(number + 1) + ". Позиция " +
			to_string(had.Get_position()) + ". Удалене точки. Переход к команде " + to_string(rules[number].Get_first_value()) + ".");
		logs.push_back(log);
		if (!Correct_command(number)) {
			is_terminate = false;
			counter = 0;
			return;
		}

		counter = rules[number].Get_first_value() - 1;
		return;
	}

	void Work_point(int number, Had& had, Line& line) {  //Если вызов .
		if (!Correct_command(number)) {
			is_terminate = false;
			counter = 0;
			return;
		}

		count_logs++;
		log = ("Строка " + to_string(count_logs) + ". Правило " +
			to_string(number + 1) + ". Позиция " + to_string(had.Get_position()) + ". Завершение программы.");
		logs.push_back(log);
		is_terminate = false;
		counter = 0;
		return;
	}

	void Start(Had& had, Line& line) {               //Запускает процесс решения правил
		had.Set_position(position);
		if (count_rule > 0) {
			while (is_terminate) {
				Work_command(counter, had, line);
			}
		}
	}

	void Print_logs() {
		cout << "\n-----------------ЛОГИ-------------\n";
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