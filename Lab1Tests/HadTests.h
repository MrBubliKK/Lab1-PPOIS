#include "pch.h"
#include "CppUnitTest.h"
#include "../Machine.cpp"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HadTests
{
	TEST_CLASS(Lab_had) {
public:

	TEST_METHOD(had_pos)  //Проверяет позицию головки
	{
		Had had;
		int pos = 10;
		had.Set_position(pos);
		Assert::AreEqual(pos, had.Get_position());
	}

	TEST_METHOD(Increase_pos)  //Проверяет увеличение головки
	{
		Had had;
		int pos = 10;
		had.Set_position(pos);
		had.Increase_position();
		pos++;
		Assert::AreEqual(pos, had.Get_position());
	}

	TEST_METHOD(Reduce_pos)  //Проверяет уменьшение головки
	{
		Had had;
		int pos = 10;
		had.Set_position(pos);
		had.Reduce_position();
		pos--;
		Assert::AreEqual(pos, had.Get_position());
	}

	};
}