#include <iostream>
#include <string.h>
#include <vector>
#include <string>

using namespace std;


class BigInteger {
public:
    BigInteger();
    BigInteger(string& str);
    BigInteger(int64_t digits);
    BigInteger(uint64_t digits);
    BigInteger(int);
    friend ostream& operator<<(ostream& os, const BigInteger& bi);
    uint64_t operator[](uint64_t i) const;
    uint64_t& operator[](uint64_t i);
    void RemoveLeadZeros();
    friend bool operator ==(const BigInteger& left, const BigInteger& right);
    friend bool operator !=(const BigInteger& left, const BigInteger& right);
    friend bool operator <(const BigInteger& left, const BigInteger& right);
    friend bool operator >(const BigInteger& left, const BigInteger& right);
    friend bool operator>=(const BigInteger& left, const BigInteger& right);
    friend bool operator<=(const BigInteger& left, const BigInteger& right);
    const BigInteger operator +() const;
    const BigInteger operator -() const;
    friend const BigInteger operator +(const  BigInteger& left, const BigInteger& right);
    friend const BigInteger operator -(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator *(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator /(const BigInteger& left, const BigInteger& right);
    void shift_right();
    bool odd() const;
    const BigInteger operator^(BigInteger n) const;
    friend string BigToString(const BigInteger& b);

private:
    static const uint64_t BASE = 1000000000;
    bool is_negative;
    std::vector<uint64_t> digits;
};

ostream& operator <<(ostream& os, const BigInteger& b) {
    if (b.digits.empty())
        os << 0;
    else {
        if (b.is_negative)
            os << '-';

        for (int64_t i = static_cast<uint64_t>(b.digits.size()) - 1; i >= 0; --i)
            os << b.digits[i];
    }
    return os;
}

std::string BigToString(const BigInteger& b) {
    string out;
    if (b.digits.empty()) 
        out = "0";        
    else {
        if (b.is_negative) 
            out = "-";

        for (int64_t i = static_cast<uint64_t>(b.digits.size()) - 1; i >= 0; --i)
            out.append(std::to_string(b.digits[i]));
    }
    return out;
}

uint64_t BigInteger::operator [](uint64_t i) const { return this->digits[i]; }
uint64_t& BigInteger::operator [](uint64_t i) { return this->digits[i]; }

BigInteger::BigInteger() {
    this->is_negative = false;
}

BigInteger::BigInteger(string& str) {
    if (str.length() == 0) {
        this->is_negative = false;
        return;
    }

    if (str[0] == '-') {
        this->is_negative = true;
        str = str.substr(1);
    }
    else {
        this->is_negative = false;
    }

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

BigInteger::BigInteger(int64_t digits) {
    if (digits < 0) {
        this->is_negative = true;
        digits = -digits;
    }
    else {
        this->is_negative = false;
    }

    do {
        this->digits.push_back(digits % BigInteger::BASE);
        digits = digits / BigInteger::BASE;
    } while (digits != 0);
}

BigInteger::BigInteger(uint64_t digits) {
    this->is_negative = false;
    do {
        this->digits.push_back(digits % BigInteger::BASE);
        digits = digits / BigInteger::BASE;
    } while (digits != 0);
}

BigInteger::BigInteger(int digit) {
    if (digit < 0) {
        this->is_negative = true;
    }
    else {
        this->is_negative = false;
    }

    this->digits.push_back(abs(digit) % BigInteger::BASE);
    digit = digit / BigInteger::BASE;

    if (digit != 0)
        this->digits.push_back(abs(digit));
}

void BigInteger::RemoveLeadZeros() {
    while (this->digits.size() > 1 && this->digits.back() == 0)
        this->digits.pop_back();  // destroy

    if (this->digits.size() == 1 && this->digits[0] == 0)
        this->is_negative = false;
}

bool operator==(const BigInteger& left, const BigInteger& right) {
    if (left.is_negative != right.is_negative)
        return false;

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
    if (left.is_negative) {
        return (right.is_negative) ? ((-right) < (-left)) : true;
    }
    else if (right.is_negative)
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

const BigInteger BigInteger::operator+() const {
    return BigInteger(*this);
}

const BigInteger BigInteger::operator-() const {
    BigInteger copy(*this);
    copy.is_negative = !copy.is_negative;
    return copy;
}

const BigInteger operator+(const BigInteger& left, const BigInteger& right) {
    if (left.is_negative)
        return (right.is_negative) ? -(-left + (-right)) : (right - (-left));
    else {
        if (right.is_negative)
            return (left - (-right));
    }

    uint64_t carry = 0;
    uint64_t max_size_integer = std::max(left.digits.size(), right.digits.size());
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
    if (right.is_negative)
        return left + (-right);
    else if (left.is_negative)
        return -(-left + right);
    else if (left < right)
        return -(right - left);

    uint16_t carry = 0;
    uint64_t left_size = left.digits.size();
    uint64_t right_size = right.digits.size();
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
        cout << "Error" << endl;

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
    for (uint64_t i = 0; i < left_size; ++i) {
        carry = 0;
        for (uint64_t j = 0; j < right_size || carry != 0; ++j) {
            cur = result.digits[i + j] + ((uint64_t)left.digits[i]) * (j < right_size ? right.digits[j] : 0) + carry;
            result.digits[i + j] = static_cast<uint64_t>(cur % BigInteger::BASE);
            carry = static_cast<uint64_t>(cur / BigInteger::BASE);
        }
    }

    result.is_negative = left.is_negative != right.is_negative;
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
    if (right == 0)
        cout << "Error" << endl;

    BigInteger base = right;
    base.is_negative = false;
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

    result.is_negative = left.is_negative != right.is_negative;

    result.RemoveLeadZeros();
    return result;
}

bool BigInteger::odd() const {
    return (this->digits.size() == 0) ? false : this->digits[0] & 1;
}

const BigInteger BigInteger::operator^(BigInteger n) const {
    BigInteger b(*this), result(1);
    while (n != 0) {
        if (n.odd())
            result = result * b;
        b = b * b;
        n = n / 2;
    }
    return result;
}

ostream& resultOperation(ostream& out, const BigInteger& left, const BigInteger& right, char& operation) {
    switch (operation) {
    case '+':
        out << (left + right);
        break;
    case '-':
        out << (left - right);
        break; 
    case '*':
        out << (left * right);
        break;
    case '/':
        out << (left / right);
        break;
    case '^':
        out << (left ^ right);
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