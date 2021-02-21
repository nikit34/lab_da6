#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/long_arith.cpp"
#include "../Project1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "453465";
			BigInteger t1(s1);
			BigInteger t2(s1);
			Assert::IsTrue(t1 == t2);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "-453465";
			std::string s2 = "-453465";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsTrue(t1 == t2);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "453465";
			std::string s2 = "543543245";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsFalse(t1 == t2);
		}
		TEST_METHOD(TestMethod4)
		{
			std::string s1 = "453465";
			std::string s2 = "-453465";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsFalse(t1 == t2);
		}
	};

	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "453465";
			std::string s2 = "543543245";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsTrue(t1 != t2);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "453465";
			std::string s2 = "-543543245";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsTrue(t1 != t2);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "453465";
			BigInteger t1(s1);
			BigInteger t2(s1);
			Assert::IsFalse(t1 != t2);
		}
		TEST_METHOD(TestMethod4)
		{
			std::string s1 = "-453465";
			std::string s2 = "-453465";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsFalse(t1 != t2);
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


namespace UnitTest2
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "4576565422";
			std::string s2 = "534658754";
			std::string s3 = "5111224176";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 + b2), s3);
		}
	};
	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "5111224176";
			std::string s2 = "4576565422";
			std::string s3 = "534658754";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 - b2), s3);
		}

		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "5111224176";
			std::string s2 = "4576565422";
			std::string s3 = "534658754";
			longNumber b1(s1);
			longNumber b2(s2);
			Assert::AreEqual(bigToString(b1 - b2), s3);
		}
	};
}
