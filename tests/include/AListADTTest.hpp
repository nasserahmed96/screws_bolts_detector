#ifndef ALISTADTTEST
#define ALISTADTTEST


#include <iostream>
#include <assert.h>
#include "AListADT.hpp"
#include <vector>
#include <memory>
#include "Error.hpp"


class AListADTTest{
	private:
		std::shared_ptr<std::vector<Error>>  m_errors;
	public:
		AListADTTest(std::shared_ptr<std::vector<Error>> errors);
		void appendingMultipleIntegerElements();
		void clear();
		void printErrors();
};

#endif
