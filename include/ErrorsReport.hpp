#ifndef ERRORSREPORT
#define ERRORSREPORT

#include <string>
#include "Error.hpp"

class ErrorsReport{
	private:
		int m_id;
		std::string m_date;
		std::string m_time;
		Error m_errors[];
	public:
		ErrorsReport();
		ErrorsReport(int id, std::string date, std::string time, Error errors[]);
		~ErrorsReport();
};

#endif
