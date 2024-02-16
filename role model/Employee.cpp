#include "Employee.h"

Employee::Employee(string firstname, string surname, unsigned long number) : 
	Person(firstname, surname), __number(number)
{

}

unsigned long Employee::getNumber()
{
	return __number;
}
