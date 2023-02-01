/*
Напишите класс BigInteger для работы с длинными целыми числами. 
  Должны поддерживаться операции:
сложение, вычитание, умножение, деление, остаток по модулю, работающие так же, как и для int; составное присваивание 
с этими операциями. Деление должно работать не дольше, чем за O(n2).
унарный минус, префиксный и постфиксный инкремент и декремент. Префиксный инкремент и декремент должны работать за O(1) 
в среднем.
операторы сравнения == != < > <= >=. Опционально можете реализовать оператор <=> и выразить сравнения через него, 
как это стало возможно в C++20.
вывод в поток и ввод из потока
метод toString(), возвращающий строковое представление числа
конструирование из int (в том числе неявное преобразование, когда это надо)
неявное преобразование в bool, когда это надо (должно работать в условных выражениях)
литеральный суффикс bi для написания литералов типа BigInteger.

Используя класс BigInteger, напишите класс Rational для работы с рациональными числами сколь угодно высокой точности. 
Числа Rational должны представляться в виде несократимых обыкновенных дробей, где числитель и знаменатель – сколь угодно 
длинные целые числа. 
  Должны поддерживаться операции:
конструктор из BigInteger, из int
сложение, вычитание, умножение, деление, составное присваивание с этими операциями
унарный минус
операторы сравнения == != < > <= >=. Опционально можете реализовать оператор <=> и выразить сравнения через него,
как это стало возможно в C++20.
метод toString(), возвращающий строковое представление числа (вида [минус]числитель/знаменатель), где числитель и 
знаменатель - взаимно простые числа; если число на самом деле целое, то знаменатель выводить не надо
метод asDecimal(sizet precision=0), возвращающий строковое представление числа в виде десятичной дроби с precision 
знаками после запятой
оператор приведения к double

В вашем файле должна отсутствовать функция main(), а сам файл должен называться biginteger.h
*/

#include <iostream>
#include <vector>
#include <string>
#include <iostream>

class BigInteger {
    std::vector<long long> digit_;
    bool is_negative_ = false;
    void RemoveLeadingZeros();
    void ShiftRight();
public:
    static const long long BASE = 1000000000;
    static const long long count_digit = 9;
    BigInteger() = default;
    BigInteger(std::string str);
    BigInteger(long long x);
    const std::vector<long long>& GetDigit() const { return digit_; };
    bool GetIsNegative() const { return is_negative_; };
    BigInteger operator-() const;
    BigInteger& operator++();
    BigInteger& operator--();
    BigInteger operator++(int);
    BigInteger operator--(int);
    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);
    BigInteger& operator*=(const BigInteger& other);
    BigInteger& operator/=(const BigInteger& other);
    BigInteger& operator%=(const BigInteger& other);
    explicit operator bool() const;
    std::string toString() const;
};
BigInteger::BigInteger(std::string str) {
    long long len_str = str.length();
    if (len_str == 0) { return; }
    else {
        if (str[0] == '-') {
            str = str.substr(1);
            is_negative_ = true;
            len_str--;
        }
        for (long long i = len_str; i > 0; i -= count_digit) {
            (i < count_digit) ? digit_.push_back(atoi(str.substr(0, i).c_str())) :
                digit_.push_back(atoi(str.substr(i - count_digit, count_digit).c_str()));
        }
    }
    RemoveLeadingZeros();
}
BigInteger::BigInteger(long long x) {
    if (x < 0) {
        is_negative_ = true;
        x = -x;
    }
    if (x == 0) {
        digit_.push_back(x);
        RemoveLeadingZeros();
    }
    while (x) {
        digit_.push_back(x % BigInteger::BASE);
        x /= BigInteger::BASE;
    }
}
BigInteger BigInteger::operator-() const {
    BigInteger copy(*this);
    copy.is_negative_ = !copy.is_negative_;
    copy.RemoveLeadingZeros();
    return copy;
}
bool operator<(const BigInteger& a, const BigInteger& b) {
    if (a.GetIsNegative()) {
        if (b.GetIsNegative()) {
            return ((-b) < (-a));
        } else {
            return true;
        }
    } else if (b.GetIsNegative()) {
        return false;
    } else {
        long long szA = a.GetDigit().size();
        long long szB = b.GetDigit().size();
        if (szA != szB) {
            return szA < szB;
        } else {
            for (long long i = szA - 1; i >= 0; --i) {
                if (a.GetDigit()[i] != b.GetDigit()[i]) {
                    return a.GetDigit()[i] < b.GetDigit()[i];
                }
            }
            return false;
        }
    }
}
bool operator>=(const BigInteger& a, const BigInteger& b) { return !(a < b); };
bool operator>(const BigInteger& a, const BigInteger& b) { return b < a; };
bool operator<=(const BigInteger& a, const BigInteger& b) { return !(b < a); };
bool operator==(const BigInteger& a, const BigInteger& b) {
    if (a.GetIsNegative() != b.GetIsNegative()) { return false; }
    return a.GetDigit() == b.GetDigit();
}
bool operator!=(const BigInteger& a, const BigInteger& b) { return !(a == b); };
BigInteger::operator bool() const { return (*this != 0); };
void BigInteger::RemoveLeadingZeros() {
    while (digit_.size() > 1 && digit_.back() == 0) {
        digit_.pop_back();
    }

    if (digit_.size() == 1 && digit_[0] == 0) {
        is_negative_ = false;
    }
}
BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}
BigInteger& BigInteger::operator--() {
    *this -= 1;
    return *this;
}
BigInteger BigInteger::operator++(int) {
    BigInteger copy(*this);
    ++* this;
    return copy;
}
BigInteger BigInteger::operator--(int) {
    BigInteger copy(*this);
    --* this;
    return copy;
}
BigInteger operator-(BigInteger a, const BigInteger& b) ;
BigInteger& BigInteger::operator+=(const BigInteger& other) {
    if (!is_negative_ && other.is_negative_) {
        *this -= (-other);
        return *this;
    } else if (is_negative_ && !other.is_negative_) {
        BigInteger tmp = other - (-*this);
        *this = tmp;
        return *this;
    }
    long long carry = 0;
    for (size_t i = 0; i < std::max(digit_.size(), other.digit_.size()) || carry != 0; ++i) {
        if (i == digit_.size()) {
            digit_.push_back(0);
        }
        digit_[i] += carry + (i < other.digit_.size() ? other.digit_[i] : 0);
        carry = digit_[i] >= BigInteger::BASE;
        if (carry != 0) {
            digit_[i] -= BigInteger::BASE;
        }
    }
    RemoveLeadingZeros();
    return *this;
}
BigInteger operator+(BigInteger a, const BigInteger& b);
BigInteger& BigInteger::operator-=(const BigInteger& other) {
    if (other.is_negative_) {
        *this += (-other);
        return *this;
    } else if (is_negative_) {
        BigInteger tmp = -(-*this + other);
        *this = tmp;
        return *this;
    } else if (*this < other) {
        BigInteger tmp = -(other - *this);
        *this = tmp;
        return *this;
    }
    long long carry = 0;
    for (size_t i = 0; i < other.digit_.size() || carry != 0; ++i) {
        digit_[i] -= carry + (i < other.digit_.size() ? other.digit_[i] : 0);
        carry = digit_[i] < 0;
        if (carry != 0) {
            digit_[i] += BigInteger::BASE;
        }
    }
    RemoveLeadingZeros();
    return *this;
}
BigInteger& BigInteger::operator*=(const BigInteger& other) {
    BigInteger bi;
    bi.digit_.resize(digit_.size() + other.digit_.size());
    for (size_t i = 0; i < digit_.size(); ++i) {
        long long carry = 0;
        for (size_t j = 0; j < other.digit_.size() || carry != 0; ++j) {
            long long cur = bi.digit_[i + j] +
                digit_[i] * static_cast<long long>(j < other.digit_.size() ? other.digit_[j] : 0) + carry;
            bi.digit_[i + j] = static_cast<int>(cur % BigInteger::BASE);
            carry = static_cast<int>(cur / BigInteger::BASE);
        }
    }
    bi.is_negative_ = is_negative_ != other.is_negative_;
    *this = bi;
    RemoveLeadingZeros();
    return *this;
}
BigInteger operator*(BigInteger a, const BigInteger& b) {
    a *= b;
    return a;
}
void BigInteger::ShiftRight() {
    if (!digit_.size()) {
        digit_.push_back(0);
        return;
    }
    digit_.push_back(digit_[digit_.size() - 1]);
    for (size_t i = digit_.size() - 2; i > 0; --i) {
        digit_[i] = digit_[i - 1];
    }
    digit_[0] = 0;
}
BigInteger& BigInteger::operator/=(const BigInteger& other) {
    BigInteger bi = other;
    bi.is_negative_ = false;
    BigInteger result, current;
    result.is_negative_ = (is_negative_ != other.is_negative_);
    result.digit_.resize(digit_.size());
    for (long long i = digit_.size() - 1; i >= 0; --i) {
        current.ShiftRight();
        current.digit_[0] = digit_[i];
        current.RemoveLeadingZeros();
        int iter = 0, left = 0, right = BigInteger::BASE;
        while (right - left >= 0) {
            int middle = (left + right) / 2;
            BigInteger tmp = bi * middle;
            if (tmp <= current) {
                iter = middle;
                left = middle + 1;
            }
            else {
                right = middle - 1;
            }
        }
        result.digit_[i] = iter;
        current -= bi * iter;
    }
    *this = result;
    RemoveLeadingZeros();
    return *this;
}
BigInteger operator/(BigInteger a, const BigInteger& b) {
    a /= b;
    return a;
}
BigInteger operator+(BigInteger a, const BigInteger& b) {
    a += b;
    return a;
}
BigInteger operator-(BigInteger a, const BigInteger& b) {
    a -= b;
    return a;
}
BigInteger& BigInteger::operator%=(const BigInteger& other) { return *this = *this - (*this / other) * other; };
BigInteger operator%(BigInteger a, const BigInteger& b) {
    a %= b;
    return a;
}
std::istream& operator>>(std::istream& in, BigInteger& n) {
    std::string str;
    in >> str;
    n = BigInteger(str);
    return in;
}
std::ostream& operator <<(std::ostream& os, const BigInteger& bi) {
    if (bi.GetDigit().empty()) {
        return os << ' ';
    }
    return os << bi.toString();
}
std::string BigInteger::toString() const {
    std::string s;
    size_t ind = digit_.size();
    if (!ind) {
        s = ' ';
        return s;
    }
    if (is_negative_) { s = '-'; };
    s += std::to_string(digit_[--ind]);
    std::string tmp;
    while (ind > 0) {
        tmp = std::to_string(digit_[--ind]);
        s += std::string(BigInteger::count_digit - tmp.size(), '0') += tmp;
    }
    return s;
}
BigInteger operator""_bi(unsigned long long x) { return BigInteger(x); };

BigInteger operator""_bi(const char* p, size_t len) {
    BigInteger bi = std::string(p, len);
    return bi;
}
class Rational {
    BigInteger numerator = 0;
    BigInteger denominator = 1;
    const static size_t decimal_default = 10;
    static BigInteger GCD(BigInteger a, BigInteger b);
    void FractionReduction();
public:
    Rational() = default;
    Rational(long long x) : numerator(x) {};
    Rational(BigInteger other): numerator(other) {};
    Rational(BigInteger numerator, BigInteger denominator);
    std::string toString() const;
    Rational operator-() const;
    const BigInteger& getNumerator() const { return numerator; };
    const BigInteger& getDenominator() const { return denominator; };
    std::string asDecimal(size_t precision) const;
    explicit operator double() const { return stod(asDecimal(Rational::decimal_default)); };
    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);
    friend Rational operator+(Rational a, const Rational& b);
};

Rational::Rational(BigInteger numerator, BigInteger denominator) : numerator(numerator), denominator(denominator) {
    FractionReduction();
}
std::string Rational::toString() const {
    std::string s = numerator.toString();
    if (denominator != 1) {
        s += '/';
        s += denominator.toString();
    }
    return s;
}
Rational& Rational::operator+=(const Rational& other) {
    BigInteger x = numerator * other.denominator + denominator * other.numerator;
    BigInteger y = denominator * other.denominator;
    Rational result(x, y);
    *this = result;
    return *this;
}
Rational& Rational::operator-=(const Rational& other) {
    BigInteger x = numerator * other.denominator - denominator * other.numerator;
    BigInteger y = denominator * other.denominator;
    Rational result(x, y);
    *this = result;
    return *this;
}
Rational& Rational::operator*=(const Rational& other) {
    BigInteger x = numerator * other.numerator;
    BigInteger y = denominator * other.denominator;
    Rational result(x, y);
    *this = result;
    return *this;
}
Rational& Rational::operator/=(const Rational& other) {
    BigInteger x = numerator * other.denominator;
    BigInteger y = denominator * other.numerator;
    Rational result(x, y);
    *this = result;
    return *this;
}
BigInteger Rational::GCD(BigInteger a, BigInteger b) {
    return b ? GCD(b, a % b) : a;
}
void Rational::FractionReduction() {
    BigInteger gcd = GCD(numerator, denominator);
    if (numerator == denominator) {
        numerator = (denominator = 1);
    }
    else {
        numerator /= gcd;
        denominator /= gcd;
    }
    if (denominator < 0) {
        denominator = -denominator;
        numerator = -numerator;
    }
}
Rational Rational::operator-() const {
    return Rational(-numerator, denominator);
}
bool operator<(const Rational& x, const Rational& y) {
    const BigInteger& numerator1 = x.getNumerator();
    const BigInteger& denominator1 = x.getDenominator();
    const BigInteger& numerator2 = y.getNumerator();
    const BigInteger& denominator2 = y.getDenominator();
    bool tmp1 = numerator1.GetIsNegative(), tmp2 = numerator2.GetIsNegative();
    if (tmp1 != tmp2) { return tmp1; };
    if (tmp1) { return numerator2 * denominator1 < numerator1* denominator2; };
    return numerator1 * denominator2 < numerator2* denominator1;
}
bool operator==(const Rational& x, const Rational& y) {
    return (x.getNumerator() == y.getNumerator()) && (x.getDenominator() == y.getDenominator());
}
bool operator!=(const Rational& x, const Rational& y) { return !(x == y); };
bool operator>(const Rational& x, const Rational& y) { return y < x; };
bool operator<=(const Rational& x, const Rational& y) { return (x < y) || (x == y); };
bool operator>=(const Rational& x, const Rational& y) { return (y < x) || (x == y); };
Rational operator+(Rational x, const Rational& y) {
    x += y;
    return x;
}
Rational operator-(Rational x, const Rational& y) {
    x -= y;
    return x;
}
Rational operator*(Rational x, const Rational& y) {
    x *= y;
    return x;
}
Rational operator/(Rational x, const Rational& y) {
    x /= y;
    return x;
}
std::string Rational::asDecimal(size_t precision) const {
    std::string s, ans;
    BigInteger int_part = (numerator > 0 ? numerator / denominator : -numerator / denominator);
    BigInteger remainder = (numerator > 0 ? numerator : -numerator) - int_part * denominator;
    if (numerator < 0) { s += '-'; };
    s += int_part.toString();
    if (precision == 0) { return s; };
    s.push_back('.');
    while (ans.size() <= precision) {
        remainder *= BigInteger::BASE;
        BigInteger tmp = remainder / denominator;
        if (BigInteger::count_digit - 2 - tmp.toString().size() > 0) {
            std::string head(BigInteger::count_digit - tmp.toString().size(), '0');
            ans += head;
        }
        ans += tmp.toString();
        remainder -= denominator * (remainder / denominator);
    }
    ans.resize(precision);
    s += ans;
    return s;
}
