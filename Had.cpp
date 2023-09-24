#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;


//КАРЕТКА
class Had {
private:
	int position;               //Передает позицию каретки

public:

	void Increase_position() {  //Передвигает каретку на 1 вправо
		position++;
	}

	void Reduce_position() {    //Передвигает каретку на 1 влево
		position--;
	}

	void Print_position() {
		cout << "Позиция каретки: " << position << endl;     //Показывает позицию каретки
	}

	int Get_position() {
		return position;
	}

	void Set_position(int position_v) {
		position = position_v;
	}

};