#pragma once
#include "Active.h"
class ActiveFactory
{
public:
	ActiveFactory();
	~ActiveFactory();
	static Active* produceActive(std::string activeName);
};

