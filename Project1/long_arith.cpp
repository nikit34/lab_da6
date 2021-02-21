#include <iostream>
#include <string.h>
#include <vector>
#include <string>
#include <iomanip> 

using namespace std;


class BigInteger {
public:
    BigInteger() {};
    BigInteger(const string& str);
    BigInteger(uint64_t digits);
    friend ostream& operator<<(ostream& os, const BigInteger& bi);
    void RemoveLeadZeros();
    friend bool operator ==(const BigInteger& left, const BigInteger& right);
    friend bool operator !=(const BigInteger& left, const BigInteger& right);
    friend bool operator <(const BigInteger& left, const BigInteger& right);
    friend bool operator >(const BigInteger& left, const BigInteger& right);
    friend bool operator>=(const BigInteger& left, const BigInteger& right);
    friend bool operator<=(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator +(const  BigInteger& left, const BigInteger& right);
    friend const BigInteger operator -(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator *(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator /(const BigInteger& left, const BigInteger& right);
    void shift_right();
    const BigInteger operator^(const BigInteger& n) const;
    friend string BigToString(const BigInteger& b);

private:
    static const uint64_t BASE = 1000000000;
    vector<uint64_t> digits;
};

ostream& operator <<(ostream& os, const BigInteger& b) {
    if (b.digits.empty())
        os << 0;
    else {
        os << b.digits.back();
        for (int64_t i = b.digits.size() - 2; i >= 0; --i)
            os << setw(9) << setfill('0') << b.digits[i];
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
    for (int64_t i = str.length() - 1; i >= 0; i = i - 9) {
        if (i < 9) {
            this->digits.push_back(atoll(str.substr(0, i + 1).c_str()));  // atoll string -> uint64_t
        }
        else {
            this->digits.push_back(atoll(str.substr(i - 8, 9).c_str()));
        }
    }
    this->RemoveLeadZeros();
}

BigInteger::BigInteger(uint64_t digits) {
    do {
        this->digits.push_back(digits % BigInteger::BASE);
        digits = digits / BigInteger::BASE;
    } while (digits != 0);
}

void BigInteger::RemoveLeadZeros() {
    while (this->digits.size() > 1 && this->digits.back() == 0)
        this->digits.pop_back();  // destroy
}

bool operator==(const BigInteger& left, const BigInteger& right) {
    if (left.digits.empty())
        return (right.digits.empty() || (right.digits.size() == 1 && right.digits[0] == 0)) ? true : false;

    if (right.digits.empty())
        return (left.digits.size() == 1 && left.digits[0] == 0) ? true : false;

    if (left.digits.size() != right.digits.size())
        return false;

    for (uint64_t i = 0; i < left.digits.size(); ++i)
        if (left.digits[i] != right.digits[i])
            return false;

    return true;
}

bool operator!=(const BigInteger& left, const BigInteger& right) {
    return !(left == right);
}

bool operator<(const BigInteger& left, const BigInteger& right) {
    if (left == right)
        return false;
    else {
        if (left.digits.size() != right.digits.size()) {
            return left.digits.size() < right.digits.size();
        }
        else {
            for (int64_t i = left.digits.size() - 1; i >= 0; --i) {
                if (left.digits[i] != right.digits[i])
                    return left.digits[i] < right.digits[i];
            }
            return false;
        }
    }
}

bool operator>(const BigInteger& left, const BigInteger& right) {
    return !(left <= right);
}

bool operator>=(const BigInteger& left, const BigInteger& right) {
    return !(left < right);
}

bool operator<=(const BigInteger& left, const BigInteger& right) {
    return (left < right || left == right);
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
        res.digits.push_back(col_digit % left.BASE); 
        carry = col_digit / left.BASE; 
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
            col_digit = col_digit + left.BASE;
            carry = 1;
        }
        res.digits.push_back(col_digit);
    }
    if (carry == 1)
        throw logic_error("Error");

    res.RemoveLeadZeros();
    return res;
}

const BigInteger operator*(const BigInteger& left, const BigInteger& right) {
    BigInteger result;
    uint64_t left_size = left.digits.size();
    uint64_t right_size = right.digits.size();
    result.digits.resize(left_size + right_size);

    uint64_t carry;
    uint64_t cur;
    for (uint64_t i = 0; i < right_size; ++i) {
        carry = 0;
        for (uint64_t j = 0; j < left_size || carry != 0; ++j) {
            cur = result.digits[i + j] + ((uint64_t)right.digits[i]) * (j < left_size ? left.digits[j] : 0) + carry;
            result.digits[i + j] = cur % BigInteger::BASE;
            carry = cur / BigInteger::BASE;
        }
    }
    result.RemoveLeadZeros();
    return result;
}

void BigInteger::shift_right() {
    if (this->digits.size() == 0) {
        this->digits.push_back(0);
        return;
    }

    this->digits.push_back(this->digits[this->digits.size() - 1]);
    for (uint64_t i = this->digits.size() - 2; i > 0; --i)
        this->digits[i] = this->digits[i - 1];
    this->digits[0] = 0;
}

const BigInteger operator/(const BigInteger& left, const BigInteger& right) {
    if (right == BigInteger("0"))
        throw logic_error("Error");

    BigInteger base = right;
    BigInteger result, current, tmp;
    result.digits.resize(left.digits.size());
    uint64_t digit_result, l, r, m;

    for (int64_t i = static_cast<uint64_t>(left.digits.size()) - 1; i >= 0; --i) {
        current.shift_right();
        current.digits[0] = left.digits[i];
        current.RemoveLeadZeros();
        digit_result = 0, l = 0, r = BigInteger::BASE;
        while (l <= r) {
            m = (l + r) / 2;
            BigInteger big_m(m);
            tmp = base * big_m;
            if (tmp <= current) {
                digit_result = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        result.digits[i] = digit_result;
        current = current - base * digit_result;
    }
    result.RemoveLeadZeros();
    return result;
}

const BigInteger BigInteger::operator^(const BigInteger& n) const {
    BigInteger b(*this);
    if (n == BigInteger(0)){
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

ostream& resultOperation(ostream& out, const BigInteger& left, const BigInteger& right, char& operation) {
    switch (operation) {
    case '+':
        out << (left + right);
        break;
    case '-':
        try {
            out << (left - right);
        }
        catch (logic_error& e) {
            out << e.what();
        }
        break; 
    case '*':
        out << (left * right);
        break;
    case '/':
        try {
            out << (left / right);
        }
        catch (logic_error& e) {
            out << e.what();
        }
        break;
    case '^':
        try {
            out << (left ^ right);
        }
        catch (logic_error& e) {
            out << e.what();
        }
        break;
    case '<':
        out << ((left < right) ? "true" : "false");
        break;
    case '>':
        out << ((left > right) ? "true" : "false");
        break;
    case '=':
        out << ((left == right) ? "true" : "false");
        break;
    default:
        out << "Error";
        break;
    }
    return out << endl;
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
        resultOperation(cout, left, right, operation);
    }
    return 0;
}