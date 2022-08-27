#ifndef ERROR
#define ERROR

#include <string>
class Error{
	private:
		std::string m_error_function;
		//std::string m_error_message;
	public:
		Error(std::string error_function = "Error in appending");
		std::string getErrorFunction() const;
		//void setErrorFunction(const std::string& error_function);
		//std::string getErrorMessage();
		//void setErrorMessage(const std::string& error_message);
};
#endif
