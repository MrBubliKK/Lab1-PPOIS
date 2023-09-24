#include "pch.h"
#include "CppUnitTest.h"
#include "RuleTests.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MachineTests
{
	TEST_CLASS(Lab_machine) {
public:

	TEST_METHOD(Check_correct_command) //��������� ������� ������������
	{
		Machine machine(0);
		machine.Add_rule("<", 1, 0);
		bool temp_flag = machine.Correct_command(0);
		Assert::IsTrue(temp_flag);
		machine.Add_rule(">", 3, 1);
		temp_flag = machine.Correct_command(1);
		Assert::IsFalse(temp_flag);
	}

	TEST_METHOD(Check_work_reduce_command)  //��������� ���������� ��� < �� 0
	{
		Machine machine(0);
		Line line;
		Had had;
		machine.Add_rule("<", 0, 0);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(0, result);
	}

	TEST_METHOD(Check_work_reduce2_command)  //��������� ���������� <
	{
		Machine machine(0);
		Line line;
		Had had;
		machine.Add_rule("<", 1, 0);
		machine.Add_rule("<", 2, 0);
		machine.Add_rule(".", -1, -1);
		machine.Work_command(1, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(result, 1);
	}

	TEST_METHOD(Check_correct_reduce_word) //��������� �������������� ��� <
	{
		Machine machine(0);
		Line line;
		Had had;
		machine.Add_rule("<", 1, 0);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(result, 0);
	}

	TEST_METHOD(Check_work_increase_command)  //��������� ���������� ��� > �� 0
	{
		Machine machine(0);
		Line line;
		Had had;
		machine.Add_rule(">", 0, 0);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(0, result);
	}

	TEST_METHOD(Check_work_increase2_command)  //��������� ���������� >
	{
		Machine machine(0);
		Line line;
		Had had;
		machine.Add_rule("<", 1, 0);
		machine.Add_rule(">", 2, 0);
		machine.Add_rule(">", 3, 0);
		machine.Add_rule(".", -1, -1);
		machine.Work_command(2, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(result, 2);
	}

	TEST_METHOD(Check_correct_increase_word) //��������� �������������� ��� >
	{
		Machine machine(0);
		Line line;
		Had had;
		machine.Add_rule(">", 1, 0);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(result, 0);
	}

	TEST_METHOD(Check_ask_command)   //��������� ����������� ? �� ����� ��� ������ 0
	{
		Machine machine(0);
		Line line;
		Had had;
		int c_l;
		vector <string> logs;
		had.Set_position(0);
		c_l = machine.Get_count_logs();
		logs = machine.Get_logs();
		line.Add_point(0, &c_l, &logs);
		machine.Set_logs(logs);
		machine.Add_rule("?", 1, 0);
		machine.Add_rule(".", -1, -1);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(0, result);
	}

	TEST_METHOD(Check_ask_work_command)  //��������� ���������� ?
	{
		Machine machine(0);
		Line line;
		Had had;
		int c_l;
		vector <string> logs;
		had.Set_position(0);
		c_l = machine.Get_count_logs();
		logs = machine.Get_logs();
		line.Add_point(0, &c_l, &logs);
		machine.Set_logs(logs);
		machine.Add_rule(">", 2, 0);
		machine.Add_rule("?", 1, 3);
		machine.Add_rule(".", -1, -1);
		machine.Work_command(1, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(2, result);
	}

	TEST_METHOD(Check_ask_first0_value)  //��������� ���������� ��� ������ 0
	{
		Machine machine(0);
		Line line;
		Had had;
		had.Set_position(0);
		machine.Add_rule("?", 0, 2);
		machine.Add_rule(">", 3, 0);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(0, result);
	}

	TEST_METHOD(Check_ask_first_value) //��������� ���������� ��� ������ �� 0
	{
		Machine machine(0);
		Line line;
		Had had;
		had.Set_position(0);
		machine.Add_rule("?", 3, 2);
		machine.Add_rule("<", 3, 0);
		machine.Add_rule(".", -1, -1);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(2, result);
	}

	TEST_METHOD(check_one_command_zero) //��������� ���������� 1 ������� �� 0
	{
		Machine machine(0);
		Line line;
		Had had;
		had.Set_position(0);
		machine.Add_rule("1", 0, 0);
		machine.Add_rule(".", -1, -1);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(0, result);
	}

	TEST_METHOD(Check_one_command) //��������� ���������� 1 ������� �� �� 0
	{
		Machine machine(0);
		Line line;
		Had had;
		had.Set_position(0);
		machine.Add_rule("1", 3, 0);
		machine.Add_rule(".", -1, -1);
		machine.Add_rule(".", -1, -1);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(result, 2);
	}

	TEST_METHOD(Check_one_no_correct_command) //��������� ���������� 1 ������� ���������
	{
		Machine machine(0);
		Line line;
		Had had;
		had.Set_position(0);
		int c_l;
		vector <string> logs;
		had.Set_position(0);
		c_l = machine.Get_count_logs();
		logs = machine.Get_logs();
		line.Add_point(0, &c_l, &logs);
		machine.Set_logs(logs);
		machine.Add_rule("1", 3, 0);
		machine.Add_rule(".", -1, -1);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(result, 0);
	}

	TEST_METHOD(Check_zero_zero_command) //�������� 0 �� ���������� ������� ��������
	{
		Machine machine(0);
		Line line;
		Had had;
		had.Set_position(0);
		int c_l;
		vector <string> logs;
		had.Set_position(0);
		c_l = machine.Get_count_logs();
		logs = machine.Get_logs();
		line.Add_point(0, &c_l, &logs);
		machine.Set_logs(logs);
		machine.Add_rule("0", 0, 0);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(result, 0);
	}

	TEST_METHOD(Check_zero_no_zero_command) //�������� 0 �� ���������� ������� ����������
	{
		Machine machine(0);
		Line line;
		Had had;
		had.Set_position(0);
		int c_l;
		vector <string> logs;
		had.Set_position(0);
		c_l = machine.Get_count_logs();
		logs = machine.Get_logs();
		line.Add_point(0, &c_l, &logs);
		machine.Set_logs(logs);
		machine.Add_rule("0", 3, 0);
		machine.Add_rule("1", 2, 0);
		machine.Add_rule("�", -1, -1);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(result, 2);
	}

	TEST_METHOD(Check_zero_no�or_command) //�������� 0 �� ���������� �������������
	{
		Machine machine(0);
		Line line;
		Had had;
		had.Set_position(0);
		int c_l;
		vector <string> logs;
		had.Set_position(0);
		c_l = machine.Get_count_logs();
		logs = machine.Get_logs();
		line.Add_point(0, &c_l, &logs);
		machine.Set_logs(logs);
		machine.Add_rule("0", 3, 0);
		machine.Add_rule("1", 2, 0);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(result, 0);
	}

	TEST_METHOD(Check_point_correct_work) //�������� �� ������������ .
	{
		Machine machine(0);
		Line line;
		Had had;
		machine.Add_rule(".", 3, 0);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(0, result);
	}

	TEST_METHOD(Check_point_work) //�������� �� ������ .
	{
		Machine machine(0);
		Line line;
		Had had;
		machine.Add_rule(".", -1, -1);
		machine.Work_command(0, had, line);
		int result = machine.Get_counter();
		Assert::AreEqual(0, result);
	}
	};
}