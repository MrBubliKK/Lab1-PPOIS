#include "pch.h"
#include "CppUnitTest.h"
#include "LineTests.h"


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Ruletests
{

	TEST_CLASS(Lab_rule) {
public:

	TEST_METHOD(Check_commmand)  //Проверяет на соответствие команды
	{
		Rule rule("<");
		string command = "<";
		Assert::AreEqual(command, rule.Get_command());
	}

	TEST_METHOD(Check_first_value)  //Проверяет на соответствие первого значения
	{
		Rule rule("<", 5);
		int first_value = 5;
		Assert::AreEqual(first_value, rule.Get_first_value());
	}

	TEST_METHOD(Check_second_value)  //Проверяет на соответствие второго значения
	{
		Rule rule("<", 7, 8);
		int second_value = 8;
		Assert::AreEqual(second_value, rule.Get_second_value());
	}

	TEST_METHOD(Check_rules_size)  //Проверяет размер списка правил
	{
		Machine machine(2);
		machine.Add_rule("<", 3, 0);
		machine.Add_rule("?", 3, 4);
		machine.Add_rule("?", 5, 7);
		int count = 3;
		Assert::AreEqual(count, machine.Get_rules_size());
	}

	TEST_METHOD(Check_add_rule)   //Проверяет добавление правила
	{
		Machine machine(2);
		machine.Add_rule("<", 1, 0);
		string command = "<";
		int first_value = 1;
		int second_value = 0;
		Assert::AreEqual(command, machine.Get_rules()[0].Get_command());
		Assert::AreEqual(first_value, machine.Get_rules()[0].Get_first_value());
		Assert::AreEqual(second_value, machine.Get_rules()[0].Get_second_value());
	}

	TEST_METHOD(Check_size_add_rule) //Проверяет размер при добавлении правил
	{
		Machine machine(2);
		machine.Add_rule("<", 1, 1);
		machine.Add_rule(">", 2, 2);
		int temp_count = machine.Get_count_rule();
		Assert::IsTrue(2 == machine.Get_count_rule());
	}

	TEST_METHOD(Check_size_del_rule) //Проверяет размер при удалении правил
	{
		Machine machine(2);
		machine.Add_rule("<", 1, 1);
		machine.Add_rule(">", 2, 2);
		machine.Del_rule();
		Assert::IsTrue(1 == machine.Get_count_rule());
	}

	TEST_METHOD(Check_logs)  //Проверяет логи на удаление пустоты
	{
		Machine machine(0);
		machine.Add_rule("<", 1, 1);
		machine.Add_rule(">", 2, 2);
		machine.Del_rule();
		machine.Del_rule();
		machine.Del_rule();
		string temp_log = ("Строка 5. Удаление команды . Команд нет.");
		Assert::AreEqual(temp_log, machine.Get_logs()[4]);
	}

	};
}