#include "AListADTTest.hpp"
#include "Error.hpp"

AListADTTest::AListADTTest() { }

Error AListADTTest::appendingMultipleIntegerElements(){
	std::string error_function = "appendingMultipleIntegerElements";
	int integers_list[] = {7, 7, 9, 12};
	AListADT<int> *newList = new AListADT<int>();
	newList->append(5);
	newList->append(7);
	newList->append(9);
	newList->append(12);
	for(newList->moveToStart(); newList->currPos() < newList->length(); newList->next())
		if(integers_list[newList->currPos()] != newList->getValue())
			return Error {error_function, "Error in appending new integer to the list"};
}


Error AListADTTest::clear() {
	std::string error_function = "clear";
	AListADT<int> *newList = new AListADT<int>();
	newList->append(5);
	newList->append(7);
	newList->append(9);
	newList->append(12);
	//newList->clear();
	if (newList->currPos() != 0)
		return Error {error_function, "Couldn't reset current pointer"};
	else if (newList->length() != 0)
	   	return	Error {error_function, "Couldn't delete list"};
}

