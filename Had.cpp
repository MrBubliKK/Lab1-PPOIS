#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;


//�������
class Had {
private:
	int position;               //�������� ������� �������

public:

	void Increase_position() {  //����������� ������� �� 1 ������
		position++;
	}

	void Reduce_position() {    //����������� ������� �� 1 �����
		position--;
	}

	void Print_position() {
		cout << "������� �������: " << position << endl;     //���������� ������� �������
	}

	int Get_position() {
		return position;
	}

	void Set_position(int position_v) {
		position = position_v;
	}

};