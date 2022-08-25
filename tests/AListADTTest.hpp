#ifndef ALISTADTTEST
#define ALISTADTTEST

#include "AListADT.hpp"
#include <iostream>

class AListADTTest{
	public:
		AListADTTest() { }
		void appendingMultipleIntegerElements(){
			int integers_list[] = {5, 7, 9, 12};
			AListADT<int> *newList = new AListADT<int>();
			newList->append(5);
			newList->append(7);
			newList->append(9);
			newList->append(12);
			for(newList->moveToStart(); newList->currPos() < newList->length(); newList->next()){
				if(integers_list[newList->currPos()] != newList->getValue())
					std::cout<<"Assertion error"<<std::endl;
				else
					std::cout<<"Test passed"<<std::endl;
			
			}
		}
};

#endif
