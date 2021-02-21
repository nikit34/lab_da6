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
			std::string s1 = "453465";
			std::string s2 = "543543245";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsTrue(t1 <= t2);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "453465";
			std::string s2 = "-543543245";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsFalse(t1 <= t2);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "453465";
			std::string s2 = "453465";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsTrue(t1 <= t2);
		}
	};

	TEST_CLASS(UnitTest4)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "543543245";
			std::string s2 = "453465";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsTrue(t1 >= t2);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "-543543245";
			std::string s2 = "453465";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsFalse(t1 >= t2);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "543543245";
			std::string s2 = "543543245";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsTrue(t1 >= t2);
		}
	};

	TEST_CLASS(UnitTest5)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "453465";
			std::string s2 = "543543245";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsTrue(t1 < t2);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "453465";
			std::string s2 = "-543543245";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsFalse(t1 < t2);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "453465";
			std::string s2 = "453465";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsFalse(t1 < t2);
		}
	};

	TEST_CLASS(UnitTest6)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "543543245";
			std::string s2 = "453465";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsTrue(t1 > t2);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "-543543245";
			std::string s2 = "453465";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsFalse(t1 > t2);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "453465";
			std::string s2 = "453465";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsFalse(t1 > t2);
		}
	};

	TEST_CLASS(UnitTest7)
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
		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "45765654665422";
			std::string s2 = "0000065875453";
			std::string s3 = "45765720540875";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 + b2), s3);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "001000005422";
			std::string s2 = "0004455453";
			std::string s3 = "1004460875";
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
			std::string s1 = "45765720540875";
			std::string s2 = "0000065875453";
			std::string s3 = "45765654665422";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 - b2), s3);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "10009121570876";
			std::string s2 = "010004576522";
			std::string s3 = "9999116994354";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 - b2), s3);
		}
	};
	TEST_CLASS(UnitTest3)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "5226";
			std::string s2 = "4565422";
			std::string s3 = "23858895372";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 * b2), s3);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "526";
			std::string s2 = "4565422";
			std::string s3 = "2401411972";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 * b2), s3);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "00526";
			std::string s2 = "45654204";
			std::string s3 = "24014111304"; // мои реквизиты )
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 * b2), s3);
		}
	};
	TEST_CLASS(UnitTest4)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "23858895372";
			std::string s2 = "4565422";
			std::string s3 = "5226";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 / b2), s3);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "2401411972";
			std::string s2 = "526";
			std::string s3 = "4565422";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 / b2), s3);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "00257983739677317712";
			std::string s2 = "5675666";
			std::string s3 = "45454355432";
			longNumber b1(s1);
			longNumber b2(s2);
			Assert::AreEqual(bigToString(b1 / b2), s3);
		}
	};
}
