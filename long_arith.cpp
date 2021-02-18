#include <iostream>
#include <string>
#include <vector>

using namespace std;


class BigInteger {
public:
    BigInteger(string& str);
    BigInteger(signed long long& digits);
    BigInteger::BigInteger(unsigned long long& digits);
    void RemoveLeadZeros();

private:
	static const uint64_t BASE = 1000000000;
	std::vector<int> digits;
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


char* resultOperation(string& line1, string& line2, char& operation){
    string l1 = line1;
    string l2 = line1;
    char *res;
    switch (operation) {
    case '+':
        *res = 'vd';
        break;
    case '-':
        *res = 'vd';
        break;
    case '*':
        *res = 'vd';
        break;
    case '/':
        *res = 'vd';
        break;
    case '^':
        *res = 'vd';
        break;
    case '<':
        *res = 'vd';
        break;
    case '>':
        *res = 'vd';
        break;
    case '=':
        *res = 'vd'.c_str();
        break;
    default:
        cout << "Error";
        break;
    }
    return &res;
}

int main() {
    string line1;
    string line2;
    char *result = nullptr;
    char operation;

     while (true) {
        cin >> line1;
        cin >> line2;
        cin >> operation;
        result = resultOperation(line1, line2, operation);
        cout << result;
    }
    return 0;
}