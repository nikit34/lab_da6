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

	TEST_CLASS(UnitTest4)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			 /*std::string s1 = "45346565456";
			 std::string s2 = "655334";
			 std::string s3 = "4980445347220790";*/
			std::string s1 = "49804";
			std::string s2 = "65006";
			std::string s3 = "114810";

			BigInteger t1(s1);
			BigInteger t2(s2);
			BigInteger t3(s3);
			Assert::IsTrue(t1 + t2 == t3);
		}
	};
}