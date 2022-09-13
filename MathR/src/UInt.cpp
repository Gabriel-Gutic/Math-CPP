#include "UInt.h"

#include <sstream>
#include <iostream>


UInt::UInt(unsigned int value)
{
	if (value > DIGIT_MAX)
	{
		m_Digits.push_back(value % BASE);
		m_Digits.push_back(value / BASE);
	}
	else
		m_Digits.push_back(value);
}

UInt::UInt(std::string_view value)
{
	uint32_t nr = 0;
	uint32_t p = 1;
	for (std::string_view::const_reverse_iterator it = value.rbegin();
		it != value.rend(); it++)
	{
		char c = *it;
		if (c < '0' || c > '9')
		{
			std::cout << "Invalid integer: " << value << std::endl;
			__debugbreak();
		}
		c -= '0';

		nr = p * c + nr;
		if (p == 100000000 || (it + 1) == value.rend())
		{
			m_Digits.push_back(nr);
			p = 1;
			nr = 0;
		}
		else
			p *= 10;
	}
}

std::string UInt::ToString() const
{
	std::stringstream ss;
	for (std::vector<uint32_t>::const_reverse_iterator it = m_Digits.rbegin(); it != m_Digits.rend(); it++)
	{
		if (it == m_Digits.rbegin())
			ss << *it;
		else
		{
			int digits = *it == 0 ? 1 : (int)log10(*it) + 1;
			for (int i = 0; i < 9 - digits; i++)
				ss << "0";
			ss << *it;
		}
	}
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const UInt& l)
{
	os << l.ToString();
	return os;
}

std::istream& operator>>(std::istream& is, UInt& l)
{
	std::string s;
	is >> s;
	l = UInt(s);
	return is;
}

// O(n) time complexity, where n is the max number of
// components of those two numbers
UInt operator+(const UInt& a, const UInt& b)
{
	UInt l;
	l.m_Digits.clear();
	size_t carry = 0;
	for (size_t i = 0; i < std::max(a.m_Digits.size(), b.m_Digits.size()) || carry; i++)
	{
		unsigned int left = i < a.m_Digits.size() ? a.m_Digits[i] : 0;
		unsigned int right = i < b.m_Digits.size() ? b.m_Digits[i] : 0;
		unsigned int sum = left + right + carry;
		if (sum > UInt::DIGIT_MAX)
		{
			carry = 1;
			sum = sum % UInt::BASE;
		}
		else
		{
			carry = 0;
		}
		l.m_Digits.push_back(sum);
	}
	return l;
}

UInt operator-(const UInt& a, const UInt& b)
{
	UInt _a = a;
	if (a <= b)
		return 0;

	UInt result;
	result.m_Digits.clear();

	size_t i;
	for (i = 0; i < b.m_Digits.size(); i++)
	{
		if (_a.m_Digits[i] < b.m_Digits[i])
		{
			size_t j = i + 1;
			while (_a.m_Digits[j] == 0) j++;

			_a.m_Digits[j]--;
			if (_a.m_Digits[j] == 0 && j == _a.m_Digits.size() - 1)
				_a.m_Digits.pop_back();
			for (size_t k = j - 1; k > i; k--)
				_a.m_Digits[k] = UInt::DIGIT_MAX;
			_a.m_Digits[i] += UInt::BASE;
		}

		result.m_Digits.push_back(_a.m_Digits[i] - b.m_Digits[i]);
	}

	for (size_t j = i; j < _a.m_Digits.size(); j++)
		result.m_Digits.push_back(_a.m_Digits[j]);

	while (result.m_Digits.back() == 0) 
		result.m_Digits.pop_back();

	return result;
}

UInt& operator+=(UInt& a, const UInt& b)
{
	a = a + b;
	return a;
}

UInt& operator-=(UInt& a, const UInt& b)
{
	a = a - b;
	return a;
}

UInt& operator*=(UInt& a, const UInt& b)
{
	a = a * b;
	return a;
}

UInt& operator++(UInt& a)
{
	a = a + 1;
	return a;
}

UInt& operator++(UInt& a, int)
{
	UInt copy = a;
	++a;
	return copy;
}

UInt operator*(const UInt& a, const UInt& b)
{
	return UInt::Karatsuba(a, b);
}

bool operator<(const UInt& a, const UInt& b)
{
	if (a.m_Digits.size() < b.m_Digits.size())
		return true;
	if (a.m_Digits.size() > b.m_Digits.size())
		return false;
	for (long long i = a.m_Digits.size() - 1; i >= 0; i--)
	{
		if (a.m_Digits[i] < b.m_Digits[i])
			return true;
		if (a.m_Digits[i] > b.m_Digits[i])
			return false;
	}
	return false;
}

bool operator>(const UInt& a, const UInt& b)
{
	return !(a <= b);
}

bool operator<=(const UInt& a, const UInt& b)
{
	if (a.m_Digits.size() < b.m_Digits.size())
		return true;
	if (a.m_Digits.size() > b.m_Digits.size())
		return false;
	for (long long i = a.m_Digits.size() - 1; i >= 0; i--)
	{
		if (a.m_Digits[i] < b.m_Digits[i])
			return true;
		if (a.m_Digits[i] > b.m_Digits[i])
			return false;
	}
	return true;
}

bool operator>=(const UInt& a, const UInt& b)
{
	return !(a < b);
}

bool operator==(const UInt& a, const UInt& b)
{
	if (a.m_Digits.size() != b.m_Digits.size())
		return false;
	for (size_t i = 0; i < a.m_Digits.size(); i++)
		if (a.m_Digits[i] != b.m_Digits[i])
			return false;
	return true;
}

bool operator!=(const UInt& a, const UInt& b)
{
	return !(a == b);
}

UInt UInt::Karatsuba(const UInt& a, const UInt& b)
{
	if (a == 0 || b == 0) return 0;
	if (a == 1) return b;
	if (b == 1) return a;

	if (a.m_Digits.size() < 70 && b.m_Digits.size() < 70)
	{
		return LongMultiplication(a, b);
	}

	UInt result;

	size_t n = std::max(a.m_Digits.size(), b.m_Digits.size());
	size_t m = n / 2;

	UInt a_L, a_R, b_L, b_R;
	if (a.m_Digits.size() < m)
	{
		a_L = 0;
		a_R = a;
	}
	else
	{
		a_L.m_Digits = std::move(std::vector<uint32_t>(a.m_Digits.begin() + m, a.m_Digits.end()));
		a_R.m_Digits = std::move(std::vector<uint32_t>(a.m_Digits.begin(), a.m_Digits.begin() + m));
		while (a_R.m_Digits.back() == 0u && a_R.m_Digits.size() > 1) a_R.m_Digits.pop_back();
	}

	if (b.m_Digits.size() < m)
	{
		b_L = 0;
		b_R = b;
	}
	else
	{
		b_L.m_Digits = std::move(std::vector<uint32_t>(b.m_Digits.begin() + m, b.m_Digits.end()));
		b_R.m_Digits = std::move(std::vector<uint32_t>(b.m_Digits.begin(), b.m_Digits.begin() + m));
		while (b_R.m_Digits.back() == 0u && b_R.m_Digits.size() > 1) b_R.m_Digits.pop_back();
	}

	UInt x = Karatsuba(a_L, b_L);
	UInt y = Karatsuba(a_R, b_R);
	UInt z = Karatsuba(a_L + a_R, b_L + b_R) - x - y;

	UInt A = 0;
	if (x != 0)
	{
		std::cout << "It's bad!" << std::endl;
		for (size_t i = 0; i < 2 * m - 1; i++)
			A.m_Digits.push_back(0);
		for (const auto& el : x.m_Digits)
		{
			A.m_Digits.push_back(el);
		}
	}

	UInt B = 0;
	if (z != 0)
	{
		for (size_t i = 0; i < m - 1; i++)
			B.m_Digits.push_back(0);
		for (const auto& el : z.m_Digits)
		{
			B.m_Digits.push_back(el);
		}
	}
	return A + B + y;
}

UInt UInt::LongMultiplication(const UInt& a, const UInt& b)
{
	UInt small, bigger;
	if (a.m_Digits.size() > b.m_Digits.size())
	{
		bigger = a;
		small = b;
	}
	else {
		bigger = b;
		small = a;
	}

	UInt result = 0;
	for (int i = 0; i < small.m_Digits.size(); i++)
	{
		for (int j = 0; j < bigger.m_Digits.size(); j++)
		{
			if (small.m_Digits[i] != 0u && bigger.m_Digits[j] != 0u)
			{
				UInt product;
				uint64_t prod = static_cast<uint64_t>(small.m_Digits[i]) * static_cast<uint64_t>(bigger.m_Digits[j]);
				size_t k;
				for (k = 0; k < i + j; k++)
					product.m_Digits.push_back(0u);
				product.m_Digits[k] = static_cast<uint32_t>(prod % static_cast<uint64_t>(BASE));
				if (prod > static_cast<uint64_t>(DIGIT_MAX))
					product.m_Digits.push_back(prod / static_cast<uint64_t>(BASE));
				result += product;
			}
		}
	}
	return result;
}
