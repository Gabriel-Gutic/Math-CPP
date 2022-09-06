#include "Benchmarking.h"

#include <iostream>


Benchmarking::Benchmarking()
{
	m_Timer.start();
}

Benchmarking::~Benchmarking()
{
	std::cout << "Time: " << m_Timer.MillisecondsToString() << std::endl;
}
