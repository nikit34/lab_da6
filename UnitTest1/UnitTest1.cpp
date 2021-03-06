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
			std::string s1 = "453465";
			std::string s2 = "543543245";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsFalse(t1 == t2);
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
			std::string s1 = "453465";
			std::string s2 = "453465";
			BigInteger t1(s1);
			BigInteger t2(s2);
			Assert::IsFalse(t1 > t2);
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
			std::string s1 = "00040054";
			std::string s2 = "10658754";
			std::string s3 = "10698808";
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
			std::string s1 = "26";
			std::string s2 = "422";
			std::string s3 = "10972";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 * b2), s3);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "526";
			std::string s2 = "542";
			std::string s3 = "285092"; // ��� ��������� )
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 * b2), s3);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "00004520";
			std::string s2 = "4002";
			std::string s3 = "18089040";
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
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 / b2), s3);
		}
	};
	TEST_CLASS(UnitTest5)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string s1 = "21";
			std::string s2 = "0003";
			std::string s3 = "9261";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 ^ b2), s3);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string s1 = "23852";
			std::string s2 = "4";
			std::string s3 = "323667581491753216";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 ^ b2), s3);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string s1 = "22";
			std::string s2 = "43";
			std::string s3 = "5298772520065297710013152795217779063266385813905550082048";
			BigInteger b1(s1);
			BigInteger b2(s2);
			Assert::AreEqual(BigToString(b1 ^ b2), s3);
		}
	};
}
