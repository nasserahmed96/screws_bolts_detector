#ifndef PAYROLL
#define PAYROLL

class Payroll{
	private:
		int ID;
		std::string name;
		std::string address;
	public:
		Payroll(int intID, std::string inname, std::string inaddress);
		~Payroll();
		int getID();
		std::string getName();
		std::string getAddr();
};
#endif

