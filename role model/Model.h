#pragma once
#pragma warning (disable:4786)
#include <iostream>
#include <Windows.h>
#include "Person.h"
#include "Admin.h"
#include "Employee.h"
#include <map>
#include <vector>
#include <array>
#include <chrono>
#include <regex>
#include <chrono>
#include <cstring>
//#include <algorithm>
#include "SQL.h"

using namespace std;

class Model
{
private:
	static unsigned short numberOfLoginAttempts;

	static string *identifier;
	static string *authenticator;

	Person *user = NULL;

	unsigned role;

	string dbName;

	string encryption(string block);
	string dencryption(string block);
	string getObjectPowers(unsigned objectNum);

	void createTableUser(string dbname);
	void createTableRoles(string dbname);
	void createTableFuns(string dbname);
	void createTableOjects(string dbName);
	void createTableMR(string dbName);
	void createTableMU(string dbName);

	vector<unsigned> getUserRoleDescNum(unsigned descendants);
	vector<map<string, string, less<string> > > getRolePowers(unsigned powers);

	unsigned inverseUANum(unsigned role);
	unsigned inversePANum(unsigned power);
	unsigned countNumPowerObjectMU(unsigned on, char power);
	unsigned getRoleNumber(string roleDiscription);
	unsigned getRoleDesc(unsigned role);

	bool userHasRole(unsigned number, unsigned role);
public:

	Model(string databaseName);

	static bool isAdmin(Person *p);

	string getUserSessionName();
	string getObjectName(unsigned objectNum);
	string getRoleName(unsigned roleNum);

	bool authorization();
	bool identification(string login);
	bool authentication(string password);
	bool deleteUser(unsigned long number);
	bool isAdmin();
	bool loginExists(string login);
	bool setRole(unsigned role);
	bool roleHasPower(unsigned role, unsigned power);
	bool userHasPower(unsigned un, unsigned on, char power);
	bool addUser(string login, string password, string firstname, string surname, unsigned long number, bool admin);
	bool updateUser(unsigned long number, map<string, array<string, 2>, less<string> > columns);
	bool updateMU(unsigned un, unsigned on, string powers);
	bool updateMR(unsigned rn, unsigned on, string powers);
	bool canReadObject(unsigned objectNum);
	bool canWriteObject(unsigned objectNum);

	void roleSwitchPower(unsigned role, unsigned power);
	void executeObject(unsigned objectNum);
	void readObject(unsigned objectNum);
	void writeObject(unsigned objectNum);

	Person* getUser(unsigned long number);

	string *getObject(unsigned number);
	string *getRole(unsigned number);

	vector<Person*> getUsers(map<string, array<string, 2>, less<string> > cwhere);
	vector<Person *> getUsers();

	vector<map<string, string, less<string> > > getUserRoles();
	//vector<map<string, string, less<string> > > getRolePowers();
	vector<map<string, string, less<string> > > getObjects();
	vector<map<string, string, less<string> > > getRoles();
	vector<map<string, string, less<string> > > getPowers();

	list<map<string, string, less<string> > > getAllData();
	list<map<string, string, less<string> > > getAllDataRoles();
	list<map<string, string, less<string> > > getAllDataMU();
	list<map<string, string, less<string> > > getAllDataMR();
	list<map<string, string, less<string> > > getAllDataObjects();

	//multimap<unsigned, Person*, less<unsigned> > audit(chrono::year_month_day begin, chrono::year_month_day end);

	class UnauthorizedAccess: public exception
	{
	public:
		string userName;
		string action;
		UnauthorizedAccess(string userName, string action) :
			exception("несанкционированный доступ"),
			userName(userName), action(action)
		{

		}
	};

	class ModelException
	{
	public:
		string discription;
		ModelException(string discription) :
			discription(discription)
		{

		}
	};

	class DateException
	{
	public:
		chrono::year_month_day data;
		string discription;

		DateException(chrono::year_month_day data, string ds) :
			data(data), discription(ds)
		{

		}
	};

	class AccessBlockedException
	{
	public:
		AccessBlockedException()
		{

		}
	};
};

