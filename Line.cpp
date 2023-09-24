#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

//�����
class Line {
private:
	string log;
	vector <int> points_line;

public:
	bool Check_point(int value_p, int* count_logs, vector <string>* logs) {
		for (int i = 0; i < points_line.size(); i++) {    //��� �������� Add_point
			if (points_line[i] == value_p) {
				(*count_logs)++;
				log = ("������ " + to_string(*count_logs) + ". ���������� �����. ������� " +
					to_string(value_p) + ". ��� ��� ����������.");
				(*logs).push_back(log);
				cout << "����� ������� ��� ����.\n";
				return false;
			}
		}
		return true;
	}

	void Add_point(int value_p, int* count_logs, vector <string>* logs) {         //��������� ������� � ������
		if (Check_point(value_p, count_logs, logs)) {
			log = ("������ " + to_string(*count_logs) + ". ���������� �����. ������� " + to_string(value_p) + ".");
			points_line.push_back(value_p);
			(*logs).push_back(log);
		}
	}

	void Second_del(int value_p) {
		if (points_line.size() == 1) {
			points_line.clear();
		}
		else if (points_line.size() == 2) {
			if (points_line[0] == value_p) {
				points_line[0] = points_line[1];
			}
			points_line.pop_back();
		}
		else {
			points_line.erase(next(points_line.begin()));
		}
	}

	void Del_point(int value_p, int* count_logs, vector <string>* logs) {                      //������� ������� � ������
		for (int i = 0; i < points_line.size(); i++) {
			if (points_line[i] == value_p) {
				log = ("������ " + to_string(*count_logs) + ". �������� �����. ������� " + to_string(value_p) + ".");
				(*logs).push_back(log);
				Second_del(value_p);
				break;
			}
		}
	}

	void Print_points_line() {                                 //������� ������ ���� ������� � ������
		for (int i = 0; i < points_line.size(); i++) {
			cout << i << ": " << points_line[i] << endl;
		}
		cout << endl;
	}

	int Get_size() {
		return points_line.size();
	}

	vector <int> Get_points_line() {
		return points_line;
	}
};