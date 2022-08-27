#include "Error.hpp"

Error::Error(std::string error_function): m_error_function{error_function} { }
		
std::string Error::getErrorFunction() const{
	return m_error_function;
}

/*
void Error::setErrorFunction(const std::string& error_function){
	m_error_function = error_function;
}

std::string Error::getErrorMessage(){
	return m_error_message;
}


void Error::setErrorMessage(const std::string& error_message){
	m_error_message = error_message;
}*/
