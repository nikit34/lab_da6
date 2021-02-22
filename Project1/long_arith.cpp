#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include <cstdlib>
#include <algorithm>
#include <cmath>


static const unsigned long long BASE = 100000;

class BigInteger {
public:
    BigInteger() = default;
    BigInteger(const std::string& str);
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bi);
    void RemoveLeadZeros();
    bool operator ==(const BigInteger& right) const;
    bool operator <(const BigInteger& right) const;
    bool operator >(const BigInteger& right) const;
    bool operator >=(const BigInteger& right) const;
    bool operator <=(const BigInteger& right) const;
    const int Compare(const BigInteger& right) const;
    friend const BigInteger operator +(const  BigInteger& left, const BigInteger& right);
    friend const BigInteger operator -(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator *(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator /(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator^(const BigInteger& b, const BigInteger& n);
    friend BigInteger IPow(const BigInteger& b, const BigInteger& n);
    const BigInteger MultShort(const BigInteger& other) const;
    friend const BigInteger MultLong(const BigInteger& left, const BigInteger& right);
    void ShiftRight();
    friend std::string BigToString(const BigInteger& b);

private:
    std::vector<unsigned long long> digits;
};

std::ostream& operator <<(std::ostream& os, const BigInteger& b) {
    os << (b.digits.empty()) ? 0 : b.digits.back();
    unsigned long long size = static_cast<unsigned long long>(b.digits.size());
    for (long long i = size - 2; i >= 0; --i)
        os << std::setw(5) << std::setfill('0') << b.digits[i];
    return os;
}

std::string BigToString(const BigInteger& b) {
    std::string out;
    if (b.digits.empty()) 
        out = "0";        
    else {
        unsigned long long size = b.digits.size();
        for (long long i = size - 1; i >= 0; --i)
            out.append(std::to_string(b.digits[i]));
    }
    return out;
}

BigInteger::BigInteger(const std::string& str) {
    unsigned long long size = str.length();
    for (long long i = size - 1; i >= 0; i = i - 5) {
        if (i < 5) {
            this->digits.push_back(atoll(str.substr(0, i + 1).c_str()));  // atoll string -> unsigned long long
        }
        else {
            this->digits.push_back(atoll(str.substr(i - 4, 5).c_str()));
        }
    }
    this->RemoveLeadZeros();
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

const int BigInteger::Compare(const BigInteger& right) const {
    unsigned long long left_size = static_cast<unsigned long long>(this->digits.size());
    unsigned long long right_size = static_cast<unsigned long long>(right.digits.size());

    if (left_size < right_size)
        return 1;
    else if (left_size > right_size)
        return -1;
    for (size_t i = left_size; i > 0; i--) {
        if (this->digits[i - 1] < right.digits[i - 1])
            return 1;
        else if (this->digits[i - 1] > right.digits[i - 1])
            return -1;
    }
    return 0;
}

const BigInteger operator+(const BigInteger& left, const BigInteger& right) {
    unsigned long long left_size = static_cast<unsigned long long>(left.digits.size());
    unsigned long long right_size = static_cast<unsigned long long>(right.digits.size());
    unsigned long long carry = 0;
    unsigned long long max_size_integer = std::max(left_size, right_size);
    unsigned long long col_digit;
    BigInteger res;

    for (unsigned long long i = 0; i < max_size_integer; ++i) {
        if (left_size <= i)
            col_digit = right.digits[i] + carry;
        else if (right_size <= i)
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
    unsigned long long left_size = static_cast<unsigned long long>(left.digits.size());
    unsigned long long right_size = static_cast<unsigned long long>(right.digits.size());

    if(left_size < right_size)
        throw std::logic_error("Error");

    int carry = 0;
    long long col_digit = 0;
    BigInteger res;

    for (unsigned long long i = 0; i < left_size; ++i) {
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
        throw std::logic_error("Error");

    res.RemoveLeadZeros();
    return res;
}

const BigInteger BigInteger::MultShort(const BigInteger& other) const {
    unsigned long long carry = 0;
    unsigned long long col_digit;
    unsigned long long size = static_cast<unsigned long long>(this->digits.size());
    BigInteger result;

    for (unsigned long long i = 0; i < size; ++i) {
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

const BigInteger MultLong(const BigInteger& left, const BigInteger& right) {
    unsigned long long left_size = static_cast<unsigned long long>(left.digits.size());
    unsigned long long right_size = static_cast<unsigned long long>(right.digits.size());

    BigInteger result;
    result.digits.resize(left_size + right_size);
    unsigned long long carry;
    unsigned long long col_digit;
    unsigned long long i, j;
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

const BigInteger operator*(const BigInteger& left, const BigInteger& right) {
    unsigned long long right_size = static_cast<unsigned long long>(right.digits.size());
    if (right_size == 1)
        return right.MultShort(left);

    unsigned long long left_size = static_cast<unsigned long long>(left.digits.size());
    if (left_size == 1)
        return left.MultShort(right);

    BigInteger result = MultLong(left, right);
    result.RemoveLeadZeros();
    return result;
}

void BigInteger::ShiftRight() {
    if (this->digits.size() == 0) {
        this->digits.push_back(0);
        return;
    }

    this->digits.push_back(this->digits[this->digits.size() - 1]);
    unsigned long long size = this->digits.size();
    for (unsigned long long i = size - 2; i > 0; --i)
        this->digits[i] = this->digits[i - 1];
    this->digits[0] = 0;
}

const BigInteger operator/(const BigInteger& left, const BigInteger& right) {
    if (right == BigInteger("0"))
        throw std::logic_error("Error");

    BigInteger base = right;
    BigInteger result, current, tmp;
    unsigned long long size = left.digits.size();
    result.digits.resize(size);
    unsigned long long digit_result, l, r, m;

    for (long long i = size - 1; i >= 0; --i) {
        current.ShiftRight();
        current.digits[0] = left.digits[i];
        current.RemoveLeadZeros();
        digit_result = 0, l = 0, r = BASE;
        while (l <= r) {
            m = (l + r) / 2;
            tmp = base.MultShort(BigInteger(std::to_string(m)));
            if (tmp <= current) {
                digit_result = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        result.digits[i] = digit_result;
        current = current - base.MultShort(BigInteger(std::to_string(digit_result)));
    }
    result.RemoveLeadZeros();
    return result;
}

const BigInteger operator^(const BigInteger& b, const BigInteger& n) {
    if (n == BigInteger("0")){
        if (b == BigInteger("0"))
            throw std::logic_error("Error");
        else
            return BigInteger("1");
    }
    if (b == BigInteger("1") || n == BigInteger("1"))
        return b;

    if (n.digits[0] % 2 == 0) {
        BigInteger x = b ^ (n / BigInteger("2"));
        return x * x;
    }
    else {
        return IPow(b, (n - BigInteger("1")) * b);
    }
}

BigInteger IPow(const BigInteger& b, const BigInteger& n) {
    if (BigInteger{ "1" } == n) {
        return b;
    }
    if (n.digits[0] % 2 == 0) {
        BigInteger x = IPow(b, n / BigInteger{ "2" });
        return x * x;
    }
    else {
        return IPow(b, n - BigInteger{ "1" }) * b;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line1;
    std::string line2;
    char operation;

    while (std::cin >> line1 >> line2 >> operation) {
        BigInteger left(line1);
        BigInteger right(line2);
        switch (operation) {
        case '+':
            std::cout << (left + right);
            break;
        case '-':
            try {
                std::cout << (left - right);
            }
            catch (std::logic_error& e) {
                std::cout << e.what();
            }
            break;
        case '*':
            std::cout << (left * right);
            break;
        case '/':
            try {
                std::cout << (left / right);
            }
            catch (std::logic_error& e) {
                std::cout << e.what();
            }
            break;
        case '^':
            try {
                std::cout << (left ^ right);
            }
            catch (std::logic_error& e) {
                std::cout << e.what();
            }
            break;
        case '<':
            std::cout << ((left < right) ? "true" : "false");
            break;
        case '>':
            std::cout << ((left > right) ? "true" : "false");
            break;
        case '=':
            std::cout << ((left == right) ? "true" : "false");
            break;
        default:
            std::cout << "Error";
            break;
        }
        std::cout << "\n";
    }
    return 0;
}


