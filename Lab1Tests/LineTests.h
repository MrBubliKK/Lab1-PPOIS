#include "pch.h"
#include "CppUnitTest.h"
#include "HadTests.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LineTests
{

	TEST_CLASS(Lab_line) {
public:

	TEST_METHOD(Chech_size) //��������� ������ ������ �����
	{
		Line line;
		vector <string> logs;
		int count_logs = 0;
		int count = 0;
		for (int i = 0; i < 2; i++) {
			line.Add_point(i, &count_logs, &logs);
			count++;
		}
		Assert::AreEqual(count, line.Get_size());
	}

	TEST_METHOD(Check_count_logs)    //��������� ���-�� ����� � ����������� �����
	{
		Line line;
		vector <string> logs;
		int c_l;
		Machine machine(0);
		for (int i = 0; i < 2; i++) {
			c_l = machine.Get_count_logs();
			logs = machine.Get_logs();
			line.Add_point(i, &c_l, &logs);
			machine.Set_logs(logs);
		}
		Assert::AreEqual(2, line.Get_size());
	}

	TEST_METHOD(Check_vector_logs_size)  //������� ������ ������� � ���������� �������
	{
		Line line;
		vector <string> logs;
		int c_l;
		Machine machine(0);
		for (int i = 0; i < 2; i++) {
			c_l = machine.Get_count_logs();
			logs = machine.Get_logs();
			line.Add_point(i, &c_l, &logs);
			machine.Set_logs(logs);
		}
		int count = machine.Get_logs().size();
		Assert::AreEqual(2, count);
	}

	TEST_METHOD(Check_first_add_point)   //��������� �� ������ ���������� ���������
	{
		Line line;
		vector <string> logs;
		int count_logs = 0;
		bool flag = true;
		Assert::AreEqual(flag, line.Check_point(3, &count_logs, &logs));
	}

	TEST_METHOD(Check_same_add_point)    //��������� �� ��������� ���������� ���������
	{
		Line line;
		vector <string> logs;
		int count_logs = 0;
		bool flag = false;
		line.Add_point(5, &count_logs, &logs);
		Assert::AreEqual(flag, line.Check_point(5, &count_logs, &logs));
	}

	TEST_METHOD(Check_del_point)     //��������� �������� ��������
	{
		Line line;
		vector <string> logs;
		int count_logs = 0;
		bool flag = true;
		line.Add_point(5, &count_logs, &logs);
		line.Del_point(5, &count_logs, &logs);
		Assert::AreEqual(flag, line.Check_point(5, &count_logs, &logs));
	}

	TEST_METHOD(Check_first_rule_second_del)  //��������� 1-� ����� ��������
	{
		Line line;
		vector <string> logs;
		int count_logs = 0;
		bool flag = true;
		line.Add_point(5, &count_logs, &logs);
		line.Second_del(5);
		Assert::AreEqual(flag, line.Check_point(5, &count_logs, &logs));
	}

	TEST_METHOD(Check_second1_rule_second_del)  //��������� 2-� ����� �������� �����
	{
		Line line;
		vector <string> logs;
		int count_logs = 0;
		bool flag = true;
		line.Add_point(5, &count_logs, &logs);
		line.Add_point(6, &count_logs, &logs);
		line.Second_del(5);
		Assert::AreEqual(flag, line.Check_point(5, &count_logs, &logs));
	}

	TEST_METHOD(Check_second2_rule_second_del)  //��������� 2-� ����� �������� ������
	{
		Line line;
		vector <string> logs;
		int count_logs = 0;
		bool flag = true;
		line.Add_point(5, &count_logs, &logs);
		line.Add_point(6, &count_logs, &logs);
		line.Second_del(6);
		Assert::AreEqual(flag, line.Check_point(6, &count_logs, &logs));
	}

	TEST_METHOD(Check_third_rule_second_del)  //��������� 3-� ����� ��������
	{
		Line line;
		vector <string> logs;
		int count_logs = 0;
		bool flag = true;
		line.Add_point(5, &count_logs, &logs);
		line.Add_point(6, &count_logs, &logs);
		line.Add_point(7, &count_logs, &logs);
		line.Second_del(6);
		Assert::AreEqual(flag, line.Check_point(6, &count_logs, &logs));
	}
	};
}