#ifndef ALISTADTTEST
#define ALISTADTTEST


#include <iostream>
#include <assert.h>
#include "AListADT.hpp"
#include "Error.hpp"

class AListADTTest{
	public:
		AListADTTest();
		Error appendingMultipleIntegerElements();
		Error clear();
};

#endif
