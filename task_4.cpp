/*
Даны два "длинных" неотрицательных числа. Требуется найти результат их сложения.

Формат ввода
На вход подаются два неотрицательных числа, каждое состоит не более чем из 1000 цифр.

Формат вывода
Выведите результат их сложения.

*/

#include <iostream> 
#include <vector>
#include <string> 

class big_uint{ 
  public:
    explicit big_uint(const std::string&);
    explicit big_uint() = default;
    std::string to_string() const; 
    big_uint operator+(const big_uint& other) const;

  private:
    static const unsigned int base = 1'000'000'000;
    std::vector<unsigned int> digits;
};

big_uint big_uint::operator+(const big_uint& other) const {
    big_uint ans = *this;
    if (other.digits.size() > ans.digits.size()) ans.digits.resize(other.digits.size());
    unsigned int overflow = 0;
    size_t i = 0;
    for (; i < other.digits.size(); i++) {
        unsigned int new_digit = ans.digits[i] + other.digits[i] + overflow;
        ans.digits[i] = new_digit % ans.base;
        overflow = new_digit / ans.base;
    }
    while (overflow && i < ans.digits.size()) {
        unsigned int new_digit = ans.digits[i] + overflow;
        ans.digits[i++] = new_digit % ans.base;
        overflow = new_digit / ans.base;
    }
    if (overflow) {
        ans.digits.push_back(overflow);
    }
    return ans;
}

std::ostream& operator<<(std::ostream& stream, const big_uint& number) {
    return stream << number.to_string(); 
}

std::istream& operator>>(std::istream& stream, big_uint& number) {
    std::string num;
    stream >> num; 
    big_uint ans(num);
    number = std::move(ans);
    return stream;
}

big_uint::big_uint(const std::string& source) {
    if (source.empty()) throw std::bad_cast();
 
    for (int i = source.length(); i > 0; i -= 9) {
        digits.push_back(0);
        for (int j = std::max(0, i - 9); j < i; ++j) {
            if (source[j] < '0' || source[j] > '9') throw std::bad_cast();
            digits.back() = digits.back() * 10 + source[j] - '0';
        }
    }
    while (!digits.empty() && digits.back() == 0) digits.pop_back();
}

std::string big_uint::to_string() const {
    if (digits.empty()) return "0";
 
    std::string result;
    result += std::to_string(digits.back());
    for (int i = digits.size() - 2; i >= 0; --i) {
        std::string tmp = std::to_string(digits[i]);
        result += std::string(9 - tmp.size(), '0') + tmp;
    }
    return result;
}

int main() {
    big_uint a, b; 
    std::cin >> a >> b;
    std::cout << a + b << '\n';
    return 0;
}