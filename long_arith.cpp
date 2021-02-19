#include <iostream>
#include <string>
#include <vector>

using namespace std;



class BigInteger {
public:
    BigInteger();
    BigInteger(string& str);
    BigInteger(int64_t& digits);
    BigInteger(uint64_t& digits);
    BigInteger(int);
    uint64_t GetSize() const;
    friend ostream& operator<<(ostream& os, const BigInteger& bi);
    uint16_t operator[](uint64_t i) const;
    uint16_t& operator[](uint64_t i);
    void RemoveLeadZeros();
    friend bool operator ==(const BigInteger& left, const BigInteger& right);
    friend bool operator !=(const BigInteger& left, const BigInteger& right);
    friend bool operator <(const BigInteger& left, const BigInteger& right);
    friend bool operator >(const BigInteger& left, const BigInteger& right);
    const BigInteger operator +() const;
    const BigInteger operator -() const;
    friend const BigInteger operator +(BigInteger left, const BigInteger& right);
    friend const BigInteger operator -(BigInteger left, const BigInteger& right);
    BigInteger& operator =(const BigInteger& value);
    BigInteger& operator +=(const BigInteger& value);
    BigInteger& operator -=(const BigInteger& value);
    BigInteger& operator *=(const BigInteger& value);
    BigInteger& operator /=(const BigInteger& value);
    BigInteger& operator +=(const int& value);
    BigInteger& operator -=(const int& value);
    const BigInteger operator ++(int);
    const BigInteger operator ++();
    const BigInteger operator --(int);
    const BigInteger operator --();
    friend const BigInteger operator *(const BigInteger& left, const BigInteger& right);
    friend const BigInteger operator /(const BigInteger& left, const BigInteger& right);
    BigInteger& operator /=(const BigInteger& value);
    void shift_right();
    friend const BigInteger operator %(const BigInteger& left, const BigInteger& right);
    bool odd() const;
    bool even() const;
    const BigInteger pow(BigInteger n) const;

    class DivideByZero: public std::exception {  };

private:
	static const uint64_t BASE = 1000000000;
	bool is_negative;
    std::vector<uint16_t> digits;
};

uint64_t BigInteger::GetSize() const {
    return this->digits.size();
}

ostream& operator <<(ostream& os, const BigInteger& b) {
    if (b.digits.empty())
        os << 0;
    else {
        if (b.is_negative)
            os << '-';

        os << b.digits.back();
        char old_fill = os.fill('0');

        for (uint64_t i = static_cast<uint64_t>(b.digits.size()) - 2; i >= 0; --i) {
            os << b.digits[i];
        }
        os.fill(old_fill);
    }
    return os;
}

uint16_t BigInteger::operator [](uint64_t i) const { return this->digits[i]; };
uint16_t& BigInteger::operator [](uint64_t i) { return this->digits[i]; };

BigInteger::BigInteger() {
    this->is_negative = false;
}

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

    for (uint64_t i = str.length(); i > 0; i -= 9) {
        if (i < 9)
            this->digits.push_back(atoi(str.substr(0, i).c_str()));  // strtoul string -> uint64_t
        else
            this->digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
    }
    this->RemoveLeadZeros();
}

BigInteger::BigInteger(int64_t& digits) {
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

BigInteger::BigInteger(uint64_t& digits) {
    this->is_negative = false;
    do {
        this->digits.push_back(digits % BigInteger::BASE);
            digits /= BigInteger::BASE;
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
    digit /= BigInteger::BASE;

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
        } else {
            for (uint64_t i = left.digits.size() - 1; i >= 0; --i) {
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

const BigInteger operator+(BigInteger left, const BigInteger& right) {
    if (left.is_negative)
        return (right.is_negative) ? -(-left + (-right)) : (right - (-left));

    else
        if (right.is_negative)
            return (left - (-right));

    int carry = 0;
    for (uint64_t i = 0; i < std::max(left.digits.size(), right.digits.size()) || carry != 0; ++i) {
        if (i == left.digits.size())
            left.digits.push_back(0);

        left.digits[i] += carry + (i < right.digits.size() ? right.digits[i] : 0);
        carry = left.digits[i] >= BigInteger::BASE;

        if (carry != 0)
            left.digits[i] -= BigInteger::BASE;
    }
    return left;
}

const BigInteger operator-(BigInteger left, const BigInteger& right) {
    if (right.is_negative)
        return left + (-right);
    else if (left.is_negative)
        return -(-left + right);
    else if (left < right)
        return -(right - left);

    int carry = 0;
    for (uint64_t i = 0; i < right.digits.size() || carry != 0; ++i) {
        left.digits[i] -= carry + (i < right.digits.size() ? right.digits[i] : 0);
        carry = left.digits[i] < 0;
        if (carry != 0)
            left.digits[i] += BigInteger::BASE;
    }

    left.RemoveLeadZeros();
    return left;
}

BigInteger& BigInteger::operator=(const BigInteger& value) {
    return *this = value;
}

BigInteger& BigInteger::operator+=(const BigInteger& value) {
    return *this = (*this + value);
}

BigInteger& BigInteger::operator-=(const BigInteger& value) {
    return *this = (*this - value);
}

BigInteger& BigInteger::operator *=(const BigInteger& value) {
    return *this = (*this * value);
}

BigInteger& BigInteger::operator /=(const BigInteger& value) {
    return *this = (*this / value);
}

const BigInteger BigInteger::operator++() {
    return (*this += 1);
}

const BigInteger BigInteger::operator++(int) {
    *this += 1;
    return *this - 1;
}

const BigInteger BigInteger::operator--() {
	return *this -= 1;
}

const BigInteger BigInteger::operator--(int) {
	*this -= 1;
	return *this + 1;
}

const BigInteger operator*(const BigInteger& left, const BigInteger& right) {
    BigInteger result;
    uint64_t left_size = left.digits.size();
    uint64_t right_size = right.digits.size();
    result.digits.resize(left_size + right_size);

    uint32_t carry;
    uint64_t cur;
    for (uint64_t i = 0; i < left_size; ++i) {
        carry = 0;
        for (uint64_t j = 0; j < right_size || carry != 0; ++j) {
            cur = result.digits[i + j] + ((uint64_t)left.digits[i]) * (j < right_size ? right.digits[j] : 0) + carry;
            result.digits[i + j] = static_cast<uint16_t>(cur % BigInteger::BASE);
            carry = static_cast<uint16_t>(cur / BigInteger::BASE);
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
        throw BigInteger::DivideByZero();

    BigInteger base = right;
    base.is_negative = false;
    BigInteger result, current, tmp;
    result.digits.resize(left.digits.size());
    uint64_t digit_result, l, r, m;

    for (uint64_t i = static_cast<uint64_t>(left.digits.size()) - 1; i >= 0; --i) {
        current.shift_right();
        current.digits[0] = left.digits[i];
        current.RemoveLeadZeros();
        digit_result = 0, l = 0, r = BigInteger::BASE;
        while (l <= r) {
            m = (l + r) / 2;
            tmp = base * m;
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

BigInteger& BigInteger::operator/=(const BigInteger& value) {
    return *this = (*this / value);
}

bool BigInteger::odd() const {
    return (this->digits.size() == 0) ? false : this->digits[0] & 1;
}

bool BigInteger::even() const {
    return !this->odd();
}

const BigInteger BigInteger::pow(BigInteger n) const {
    BigInteger a(*this), result(1);
    while (n != 0) {
        if (n.odd())
            result *= a;
        a *= a;
        n /= 2;
    }
    return result;
}

void resultOperation(string& line1, string& line2, char& operation, BigInteger& res){
    string l1 = line1;
    string l2 = line1;
    BigInteger left(line1);
    BigInteger right(line2);

    switch (operation) {
    case '+':
        res = left + right;
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
    char operation;
    BigInteger result;

     while (true) {
        cin >> line1;
        cin >> line2;
        cin >> operation;
        resultOperation(line1, line2, operation, result);
        cout << result;
    }
    return 0;
}