#include "HugeInt.h"


HugeInt::HugeInt(int num)
 {
    if (!num)
    {
        digits.push_back(0);  // Handle the case when num is 0
        return ;
    }
    while (num > 0)
    {
        digits.push_back(num % 10);
        num /= 10;
    }
}

HugeInt::HugeInt(const std::string& numStr)
{
    for (int i = numStr.size() - 1; i >= 0; --i)
    {
        if (!isdigit(numStr[i]))
            throw std::invalid_argument("Invalid character in input string");
        digits.push_back(numStr[i] - '0');
    }
    if (digits.empty())
        digits.push_back(0);
}

HugeInt HugeInt::operator+(const HugeInt& other) const
{
    HugeInt result;
    int carry = 0;
    int max_size = std::max(digits.size(), other.digits.size());

    for (int i = 0; i < max_size || carry; ++i)
    {
        int sum = carry;
        if (i < digits.size())
            sum += digits[i];
        if (i < other.digits.size())
            sum += other.digits[i];
        carry = sum / 10;
        result.digits.push_back(sum % 10);
    }

    result.removeLeadingZeros();
    return result;
}

HugeInt HugeInt::operator-(const HugeInt& other) const
{
    HugeInt result;
    int borrow = 0;

    for (int i = 0; i < digits.size(); ++i)
    {
        int diff = digits[i] - borrow;
        if (i < other.digits.size())
            diff -= other.digits[i];
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        result.digits.push_back(diff);
    }

    result.removeLeadingZeros();
    return result;
}

    HugeInt HugeInt::operator*(const HugeInt& other) const
    {
        HugeInt result;
        result.digits.resize(digits.size() + other.digits.size(), 0);

        for (int i = 0; i < digits.size(); ++i)
        {
            int carry = 0;
            for (int j = 0; j < other.digits.size() || carry; ++j)
            {
                long long product = result.digits[i + j] +
                    (long long)digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result.digits[i + j] = product % 10;
                carry = product / 10;
            }
        }

        result.removeLeadingZeros();
        return result;
    }

HugeInt HugeInt::operator/(const HugeInt& other) const
{
    HugeInt result, current;
    for (int i = digits.size() - 1; i >= 0; --i)
    {
        current.digits.insert(current.digits.begin(), digits[i]);
        current.removeLeadingZeros();
        int quotient = 0;
        while (current >= other)
        {
            current = current - other;
            quotient++;
        }
        result.digits.insert(result.digits.begin(), quotient);
    }

    result.removeLeadingZeros();
    return result;
}

HugeInt HugeInt::operator%(const HugeInt& other) const
{
    HugeInt current;
    for (int i = digits.size() - 1; i >= 0; --i)
    {
        current.digits.insert(current.digits.begin(), digits[i]);
        current.removeLeadingZeros();
        while (current >= other)
            current = current - other;
    }
    return current;
}

bool HugeInt::operator<(const HugeInt& other) const
{
    if (digits.size() != other.digits.size())
        return digits.size() < other.digits.size();
    for (int i = digits.size() - 1; i >= 0; --i)
        if (digits[i] != other.digits[i])
            return digits[i] < other.digits[i];
    return false; // They are equal
}

 std::string HugeInt::to_string() const
{
    if (digits.size())
    {
        std::stringstream ss;
        for (int i = digits.size() - 1; i >= 0; --i)
            ss << digits[i];

        return ss.str();
    }
    return "";
}
std::ostream& operator<<(std::ostream& os, const HugeInt& num)
{
    if (num.digits.size())
    {
        for (int i = num.digits.size() - 1; i >= 0; --i)
            os << num.digits[i];
    }
    return os;
}