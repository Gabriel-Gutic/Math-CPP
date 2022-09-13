#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <string_view>


class UInt
{
public:
	UInt(unsigned int value = 0u);
	explicit UInt(std::string_view value);
	~UInt() = default;

	std::string ToString() const;

	friend std::ostream& operator<<(std::ostream& os, const UInt& l);
	friend std::istream& operator>>(std::istream& is, UInt& l);
	friend UInt operator+(const UInt& a, const UInt& b);
	friend UInt operator-(const UInt& a, const UInt& b);
	friend UInt& operator+=(UInt& a, const UInt& b);
	friend UInt& operator-=(UInt& a, const UInt& b);
	friend UInt& operator*=(UInt& a, const UInt& b);
	friend UInt& operator++(UInt& a);
	friend UInt& operator++(UInt& a, int);
	friend UInt operator*(const UInt& a, const UInt& b);
	friend bool operator<(const UInt& a, const UInt& b);
	friend bool operator>(const UInt& a, const UInt& b);
	friend bool operator<=(const UInt& a, const UInt& b);
	friend bool operator>=(const UInt& a, const UInt& b);
	friend bool operator==(const UInt& a, const UInt& b);
	friend bool operator!=(const UInt& a, const UInt& b);
private:
	static UInt Karatsuba(const UInt& a, const UInt& b);
	static UInt LongMultiplication(const UInt& a, const UInt& b);
private:
	std::vector<uint32_t> m_Digits;

	static const uint32_t DIGIT_MAX = 999999999u;
	static const uint32_t BASE = 1000000000u;
};

