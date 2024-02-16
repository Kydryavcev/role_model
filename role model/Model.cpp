#include "Model.h"

unsigned short Model::numberOfLoginAttempts = 0;

string *Model::identifier    = NULL;
string *Model::authenticator = NULL;

char myTolower(char c)
{
	if (c >= 'A' && c <= 'Z') c += 'z' - 'Z';
	if (c >= 'А' && c <= 'Я') c += 'я' - 'Я';

	return c;
}

char myToupper(char c)
{
	if (c >= 'a' && c <= 'z') c -= 'z' - 'Z';
	if (c >= 'а' && c <= 'я') c -= 'я' - 'Я';

	return c;
}

void Model::createTableUser(string databaseName)
{
	list<array<string, 2> > columnDescriptions;

	columnDescriptions.push_back({ {"char(100)", "login"} });
	columnDescriptions.push_back({ {"char(100)", "password"} });
	columnDescriptions.push_back({ {"int", "number"} });
	columnDescriptions.push_back({ {"char(20)", "firstname"} });
	columnDescriptions.push_back({ {"char(20)", "surname"} });
	columnDescriptions.push_back({ {"bool", "admin"} });
	columnDescriptions.push_back({ {"int", "role"} });

	SQL::CREATE_TABLE(databaseName, columnDescriptions);

	map<string, string, less<string> > user;

	unsigned roleNumUser = 0b100000;

	user["login"] = "admin";
	user["password"] = encryption("Абвг");
	user["number"] = "1";
	user["firstname"] = "Admin";
	user["surname"] = "Nosurname";
	user["admin"] = "true";
	user["role"] = to_string(roleNumUser);

	SQL::INSERT(databaseName, user);

	roleNumUser = 0b1;

	user["login"] = "михаил";
	user["password"] = encryption("Абвг");
	user["number"] = "2";
	user["firstname"] = "Михаил";
	user["surname"] = "Nosurname";
	user["admin"] = "false";
	user["role"] = to_string(roleNumUser);

	SQL::INSERT(databaseName, user);

	roleNumUser = 0b1;

	user["login"] = "петр";
	user["password"] = encryption("Абвг");
	user["number"] = "3";
	user["firstname"] = "Петр";
	user["surname"] = "Nosurname";
	user["admin"] = "false";
	user["role"] = to_string(roleNumUser);

	SQL::INSERT(databaseName, user);

	roleNumUser = 0b1;

	user["login"] = "василий";
	user["password"] = encryption("Абвг");
	user["number"] = "4";
	user["firstname"] = "Василий";
	user["surname"] = "Nosurname";
	user["admin"] = "false";
	user["role"] = to_string(roleNumUser);

	SQL::INSERT(databaseName, user);

	roleNumUser = 0b100;

	user["login"] = "мария";
	user["password"] = encryption("Абвг");
	user["number"] = "5";
	user["firstname"] = "Мария";
	user["surname"] = "Nosurname";
	user["admin"] = "false";
	user["role"] = to_string(roleNumUser);

	SQL::INSERT(databaseName, user);

	roleNumUser = 0b10;

	user["login"] = "татьяна";
	user["password"] = encryption("Абвг");
	user["number"] = "6";
	user["firstname"] = "Татьяна";
	user["surname"] = "Nosurname";
	user["admin"] = "false";
	user["role"] = to_string(roleNumUser);

	SQL::INSERT(databaseName, user);

	roleNumUser = 0b100;

	user["login"] = "ольга";
	user["password"] = encryption("Абвг");
	user["number"] = "7";
	user["firstname"] = "Ольга";
	user["surname"] = "Nosurname";
	user["admin"] = "false";
	user["role"] = to_string(roleNumUser);

	SQL::INSERT(databaseName, user);

	roleNumUser = 0b1000;

	user["login"] = "виктор";
	user["password"] = encryption("Абвг");
	user["number"] = "8";
	user["firstname"] = "Виктор";
	user["surname"] = "Nosurname";
	user["admin"] = "false";
	user["role"] = to_string(roleNumUser);

	SQL::INSERT(databaseName, user);

	roleNumUser = 0b10000;

	user["login"] = "максим";
	user["password"] = encryption("Абвг");
	user["number"] = "9";
	user["firstname"] = "Максим";
	user["surname"] = "Nosurname";
	user["admin"] = "false";
	user["role"] = to_string(roleNumUser);

	SQL::INSERT(databaseName, user);

	roleNumUser = 0b10;

	user["login"] = "леонид";
	user["password"] = encryption("Абвг");
	user["number"] = "10";
	user["firstname"] = "Леонид";
	user["surname"] = "Nosurname";
	user["admin"] = "false";
	user["role"] = to_string(roleNumUser);

	SQL::INSERT(databaseName, user);
}

void Model::createTableRoles(string databaseName)
{
	list<array<string, 2> > columnDescriptionsRoles;

	columnDescriptionsRoles.push_back({ {"int", "role"} });
	columnDescriptionsRoles.push_back({ {"char(100)", ""} });
	columnDescriptionsRoles.push_back({ {"int", "descendants"} });

	SQL::CREATE_TABLE(databaseName + "roles", columnDescriptionsRoles);

	map<string, string, less<string> > role;

	unsigned roleNum = 0b1;
	unsigned roleDescen = 0b0;

	role["role"] = to_string(roleNum);
	role["description"] = "middle-программист";
	role["descendants"] = to_string(roleDescen);

	SQL::INSERT(databaseName + "roles", role);

	roleNum = 0b10;
	roleDescen = 0b1;

	role["role"] = to_string(roleNum);
	role["description"] = "senior-программист";
	role["descendants"] = to_string(roleDescen);

	SQL::INSERT(databaseName + "roles", role);

	roleNum = 0b100;
	roleDescen = 0b0;

	role["role"] = to_string(roleNum);
	role["description"] = "тестировщик";
	role["descendants"] = to_string(roleDescen);

	SQL::INSERT(databaseName + "roles", role);

	roleNum = 0b1000;
	roleDescen = 0b110;

	role["role"] = to_string(roleNum);
	role["description"] = "тимлид";
	role["descendants"] = to_string(roleDescen);

	SQL::INSERT(databaseName + "roles", role);

	roleNum = 0b10000;
	roleDescen = 0b1000;

	role["role"] = to_string(roleNum);
	role["description"] = "архитектор ПО";
	role["descendants"] = to_string(roleDescen);

	SQL::INSERT(databaseName + "roles", role);

	roleNum = 0b100000;
	roleDescen = 0b0;

	role["role"] = to_string(roleNum);
	role["description"] = "админ";
	role["descendants"] = to_string(roleDescen);

	SQL::INSERT(databaseName + "roles", role);
}

void Model::createTableFuns(string databaseName)
{
	list<array<string, 2> > columnDescriptionsAlpha;

	columnDescriptionsAlpha.push_back({ {"int", "role"} });
	columnDescriptionsAlpha.push_back({ {"int", "sup"} });

	SQL::CREATE_TABLE(databaseName + "alpha", columnDescriptionsAlpha);

	map<string, string, less<string> > roleAlpha;

	unsigned roleNum = 0b1;

	roleAlpha["role"] = to_string(roleNum);
	roleAlpha["sup"] = to_string(10);

	SQL::INSERT(databaseName + "alpha", roleAlpha);

	roleNum = 0b10;

	roleAlpha["role"] = to_string(roleNum);
	roleAlpha["sup"] = to_string(5);

	SQL::INSERT(databaseName + "alpha", roleAlpha);

	roleNum = 0b100;

	roleAlpha["role"] = to_string(roleNum);
	roleAlpha["sup"] = to_string(5);

	SQL::INSERT(databaseName + "alpha", roleAlpha);

	roleNum = 0b1000;

	roleAlpha["role"] = to_string(roleNum);
	roleAlpha["sup"] = to_string(2);

	SQL::INSERT(databaseName + "alpha", roleAlpha);

	roleNum = 0b10000;

	roleAlpha["role"] = to_string(roleNum);
	roleAlpha["sup"] = to_string(1);

	SQL::INSERT(databaseName + "alpha", roleAlpha);

	roleNum = 0b100000;

	roleAlpha["role"] = to_string(roleNum);
	roleAlpha["sup"] = to_string(1);

	SQL::INSERT(databaseName + "alpha", roleAlpha);

	list<array<string, 2> > columnDescriptionsBeta;

	columnDescriptionsBeta.push_back({ {"int", "object"} });
	columnDescriptionsBeta.push_back({ {"char(20)", "power"} });
	columnDescriptionsBeta.push_back({ {"int", "sup"} });

	SQL::CREATE_TABLE(databaseName + "beta", columnDescriptionsBeta);

	map<string, string, less<string> > powerBeta;

	powerBeta["object"] = "1";
	powerBeta["power"] = "w";
	powerBeta["sup"] = to_string(2);

	SQL::INSERT(databaseName + "beta", powerBeta);

	powerBeta["object"] = "1";
	powerBeta["power"] = "o";
	powerBeta["sup"] = to_string(0);

	SQL::INSERT(databaseName + "beta", powerBeta);

	powerBeta["object"] = "4";
	powerBeta["power"] = "w";
	powerBeta["sup"] = to_string(0);

	SQL::INSERT(databaseName + "beta", powerBeta);

	powerBeta["object"] = "4";
	powerBeta["power"] = "o";
	powerBeta["sup"] = to_string(0);

	SQL::INSERT(databaseName + "beta", powerBeta);

	powerBeta["object"] = "5";
	powerBeta["power"] = "w";
	powerBeta["sup"] = to_string(0);

	SQL::INSERT(databaseName + "beta", powerBeta);

	powerBeta["object"] = "5";
	powerBeta["power"] = "o";
	powerBeta["sup"] = to_string(0);

	SQL::INSERT(databaseName + "beta", powerBeta);

	powerBeta["object"] = "6";
	powerBeta["power"] = "w";
	powerBeta["sup"] = to_string(0);

	SQL::INSERT(databaseName + "beta", powerBeta);

	powerBeta["object"] = "6";
	powerBeta["power"] = "o";
	powerBeta["sup"] = to_string(0);

	SQL::INSERT(databaseName + "beta", powerBeta);

	powerBeta["object"] = "7";
	powerBeta["power"] = "w";
	powerBeta["sup"] = to_string(0);

	SQL::INSERT(databaseName + "beta", powerBeta);

	powerBeta["object"] = "7";
	powerBeta["power"] = "o";
	powerBeta["sup"] = to_string(0);

	SQL::INSERT(databaseName + "beta", powerBeta);
}

void Model::createTableOjects(string databaseName)
{
	list<array<string, 2> > columnDescriptionsObject;

	columnDescriptionsObject.push_back({ {"int", "object"} });
	columnDescriptionsObject.push_back({ {"char(100)", "name"} });

	SQL::CREATE_TABLE(databaseName + "objects", columnDescriptionsObject);

	map<string, string, less<string> > object;

	object["object"] = to_string(1);
	object["name"] = "UML-диаграмма проекта.vsdx";

	SQL::INSERT(databaseName + "objects", object);

	object["object"] = to_string(2);
	object["name"] = "MySQL.exe";

	SQL::INSERT(databaseName + "objects", object);

	object["object"] = to_string(3);
	object["name"] = "PyCharm.exe";

	SQL::INSERT(databaseName + "objects", object);

	object["object"] = to_string(4);
	object["name"] = "База данных пользователей.bin";

	SQL::INSERT(databaseName + "objects", object);

	object["object"] = to_string(5);
	object["name"] = "База данных ролей.bin";

	SQL::INSERT(databaseName + "objects", object);

	object["object"] = to_string(6);
	object["name"] = "База данный полномочий.bin";

	SQL::INSERT(databaseName + "objects", object);

	object["object"] = to_string(7);
	object["name"] = "База данный прав ролей к объектам.bin";

	SQL::INSERT(databaseName + "objects", object);

	object["object"] = to_string(8);
	object["name"] = "База данный объектов.bin";

	SQL::INSERT(databaseName + "objects", object);
}

void Model::createTableMR(string databaseName)
{
	list<array<string, 2> > columnMR;

	columnMR.push_back({ {"int", "role"} });
	columnMR.push_back({ {"int", "object"} });
	columnMR.push_back({ {"char(20)", "powers"} });

	SQL::CREATE_TABLE(databaseName + "MR", columnMR);

	map<string, string, less<string> > elemMR;

	//---------------------------

	unsigned roleNumM = 0b1;

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(1);
	elemMR["powers"] = "r";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10;

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(1);
	elemMR["powers"] = "r";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100;

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(1);
	elemMR["powers"] = "r";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b1000;

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(1);
	elemMR["powers"] = "r";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10000;

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(1);
	elemMR["powers"] = "rwo";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100000;

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(1);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	//---------------------------

	roleNumM = 0b1; // 1

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(2);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10; // 2

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(2);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100; // 3

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(2);
	elemMR["powers"] = "e";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b1000; // 4

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(2);
	elemMR["powers"] = "e";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10000; // 5

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(2);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100000; // 6

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(2);
	elemMR["powers"] = "o";

	SQL::INSERT(databaseName + "MR", elemMR);

	//---------------------------

	roleNumM = 0b1; // 1

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(3);
	elemMR["powers"] = "e";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10; // 2

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(3);
	elemMR["powers"] = "e";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100; // 3

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(3);
	elemMR["powers"] = "e";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b1000; // 4

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(3);
	elemMR["powers"] = "e";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10000; // 5

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(3);
	elemMR["powers"] = "e";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100000; // 6

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(3);
	elemMR["powers"] = "o";

	SQL::INSERT(databaseName + "MR", elemMR);

	//---------------------------

	roleNumM = 0b1; // 1

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(4);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10; // 2

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(4);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100; // 3

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(4);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b1000; // 4

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(4);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10000; // 5

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(4);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100000; // 6

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(4);
	elemMR["powers"] = "rwo";

	SQL::INSERT(databaseName + "MR", elemMR);

	//---------------------------

	roleNumM = 0b1; // 1

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(5);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10; // 2

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(5);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100; // 3

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(5);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b1000; // 4

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(5);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10000; // 5

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(5);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100000; // 6

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(5);
	elemMR["powers"] = "rwo";

	SQL::INSERT(databaseName + "MR", elemMR);//---------------------------

	roleNumM = 0b1; // 1

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(6);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10; // 2

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(6);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100; // 3

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(6);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b1000; // 4

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(6);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10000; // 5

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(6);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100000; // 6

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(6);
	elemMR["powers"] = "rwo";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b1; // 1

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(7);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10; // 2

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(7);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100; // 3

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(7);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b1000; // 4

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(7);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10000; // 5

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(7);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100000; // 6

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(7);
	elemMR["powers"] = "rwo";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b1; // 1

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(8);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10; // 2

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(8);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100; // 3

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(8);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b1000; // 4

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(8);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b10000; // 5

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(8);
	elemMR["powers"] = "";

	SQL::INSERT(databaseName + "MR", elemMR);

	roleNumM = 0b100000; // 6

	elemMR["role"] = to_string(roleNumM);
	elemMR["object"] = to_string(8);
	elemMR["powers"] = "rwo";

	SQL::INSERT(databaseName + "MR", elemMR);
}

void Model::createTableMU(string databaseName)
{
	list<array<string, 2> > columnMU;

	columnMU.push_back({ {"int", "user"} });
	columnMU.push_back({ {"int", "object"} });
	columnMU.push_back({ {"char(20)", "powers"} });

	SQL::CREATE_TABLE(databaseName + "MU", columnMU);

	map<string, string, less<string> > elemMU;

}

Model::Model(string databaseName) :
	dbName(databaseName)
{
	if (SQL::existsTable(databaseName)) return;

	createTableUser(dbName);

	createTableRoles(dbName);

	createTableFuns(dbName);

	createTableOjects(dbName);

	createTableMR(dbName);

	createTableMU(dbName);
}

bool Model::authorization()
{
	if (identifier == NULL || authenticator == NULL)
	{
		throw ModelException("Перед авторизацией, необходимо ввести логин и пароль.");
	}

	list<map<string, string, less<string> > > selectedUsers;

	string columnsArr[] = {"password", "number", "firstname", "surname", "admin"};
	vector<string> columns(columnsArr, columnsArr + 5);

	map<string, array<string, 2>, less<string> > cwhere;

	transform((*identifier).begin(), (*identifier).end(), (*identifier).begin(), myTolower);

	cwhere["login"] = { {"=", (*identifier)} };

	selectedUsers = SQL::SELECT(dbName, columns, cwhere);

	if (selectedUsers.size() == 0u)
	{
		return false;
	}

	map<string, string, less<string> > selectedUser = selectedUsers.front();

	string depass = dencryption(selectedUser["password"]);

	if (*authenticator != depass)
	{
		return false;
	}

	Person *user;

	if (selectedUser["admin"] == "true")
	{
		user = new Admin(selectedUser["firstname"], selectedUser["surname"], stol(selectedUser["number"]));
	}
	else
	{
		user = new Employee(selectedUser["firstname"], selectedUser["surname"], stol(selectedUser["number"]));
	}

	this->user = user;

	return true;
}

bool Model::identification(string login)
{
	transform(login.begin(), login.end(), login.begin(), myTolower);

	list<map<string, string, less<string> > > selectedUsers;

	string columnsArr[] = { "number"};
	vector<string> columns(columnsArr, columnsArr + 1);

	map<string, array<string, 2>, less<string> > cwherel;

	cwherel["login"] = { {"=",login} };

	selectedUsers = SQL::SELECT(dbName, columns, cwherel);

	bool result = (selectedUsers.size() != 0u);

	if (result)
	{
		identifier = new string(login);
	}
	else
	{
		numberOfLoginAttempts++;

		if (numberOfLoginAttempts >= 10)
		{
			throw AccessBlockedException();
		}

		if (numberOfLoginAttempts % 3 == 0)
		{
			cout << endl << "Не верный логин. Терминал ввода заблокирован. Подождите 10 секунд." << endl;
			Sleep(10000);
		}
	}

	return result;
}

bool Model::authentication(string password)
{
	if (identifier == NULL)
	{
		throw ModelException("Перед вводом пароля, необходимо ввести логин.");
	}

	string login = *identifier;

	list<map<string, string, less<string> > > selectedUsers;

	string columnsArr[] = { "password"};
	vector<string> columns(columnsArr, columnsArr + 1);

	map<string, array<string, 2>, less<string> > cwhere;

	transform((*identifier).begin(), (*identifier).end(), (*identifier).begin(), myTolower);

	cwhere["login"] = { {"=", (*identifier)} };

	selectedUsers = SQL::SELECT(dbName, columns, cwhere);

	map<string, string, less<string> > selectedUser = selectedUsers.front();

	string depass = dencryption(selectedUser["password"]);

	if (password != depass)
	{
		numberOfLoginAttempts++;

		if (numberOfLoginAttempts >= 10)
		{
			throw ModelException("Вы израсходовали все попытки для входа.");
		}

		if (numberOfLoginAttempts % 3 == 0)
		{
			cout << endl << "Не верных пароль. Терминал ввода заблокирован. Подождите 10 секунд." << endl;
			Sleep(10000);
		}

		return false;
	}
	else
	{
		authenticator = new string(password);
	}

	return true;
}

bool Model::isAdmin()
{
	if (this->user == NULL)
		throw ModelException("Данная операция недоступна. В системе никто не авторизировался.");

	return typeid(*(this->user)) == typeid(Admin);
}

bool Model::isAdmin(Person *p)
{
	return typeid(*p) == typeid(Admin);
}

string Model::encryption(string block)
{
	char matrix[9][10];

	unsigned seed = 0;

	for (int i = 0; i < block.length(); i++)
	{
		seed += block[i];
	}

	srand(seed);

	for (unsigned i = 0; i < 9; i++)
	{
		for (unsigned j = 0; j < 9; j++)
		{
			matrix[i][j] = 48 + rand() / ((RAND_MAX + 1u) / 207);
		}

		matrix[i][9] = '\0';
	}

	unsigned position = 0;

	bool blockend = false;

	for (unsigned i = 0; i < 9; i++)
	{
		if (position >= block.size())
		{
			matrix[i][8] = 3;

			blockend = true;
			break;
		}

		matrix[i][8] = block[position++];		
	}

	for (unsigned i = 7; (i >= 0) && !blockend; i--)
	{
		if (position >= block.size())
		{
			matrix[8][i] = 3;

			blockend = true;

			break;
		}

		matrix[8][i] = block[position++];
	}

	for (unsigned i = 1; (i < 8) && !blockend; i--)
	{
		if (position >= block.size())
		{
			matrix[8 - i][i] = 3;

			blockend = true;

			break;
		}

		matrix[8 - i][i] = block[position++];
	}

	string result;

	for (unsigned i = 0; i < 9; i++)
	{
		result += string(matrix[i]);
	}

	return result;
}

string Model::dencryption(string block)
{
	string result;

unsigned position = 8;

bool blockend = false;

for (unsigned i = 0; i < 9; i++)
{
	if (block[position] == static_cast<char>(3))
	{
		blockend = true;

		break;
	}

	result += block[position];

	position += 9;
}

position = 79;

for (unsigned i = 7; (i >= 0) && !blockend; i--)
{
	if (block[position] == static_cast<char>(3))
	{
		blockend = true;

		break;
	}

	result += block[position];

	position -= 1;
}

position = 64;

for (unsigned i = 1; (i < 8) && !blockend; i--)
{
	if (block[position] == static_cast<char>(3))
	{
		blockend = true;

		break;
	}

	result += block[position];

	position -= 8;
}

return result;
}

bool Model::setRole(unsigned role)
{
	if (this->user == NULL)
		throw ModelException("Операция выбора роли пользователя недоступна для не авторизованных пользователей.");

	vector<map<string, string, less<string> > > roles = getUserRoles();

	bool roleAvailable = false;

	for (int i = 0; i < roles.size(); i++)
	{
		if (stoi(roles[i]["role"]) == role)
		{
			roleAvailable = true;

			break;
		}
	}

	if (!roleAvailable)
	{
		throw UnauthorizedAccess(this->user->getFirstname(), "к роле с номером " + role);
	}

	this->role = role;

	return true;
}

unsigned Model::inverseUANum(unsigned role)
{
	unsigned result = 0;

	list<map<string, string, less<string> > > selectedUsers;

	string columnsArr[] = { "number" };
	vector<string> columns(columnsArr, columnsArr + 1);

	map<string, array<string, 2>, less<string> > cwhere;

	selectedUsers = SQL::SELECT(dbName, columns, cwhere);

	list<map<string, string, less<string> > >::iterator selusiter = selectedUsers.begin();

	while (selusiter != selectedUsers.end())
	{
		if (userHasRole(stoi((*selusiter)["number"]), role))
		{
			result++;
		}

		selusiter++;
	}

	return result;
}

unsigned Model::inversePANum(unsigned power)
{
	unsigned result = 0;

	list<map<string, string, less<string> > > roles;

	string columnArr[] = { "powers" };

	vector<string> column = { columnArr, columnArr + 1 };

	map<string, array<string, 2>, less<string> > cwhere;

	roles = SQL::SELECT(dbName + "roles", column, cwhere);

	list<map<string, string, less<string> > >::iterator roliter = roles.begin();

	while (roliter != roles.end())
	{
		map<string, string, less<string> > role = *roliter++;

		unsigned powers = stoi(role["powers"]);

		unsigned rsadfkasj = powers & power;

		if ((powers & power) != 0)
		{
			result++;
		}
	}

	return result;
}

unsigned Model::countNumPowerObjectMU(unsigned on, char power)
{
	unsigned counter = 0;

	list<map<string, string, less<string> > > muelems;

	string columnsArr[] = { "powers" };
	vector<string> columns{ columnsArr, columnsArr + 1 };

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["object"] = { {"=",to_string(on)} };

	muelems = SQL::SELECT(dbName + "MU", columns, cwhere);

	list<map<string, string, less<string> > >::iterator muelem = muelems.begin();

	while (muelem != muelems.end())
	{
		string pmu = (*muelem)["powers"];

		if (pmu.find(power) != string::npos)
		{
			counter += 1;
		}

		muelem++;
	}

	return counter;
}

bool Model::userHasRole(unsigned number, unsigned role)
{
	list<map<string, string, less<string> > > selectedUsers;

	string columnsArr[] = { "role" };
	vector<string> columns(columnsArr, columnsArr + 1);

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["number"] = { {"=", to_string(number)} };

	selectedUsers = SQL::SELECT(dbName, columns, cwhere);

	if (selectedUsers.size() == 0u)
	{
		return false;
	}

	map<string, string, less<string> > selectedUser = selectedUsers.front();

	if (stoi(selectedUser["role"]) == role)
	{
		return true;
	}

	list<map<string, string, less<string> > > roleData;

	string columnsArrRD[] = { "role", "descendants" };
	vector<string> columnsRD(columnsArrRD, columnsArrRD + 2);

	map<string, array<string, 2>, less<string> > cwhereRD;

	cwhereRD["role"] = { {"=", selectedUser["role"]} };

	roleData = SQL::SELECT(dbName + "roles", columnsRD, cwhereRD);

	map<string, string, less<string> > rolef = roleData.front();

	vector<unsigned> roleDescNum = getUserRoleDescNum(stoi(rolef["descendants"]));

	for (int i = 0; i < roleDescNum.size(); i++)
	{
		if (roleDescNum[i] == role)
		{
			return true;
		}
	}

	return false;
}

vector<map<string, string, less<string> > > Model::getRoles()
{
	if (this->user == NULL)
		throw ModelException("Операция получения ролей недоступна для не авторизованных пользователей.");

	if (!canReadObject(5))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(5);
		throw UnauthorizedAccess(nameu, action);
	}

	vector<map<string, string, less<string> > > roles;

	list<map<string, string, less<string> > > roleData;

	string columnsArrRD[] = { "role", "description" };
	vector<string> columnsRD(columnsArrRD, columnsArrRD + 2);

	map<string, array<string, 2>, less<string> > cwhereRD;

	roleData = SQL::SELECT(dbName + "roles", columnsRD, cwhereRD);

	list<map<string, string, less<string> > >::iterator rditer = roleData.begin();

	while (rditer != roleData.end())
	{
		roles.push_back(*rditer);

		rditer++;
	}

	return roles;
}

bool Model::roleHasPower(unsigned role, unsigned power)
{
	if (this->user == NULL)
		throw ModelException("Операция проверки присутствия прав в роли недоступна для не авторизованных пользователей.");

	if (!canReadObject(7))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(7);
		throw UnauthorizedAccess(nameu, action);
	}

	list<map<string, string, less<string> > > roles;

	string columnArr[] = { "powers" };

	vector<string> column = { columnArr, columnArr + 1 };

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["role"] = { {"=", to_string(role)} };

	roles = SQL::SELECT(dbName + "roles", column, cwhere);

	map<string, string, less<string> > rolef = roles.front();

	unsigned rolePowers = stoi(rolef["powers"]);

	return ((rolePowers & power) != 0);
}

bool Model::userHasPower(unsigned un, unsigned on, char power)
{
	if (this->user == NULL)
		throw ModelException("Операция проверки присутствия полномочия у пользователя недоступна для не авторизованных пользователей.");

	if (!canReadObject(6))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(6);
		throw UnauthorizedAccess(nameu, action);
	}

	list<map<string, string, less<string> > > powersMUs;

	string columnArr[] = { "powers" };

	vector<string> column = { columnArr, columnArr + 1 };

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["user"] = { {"=", to_string(un)} };
	cwhere["object"] = { {"=", to_string(on)} };

	powersMUs = SQL::SELECT(dbName + "MU", column, cwhere);
	
	if (powersMUs.size() == 0)
	{
		return false;
	}
	else
	{
		map<string, string, less<string> > powersMU = powersMUs.front();

		string userPowers = powersMU["powers"];

		return (userPowers.find(power) != string::npos);
	}
}

void Model::roleSwitchPower(unsigned role, unsigned power)
{
	if (this->user == NULL)
		throw ModelException("Операция изменения полномочий в роли недоступна для не авторизованных пользователей.");

	if (!canWriteObject(7))
	{
		string nameu = this->user->getFirstname();
		string action = "к записи в файл с именем " + getObjectName(7);
		throw UnauthorizedAccess(nameu, action);
	}

	if (!roleHasPower(role, power))
	{
		list<map<string, string, less<string> > > psbeta;

		string columnArrR[] = { "sup" };

		vector<string> columnR = { columnArrR, columnArrR + 1 };

		map<string, array<string, 2>, less<string> > cwhereR;

		cwhereR["power"] = { { "=", to_string(power) } };

		psbeta = SQL::SELECT(dbName + "beta", columnR, cwhereR);

		map<string, string, less<string> > pbeta = psbeta.front();

		unsigned psup = stoi(pbeta["sup"]);

		unsigned pcur = inversePANum(power);

		if (pcur >= psup)
		{
			throw ModelException("Достигнут лимит ролей для полномочия " + to_string(power));
		}
	}

	list<map<string, string, less<string> > > roles;

	string columnArr[] = { "powers" };

	vector<string> column = { columnArr, columnArr + 1 };

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["role"] = { {"=", to_string(role)} };

	roles = SQL::SELECT(dbName + "roles", column, cwhere);

	map<string, string, less<string> > rolef = roles.front();

	unsigned rolePowers = stoi(rolef["powers"]);

	rolePowers ^= power;

	map<string, array<string, 2>, less<string> > columns;

	columns["powers"] = { "=", to_string(rolePowers) };

	map<string, array<string, 2>, less<string> > cwheres;

	cwheres["role"] = { { "=", to_string(role)} };

	SQL::UPDATE(dbName + "roles", columns, cwheres);
}

vector<map<string, string, less<string> > > Model::getPowers()
{
	if (this->user == NULL)
		throw ModelException("Операция получения списка полномочий недоступна для не авторизованных пользователей.");

	if (!canReadObject(6))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(6);
		throw UnauthorizedAccess(nameu, action);
	}

	vector<map<string, string, less<string> > > powers;

	list<map<string, string, less<string> > > powerData;

	string columnsArrPD[] = { "power", "description" };
	vector<string> columnsPD(columnsArrPD, columnsArrPD + 2);

	map<string, array<string, 2>, less<string> > cwherePD;

	powerData = SQL::SELECT(dbName + "powers", columnsPD, cwherePD);

	list<map<string, string, less<string> > >::iterator pditer = powerData.begin();

	while (pditer != powerData.end())
	{
		powers.push_back(*pditer);

		pditer++;
	}

	return powers;
}

vector<map<string, string, less<string> > > Model::getUserRoles()
{
	if (this->user == NULL)
		throw ModelException("Операция получения роли пользователя недоступна для не авторизованных пользователей.");

	Employee *emp = dynamic_cast<Employee *>(user);

	vector<map<string, string, less<string> > > roles;

	list<map<string, string, less<string> > > selectedUsers;

	string columnsArr[] = { "role" };
	vector<string> columns(columnsArr, columnsArr + 1);

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["number"] = { {"=", to_string(emp->getNumber())} };

	selectedUsers = SQL::SELECT(dbName, columns, cwhere);

	map<string, string, less<string> > selectedUser = selectedUsers.front();

	list<map<string, string, less<string> > > roleData;

	string columnsArrRD[] = { "role", "description", "descendants" };
	vector<string> columnsRD(columnsArrRD, columnsArrRD + 3);

	map<string, array<string, 2>, less<string> > cwhereRD;

	cwhereRD["role"] = { {"=", selectedUser["role"]} };

	roleData = SQL::SELECT(dbName + "roles", columnsRD, cwhereRD);

	map<string, string, less<string> > role = roleData.front();

	roles.push_back(role);

	vector<unsigned> roleDescNum = getUserRoleDescNum(stoi(role["descendants"]));

	for (int i = 0; i < roleDescNum.size(); i++)
	{
		cwhereRD["role"] = { {"=", to_string(roleDescNum[i])} };

		roleData = SQL::SELECT(dbName + "roles", columnsRD, cwhereRD);

		roles.push_back(roleData.front());
	}

	return roles;
}

vector<unsigned> Model::getUserRoleDescNum(unsigned descendants)
{
	vector<unsigned> rolesNum;

	unsigned roleNum = 0b1;

	while (descendants >= roleNum)
	{
		if ((descendants & roleNum) != 0)
		{
			rolesNum.push_back(roleNum);

			list<map<string, string, less<string> > > roleData;

			string columnsArrRD[] = {"descendants"};
			vector<string> columnsRD(columnsArrRD, columnsArrRD + 1);

			map<string, array<string, 2>, less<string> > cwhereRD;

			cwhereRD["role"] = { {"=", to_string(roleNum)} };

			roleData = SQL::SELECT(dbName + "roles", columnsRD, cwhereRD);

			map<string, string, less<string> > role = roleData.front();

			vector<unsigned> rolesNumRe = getUserRoleDescNum(stoi(role["descendants"]));

			//merge(rolesNum.begin(), rolesNum.end(), rolesNumRe.begin(), rolesNumRe.end(), rolesNum);

			for (int i = 0; i < rolesNumRe.size(); i++)
			{
				rolesNum.push_back(rolesNumRe[i]);
			}
		}

		roleNum <<= 1;
	}

	return rolesNum;
}

//vector<map<string, string, less<string> > > Model::getRolePowers()
//{
//	if (this->user == NULL)
//		throw ModelException("Операция получения информации о правах роли недоступна для не авторизованных пользователей.");
//
//	list<map<string, string, less<string> > > selectedRoles;
//
//	string columnsArr[] = { "powers" };
//	vector<string> columns(columnsArr, columnsArr + 1);
//
//	map<string, array<string, 2>, less<string> > cwhere;
//
//	cwhere["role"] = { {"=", to_string(this->role)} };
//
//	selectedRoles = SQL::SELECT(dbName + "roles", columns, cwhere);
//
//	map<string, string, less<string> > role = selectedRoles.front();
//
//	return getRolePowers(stoi(role["powers"]));
//}

unsigned Model::getRoleDesc(unsigned role)
{
	list<map<string, string, less<string> > > roleData;

	string columnsArrRD[] = {"descendants"};
	vector<string> columnsRD(columnsArrRD, columnsArrRD + 1);

	map<string, array<string, 2>, less<string> > cwhereRD;

	cwhereRD["role"] = { {"=", to_string(this->role)} };

	roleData = SQL::SELECT(dbName + "roles", columnsRD, cwhereRD);

	map<string, string, less<string> > roled = roleData.front();

	return stoi(roled["descendants"]);
}

vector<map<string, string, less<string> > > Model::getObjects()
{
	if (this->user == NULL)
		throw ModelException("Операция получения информации об объектах недоступна для не авторизованных пользователей.");

	vector<map<string, string, less<string> > > objects;

	list<map<string, string, less<string> > > objectsDB;

	string columnsArr[] = { "object", "name"};
	vector<string> columns(columnsArr, columnsArr + 2);

	map<string, array<string, 2>, less<string> > cwhere;

	objectsDB = SQL::SELECT(dbName + "objects", columns, cwhere);

	list<map<string, string, less<string> > >::iterator odbiter = objectsDB.begin();

	while (odbiter != objectsDB.end())
	{
		objects.push_back(*odbiter);

		odbiter++;
	}

	return objects;
}

void Model::executeObject(unsigned objectNum)
{
	if (this->user == NULL)
		throw ModelException("Операция выполнения файла недоступна для не авторизованных пользователей.");

	string powers = getObjectPowers(objectNum);

	if (powers.find("e") == string::npos)
	{
		string nameu = this->user->getFirstname();
		string action = "к выполнению программы с именем " + getObjectName(objectNum);
		throw UnauthorizedAccess(nameu, action);
	}

	cout << "Программа запускается..." << endl << "Программа поработала..." << endl << "Программа закончила выполнение" << endl;
}

void Model::readObject(unsigned objectNum)
{
	if (this->user == NULL)
		throw ModelException("Операция чтения файла недоступна для не авторизованных пользователей.");

	string powers = getObjectPowers(objectNum);

	if (powers.find("r") == string::npos)
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(objectNum);
		throw UnauthorizedAccess(nameu, action);
	}


	if (objectNum == 4)
	{
		list<map<string, string, less<string> > > table = getAllData();

		list<map<string, string, less<string> > >::iterator ittab = table.begin();

		cout << endl << "+----------+--------------------+---------------------------------------------------------------------------------+--------------------+--------------------+-----+------------------------------+" << endl;

		cout << "|" << setw(10) << "№" << "|" << setw(20) << "Логин" << "|" << setw(81) << "Пароль" << "|" << setw(20) << "Имя" << "|" << setw(20) << "Фамилия" << "|" << setw(5) << "Admin" << "|" << setw(30) << "Роль" << "|" << endl;

		cout << "+----------+--------------------+---------------------------------------------------------------------------------+--------------------+--------------------+-----+------------------------------+" << endl;

		while (ittab != table.end())
		{
			cout << "|" << setw(10) << (*ittab)["number"] << "|" << setw(20) << (*ittab)["login"] << "|" << setw(81) << (*ittab)["password"] << "|" << setw(20) << (*ittab)["firstname"] << "|" << setw(20) << (*ittab)["surname"] << "|" << setw(5) << (*ittab)["admin"] << "|" << setw(30) << getRoleName(stoi((*ittab)["role"])) << "|" << endl;

			ittab++;
		}

		cout << "+----------+--------------------+---------------------------------------------------------------------------------+--------------------+--------------------+-----+------------------------------+" << endl;

		cout << endl << endl << "Введите что-нибудь для продолжения: ";

		string a;

		cin >> a;
	}
	else if (objectNum == 5)
	{
		list<map<string, string, less<string> > > table = getAllDataRoles();

		list<map<string, string, less<string> > >::iterator ittab = table.begin();

		cout << endl << "+--------+----------------------------------------------------------------------------------------------------+--------+" << endl;

		cout << "|" << setw(8) << "№" << "|" << setw(100) << "Описание" << "|" << setw(8) << "Потомки" << "|" << endl;

		cout << "+--------+----------------------------------------------------------------------------------------------------+--------+" << endl;

		while (ittab != table.end())
		{
			cout << "|" << setw(8) << (*ittab)["role"] << "|" << setw(100) << (*ittab)["description"] << "|" << setw(8) << (*ittab)["descendants"] << "|" << endl;

			ittab++;
		}

		cout << "+--------+----------------------------------------------------------------------------------------------------+--------+" << endl;

		cout << endl << endl << "Введите что-нибудь для продолжения: ";

		string a;

		cin >> a;
	}
	else if (objectNum == 6)
	{
		list<map<string, string, less<string> > > table = getAllDataMU();

		list<map<string, string, less<string> > >::iterator ittab = table.begin();

		cout << endl << "+----------------+----------------+--------------------+" << endl;

		cout << "|" << setw(16) << "№ пользователя" << "|" << setw(16) << "№ объекта" << "|" << setw(20) << "Права" << "|" << endl;

		cout << "+----------------+----------------+--------------------+" << endl;

		while (ittab != table.end())
		{
			cout << "|" << setw(16) << (*ittab)["user"] << "|" << setw(16) << (*ittab)["object"] << "|" << setw(20) << (*ittab)["powers"] << "|" << endl;

			ittab++;
		}

		cout << "+----------------+----------------+--------------------+" << endl;

		cout << endl << endl << "Введите что-нибудь для продолжения: ";

		string a;

		cin >> a;
	}
	else if (objectNum == 7)
	{
		list<map<string, string, less<string> > > table = getAllDataMR();

		list<map<string, string, less<string> > >::iterator ittab = table.begin();

		cout << endl << "+----------------+----------------+--------------------+" << endl;

		cout << "|" << setw(16) << "№ роли" << "|" << setw(16) << "№ объекта" << "|" << setw(20) << "Права" << "|" << endl;

		cout << "+----------------+----------------+--------------------+" << endl;

		while (ittab != table.end())
		{
			cout << "|" << setw(16) << (*ittab)["role"] << "|" << setw(16) << (*ittab)["object"] << "|" << setw(20) << (*ittab)["powers"] << "|" << endl;

			ittab++;
		}

		cout << "+----------------+----------------+--------------------+" << endl;

		cout << endl << endl << "Введите что-нибудь для продолжения: ";

		string a;

		cin >> a;
	}
	else if (objectNum == 8)
	{
		list<map<string, string, less<string> > > table = getAllDataObjects();

		list<map<string, string, less<string> > >::iterator ittab = table.begin();

		cout << endl << "+----------------+----------------------------------------------------------------------------------------------------+" << endl;

		cout << "|" << setw(16) << "№" << "|" << setw(100) << "Название объекта" << "|" << endl;

		cout << "+----------------+----------------------------------------------------------------------------------------------------+" << endl;

		while (ittab != table.end())
		{
			cout << "|" << setw(16) << (*ittab)["object"] << "|" << setw(100) << (*ittab)["name"] << "|" << endl;

			ittab++;
		}

		cout << "+----------------+----------------------------------------------------------------------------------------------------+" << endl;

		cout << endl << endl << "Введите что-нибудь для продолжения: ";

		string a;

		cin >> a;
	}
	else
	{
		cout << "Файл читается" << endl;
	}	
}

void Model::writeObject(unsigned objectNum)
{
	if (this->user == NULL)
		throw ModelException("Операция выполнения файла недоступна для не авторизованных пользователей.");

	string powers = getObjectPowers(objectNum);

	if (powers.find("w") == string::npos)
	{
		string nameu = this->user->getFirstname();
		string action = "к записи в файл с именем " + getObjectName(objectNum);
		throw UnauthorizedAccess(nameu, action);
	}

	if (objectNum == 4)
	{
		if (!canWriteObject(4))
		{
			string action{ "запись в файл с именем " + getObjectName(4) };

			throw Model::UnauthorizedAccess(getUserSessionName(), action);
		}

		bool exitUPD = false;

		int numberUPD;

		cout << "-----Обновление учетной записи------" << endl;

		while (true)
		{
			cout << "Введите номер сотрудника, данные которого хотите изменить: ";

			cin >> numberUPD;

			if (cin.good() && numberUPD > 0)
			{
				cin.ignore(30, '\n');

				break;
			}

			cin.clear();

			cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

			cin.ignore(30, '\n');
		}

		while (getUser(numberUPD) == NULL)
		{
			string yesNo;

			cout << "Пользователя с таким номером не существует. Попробовать еще раз?" << endl
				<< "Продолжить обновление(Да/Нет): ";

			cin >> yesNo;

			while (yesNo != "Да" && yesNo != "Нет")
			{
				cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
					<< "Попробуйте еще раз: ";

				cin >> yesNo;
			}

			if (yesNo == "Да")
			{
				cout << "Введите номер сотрудника, данные которого хотите изменить: ";
				cin >> numberUPD;
			}
			else
			{
				exitUPD = true;

				break;
			}
		}

		if (exitUPD)
			return;

		map<string, array<string, 2>, less<string> > columnsUPD;

		while (true)
		{
			unsigned numMenuUPD;

			cout << "Выберите поля для обновления" << endl
				<< "1) Логин" << (columnsUPD.contains("login") ? ": указано \"" + columnsUPD["login"][1] + "\";" : ";") << endl
				<< "2) Пароль" << (columnsUPD.contains("password") ? ": указано \"" + columnsUPD["password"][1] + "\";" : ";") << endl
				<< "3) Имя" << (columnsUPD.contains("firstname") ? ": указано \"" + columnsUPD["firstname"][1] + "\";" : ";") << endl
				<< "4) Фамилия" << (columnsUPD.contains("surname") ? ": указано \"" + columnsUPD["surname"][1] + "\";" : ";") << endl
				<< "5) Админ" << (columnsUPD.contains("admin") ? ": указано \"" + columnsUPD["admin"][1] + "\";" : ";") << endl
				<< "6) Роль" << (columnsUPD.contains("role") ? ": указано \"" + columnsUPD["role"][1] + "\";" : ";") << endl
				<< "0) Обновить учетную запись." << endl;

			cout << "Ваш выбор: ";

			cin >> numMenuUPD;

			switch (numMenuUPD)
			{
			case 1:
			{
				string loginUPD;

				cout << "Введите новый логин: ";

				cin >> loginUPD;

				//regex rxl{ R"([A-Za-zА-Яа-я\d_.-]{5,})" };

				//while (!regex_match(loginUPD.begin(), loginUPD.end(), rxl))
				//{
				//    cout << "Логин должен состоять из букв русского и латинского алфавита, а также из символов '_', '.', '-'. И быть длиной от 5 символов." << endl
				//        << "Попробуйте ещё раз: ";

				//    cin >> loginUPD;
				//}

				while (loginExists(loginUPD))
				{
					cout << "Данный логин занят." << endl
						<< "Попробуйте еще раз: ";

					cin >> loginUPD;
				}

				columnsUPD["login"] = { {"=", loginUPD} };

				break;
			}
			case 2:
			{
				string passwordUPD;

				cout << "Введите новый пароль: ";

				cin >> passwordUPD;

				regex rx{ R"([A-Ja-jА-Иа-и]{8,})" };

				while (!regex_match(passwordUPD.begin(), passwordUPD.end(), rx))
				{
					cout << "Пароль может содержать только десять первых букв русского и латинского алфавитов. И быть длиной от 8 символов." << endl
						<< "Попробуйте ещё раз: ";

					cin >> passwordUPD;
				}

				columnsUPD["password"] = { {"=", passwordUPD} };

				break;
			}
			case 3:
			{
				string firstnameUPD;

				regex rxfs{ R"([A-Za-zА-Яа-я]{3,})" };

				while (true)
				{
					cout << "Введите новое имя: ";

					cin >> firstnameUPD;

					if (regex_match(firstnameUPD.begin(), firstnameUPD.end(), rxfs))
					{
						break;
					}

					cout << "Фамилия может содержать только буквы русского и латинского алфавитов. И быть длиной от 3 символов." << endl;
				}

				columnsUPD["firstname"] = { {"=", firstnameUPD} };

				break;
			}
			case 4:
			{
				string surnameUPD;

				regex rxfs{ R"([A-Za-ZА-Яа-я]{3,})" };

				while (true)
				{
					cout << "Введите новую фамилию: ";

					cin >> surnameUPD;

					if (regex_match(surnameUPD.begin(), surnameUPD.end(), rxfs))
					{
						break;
					}

					cout << "Фамилия может содержать только буквы русского и латинского алфавитов. И быть длиной от 3 символов." << endl;
				}

				columnsUPD["surname"] = { {"=", surnameUPD} };

				break;
			}
			case 5:
			{
				string adminUPD;

				cout << "Сделать пользователя админом(Да/Нет): ";

				cin >> adminUPD;

				while (adminUPD != "Да" && adminUPD != "Нет")
				{
					cout << "Вы ввели некорректные данные. Данное поле принимает значения Да или Нет." << endl
						<< "Попробуйте еще раз: ";

					cin >> adminUPD;
				}

				if (adminUPD == "Да")
				{
					columnsUPD["admin"] = { {"=", "true"} };
				}
				else
				{
					columnsUPD["admin"] = { {"=", "false"} };
				}

				break;
			}
			case 6:
			{
				cout << "Список существующих ролей:" << endl;

				vector<map<string, string, less<string> > > rolesEx = getRoles();

				for (int i = 0; i < rolesEx.size(); i++)
				{
					cout << i + 1 << ") " << rolesEx[i]["description"] << ";" << endl;
				}

				unsigned roleNumUp;

				while (true)
				{
					cout << "Выберите роль: ";

					cin >> roleNumUp;

					if (cin.good() && roleNumUp > 0 && roleNumUp < rolesEx.size() + 1)
					{
						cin.ignore(30, '\n');

						break;
					}

					cin.clear();

					cout << "Вы ввели некорректные данные. Введите число от 1 до " << rolesEx.size() << ". Соответствующее нужному пункту меню." << endl;

					cin.ignore(30, '\n');
				}

				columnsUPD["role"] = { {"=", rolesEx[roleNumUp - 1]["description"]} };

				break;
			}
			case 0:
				exitUPD = true;

				break;
			default:
				cout << "Вы ввели некорректные данные. Введите число от 0 до 5. Соответствующее нужному пункту меню." << endl;
				break;
			}

			if (exitUPD)
				break;
		}

		cout << "------------------------------------" << endl;

		try
		{
			updateUser(numberUPD, columnsUPD);
		}
		catch (Model::ModelException ex)
		{
			cout << endl << "Произошло исключение" << endl << endl;

			cout << ex.discription << endl;
		}
		catch (exception ex)
		{
			cout << ex.what() << endl;
		}
		catch (...)
		{
			cout << "Произошло исключение" << endl;
		}

		cout << endl << "Блок обновления закончен." << endl;

		Sleep(3000);
	}
	else if (objectNum == 6)
	{
		if (!canWriteObject(6))
		{
			string action{ "запись в файл с именем " + getObjectName(6) };

			throw Model::UnauthorizedAccess(getUserSessionName(), action);
		}
		bool exitUPD = false;

		int numberUser, numberObject;

		string newPowers;

		cout << "-----Обновление таблицы MU------" << endl;

		while (true)
		{
			cout << "Введите номер сотрудника, которому хотите изменить полномочия: ";

			cin >> numberUser;

			if (cin.good() && numberUser > 0)
			{
				cin.ignore(30, '\n');

				break;
			}

			cin.clear();

			cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

			cin.ignore(30, '\n');
		}

		while (getUser(numberUser) == NULL)
		{
			string yesNo;

			cout << "Пользователя с таким номером не существует. Попробовать еще раз?" << endl
				<< "Продолжить обновление(Да/Нет): ";

			cin >> yesNo;

			while (yesNo != "Да" && yesNo != "Нет")
			{
				cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
					<< "Попробуйте еще раз: ";

				cin >> yesNo;
			}

			if (yesNo == "Да")
			{
				cout << "Введите номер сотрудника, которому хотите изменить полномочия: ";
				cin >> numberUser;
			}
			else
			{
				exitUPD = true;

				break;
			}
		}

		if (exitUPD)
			return;

		while (true)
		{
			cout << "Введите номер объекта, права к которому будут выданы: ";

			cin >> numberObject;

			if (cin.good() && numberObject > 0)
			{
				cin.ignore(30, '\n');

				break;
			}

			cin.clear();

			cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

			cin.ignore(30, '\n');
		}

		while (getObject(numberObject) == NULL)
		{
			string yesNo;

			cout << "Объекта с таким номером не существует. Попробовать еще раз?" << endl
				<< "Продолжить обновление(Да/Нет): ";

			cin >> yesNo;

			while (yesNo != "Да" && yesNo != "Нет")
			{
				cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
					<< "Попробуйте еще раз: ";

				cin >> yesNo;
			}

			if (yesNo == "Да")
			{
				cout << "Введите номер объекта, права к которому будут выданы: ";
				cin >> numberObject;
			}
			else
			{
				exitUPD = true;

				break;
			}
		}

		if (exitUPD)
			return;

		regex rgpowers{ R"(([rweo]*|-))" };

		while (true)
		{
			cout << "Введите права: ";

			cin >> newPowers;

			if (cin.good() && regex_match(newPowers.begin(), newPowers.end(), rgpowers))
			{
				cin.ignore(30, '\n');

				break;
			}

			cin.clear();

			cout << "Вы ввели некорректные данные. Введите строку из прав: r, w, e, o. Или '-' в случае отсутствия прав." << endl;

			cin.ignore(30, '\n');
		}

		try
		{
			if (newPowers == "-")
			{
				newPowers = "";
			}

			updateMU(numberUser, numberObject, newPowers);
		}
		catch (Model::ModelException ex)
		{
			cout << endl << "Произошло исключение" << endl << endl;

			cout << ex.discription << endl;
		}
		catch (exception ex)
		{
			cout << ex.what() << endl;
		}
		catch (...)
		{
			cout << "Произошло исключение" << endl;
		}

		cout << endl << "Блок обновления MU закончен." << endl;

		Sleep(3000);

	}
	else if (objectNum == 7)
	{
		if (!canWriteObject(7))
		{
			string action{ "запись в файл с именем " + getObjectName(7) };

			throw Model::UnauthorizedAccess(getUserSessionName(), action);
		}
		bool exitUPD = false;

		int numberUser, numberObject;

		string newPowers;

		cout << "-----Обновление таблицы MR------" << endl;

		while (true)
		{
			cout << "Введите номер роли, которой хотите изменить права: ";

			cin >> numberUser;

			if (cin.good() && numberUser > 0)
			{
				cin.ignore(30, '\n');

				break;
			}

			cin.clear();

			cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

			cin.ignore(30, '\n');
		}

		while (getRole(numberUser) == NULL)
		{
			string yesNo;

			cout << "Роли с таким номером не существует. Попробовать еще раз?" << endl
				<< "Продолжить обновление(Да/Нет): ";

			cin >> yesNo;

			while (yesNo != "Да" && yesNo != "Нет")
			{
				cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
					<< "Попробуйте еще раз: ";

				cin >> yesNo;
			}

			if (yesNo == "Да")
			{
				cout << "Введите номер роли, которой хотите изменить права: ";
				cin >> numberUser;
			}
			else
			{
				exitUPD = true;

				break;
			}
		}

		if (exitUPD)
			return;

		while (true)
		{
			cout << "Введите номер объекта, права к которому будут выданы: ";

			cin >> numberObject;

			if (cin.good() && numberObject > 0)
			{
				cin.ignore(30, '\n');

				break;
			}

			cin.clear();

			cout << "Вы ввели некорректные данные. Введите положительное число." << endl;

			cin.ignore(30, '\n');
		}

		while (getObject(numberObject) == NULL)
		{
			string yesNo;

			cout << "Объекта с таким номером не существует. Попробовать еще раз?" << endl
				<< "Продолжить обновление(Да/Нет): ";

			cin >> yesNo;

			while (yesNo != "Да" && yesNo != "Нет")
			{
				cout << "Вы ввели некорректные данные. Необходимо значение Да или Нет." << endl
					<< "Попробуйте еще раз: ";

				cin >> yesNo;
			}

			if (yesNo == "Да")
			{
				cout << "Введите номер объекта, права к которому будут выданы: ";
				cin >> numberObject;
			}
			else
			{
				exitUPD = true;

				break;
			}
		}

		if (exitUPD)
			return;

		regex rgpowers{ R"([rweo]*)" };

		while (true)
		{
			cout << "Введите права: ";

			cin >> newPowers;

			if (cin.good() && regex_match(newPowers.begin(), newPowers.end(), rgpowers))
			{
				cin.ignore(30, '\n');

				break;
			}

			cin.clear();

			cout << "Вы ввели некорректные данные. Введите строку из прав: r, w, e, o." << endl;

			cin.ignore(30, '\n');
		}

		try
		{
			updateMR(numberUser, numberObject, newPowers);
		}
		catch (Model::ModelException ex)
		{
			cout << endl << "Произошло исключение" << endl << endl;

			cout << ex.discription << endl;
		}
		catch (exception ex)
		{
			cout << ex.what() << endl;
		}
		catch (...)
		{
			cout << "Произошло исключение" << endl;
		}

		cout << endl << "Блок обновления MU закончен." << endl;

		Sleep(3000);

	}
	else
	{
		cout << "Файл перезаписывается" << endl;
	}	
}

string Model::getObjectPowers(unsigned objectNum)
{
	string resultPower = "";

	vector<unsigned> roles = getUserRoleDescNum(this->role);

	roles.push_back(this->role);

	list<map<string, string, less<string> > > powers;

	string columnsArr[] = { "powers" };

	vector<string> columns{ columnsArr, columnsArr + 1 };

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["object"] = { {"=", to_string(objectNum)} };

	for (int i = 0; i < roles.size(); i++)
	{
		cwhere["role"] = { {"=", to_string(roles[i])} };

		powers = SQL::SELECT(dbName + "MR", columns, cwhere);

		list<map<string, string, less<string> > >::iterator psit = powers.begin();

		while (psit != powers.end())
		{
			string p = (*psit)["powers"];

			if (resultPower.find("r") == string::npos)
			{
				if (p.find("r") != string::npos)
					resultPower += "r";
			}
			
			if (resultPower.find("w") == string::npos)
			{
				if (p.find("w") != string::npos)
					resultPower += "w";
			}
			
			if (resultPower.find("0") == string::npos)
			{
				if (p.find("0") != string::npos)
					resultPower += "0";
			}
			
			if (resultPower.find("e") == string::npos)
			{
				if (p.find("e") != string::npos)
					resultPower += "e";
			}

			psit++;
		}
	}

	Employee *eu = dynamic_cast<Employee *>(this->user);

	list<map<string, string, less<string> > > userPowers;

	map<string, array<string, 2>, less<string> > cwhereu;

	cwhereu["object"] = { {"=", to_string(objectNum)} };
	cwhereu["user"] = { {"=", to_string(eu->getNumber())} };

	userPowers = SQL::SELECT(dbName + "MU", columns, cwhereu);
	
	list<map<string, string, less<string> > >::iterator upit = userPowers.begin();

	while (upit != userPowers.end())
	{
		string p = (*upit)["powers"];

		if (resultPower.find("r") == string::npos)
		{
			if (p.find("r") != string::npos)
				resultPower += "r";
		}
		
		if (resultPower.find("w") == string::npos)
		{
			if (p.find("w") != string::npos)
				resultPower += "w";
		}
		
		if (resultPower.find("0") == string::npos)
		{
			if (p.find("0") != string::npos)
				resultPower += "0";
		}
		
		if (resultPower.find("e") == string::npos)
		{
			if (p.find("e") != string::npos)
				resultPower += "e";
		}

		upit++;
	}

	return resultPower;
}

string Model::getObjectName(unsigned objectNum)
{
	list<map<string, string, less<string> > > objects;

	string columnsArr[] = { "name" };

	vector<string> columns{ columnsArr, columnsArr + 1 };

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["object"] = { {"=", to_string(objectNum)} };

	objects = SQL::SELECT(dbName + "objects", columns, cwhere);

	return (objects.front())["name"];
}

string Model::getRoleName(unsigned roleNum)
{
	list<map<string, string, less<string> > > objects;

	string columnsArr[] = { "description" };

	vector<string> columns{ columnsArr, columnsArr + 1 };

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["role"] = { {"=", to_string(roleNum)} };

	objects = SQL::SELECT(dbName + "roles", columns, cwhere);

	return (objects.front())["description"];
}

vector<map<string, string, less<string> > > Model::getRolePowers(unsigned powers)
{
	vector<map<string, string, less<string> > > powersv;

	unsigned powerNum = 0b1;

	while (powers >= powerNum)
	{
		if ((powers & powerNum) != 0)
		{
			list<map<string, string, less<string> > > powerData;

			string columnsArr[] = {"power", "description" };
			vector<string> columns(columnsArr, columnsArr + 2);

			map<string, array<string, 2>, less<string> > cwhereRD;

			cwhereRD["power"] = { {"=", to_string(powerNum)} };

			powerData = SQL::SELECT(dbName + "powers", columns, cwhereRD);

			map<string, string, less<string> > power = powerData.front();

			powersv.push_back(power);
		}

		powerNum <<= 1;
	}

	return powersv;
}

Person* Model::getUser(unsigned long number)
{
	if (this->user == NULL)
		throw ModelException("Операция получения информации о пользователе недоступна для не авторизованных пользователей.");		

	if (!canReadObject(4))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(4);
		throw UnauthorizedAccess(nameu, action);
	}

	list<map<string, string, less<string> > > selectedUsers;

	string columnsArr[] = { "number", "firstname", "surname", "admin" };
	vector<string> columns(columnsArr, columnsArr + 4);

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["number"] = { {"=", to_string(number)} };

	selectedUsers = SQL::SELECT(dbName, columns, cwhere);

	if (selectedUsers.size() == 0u)
	{
		return NULL;
	}

	map<string, string, less<string> > selectedUser = selectedUsers.front();

	Person *user;

	if (selectedUser["admin"] == "true")
	{
		user = new Admin(selectedUser["firstname"], selectedUser["surname"], stol(selectedUser["number"]));
	}
	else
	{
		user = new Employee(selectedUser["firstname"], selectedUser["surname"], stol(selectedUser["number"]));
	}

	return user;
}

string *Model::getObject(unsigned number)
{
	if (this->user == NULL)
		throw ModelException("Операция получения информации о объекте недоступна для не авторизованных пользователей.");

	if (!canReadObject(8))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(8);
		throw UnauthorizedAccess(nameu, action);
	}

	list<map<string, string, less<string> > > selectedObjects;

	string columnsArr[] = { "name" };
	vector<string> columns(columnsArr, columnsArr + 1);

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["object"] = { {"=", to_string(number)} };

	selectedObjects = SQL::SELECT(dbName + "objects", columns, cwhere);

	if (selectedObjects.size() == 0u)
	{
		return NULL;
	}

	map<string, string, less<string> > selectedObject = selectedObjects.front();

	return new string(selectedObject["name"]);
}

string *Model::getRole(unsigned number)
{
	if (this->user == NULL)
		throw ModelException("Операция получения информации о роли недоступна для не авторизованных пользователей.");

	if (!canReadObject(5))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(5);
		throw UnauthorizedAccess(nameu, action);
	}

	list<map<string, string, less<string> > > selectedRoles;

	string columnsArr[] = { "description" };
	vector<string> columns(columnsArr, columnsArr + 1);

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["role"] = { {"=", to_string(number)} };

	selectedRoles = SQL::SELECT(dbName + "roles", columns, cwhere);

	if (selectedRoles.size() == 0u)
	{
		return NULL;
	}

	map<string, string, less<string> > selectedRole = selectedRoles.front();

	return new string(selectedRole["description"]);
}

vector<Person *> Model::getUsers(map<string, array<string, 2>, less<string> > cwhere)
{
	if (this->user == NULL)
		throw ModelException("Операция получения информации о пользователях недоступна для не авторизованных пользователей.");

	if (!canReadObject(4))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(4);
		throw UnauthorizedAccess(nameu, action);
	}

	if (cwhere.contains("login"))
	{
		transform(cwhere["login"][1].begin(), cwhere["login"][1].end(), cwhere["login"][1].begin(), myTolower);
	}

	if (cwhere.contains("firstname"))
	{
		transform(cwhere["firstname"][1].begin(), cwhere["firstname"][1].end(), cwhere["firstname"][1].begin(), myTolower);

		cwhere["firstname"][1][0] = myToupper(cwhere["firstname"][1][0]);
	}

	if (cwhere.contains("surname"))
	{
		transform(cwhere["surname"][1].begin(), cwhere["surname"][1].end(), cwhere["surname"][1].begin(), myTolower);

		cwhere["surname"][1][0] = myToupper(cwhere["surname"][1][0]);
	}

	list<map<string, string, less<string> > > selectedUsers;

	string columnsArr[] = { "number", "firstname", "surname", "admin" };
	vector<string> columns(columnsArr, columnsArr + 4);

	selectedUsers = SQL::SELECT(dbName, columns, cwhere);

	vector<Person *> persons;

	list<map<string, string, less<string> > >::iterator iterus = selectedUsers.begin();

	while (iterus != selectedUsers.end())
	{
		map<string, string, less<string> > selectedUser = *iterus++;

		Person *user;

		if (selectedUser["admin"] == "true")
		{
			user = new Admin(selectedUser["firstname"], selectedUser["surname"], stol(selectedUser["number"]));
		}
		else
		{
			user = new Employee(selectedUser["firstname"], selectedUser["surname"], stol(selectedUser["number"]));
		}

		persons.push_back(user);
	}

	return persons;
}

list<map<string, string, less<string> > > Model::getAllData()
{
	if (this->user == NULL)
		throw ModelException("Операция получения информации о пользователях недоступна для не авторизованных пользователей.");


	if (!canReadObject(4))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(4);
		throw UnauthorizedAccess(nameu, action);
	}

	list<map<string, string, less<string> > > selectedUsers;

	string columnsArr[] = { "number", "firstname", "surname", "admin", "login", "password", "role"};
	vector<string> columns(columnsArr, columnsArr + 7);

	map<string, array<string, 2>, less<string> > cwhere;

	return SQL::SELECT(dbName, columns, cwhere);
}

list<map<string, string, less<string> > > Model::getAllDataRoles()
{
	if (this->user == NULL)
		throw ModelException("Операция получения информации о ролях недоступна для не авторизованных пользователей.");


	if (!canReadObject(5))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(5);
		throw UnauthorizedAccess(nameu, action);
	}

	string columnsArr[] = { "role", "description", "descendants"};
	vector<string> columns(columnsArr, columnsArr + 3);

	map<string, array<string, 2>, less<string> > cwhere;

	return SQL::SELECT(dbName + "roles", columns, cwhere);
}

list<map<string, string, less<string> > > Model::getAllDataMU()
{
	if (this->user == NULL)
		throw ModelException("Операция получения информации о матрице MU недоступна для не авторизованных пользователей.");


	if (!canReadObject(6))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(6);
		throw UnauthorizedAccess(nameu, action);
	}

	string columnsArr[] = { "user", "object", "powers" };
	vector<string> columns(columnsArr, columnsArr + 3);

	map<string, array<string, 2>, less<string> > cwhere;

	return SQL::SELECT(dbName + "MU", columns, cwhere);
}

list<map<string, string, less<string> > > Model::getAllDataMR()
{
	if (this->user == NULL)
		throw ModelException("Операция получения информации о матрице MR недоступна для не авторизованных пользователей.");


	if (!canReadObject(7))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(7);
		throw UnauthorizedAccess(nameu, action);
	}

	string columnsArr[] = { "role", "object", "powers" };
	vector<string> columns(columnsArr, columnsArr + 3);

	map<string, array<string, 2>, less<string> > cwhere;

	return SQL::SELECT(dbName + "MR", columns, cwhere);
}

list<map<string, string, less<string> > > Model::getAllDataObjects()
{
	if (this->user == NULL)
		throw ModelException("Операция получения информации об объектах недоступна для не авторизованных пользователей.");


	if (!canReadObject(8))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(8);
		throw UnauthorizedAccess(nameu, action);
	}

	string columnsArr[] = {"object", "name" };
	vector<string> columns(columnsArr, columnsArr + 2);

	map<string, array<string, 2>, less<string> > cwhere;

	return SQL::SELECT(dbName + "objects", columns, cwhere);
}

vector<Person *> Model::getUsers()
{
	if (this->user == NULL)
		throw ModelException("Операция получения информации о пользователях недоступна для не авторизованных пользователей.");

	if (!canReadObject(4))
	{
		string nameu = this->user->getFirstname();
		string action = "к чтению файла с именем " + getObjectName(4);
		throw UnauthorizedAccess(nameu, action);
	}

	map<string, array<string, 2>, less<string> > cwhere;

	list<map<string, string, less<string> > > selectedUsers;

	string columnsArr[] = { "number", "firstname", "surname", "admin" };
	vector<string> columns(columnsArr, columnsArr + 4);

	selectedUsers = SQL::SELECT(dbName, columns, cwhere);

	vector<Person *> persons;

	list<map<string, string, less<string> > >::iterator iterus = selectedUsers.begin();

	while (iterus != selectedUsers.end())
	{
		map<string, string, less<string> > selectedUser = *iterus++;

		Person *user;

		if (selectedUser["admin"] == "true")
		{
			user = new Admin(selectedUser["firstname"], selectedUser["surname"], stol(selectedUser["number"]));
		}
		else
		{
			user = new Employee(selectedUser["firstname"], selectedUser["surname"], stol(selectedUser["number"]));
		}

		persons.push_back(user);
	}

	return persons;
}

bool Model::addUser(string login, string password, string firstname, string surname, unsigned long number, bool admin)
{
	if (this->user == NULL)
		throw ModelException("Операция создания пользователя недоступна для не авторизованных пользователей.");

	if (!canWriteObject(4))
	{
		string nameu = this->user->getFirstname();
		string action = "к записи в файл с именем " + getObjectName(4);
		throw UnauthorizedAccess(nameu, action);
	}

	if (!canWriteObject(4))
	{
		string nameu = this->user->getFirstname();
		string action = "к записи в файл с именем " + getObjectName(4);
		throw UnauthorizedAccess(nameu, action);
	}

	map<string, array<string, 2>, less<string> > cwhere;

	transform(login.begin(), login.end(), login.begin(), myTolower);

	//regex rxl{ R"([A-Za-zА-Яа-я\d_.-]{5,})" };

	//if (!regex_match(login.begin(), login.end(), rxl))
	//	throw ModelException("Логин должен состоять из букв русского и латинского алфавита, а также из символов '_', '.', '-'. И быть длиной от 5 символов.");

	cwhere["login"] = { {"=", login} };

	vector<Person *> users = getUsers(cwhere);

	if (users.size() != 0)
	{
		throw ModelException("Логин " + login + " занят. Добавление невозможно.");
	}

	if (getUser(number) != NULL)
	{
		throw ModelException("Пользователь с номером " + to_string(number) + " уже существует. Добавление невозможно.");
	}

	map<string, string, less<string> > user;

	user["login"] = login;

	regex rx{ R"([A-Ja-jА-Иа-и]{8,})" };
	//regex rx{ R"([А-Яа-я\d]{8,})" };

	if (!regex_match(password.begin(), password.end(), rx))
		throw ModelException("Пароль может содержать только десять первых букв русского и латинского алфавитов. И быть длиной от 8 символов.");

	transform(firstname.begin(), firstname.end(), firstname.begin(), myTolower);
	transform(surname.begin(), surname.end(), surname.begin(), myTolower);

	firstname[0] = myToupper(firstname[0]);
	surname[0] = myToupper(surname[0]);

	user["password"] = encryption(password);
	user["firstname"] = firstname;
	user["surname"] = surname;
	user["number"] = to_string(number);

	if (admin)
		user["admin"] = "true";
	else
		user["admin"] = "false";

	return SQL::INSERT("users", user);
}

bool Model::updateUser(unsigned long number, map<string, array<string, 2>, less<string> > columns)
{
	if (this->user == NULL)
		throw ModelException("Операция обновления учетной записи недоступна для не авторизованных пользователей.");


	if (!canWriteObject(4))
	{
		string nameu = this->user->getFirstname();
		string action = "к записи в файл с именем " + getObjectName(4);
		throw UnauthorizedAccess(nameu, action);
	}

	if (columns.contains("number"))
	{
		throw ModelException("Операция изменения номера сотрудника недоступна.");
	}

	if (columns.contains("login"))
	{
		map<string, array<string, 2>, less<string> > cwherel;

		regex rxl{ R"([A-Za-zА-Яа-я\d_.-]{5,})" };

		if (!regex_match(columns["login"][1].begin(), columns["login"][1].end(), rxl))
			throw ModelException("Логин должен состоять из букв русского и латинского алфавита, а также из символов '_', '.', '-'. И быть длиной от 5 символов.");

		transform(columns["login"][1].begin(), columns["login"][1].end(), columns["login"][1].begin(), myTolower);

		cwherel["login"] = { {columns["login"][0],columns["login"][1]}};

		vector<Person *> users = getUsers(cwherel);

		if (users.size() != 0)
		{
			throw ModelException("Логин " + columns["login"][1] + " занят. Обновление невозможно.");
		}
	}

	if (columns.contains("password"))
	{
		string passwordup = columns["password"][1];

		regex rx{ R"([A-Ja-jА-Иа-и]{8,})" };

		if (!regex_match(passwordup.begin(), passwordup.end(), rx))
			throw ModelException("Пароль может содержать только десять первых букв русского и латинского алфавитов. И быть длиной от 8 символов.");

		columns["password"][1] = encryption(columns["password"][1]);
	}

	if (columns.contains("firstname"))
	{
		transform(columns["firstname"][1].begin(), columns["firstname"][1].end(), columns["firstname"][1].begin(), myTolower);

		columns["firstname"][1][0] = myToupper(columns["firstname"][1][0]);
	}

	if (columns.contains("surname"))
	{
		transform(columns["surname"][1].begin(), columns["surname"][1].end(), columns["surname"][1].begin(), myTolower);

		columns["surname"][1][0] = myToupper(columns["surname"][1][0]);
	}

	if (columns.contains("role"))
	{
		unsigned role = getRoleNumber(columns["role"][1]);

		columns["role"][1] = to_string(role);

		if (!userHasRole(number, role))
		{
			list<map<string, string, less<string> > > rsalpha;

			string columnArrR[] = { "sup" };

			vector<string> columnR = { columnArrR, columnArrR + 1 };

			map<string, array<string, 2>, less<string> > cwhereR;

			cwhereR["role"] = { { "=", to_string(role) } };

			rsalpha = SQL::SELECT(dbName + "alpha", columnR, cwhereR);

			map<string, string, less<string> > ralpha = rsalpha.front();

			unsigned rsup = stoi(ralpha["sup"]);

			unsigned rcur = inverseUANum(role);

			if (rcur >= rsup)
			{
				throw ModelException("Достигнут лимит пользователей на роль " + *getRole(stoi(columns["role"][1])));
			}
		}
	}

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["number"] = { { "=", to_string(number)}};

	return SQL::UPDATE(dbName, columns, cwhere);
}

bool Model::updateMU(unsigned un, unsigned on, string powers)
{
	if (this->user == NULL)
		throw ModelException("Операция изменения полномочий пользователя недоступна для не авторизованных пользователей.");

	if (!canWriteObject(6))
	{
		string nameu = this->user->getFirstname();
		string action = "к записи в файл с именем " + getObjectName(6);
		throw UnauthorizedAccess(nameu, action);
	}

	regex rgpowers{ R"([rweo]*)" };

	if (!regex_match(powers.begin(), powers.end(), rgpowers))
	{
		throw ModelException("Не верно задано множество прав: " + powers);
	}

	for (string::iterator power = powers.begin(); power != powers.end(); power++)
	{
		if (!userHasPower(un, on, *power))
		{
			list<map<string, string, less<string> > > psbeta;

			string columnArrR[] = { "sup" };

			vector<string> columnR = { columnArrR, columnArrR + 1 };

			map<string, array<string, 2>, less<string> > cwhereR;

			cwhereR["object"] = { { "=", to_string(on) } };
			cwhereR["power"] = { { "=", string{*power} } };

			psbeta = SQL::SELECT(dbName + "beta", columnR, cwhereR);

			if (psbeta.size() != 0)
			{
				map<string, string, less<string> > pbeta = psbeta.front();

				unsigned psup = stoi(pbeta["sup"]);

				unsigned pcur = countNumPowerObjectMU(on, *power);

				if (pcur >= psup)
				{
					string pex{ *power }, oex{ *getObject(on) };

					throw ModelException("Достигнут лимит пользователей для полномочия " + pex + " к объекту " + oex);
				}
			}
		}
	}

	list<map<string, string, less<string> > > muelems;

	string columnArr[] = { "powers" };

	vector<string> column = { columnArr, columnArr + 1 };

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["user"] = { {"=", to_string(un)} };
	cwhere["object"] = { {"=", to_string(on)} };

	muelems = SQL::SELECT(dbName + "MU", column, cwhere);

	if (muelems.size() == 0)
	{
		map<string, string, less<string> > elemMU;

		elemMU["user"] = to_string(un);
		elemMU["object"] = to_string(on);
		elemMU["powers"] = powers;

		SQL::INSERT(dbName + "MU", elemMU);
	}
	else
	{
		map<string, array<string, 2>, less<string> > columns;

		columns["powers"] = { "=", powers };

		SQL::UPDATE(dbName + "MU", columns, cwhere);
	}

	return true;
}

bool Model::updateMR(unsigned un, unsigned on, string powers)
{
	if (this->user == NULL)
		throw ModelException("Операция изменения прав в роли недоступна для не авторизованных пользователей.");

	if (!canWriteObject(7))
	{
		string nameu = this->user->getFirstname();
		string action = "к записи в файл с именем " + getObjectName(7);
		throw UnauthorizedAccess(nameu, action);
	}

	regex rgpowers{ R"([rweo]*)" };

	if (!regex_match(powers.begin(), powers.end(), rgpowers))
	{
		throw ModelException("Не верно задано множество прав: " + powers);
	}

	list<map<string, string, less<string> > > mrelems;

	string columnArr[] = { "powers" };

	vector<string> column = { columnArr, columnArr + 1 };

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["role"] = { {"=", to_string(un)} };
	cwhere["object"] = { {"=", to_string(on)} };

	mrelems = SQL::SELECT(dbName + "MR", column, cwhere);

	if (mrelems.size() == 0)
	{
		map<string, string, less<string> > elemMR;

		elemMR["role"] = to_string(un);
		elemMR["object"] = to_string(on);
		elemMR["powers"] = powers;

		SQL::INSERT(dbName + "MR", elemMR);
	}
	else
	{
		map<string, array<string, 2>, less<string> > columns;

		columns["powers"] = { "=", powers };

		SQL::UPDATE(dbName + "MR", columns, cwhere);
	}

	return true;
}

unsigned Model::getRoleNumber(string roleDiscription)
{
	list<map<string, string, less<string> > > roles;

	string columnArr[] = { "role" };

	vector<string> column = { columnArr, columnArr + 1 };

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["description"] = { {"=", roleDiscription} };

	roles = SQL::SELECT(dbName + "roles", column, cwhere);

	map<string, string, less<string> > role = roles.front();

	return stoi(role["role"]);
}

bool Model::deleteUser(unsigned long number)
{
	if (this->user == NULL)
		throw ModelException("Операция удаления пользователя недоступна для не авторизованных пользователей.");

	if (!canWriteObject(4))
	{
		string nameu = this->user->getFirstname();
		string action = "к записи в файл с именем " + getObjectName(4);
		throw UnauthorizedAccess(nameu, action);
	}

	if (number == 1)
		throw ModelException("Невозможно удалить пользователя с данным номером.");

	if (getUser(number) == NULL)
		throw ModelException("Пользователь с номером " + to_string(number) + " не существует. Удаление невозможно.");

	map<string, array<string, 2>, less<string> > cwhere;

	cwhere["number"] = { { "=", to_string(number)} };

	SQL::DELETE_ROWS(dbName + "audit", cwhere);

	return SQL::DELETE_ROWS(dbName, cwhere) > 0;
}

bool Model::loginExists(string login)
{
	if (this->user == NULL)
		throw ModelException("Операция аудита недоступна для не авторизованных пользователей.");

	if (typeid(*(this->user)) != typeid(Admin))
		throw UnauthorizedAccess(this->user->getFirstname(), "к данным аудита");

	transform(login.begin(), login.end(), login.begin(), myTolower);

	map<string, array<string, 2>, less<string> > cwherel;

	cwherel["login"] = { {"=",login} };

	vector<Person *> users = getUsers(cwherel);

	return users.size() != 0;
}

bool Model::canReadObject(unsigned objectNum)
{
	if (this->user == NULL)
		throw ModelException("Операция чтения файла недоступна для не авторизованных пользователей.");

	string powers = getObjectPowers(objectNum);

	return powers.find("r") != string::npos;
}

bool Model::canWriteObject(unsigned objectNum)
{
	if (this->user == NULL)
		throw ModelException("Операция записи в файл недоступна для не авторизованных пользователей.");

	string powers = getObjectPowers(objectNum);

	return powers.find("w") != string::npos;
}

string Model::getUserSessionName()
{
	return this->user->getFirstname();
}