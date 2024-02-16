#pragma once
#include "Person.h"

Person::Person(std::string firstname, std::string surname): 
	__firstname(firstname), __surname(surname)
{

}

std::string Person::getFirstname()  const
{
	return __firstname;
}

void Person::setFirstname(std::string firstname)
{
	__firstname = firstname;
}

std::string Person::getSurname()  const
{
	return __surname;
}

void Person::setSurname(std::string surname)
{
	__surname = surname;
}

bool operator<(const Person &p1, const Person &p2)
{
	if (p1.__surname == p2.__surname)
	{
		return p1.__firstname < p2.__firstname;
	}

	return p1.__surname < p2.__surname;
}

bool operator==(const Person &p1, const Person &p2)
{
	return (p1.__surname == p2.__surname) && (p1.__firstname == p2.__firstname);
}


std::ostream &operator<<(std::ostream &stream, const Person &p)
{
	stream << "Имя: " << p.getFirstname() << "; Фамилия: " << p.getSurname();
	return stream;
}