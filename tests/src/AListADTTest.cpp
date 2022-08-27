#include "AListADTTest.hpp"
#include "Error.hpp"

AListADTTest::AListADTTest() { }

void AListADTTest::appendingMultipleIntegerElements(){
			std::string error_function = "appendingMultipleIntegerElements";
			int integers_list[] = {7, 7, 9, 12};
			AListADT<int> *newList = new AListADT<int>();
			newList->append(5);
			newList->append(7);
			newList->append(9);
			newList->append(12);
			for(newList->moveToStart(); newList->currPos() < newList->length(); newList->next()){
				if(integers_list[newList->currPos()] != newList->getValue()){
					throw Error {};
				}
			std::cout<<"AListADT function works as expected"<<std::endl;
			}
}

