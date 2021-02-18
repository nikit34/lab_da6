#include <iostream>
#include <string>
#include <vector>

using namespace std;


class BigInteger {
public:
    BigInteger(string& str);
    BigInteger(signed long long& digits);
    BigInteger(unsigned long long& digits);
    void RemoveLeadZeros();
    friend bool operator==(const BigInteger& left, const BigInteger& right);

private:
	static const uint64_t BASE = 1000000000;
	std::vector<uint16_t> digits;
	bool is_negative;
};

BigInteger::BigInteger(string& str) {
    if (str.length() == 0){
        this->is_negative = false;
        return;
    }

    if (str[0] == '-') {
        this->is_negative = true;
        str = str.substr(1);
    } else {
        this->is_negative = false;
    }

    for (long long i = str.length(); i > 0; i -= 9) {
        if (i < 9)
            this->digits.push_back(atoi(str.substr(0, i).c_str()));  // atoi string -> long
        else
            this->digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
    }
    this->RemoveLeadZeros();

}

void BigInteger::RemoveLeadZeros() {
    while (this->digits.size() > 1 && this->digits.back() == 0)
        this->digits.pop_back();  // destroy

    if (this->digits.size() == 1 && this->digits[0] == 0)
        this->is_negative = false;
}

BigInteger::BigInteger(signed long long& digits) {
        if (digits < 0) {
            this->is_negative = true;
            digits = -digits;
        }
        else {
            this->is_negative = false;
        }

        do {
            this->digits.push_back(digits % BigInteger::BASE);
            digits /= BigInteger::BASE;
        } while (digits != 0);
}

BigInteger::BigInteger(unsigned long long& digits) {
    this->is_negative = false;
    do {
        this->digits.push_back(digits % BigInteger::BASE);
            digits /= BigInteger::BASE;
    } while (digits != 0);
}

bool operator==(const BigInteger& left, const BigInteger& right) {
        if (left.is_negative != right.is_negative)
            return false;

        if (left.digits.empty())
            return true ? (right.digits.empty() || (right.digits.size() == 1 && right.digits[0] == 0)) : false;

        if (right.digits.empty())
            return true ? (left.digits.size() == 1 && left.digits[0] == 0) : false;

        if (left.digits.size() != right.digits.size())
            return false;
            
        for (size_t i = 0; i < left.digits.size(); ++i)
            if (left.digits[i] != right.digits[i])
                return false;

        return true;
}

void resultOperation(string& line1, string& line2, char& operation, vector<uint16_t>& res){
    string l1 = line1;
    string l2 = line1;
    BigInteger left(line1);
    BigInteger right(line2);

    switch (operation) {
    case '+':

        break;
    case '-':

        break;
    case '*':

        break;
    case '/':

        break;
    case '^':

        break;
    case '<':

        break;
    case '>':

        break;
    case '=':

        break;
    default:
        cout << "Error";
        break;
    }
}

int main() {
    string line1;
    string line2;
    std::vector<uint16_t> result;
    char operation;

     while (true) {
        cin >> line1;
        cin >> line2;
        cin >> operation;
        resultOperation(line1, line2, operation, result);
        cout << result.size();
    }
    return 0;
}