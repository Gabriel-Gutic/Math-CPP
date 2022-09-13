#pragma once
#include "UInt.h"


class Int
{
public:
	Int(int val = 0);
	Int(const UInt& val);
	explicit Int(std::string_view val);
	~Int() = default;

	std::string ToString() const;

	bool IsNAN() const;
	UInt Abs() const;

	friend std::ostream& operator<<(std::ostream& os, const Int& a);
	friend std::istream& operator>>(std::istream& is, Int& a);

	friend Int operator+(const Int& a, const Int& b);
	friend Int operator-(const Int& a, const Int& b);
	friend Int& operator+=(Int& a, const Int& b);
	friend Int& operator-=(Int& a, const Int& b);
	friend Int& operator++(Int& a);
	friend Int& operator++(Int& a, int);
	friend Int& operator--(Int& a);
	friend Int& operator--(Int& a, int);
	friend Int operator*(const Int& a, const Int& b);
	friend Int& operator*=(Int& a, const Int& b);

	friend bool operator<(const Int& a, const Int& b);
	friend bool operator>(const Int& a, const Int& b);
	friend bool operator<=(const Int& a, const Int& b);
	friend bool operator>=(const Int& a, const Int& b);
	friend bool operator==(const Int& a, const Int& b);
	friend bool operator!=(const Int& a, const Int& b);
public:
	static Int GetNAN();
private:
	UInt m_Value;
	bool m_IsPositive;
};

Int operator-(const UInt& a, const UInt& b);

