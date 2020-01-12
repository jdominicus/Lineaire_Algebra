#include "pch.h"
#include "CppUnitTest.h"
#include "../Lineaire_Algebra/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Matrix m{ 2,2 };
			m(0, 0) = 9;
			m(0, 1) = -7;
			m(1, 0) = 5;
			m(1, 1) = -5;

			Matrix n{ 2,2 };
			n(0, 0) = -4;
			n(0, 1) = -1;
			n(1, 0) = 7;
			n(1, 1) = 1;

			Matrix result = m - n;

			Assert::AreEqual(result(0, 0), (double)13);
			Assert::AreEqual(result(0, 1), (double)-6);
			Assert::AreEqual(result(1, 0), (double)-2);
			Assert::AreEqual(result(1, 1), (double)-6);
		}
	};
}
