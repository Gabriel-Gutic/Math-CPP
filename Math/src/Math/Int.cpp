#include "Int.h"

#include <iostream>

Int::Int(int val)
	:m_Value(static_cast<unsigned int>(abs(val))), m_IsPositive(val >= 0)
{
}

Int::Int(const UInt& val)
	:m_Value(val), m_IsPositive(true)
{
}

Int::Int(std::string_view val)
{
	m_IsPositive = (val[0] != '-');

	if (m_IsPositive)
		m_Value = UInt(val);
	else
	{
		m_Value = UInt(val.substr(1));
		if (m_Value == 0)
			m_IsPositive = true;
	}
}

std::string Int::ToString() const
{
	if (m_Value.IsNAN())
		return "nan";
	std::stringstream ss;
	if (!m_IsPositive)
		ss << '-';
	ss << m_Value;
	return ss.str();
}

bool Int::IsNAN() const
{
	return m_Value.IsNAN();
}

UInt Int::Abs() const
{
	return m_Value;
}

Int Int::GetNAN()
{
	return Int(UInt::GetNAN());
}

std::ostream& operator<<(std::ostream& os, const Int& a)
{
	os << a.ToString();
	return os;
}

std::istream& operator>>(std::istream& is, Int& a)
{
	std::string str;
	is >> str;
	a = Int(str);
	return is;
}

Int operator+(const Int& a, const Int& b)
{
	if (a.IsNAN() || b.IsNAN())
		return Int::GetNAN();
	if (a.m_IsPositive == b.m_IsPositive)
	{
		UInt sum = a.m_Value + b.m_Value;
		Int result = Int(sum);
		result.m_IsPositive = a.m_IsPositive;
		return result;
	}

	Int result;
	if (a.m_Value == b.m_Value)
	{
		result = Int(0);
	}
	if (a.m_Value > b.m_Value)
	{
		UInt dif = UInt::DifferenceBetweenUInt(a.m_Value, b.m_Value);
		result = Int(dif);
		result.m_IsPositive = a.m_IsPositive;
	}
	else 
	{
		UInt dif = UInt::DifferenceBetweenUInt(b.m_Value, a.m_Value);
		result = Int(dif);
		result.m_IsPositive = b.m_IsPositive;
	}
	return result;
}

Int operator-(const Int& a, const Int& b)
{
	if (a.IsNAN() || b.IsNAN())
		return Int::GetNAN();
	Int _b = b;
	_b.m_IsPositive = !(b.m_IsPositive);
	return a + _b;
}

Int& operator+=(Int& a, const Int& b)
{
	a = a + b;
	return a;
}

Int& operator-=(Int& a, const Int& b)
{
	a = a - b;
	return a;
}

Int& operator++(Int& a)
{
	a = a + 1;
	return a;
}

Int& operator++(Int& a, int)
{
	Int copy = a;
	++a;
	return copy;
}

Int& operator--(Int& a)
{
	a = a - 1;
	return a;
}

Int& operator--(Int& a, int)
{
	Int copy = a;
	--a;
	return copy;
}

Int operator*(const Int& a, const Int& b)
{
	if (a.IsNAN() || b.IsNAN())
		return Int::GetNAN();
	UInt prod = a.m_Value * b.m_Value;
	if (prod == 0)
		return 0;
	Int result = Int(prod);
	result.m_IsPositive = !(a.m_IsPositive ^ b.m_IsPositive);
	return result;
}

Int& operator*=(Int& a, const Int& b)
{
	a = a * b;
	return a;
}

bool operator<(const Int& a, const Int& b)
{
	if (a.IsNAN() || b.IsNAN())
		return false;
	if (a.m_Value == 0 && b.m_Value == 0)
		return false;
	if (a.m_IsPositive && !b.m_IsPositive)
		return false;
	if (!a.m_IsPositive && b.m_IsPositive)
		return true;
	if (!a.m_IsPositive && !b.m_IsPositive)
		return a.m_Value > b.m_Value;
	return a.m_Value < b.m_Value;
}

bool operator>(const Int& a, const Int& b)
{
	if (a.IsNAN() || b.IsNAN())
		return false;
	if (a.m_Value == 0 && b.m_Value == 0)
		return false;
	if (a.m_IsPositive && !b.m_IsPositive)
		return true;
	if (!a.m_IsPositive && b.m_IsPositive)
		return false;
	if (!a.m_IsPositive && !b.m_IsPositive)
		return a.m_Value < b.m_Value;
	return a.m_Value > b.m_Value;
}

bool operator<=(const Int& a, const Int& b)
{
	if (a.IsNAN() && b.IsNAN())
		return true;
	else if (a.IsNAN() || b.IsNAN())
		return false;
	return !(a > b);
}

bool operator>=(const Int& a, const Int& b)
{
	if (a.IsNAN() && b.IsNAN())
		return true;
	else if (a.IsNAN() || b.IsNAN())
		return false;
	return !(a < b);
}

bool operator==(const Int& a, const Int& b)
{
	if (a.IsNAN() && b.IsNAN())
		return true;
	else if (a.IsNAN() || b.IsNAN())
		return false;
	if (a.m_Value == 0 && b.m_Value == 0)
		return true;
	return (a.m_Value == b.m_Value) && (a.m_IsPositive == b.m_IsPositive);
}

bool operator!=(const Int& a, const Int& b)
{
	return !(a == b);
}

Int operator-(const UInt& a, const UInt& b)
{
	return Int(a) - Int(b);
}
