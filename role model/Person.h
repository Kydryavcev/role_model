#pragma once
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

class Person
{
private:
	string __firstname;
	string __surname;

	virtual void virtFunc() // Для нужд typeid
	{

	}
public:
	Person(string firstname, string surname);

	string getFirstname() const;
	void   setFirstname(string firstname);

	string getSurname() const;
	void   setSurname(string surname);

	friend bool operator<(const Person &p1, const Person &p2);
	friend bool operator==(const Person &p1, const Person &p2);
};

