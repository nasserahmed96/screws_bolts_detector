#ifndef UALDICTTEST
#define UALDICTTEST

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Error.hpp"


class UALDictTest{
	private:
		std::shared_ptr<std::vector<Error>> m_errors;
	public:
		UALDictTest(std::shared_ptr<std::vector<Error>> errors);
		void clear();
		void insertStringKeyIntValue();
		int removeStringKeyReturnIntValue();
		int removeLastElementWithIntegerValue();
		int findStringKeyElementWithIntegerValue();
		int size();
		void runTests();
};


#endif
