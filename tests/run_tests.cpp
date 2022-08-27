#include <vector>
#include "AListADTTest.hpp"


/*
 * Nasser 24-08-2022 20:49
 * As the system consists of many components, I need a detailed report about the errors, so I will try to create a custom class that handles excpetion, the class will contain
 * -Function name
 * -Error message
 * -Error level
 *  Any way, unlike assertion I want to continue running tests to get an overview of the failers of the system, and if the errors are greater than 1 then I will ask the user
 *  to check the PDF report
 */

void generateStartupErrors(const std::vector<Error>& errors);
void printErrorsVector(const std::vector<Error>& errors);


int runTests(){
	/*
	 * I will use a string exception for now, until I create the custom exception class
	 */
	std::vector<Error> errors;
	try{
		AListADTTest *newTest = new AListADTTest(); 
		newTest->appendingMultipleIntegerElements();
	}
	catch(const char *message){
		std::cout<<message<<std::endl;
	}	
	catch(const Error& error)
	{
		errors.push_back(error);
	}
	if(errors.size() > 0){
		std::cout<<"Couldn't start the system please check the error report"<<std::endl;
		generateStartupErrors(errors);
	}
	return 0;

}


void generateStartupErrors(const std::vector<Error>& errors){
	std::vector<Error> tags_errors;
	std::string row = "<tr> {{ cols }} </tr>";
	std::string col = "<td> {{ content }} </td>";
	
	for(int i = 0;i < errors.size(); i++){
		tags_errors.push_back(errors[i]);
	}
	printErrorsVector(tags_errors);

}


void printErrorsVector(const std::vector<Error>& errors){
	for(int i = 0;i < errors.size();i++){
		std::string error_msg = errors[i].getErrorMessage();
		std::cout<<errors[i].getErrorMessage()<<std::endl;
	}
}
