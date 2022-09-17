#include <UALDictTest.hpp>
#include <UALDict.hpp>


void UALDictTest::clear(){


}

void UALDictTest::insertStringKeyIntValue(){
	std::string k = "test_key";
	int e = 5;
	UALDict<std::string, int> *test_unsorted_list = new UALDict<std::string, int>(5);
	test_unsorted_list->insert("test_key_5", 5);
	test_unsorted_list->insert("test_key_6", 6);
	test_unsorted_list->insert("test_key_7", 7);
	test_unsorted_list->printDict();	
}

int UALDictTest::removeStringKeyReturnIntValue(){
	
	
}

int UALDictTest::removeLastElementWithIntegerValue(){


}

int UALDictTest::findStringKeyElementWithIntegerValue(){


}


int UALDictTest::size(){


}


void UALDictTest::runTests(){
	this->insertStringKeyIntValue();
}
