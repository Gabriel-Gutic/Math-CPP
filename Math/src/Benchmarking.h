#pragma once
#include "Timer.h"


class Benchmarking
{
public:
	Benchmarking();
	~Benchmarking();
private:
	Timer m_Timer;
};

#define BENCHMARKING() Benchmarking __Benchmarking__

