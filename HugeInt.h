#ifndef HUGEINT_H
#define HUGEINT_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <map>


template<typename T>
using remove_ptr_ref = std::remove_cv_t< std::remove_pointer_t<std::remove_reference_t<T> > >;

template <typename Iter>
constexpr bool is_iterator_char = std::is_same_v< remove_ptr_ref< typename std::iterator_traits<Iter>::value_type >, char >;

class HugeInt
{
    private:
        std::vector<int> digits;
        

        /*
        * Helper function to remove leading zeros from the number
        */
        void removeLeadingZeros()
        {
            while (digits.size() > 1 && digits.back() == 0)
                digits.pop_back();
        }

    public:

        /*
        * default constructor
        */
        HugeInt() {}

        /*
        * Constructor from an integer
        */
        HugeInt(int num);
       

        /*
         * Constructor from a range
         * is good choice enable only iterator of chars?
        */ 
        template <typename Iter, typename = std::enable_if_t<is_iterator_char<Iter> > >
        HugeInt(Iter begin, Iter end)
        {
            --end;
            --begin;
            while(end != begin)
            {
                if (!isdigit(*end))
                    throw std::invalid_argument("Invalid character in input string");
                digits.push_back(*end - '0');
                --end;
            }
            if (digits.empty())
                digits.push_back(0);
        }

        HugeInt(const std::string& numStr);

        HugeInt(const HugeInt& huge) : HugeInt(huge.to_string())
        {}

        HugeInt(const char* numStr) : HugeInt(std::string(numStr))
        {}

        void swap(HugeInt& a, HugeInt& b)
        {
            std::swap(a.digits, b.digits);
        }

        HugeInt& operator=(const std::string& numStr)
        {
            HugeInt h(numStr);
            swap(h, *this);
            return *this;
        }

        size_t digitCount() const
        {
            return digits.size();
        }

        HugeInt& operator=(const HugeInt& huge)
        {
            if(this != &huge)
            {
                HugeInt h(huge.to_string());
                swap(h, *this);   
            }
            return *this;
        }

        HugeInt& operator=(const char* numStr)
        {
            HugeInt h{ std::string(numStr) };
            swap(h, *this);
        
            return *this;
        }

        HugeInt operator+(const HugeInt& other) const;
    
        HugeInt operator-(const HugeInt& other) const;

        HugeInt operator*(const HugeInt& other) const;
        
        HugeInt operator/(const HugeInt& other) const;
        
        HugeInt operator%(const HugeInt& other) const;

        HugeInt& operator+= (const HugeInt& other)
        {
            *this = *this + other;
            return *this;
        }

        HugeInt& operator-= (const HugeInt& other)
        {
            *this = *this - other;
            return *this;
        }

        HugeInt& operator*= (const HugeInt& other)
        {
            *this = *this * other;
            return *this;
        }

        HugeInt& operator/= (const HugeInt& other)
        {
            *this = *this / other;
            return *this;
        }

        HugeInt& operator%=(const HugeInt& other)
        {
           *this = *this % other;

            return *this;
        }
        
        bool operator==(const HugeInt& other) const
        {
            return digits == other.digits;
        }

        bool operator!=(const HugeInt& other) const
        {
            return !(*this == other);
        }

        bool operator<(const HugeInt& other) const;

        bool operator!() const
        {
            return digits.size() == 1 && digits[0] == 0;
        }

        bool operator<=(const HugeInt& other) const
        {
            return *this < other || *this == other;
        }
        operator bool() const
        {
            return !this->operator!();
        }
        bool operator>(const HugeInt& other) const
        {
            return !(*this <= other);
        }

        bool operator>=(const HugeInt& other) const
        {
            return !(*this < other);
        }

        std::string to_string() const;
    
        friend std::ostream& operator<<(std::ostream& os, const HugeInt& num);
};

std::ostream& operator<<(std::ostream& os, const HugeInt& num);

#endif