#pragma once
#pragma warning (disable:4786)
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>
#include <cstdint>
#include <cstring>
#include <vector>
#include <array>
#include <list>
#include <algorithm>
#include <cctype>
#include <map>

using namespace std;

class SQL
{
private:
	SQL();
	static bool existsFileListOfTables();

	static unsigned int getIndexAttribute(string tableName, string attribute);
	static unsigned int getRowSize(string tableName);

	static const string FILE_LIST_OF_TABLES_NAME;

	static map<string, int, less<string> > getColumnsSize(string tableName);
	static map<string, int, less<string> > getColumnsPosition(string tableName);

	static map<string, string, less<string> > getColumnsType(string tableName);
public:
	static bool CREATE_TABLE(string name, list<array<string,2> > columnDescriptions);
	static bool INSERT(string tableName, map<string, string, less<string> > args);

	static int DELETE_ROWS(string tableName, map<string, array<string, 2>, less<string> > cwhere); // cwhere - column where

	static list<map<string, string, less<string> > > SELECT(string tableName, vector<string> columns, map<string, array<string, 2>, less<string> > cwhere); // cwhere - column where
	
	static bool UPDATE(string tableName, map<string, array<string, 2>, less<string> > columns, map<string, array<string, 2>, less<string> > cwhere);

	static bool existsTable(string tableName);

	static string getDiscriptionTable(string tableName);

	static vector<array<string, 2> > getDiscriptionColumnTable(string tableName);

	class ListOfTablesFileException
	{
	public:
		string discription;
		ListOfTablesFileException(string discription) :
			discription(discription)
		{

		}
	};

	class TableException
	{
	public:
		string tableName;
		string discription;

		TableException(string tableName, string discription) :
			tableName(tableName),
			discription(discription)
		{

		}
	};

	class TypeException
	{
	public:
		string expectedType;
		string passedValue;

		TypeException(string expectedType, string passedValue) :
			expectedType(expectedType),
			passedValue(passedValue)
		{

		}
	};

	class UnknownType
	{
	public:
		string type;
		UnknownType(string type) :
			type(type)
		{

		}
	};

	class InsertException
	{
	public:
		string discription;

		InsertException(string discription) : 
			discription(discription)
		{

		}
	};
};
