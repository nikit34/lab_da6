#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/long_arith.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "453465";
			std::string s2 = "6767657665";
			BigInteger t1(s1);
			BigInteger t2(s2);
			BigInteger t3(s2);
			t1 = t2;
			Assert::AreEqual(t1, t3);
		}
	};

	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "453465";
			std::string s2 = "6767657665";
			BigInteger t1(s1);
			BigInteger t2(s2);
			BigInteger t3(s2);
			t1 = t2;
			Assert::AreEqual(t1, t3);
		}
	};

	TEST_CLASS(UnitTest3)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			std::string s = "453465";
			BigInteger t(s);
			Assert::AreEqual(t.odd(), true);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string s = "-453465";
			BigInteger t(s);
			Assert::AreEqual(t.odd(), true);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s = "45346565456";
			BigInteger t(s);
			Assert::AreEqual(t.odd(), false);
		}
	};
}
