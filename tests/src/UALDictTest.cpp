#include <UALDictTest.hpp>
#include <UALDict.hpp>


UALDictTest::UALDictTest(std::shared_ptr<std::vector<Error>> errors): m_errors {errors} {}

void UALDictTest::clear(){


}

void UALDictTest::insertStringKeyIntValue(){
	std::string k = "test_key";
	int e = 5;
	UALDict<std::string, int> *test_unsorted_list = new UALDict<std::string, int>(5);
	int test_integers[] = {5, 6, 7};
	std::string test_keys[] = {"test_first_int", "test_second_int", "test_third_int"};
	test_unsorted_list->insert("test_first_int", 6);
	test_unsorted_list->insert("test_second_int", test_integers[1]);
	test_unsorted_list->insert("test_third_int", test_integers[2]);
	for(int i = 0;i < 3;i++)
		if (test_unsorted_list->find(test_keys[i]) != test_integers[i])
			m_errors->push_back(Error{__func__, "Failed to add element to the dictionary"});
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
