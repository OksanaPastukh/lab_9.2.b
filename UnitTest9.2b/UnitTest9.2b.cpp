#include "pch.h"
#include "CppUnitTest.h"
#include "../Project9.2.b/project9.2.b.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest92b
{
	TEST_CLASS(UnitTest92b)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int c;
			Student* p = new Student[5];
			p[0].prizv = "Pastukh";
			p[0].course = 1;
			p[0].specialty = ComputerScience;
			p[0].grades_in_programming = 5;
			p[1].prizv = "Petrov";
			p[1].course = 2;
			p[1].specialty = Informatics;
			p[1].grades_in_numerical_methods = 4;
			p[2].prizv = "Ivanov";
			p[2].course = 3;
			p[2].specialty = Informatics;
			p[2].grades_in_numerical_methods = 3;
			p[3].prizv = "Abramov";
			p[3].course = 4;
			p[3].specialty = Mathematics;
			p[3].grades_in_pedagogy = 2;
			p[4].prizv = "Karginov";
			p[4].course = 4;
			p[4].specialty = Mathematics;
			p[4].grades_in_pedagogy = 2;
			c = BinSearch(p, 5, "Ivanov", 3, 3);
			Assert::AreEqual(c, 2);
		}
	};
}
