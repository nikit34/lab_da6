#include <iostream>
#include <string.h>
#include <vector>
#include <string>
#include <iomanip> 

using namespace std;



static const uint64_t BASE = 100000;

class BigInteger {
public:
    BigInteger() {};
    BigInteger(const string& str);
    BigInteger(uint64_t digits);
    friend ostream& operator<<(ostream& os, const BigInteger& bi);
    void RemoveLeadZeros();
    bool operator ==(const BigInteger& right) const;
    bool operator <(const BigInteger& right) const;
    bool operator >(const BigInteger& right) const;
    bool operator >=(const BigInteger& right) const;
    bool operator <=(const BigInteger& right) const;
    const int16_t Compare(const BigInteger& right) const;
    friend const BigInteger operator +(const  BigInteger& left, const BigInteger& right);
    friend const BigInteger operator -(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator *(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator /(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator^(const BigInteger& b, const BigInteger& n);
    const BigInteger MultShort(const BigInteger& other) const;
    void ShiftRight();
    friend string BigToString(const BigInteger& b);

private:
    vector<uint64_t> digits;
};

ostream& operator <<(ostream& os, const BigInteger& b) {
    if (b.digits.empty())
        os << 0;
    else {
        os << b.digits.back();
        for (int64_t i = b.digits.size() - 2; i >= 0; --i)
            os << setw(5) << setfill('0') << b.digits[i];
    }
    return os;
}

string BigToString(const BigInteger& b) {
    string out;
    if (b.digits.empty()) 
        out = "0";        
    else {
        for (int64_t i = b.digits.size() - 1; i >= 0; --i)
            out.append(to_string(b.digits[i]));
    }
    return out;
}

BigInteger::BigInteger(const string& str) {
    for (int64_t i = str.length() - 1; i >= 0; i = i - 5) {
        if (i < 5) {
            this->digits.push_back(atoll(str.substr(0, i + 1).c_str()));  // atoll string -> uint64_t
        }
        else {
            this->digits.push_back(atoll(str.substr(i - 4, 5).c_str()));
        }
    }
    this->RemoveLeadZeros();
}

BigInteger::BigInteger(uint64_t digits) {
    do {
        this->digits.push_back(digits % BASE);
        digits = digits / BASE;
    } while (digits != 0);
}

void BigInteger::RemoveLeadZeros() {
    while (this->digits.size() > 1 && this->digits.back() == 0)
        this->digits.pop_back();  // destroy
}

bool BigInteger::operator==(const BigInteger& right) const {
    return (this->Compare(right) == 0 ? true : false);
}

bool BigInteger::operator<(const BigInteger& right) const {
    return (this->Compare(right) == 1 ? true : false);
}

bool BigInteger::operator>(const BigInteger& right) const {
    return (this->Compare(right) == -1 ? true : false);
}

bool BigInteger::operator>=(const BigInteger& right) const {
    return ((this->Compare(right) == -1 || this->Compare(right) == 0) ? true : false);
}

bool BigInteger::operator<=(const BigInteger& right) const {
    return ((this->Compare(right) == 1 || this->Compare(right) == 0) ? true : false);
}

const int16_t BigInteger::Compare(const BigInteger& right) const {
    if (this->digits.size() < right.digits.size())
        return 1;
    else if (this->digits.size() > right.digits.size())
        return -1;
    for (size_t i = this->digits.size(); i > 0; i--) {
        if (this->digits[i - 1] < right.digits[i - 1])
            return 1;
        else if (this->digits[i - 1] > right.digits[i - 1])
            return -1;
    }
    return 0;
}

const BigInteger operator+(const BigInteger& left, const BigInteger& right) {
    uint64_t carry = 0;
    uint64_t max_size_integer = max(left.digits.size(), right.digits.size());
    uint64_t col_digit = 0;
    BigInteger res;

    for (uint64_t i = 0; i < max_size_integer; ++i) {
        if (left.digits.size() <= i)
            col_digit = right.digits[i] + carry;
        else if (right.digits.size() <= i)
            col_digit = left.digits[i] + carry; 
        else
            col_digit = left.digits[i] + right.digits[i] + carry;  
        res.digits.push_back(col_digit % BASE); 
        carry = col_digit / BASE; 
    }
    if (carry != 0)
        res.digits.push_back(carry);
    return res;
}

const BigInteger operator-(const BigInteger& left, const BigInteger& right) {
    uint64_t left_size = left.digits.size();
    uint64_t right_size = right.digits.size(); 

    if(left_size < right_size)
        throw logic_error("Error");

    uint16_t carry = 0;
    int64_t col_digit = 0;
    BigInteger res;

    for (uint64_t i = 0; i < left_size; ++i) {
        if (i >= right_size)
            col_digit = left.digits[i] - carry;
        else
            col_digit = left.digits[i] - right.digits[i] - carry;
        carry = 0;
        if (col_digit < 0) {
            col_digit = col_digit + BASE;
            carry = 1;
        }
        res.digits.push_back(col_digit);
    }
    if (carry == 1)
        throw logic_error("Error");

    res.RemoveLeadZeros();
    return res;
}

const BigInteger BigInteger::MultShort(const BigInteger& other) const {
    uint64_t carry = 0;
    uint64_t col_digit;
    uint64_t size = this->digits.size();
    BigInteger result;

    for (uint64_t i = 0; i < size; ++i) {
        col_digit = this->digits[i] * other.digits[0] + carry;
        result.digits.push_back(col_digit % BASE);
        carry = col_digit / BASE;
    }
    if (carry != 0) {
        result.digits.push_back(carry);
    }
    result.RemoveLeadZeros();
    return result;
}

const BigInteger operator*(const BigInteger& left, const BigInteger& right) {
    uint64_t right_size = right.digits.size();
    if (right_size == 1)
        return right.MultShort(left);

    uint64_t left_size = left.digits.size();
    if (left_size == 1)
        return left.MultShort(right);

    BigInteger result;
    result.digits.resize(left_size + right_size);
    uint64_t carry;
    uint64_t col_digit;
    uint64_t i, j;
    for (i = 0; i < right_size; ++i) {
        carry = 0;
        for (j = 0; j < left_size || carry != 0; ++j) {
            col_digit = result.digits[i + j] + (right.digits[i]) * (j < left_size ? left.digits[j] : 0) + carry;
            result.digits[i + j] = col_digit % BASE;
            carry = col_digit / BASE;
        }
    }
    result.RemoveLeadZeros();
    return result;
}

void BigInteger::ShiftRight() {
    if (this->digits.size() == 0) {
        this->digits.push_back(0);
        return;
    }

    this->digits.push_back(this->digits[this->digits.size() - 1]);
    uint64_t size = this->digits.size();
    for (uint64_t i = size - 2; i > 0; --i)
        this->digits[i] = this->digits[i - 1];
    this->digits[0] = 0;
}

const BigInteger operator/(const BigInteger& left, const BigInteger& right) {
    if (right == BigInteger(0))
        throw logic_error("Error");

    BigInteger base = right;
    BigInteger result, current, tmp;
    result.digits.resize(left.digits.size());
    uint64_t digit_result, l, r, m;

    for (int64_t i = left.digits.size() - 1; i >= 0; --i) {
        current.ShiftRight();
        current.digits[0] = left.digits[i];
        current.RemoveLeadZeros();
        digit_result = 0, l = 0, r = BASE;
        while (l <= r) {
            m = (l + r) / 2;
            tmp = base.MultShort(BigInteger(m));
            if (tmp <= current) {
                digit_result = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        result.digits[i] = digit_result;
        current = current - base * BigInteger(digit_result);
    }
    result.RemoveLeadZeros();
    return result;
}

const BigInteger operator^(const BigInteger& b, const BigInteger& n) {
    if (n.digits[0] == 0 && n.digits.size() == 1){
        if (b == BigInteger(0))
            throw logic_error("Error");
        else
            return BigInteger(1);
    }
    if (b == BigInteger(1) || n == BigInteger(1))
        return b;

    if (n.digits[0] % 2 == 0) {
        BigInteger x = b ^ (n / BigInteger(2));
        return x * x;
    }
    else {
        return b ^ (n - BigInteger(1)) * b;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line1;
    string line2;
    char operation;

    while (cin >> line1 >> line2 >> operation) {
        BigInteger left(line1);
        BigInteger right(line2);
        switch (operation) {
        case '+':
            cout << (left + right);
            break;
        case '-':
            try {
                cout << (left - right);
            }
            catch (logic_error& e) {
                cout << e.what();
            }
            break;
        case '*':
            cout << (left * right);
            break;
        case '/':
            try {
                cout << (left / right);
            }
            catch (logic_error& e) {
                cout << e.what();
            }
            break;
        case '^':
            try {
                cout << (left ^ right);
            }
            catch (logic_error& e) {
                cout << e.what();
            }
            break;
        case '<':
            cout << ((left < right) ? "true" : "false");
            break;
        case '>':
            cout << ((left > right) ? "true" : "false");
            break;
        case '=':
            cout << ((left == right) ? "true" : "false");
            break;
        default:
            cout << "Error";
            break;
        }
        cout << endl;
    }
    return 0;
}