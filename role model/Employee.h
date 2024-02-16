#pragma once
#include "Person.h"
using namespace std;

class Employee : public Person
{
private:
	unsigned long __number;
public:
	Employee(string firstname, string surname, unsigned long number);

	unsigned long getNumber();
};

