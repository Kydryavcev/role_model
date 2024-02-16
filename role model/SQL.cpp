#include "SQL.h"

const string SQL::FILE_LIST_OF_TABLES_NAME = "listOfTables.bin";

bool SQL::existsFileListOfTables()
{
	const filesystem::path pathFileListOfTables{ "Data\\" + SQL::FILE_LIST_OF_TABLES_NAME};

	if (filesystem::exists(pathFileListOfTables))
	{
		return true;
	}

	const filesystem::path pathDirectory{ "Data" };

	if (!filesystem::exists(pathDirectory))
	{
		filesystem::create_directory("Data");
	}

	ofstream fileListOfTables("Data\\" + SQL::FILE_LIST_OF_TABLES_NAME);

	bool result = static_cast<bool>(fileListOfTables);

	fileListOfTables.close();

	return result;
}

unsigned int SQL::getIndexAttribute(string tableName, string attribute)
{
	vector<array<string, 2> > columnsDiscription = getDiscriptionColumnTable(tableName);
	int size = columnsDiscription.size();

	for (int i = 0; i < size; i++)
	{
		string data = columnsDiscription[i][1];
		if (data == attribute)
		{
			return i;
		}
	}

	throw TableException(tableName, "Аттрибута с именем " + attribute + " не существует");
}

bool SQL::existsTable(string name)
{
	if (!existsFileListOfTables())
	{
		cout << "Не удалось открыть файл с описанием таблиц базы данных." << endl;

		throw ListOfTablesFileException("не удалось открыть файл");
	}

	ifstream listOfTables{ "Data\\" + FILE_LIST_OF_TABLES_NAME, ios::binary };

	while (listOfTables)
	{
		int tableDescriptionSize;

		listOfTables.read(reinterpret_cast<char *>(&tableDescriptionSize), sizeof(tableDescriptionSize));

		if (!listOfTables) // если  файл пуст
		{
			return false;
		}

		char *dicriptionTableChar = new char[tableDescriptionSize];

		listOfTables.read(dicriptionTableChar, tableDescriptionSize);

		char *token, *next_token;

		token = strtok_s(dicriptionTableChar, " ", &next_token);

		string nameTable{ token };		
		
		delete[]dicriptionTableChar;

		if (nameTable == name)
		{
			return true;
		}
	}

	return false;
}

string SQL::getDiscriptionTable(string name)
{
	if (!existsFileListOfTables())
	{
		cout << "Не удалось открыть файл с описанием таблиц базы данных." << endl;

		throw ListOfTablesFileException("не удалось открыть файл");
	}

	ifstream listOfTables{ "Data\\" + FILE_LIST_OF_TABLES_NAME, ios::binary };

	char *dicriptionTableChar;

	while (listOfTables)
	{
		int tableDescriptionSize;

		listOfTables.read(reinterpret_cast<char *>(&tableDescriptionSize), sizeof(tableDescriptionSize));

		if (!listOfTables) // если  файл пуст
		{
			throw TableException(name, "таблицы с названием " + name + " не существует");
		}

		dicriptionTableChar = new char[tableDescriptionSize];

		listOfTables.read(dicriptionTableChar, tableDescriptionSize);

		char *token, *next_token;

		token = strtok_s(dicriptionTableChar, " ", &next_token);

		string nameTable{ token };

		if (nameTable == name)
		{
			char *discriptionColumnTableToken = strtok_s(NULL, "\0", &next_token);

			if (discriptionColumnTableToken == NULL)
			{
				throw TableException(name, "описание столбцов таблицы повреждено");
			}

			int discriptionColumnTableSize = tableDescriptionSize - nameTable.size();

			char *discriptionColumnTable = new char[discriptionColumnTableSize];

			strcpy_s(discriptionColumnTable, discriptionColumnTableSize, discriptionColumnTableToken);

			string discription(discriptionColumnTable);

			delete[]dicriptionTableChar;

			delete[]discriptionColumnTable;

			return discription;
		}

		delete[]dicriptionTableChar;
	}

	throw TableException(name, "таблицы с названием " + name + " не существует");
}

vector<array<string,2> > SQL::getDiscriptionColumnTable(string tableName)
{
	string discriptionTableString = getDiscriptionTable(tableName);

	vector<array<string, 2> > columnsDiscription;

	char *columnDiscription, *nextColumnDiscription = NULL, *columnType, *columnName = NULL;

	int columnCounter = 0;

	char *discriptionTable = new char[discriptionTableString.size() + 1];

	strcpy_s(discriptionTable, discriptionTableString.size() + 1, discriptionTableString.c_str());

	columnDiscription = strtok_s(discriptionTable, ",\0", &nextColumnDiscription);

	while (columnDiscription)
	{

		columnType = strtok_s(columnDiscription, " ", &columnName);

		array<string, 2> columnTypeAndName;

		columnTypeAndName[0] = columnType;
		columnTypeAndName[1] = columnName;

		columnsDiscription.push_back(columnTypeAndName);

		columnDiscription = strtok_s(NULL, ",\0", &nextColumnDiscription);
	}

	delete[]discriptionTable;

	return columnsDiscription;
}

map<string, int, less<string> > SQL::getColumnsSize(string tableName)
{
	map <string, int, less<string> > columnsSize;

	vector<array<string, 2> > discriptionColumns = getDiscriptionColumnTable(tableName);

	for (unsigned int i = 0; i < discriptionColumns.size(); i++)
	{
		if (discriptionColumns[i][0] == "int")
		{
			columnsSize[discriptionColumns[i][1]] = sizeof(int);
		}
		else if (discriptionColumns[i][0] == "float")
		{
			columnsSize[discriptionColumns[i][1]] = sizeof(float);
		}
		else if (discriptionColumns[i][0] == "double")
		{
			columnsSize[discriptionColumns[i][1]] = sizeof(double);
		}
		else if (discriptionColumns[i][0] == "bool")
		{
			columnsSize[discriptionColumns[i][1]] = sizeof(char);
		}
		else if (discriptionColumns[i][0] == "char(20)") // сделать регулярное выражение, для выделения длины строки
		{
			columnsSize[discriptionColumns[i][1]] = sizeof(char) * 20;
		}
		else if (discriptionColumns[i][0] == "char(100)") // сделать регулярное выражение, для выделения длины строки
		{
			columnsSize[discriptionColumns[i][1]] = sizeof(char) * 100;
		}
		else
		{
			throw UnknownType(discriptionColumns[i][0]);
		}
	}

	return columnsSize;
}

map<string, int, less<string> > SQL::getColumnsPosition(string tableName)
{
	unsigned int position = 0;

	map <string, int, less<string> > columnsPosition;

	vector<array<string, 2> > discriptionColumns = getDiscriptionColumnTable(tableName);

	for (unsigned int i = 0; i < discriptionColumns.size(); i++)
	{
		if (discriptionColumns[i][0] == "int")
		{
			columnsPosition[discriptionColumns[i][1]] = position;

			position += sizeof(int);
		}
		else if (discriptionColumns[i][0] == "float")
		{
			columnsPosition[discriptionColumns[i][1]] = position;

			position += sizeof(float);
		}
		else if (discriptionColumns[i][0] == "double")
		{
			columnsPosition[discriptionColumns[i][1]] = position;

			position += sizeof(double);
		}
		else if (discriptionColumns[i][0] == "bool")
		{
			columnsPosition[discriptionColumns[i][1]] = position;

			position += sizeof(char);
		}
		else if (discriptionColumns[i][0] == "char(20)") // сделать регулярное выражение, для выделения длины строки
		{
			columnsPosition[discriptionColumns[i][1]] = position;
			position += sizeof(char) * 20;
		}
		else if (discriptionColumns[i][0] == "char(100)") // сделать регулярное выражение, для выделения длины строки
		{
			columnsPosition[discriptionColumns[i][1]] = position;
			position += sizeof(char) * 100;
		}
		else
		{
			throw UnknownType(discriptionColumns[i][0]);
		}
	}

	return columnsPosition;
}

map<string, string, less<string> > SQL::getColumnsType(string tableName)
{
	map<string, string, less<string> > columnsType;

	vector<array<string, 2> > discriptionColumns = getDiscriptionColumnTable(tableName);

	for (unsigned int i = 0; i < discriptionColumns.size(); i++)
	{
		columnsType[discriptionColumns[i][1]] = discriptionColumns[i][0];
	}

	return columnsType;
}

unsigned int SQL::getRowSize(string tableName)
{
	int rowSize = 0;

	vector<array<string, 2> > discriptionColumns = getDiscriptionColumnTable(tableName);

	for (unsigned int i = 0; i < discriptionColumns.size(); i++)
	{
		if (discriptionColumns[i][0] == "int")
		{
			rowSize += sizeof(int);
		}
		else if (discriptionColumns[i][0] == "float")
		{
			rowSize += sizeof(float);
		}
		else if (discriptionColumns[i][0] == "double")
		{
			rowSize += sizeof(double);
		}
		else if (discriptionColumns[i][0] == "bool")
		{
			rowSize += sizeof(char);
		}
		else if (discriptionColumns[i][0] == "char(20)") // сделать регулярное выражение, для выделения длины строки
		{
			rowSize += sizeof(char) * 20;
		}
		else if (discriptionColumns[i][0] == "char(100)") // сделать регулярное выражение, для выделения длины строки
		{
			rowSize += sizeof(char) * 100;
		}
		else
		{
			throw UnknownType(discriptionColumns[i][0]);
		}
	}

	return rowSize;
}

bool SQL::CREATE_TABLE(string name, list<array<string, 2> > columnDescriptions)
{
	if (!existsFileListOfTables())
	{
		throw ListOfTablesFileException("Не удалось открыть файл с описанием таблиц базы данных.");
	}

	if (existsTable(name))
	{
		return false;
	}

	int numColums = columnDescriptions.size();

	if (numColums == 0)
	{
		throw TableException(name, "При создании таблицы не определен ни один столбец.");
	}

	string tableDescription = name + " ";

	list<array<string, 2> >::iterator iter = columnDescriptions.begin();
	list<string> names;

	while (iter != columnDescriptions.end())
	{
 		if ((*iter)[1] == "")
		{
			throw TableException(name, "Имя столбца не задано.");
		}
		else
		{
			if (!names.empty() && find(names.begin(), names.end(), (*iter)[1]) != names.end())
			{

				string namecolumn((*iter)[1]);
				throw TableException(name, "Задано два столбца с одинаковым именем " + (*iter)[1] + ".");
			}

			names.push_back((*iter)[1]);
		}

		if ((*iter)[0] == "int")
		{
			tableDescription += "int " + (*iter++)[1] + ",";
		}
		else if ((*iter)[0] == "float")
		{
			tableDescription += "float " + (*iter++)[1] + ",";
		}
		else if ((*iter)[0] == "double")
		{
			tableDescription += "double " + (*iter++)[1] + ",";
		}
		else if ((*iter)[0] == "bool")
		{
			tableDescription += "bool " + (*iter++)[1] + ",";
		}
		else if ((*iter)[0] == "char(20)") // сделать регулярное выражение, для выделения длины строки
		{
			tableDescription += "char(20) " + (*iter++)[1] + ",";
		}
		else if ((*iter)[0] == "char(100)") // сделать регулярное выражение, для выделения длины строки
		{
			tableDescription += "char(100) " + (*iter++)[1] + ",";
		}
		else
		{
			throw UnknownType((*iter)[0]);
		}
	}

	tableDescription += '\0';

	int tableDescriptionSize = sizeof(char) * tableDescription.length();

	ofstream tableFile{ "Data\\" + name + ".bin", ios::binary };

	if (!tableFile)
	{
		throw TableException(name, "Не удалось создать файл описывающий таблицу.");
	}

	tableFile.close();

	ofstream listOfTables{ "Data\\" + FILE_LIST_OF_TABLES_NAME, ios::binary | ios::app };

	listOfTables.write(reinterpret_cast<char *>(&tableDescriptionSize), sizeof(int));
	listOfTables.write(tableDescription.c_str(), tableDescriptionSize);

	cout << "Таблица успешно создана." << endl;

	return true;
}

bool SQL::INSERT(string tableName, map<string, string, less<string> > args)
{
	if (!existsTable(tableName))
		throw TableException(tableName, "таблицы с названием " + tableName + " не существует");

	vector<array<string, 2> > columnsDiscription = getDiscriptionColumnTable(tableName);

	int csdSize = columnsDiscription.size();
	int columnCounter = columnsDiscription.size();

	vector<array<string, 2> >::iterator iterdisc = columnsDiscription.begin();

	while (iterdisc != columnsDiscription.end())
	{
		if (!args.contains((*iterdisc)[1]))
			throw InsertException("При создание нового предложения не указан аттрибут: " + (*iterdisc)[1]);

		if ((*iterdisc)[0] == "int")
		{
			try
			{
				stoi(args[(*iterdisc)[1]]);
			}
			catch (const std::invalid_argument)
			{
				throw TypeException("int", args[(*iterdisc)[1]]);
			}
			catch (const std::out_of_range)
			{
				throw TypeException("int", "Привышен диапазон значений.");
			}
		}
		else if ((*iterdisc)[0] == "float")
		{
			try
			{
				stof(args[(*iterdisc)[1]]);
			}
			catch (const std::invalid_argument)
			{
				throw TypeException("float", args[(*iterdisc)[1]]);
			}
			catch (const std::out_of_range)
			{
				throw TypeException("float", "Привышен диапазон значений.");
			}
		}
		else if ((*iterdisc)[0] == "double")
		{
			try
			{
				stod(args[(*iterdisc)[1]]);
			}
			catch (const std::invalid_argument)
			{
				throw TypeException("double", args[(*iterdisc)[1]]);
			}
			catch (const std::out_of_range)
			{
				throw TypeException("double", "Привышен диапазон значений.");
			}
		}
		else if ((*iterdisc)[0] == "bool")
		{
			if (!(string{ args[(*iterdisc)[1]] } == "false") && !(string{ args[(*iterdisc)[1]] } == "true"))
			{
				throw TypeException("bool", args[(*iterdisc)[1]]);
			}
		}
		else if ((*iterdisc)[0] == "char(20)") // сделать регулярное выражение, для выделения длины строки
		{
			if (args[(*iterdisc)[1]].size() > 19)
			{
				args[(*iterdisc)[1]] = args[(*iterdisc)[1]].substr(0, 19);
			}
		}
		else if ((*iterdisc)[0] == "char(100)") // сделать регулярное выражение, для выделения длины строки
		{
			if (args[(*iterdisc)[1]].size() > 99)
			{
				args[(*iterdisc)[1]] = args[(*iterdisc)[1]].substr(0, 99);
			}
		}
		
		iterdisc++;
	}

	ofstream tableFile{ "Data\\" + tableName + ".bin", ios::binary | ios::app };

	if (!tableFile)
		throw TableException(tableName, "При открытии файла, описывающего таблицу, произошла ошибка.");

	iterdisc = columnsDiscription.begin();

	while (iterdisc != columnsDiscription.end())
	{
		if ((*iterdisc)[0] == "int")
		{
			int value = stoi(string{ args[(*iterdisc)[1]] });
			tableFile.write(reinterpret_cast<char *>(&value), sizeof(int));
		}
		else if ((*iterdisc)[0] == "float")
		{
			float value = stof(string{ args[(*iterdisc)[1]] });
			tableFile.write(reinterpret_cast<char *>(&value), sizeof(float));
		}
		else if ((*iterdisc)[0] == "double")
		{
			double value = stod(string{ args[(*iterdisc)[1]] });
			tableFile.write(reinterpret_cast<char *>(&value), sizeof(double));
		}
		else if ((*iterdisc)[0] == "bool")
		{
			char value = 0;

			if (args[(*iterdisc)[1]] == "false")
			{
				value = 0;
			}
			else if (args[(*iterdisc)[1]] == "true")
			{
				value = 1;
			}
			else
			{
				tableFile.close();
				throw TypeException("bool", args[(*iterdisc)[1]]);
			}

			tableFile.write(reinterpret_cast<char *>(&value), sizeof(char));
		}
		else if ((*iterdisc)[0] == "char(20)") // сделать регулярное выражение, для выделения длины строки
		{
			char value[20];

			strcpy_s(value, 20, args[(*iterdisc)[1]].c_str());

			tableFile.write(reinterpret_cast<char *>(value), sizeof(char) * 20);
		}
		else if ((*iterdisc)[0] == "char(100)") // сделать регулярное выражение, для выделения длины строки
		{
			char value[100];

			strcpy_s(value, 100, args[(*iterdisc)[1]].c_str());

			tableFile.write(reinterpret_cast<char *>(value), sizeof(char) * 100);
		}
		else
		{
			tableFile.close();
			throw UnknownType((*iterdisc)[0]);
		}

		iterdisc++;
	}

	tableFile.close();

	return true;
}

bool SQL::UPDATE(string tableName, map<string, array<string, 2>, less<string> > columns, map<string, array<string, 2>, less<string> > cwhere)
{
	if (!existsTable(tableName))
		throw TableException(tableName, "таблицы с названием " + tableName + " не существует");

	bool result = false;

	vector<string> columnsWhere;

	map<string, array<string, 2>, less<string> >::iterator itercwhere = cwhere.begin();

	while (itercwhere != cwhere.end())
	{
		columnsWhere.push_back((*itercwhere++).first);
	}

	map<string, int, less<string> > columnsPosition = getColumnsPosition(tableName);
	map<string, int, less<string> > columnsSize = getColumnsSize(tableName);

	map<string, string, less<string> > columnsType = getColumnsType(tableName);



	map<string, array<string, 2>, less<string> >::iterator itercol = columns.begin();

	while (itercol != columns.end())
	{
		string columnType = columnsType[(*itercol).first];

		if (columnType == "int")
		{
			try
			{
				stoi(((*itercol).second)[1]);
			}
			catch (const std::invalid_argument)
			{
				throw TypeException("int", ((*itercol).second)[1]);
			}
			catch (const std::out_of_range)
			{
				throw TypeException("int", "Привышен диапазон значений.");
			}
		}
		else if (columnType == "float")
		{
			try
			{
				stof(((*itercol).second)[1]);
			}
			catch (const std::invalid_argument)
			{
				throw TypeException("float", ((*itercol).second)[1]);
			}
			catch (const std::out_of_range)
			{
				throw TypeException("float", "Привышен диапазон значений.");
			}
		}
		else if (columnType == "double")
		{
			try
			{
				stod(((*itercol).second)[1]);
			}
			catch (const std::invalid_argument)
			{
				throw TypeException("double", ((*itercol).second)[1]);
			}
			catch (const std::out_of_range)
			{
				throw TypeException("double", "Привышен диапазон значений.");
			}
		}
		else if (columnType == "bool")
		{
			if (!(((*itercol).second)[1] == "false") && !(((*itercol).second)[1] == "true"))
			{
				throw TypeException("bool", ((*itercol).second)[1]);
			}
		}
		else if (columnType == "char(20)") // сделать регулярное выражение, для выделения длины строки
		{
			if ((((*itercol).second)[1]).size() > 19)
			{
				((*itercol).second)[1] = (((*itercol).second)[1]).substr(0, 19);
			}
		}
		else if (columnType == "char(100)") // сделать регулярное выражение, для выделения длины строки
		{
			if ((((*itercol).second)[1]).size() > 99)
			{
				((*itercol).second)[1] = (((*itercol).second)[1]).substr(0, 99);
			}
		}

		itercol++;
	}

	fstream table;
	table.open("Data\\" + tableName + ".bin", ios::out | ios::in | ios::binary);

	table.seekg(0);

	unsigned long long positionInTable = 0;

	while (table)
	{
		bool update = true;

		for (unsigned int i = 0; i < columnsWhere.size(); i++)
		{
			int columnPosition = columnsPosition[columnsWhere[i]];

			table.seekg(positionInTable + columnPosition);

			string typeColumn = columnsType[columnsWhere[i]];

			if (typeColumn == "int")
			{
				int valueWhere;

				try
				{
					valueWhere = stoi(cwhere[columnsWhere[i]][1]);
				}
				catch (const std::invalid_argument)
				{
					throw TypeException("int", cwhere[columnsWhere[i]][1]);
				}
				catch (const std::out_of_range)
				{
					throw TypeException("int", "Привышен диапазон значений.");
				}

				int value;
				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && value <= valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && value < valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && value >= valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && value > valueWhere)
				{
					update = false;
				}
			}
			else if (typeColumn == "float")
			{
				float valueWhere;

				try
				{
					valueWhere = stof(cwhere[columnsWhere[i]][1]);
				}
				catch (const std::invalid_argument)
				{
					throw TypeException("float", cwhere[columnsWhere[i]][1]);
				}
				catch (const std::out_of_range)
				{
					throw TypeException("float", "Привышен диапазон значений.");
				}

				float value;
				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && value <= valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && value < valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && value >= valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && value > valueWhere)
				{
					update = false;
				}
			}
			else if (typeColumn == "double")
			{
				double valueWhere;

				try
				{
					valueWhere = stod(cwhere[columnsWhere[i]][1]);
				}
				catch (const std::invalid_argument)
				{
					throw TypeException("double", cwhere[columnsWhere[i]][1]);
				}
				catch (const std::out_of_range)
				{
					throw TypeException("double", "Привышен диапазон значений.");
				}

				double value;
				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && value <= valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && value < valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && value >= valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && value > valueWhere)
				{
					update = false;
				}
			}
			else if (typeColumn == "bool")
			{
				char valueWhere;

				if (cwhere[columnsWhere[i]][1] == "false")
				{
					valueWhere = 0;
				}
				else if (cwhere[columnsWhere[i]][1] == "true")
				{
					valueWhere = 1;
				}
				else
				{
					throw TypeException("bool", cwhere[columnsWhere[i]][1]);
				}

				char value;

				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (value != 0) value = 1;

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					update = false;
				}
			}
			else if (typeColumn == "char(20)") // сделать регулярное выражение, для выделения длины строки
			{
				char value[20];

				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && string(value) != cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && string(value) == cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && string(value) <= cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && string(value) < cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && string(value) >= cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && string(value) > cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
			}
			else if (typeColumn == "char(100)") // сделать регулярное выражение, для выделения длины строки
			{
				char value[100];

				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && string(value) != cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && string(value) == cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && string(value) <= cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && string(value) < cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && string(value) >= cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && string(value) > cwhere[columnsWhere[i]][1])
				{
					update = false;
				}
			}
			else
			{
				throw UnknownType(typeColumn);
			}

			if (!update) break;
		}

		if (!update)
		{
			positionInTable += getRowSize(tableName);

			table.seekg(positionInTable);

			table.get(); // для обноружения конца файла

			continue;
		}

		itercol = columns.begin();

		while (itercol != columns.end())
		{
			int columnPosition = columnsPosition[(*itercol).first];
			string columnType  = columnsType[(*itercol).first];

			if (columnType == "int")
			{
				int valueFile, value = stoi(((*itercol).second)[1]);

				table.seekg(positionInTable + columnPosition);

				table.read(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);


				if (((*itercol).second)[0] == "=")
				{
					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&value), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "+=")
				{
					valueFile += value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "-=")
				{
					valueFile -= value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "*=")
				{
					valueFile *= value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "/=")
				{
					valueFile /= value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
			}
			else if (columnType == "float")
			{
				float valueFile, value = stof(((*itercol).second)[1]);

				table.seekg(positionInTable + columnPosition);

				table.read(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);


				if (((*itercol).second)[0] == "=")
				{
					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&value), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "+=")
				{
					valueFile += value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "-=")
				{
					valueFile -= value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "*=")
				{
					valueFile *= value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "/=")
				{
					valueFile /= value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
			}
			else if (columnType == "double")
			{
				double valueFile, value = stod(((*itercol).second)[1]);

				table.seekg(positionInTable + columnPosition);

				table.read(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);


				if (((*itercol).second)[0] == "=")
				{
					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&value), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "+=")
				{
					valueFile += value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "-=")
				{
					valueFile -= value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "*=")
				{
					valueFile *= value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
				else if (((*itercol).second)[0] == "/=")
				{
					valueFile /= value;

					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&valueFile), columnsSize[(*itercol).first]);
				}
			}
			else if (columnType == "bool")
			{
				char value = 0;

				if (((*itercol).second)[1] == "false")
				{
					value = 0;
				}
				else if (((*itercol).second)[1] == "true")
				{
					value = 1;
				}
				else
				{
					throw TypeException("bool", ((*itercol).second)[1]);
				}

				if (((*itercol).second)[0] == "=")
				{
					table.seekp(positionInTable + columnPosition);

					table.write(reinterpret_cast<char *>(&value), columnsSize[(*itercol).first]);
				}
			}
			else if (columnType == "char(20)") // сделать регулярное выражение, для выделения длины строки
			{
				char value[20];

				strcpy_s(value, 20, (((*itercol).second)[1]).c_str());

				table.seekp(positionInTable + columnPosition);

				table.write(reinterpret_cast<char *>(value), columnsSize[(*itercol).first]);
			}
			else if (columnType == "char(100)") // сделать регулярное выражение, для выделения длины строки
			{
				char value[100];

				strcpy_s(value, 100, (((*itercol).second)[1]).c_str());

				table.seekp(positionInTable + columnPosition);

				table.write(reinterpret_cast<char *>(value), columnsSize[(*itercol).first]);
			}
			else
			{
				throw UnknownType(columnType);
			}

			itercol++;
		}

		result = true;

		positionInTable += getRowSize(tableName);

		table.seekg(positionInTable);

		table.get(); // для обноружения конца файла
	}

	table.close();

	return result;
}

int SQL::DELETE_ROWS(string tableName, map<string, array<string, 2>, less<string> > cwhere)
{
	if (!existsTable(tableName))
		throw TableException(tableName, "таблицы с названием " + tableName + " не существует");

	int numberRowsDeleted = 0;

	vector<string> columnsWhere;

	map<string, array<string, 2>, less<string> >::iterator itercwhere = cwhere.begin();

	while (itercwhere != cwhere.end())
	{
		columnsWhere.push_back((*itercwhere++).first);
	}

	map<string, int, less<string> > columnsPosition = getColumnsPosition(tableName);
	map<string, int, less<string> > columnsSize = getColumnsSize(tableName);

	map<string, string, less<string> > columnsType = getColumnsType(tableName);

	fstream table;
	table.open("Data\\" + tableName + ".bin", ios::out | ios::in | ios::binary);

	table.seekg(0);
	//table.seekp(0);

	unsigned long long positionInTable = 0, lastRowPositionEnd = 0;

	while (table)
	{
		bool deleteRow = true;

		for (unsigned int i = 0; i < columnsWhere.size(); i++)
		{
			int columnPosition = columnsPosition[columnsWhere[i]];

			table.seekg(positionInTable + columnPosition);

			string typeColumn = columnsType[columnsWhere[i]];

			if (typeColumn == "int")
			{
				int valueWhere;

				try
				{
					valueWhere = stoi(cwhere[columnsWhere[i]][1]);
				}
				catch (const std::invalid_argument)
				{
					throw TypeException("int", cwhere[columnsWhere[i]][1]);
				}
				catch (const std::out_of_range)
				{
					throw TypeException("int", "Привышен диапазон значений.");
				}

				int value;
				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && value <= valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && value < valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && value >= valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && value > valueWhere)
				{
					deleteRow = false;
				}
			}
			else if (typeColumn == "float")
			{
				float valueWhere;

				try
				{
					valueWhere = stof(cwhere[columnsWhere[i]][1]);
				}
				catch (const std::invalid_argument)
				{
					throw TypeException("float", cwhere[columnsWhere[i]][1]);
				}
				catch (const std::out_of_range)
				{
					throw TypeException("float", "Привышен диапазон значений.");
				}

				float value;
				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && value <= valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && value < valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && value >= valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && value > valueWhere)
				{
					deleteRow = false;
				}
			}
			else if (typeColumn == "double")
			{
				double valueWhere;

				try
				{
					valueWhere = stod(cwhere[columnsWhere[i]][1]);
				}
				catch (const std::invalid_argument)
				{
					throw TypeException("double", cwhere[columnsWhere[i]][1]);
				}
				catch (const std::out_of_range)
				{
					throw TypeException("double", "Привышен диапазон значений.");
				}

				double value;
				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && value <= valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && value < valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && value >= valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && value > valueWhere)
				{
					deleteRow = false;
				}
			}
			else if (typeColumn == "bool")
			{
				char valueWhere;

				if (cwhere[columnsWhere[i]][1] == "false")
				{
					valueWhere = 0;
				}
				else if (cwhere[columnsWhere[i]][1] == "true")
				{
					valueWhere = 1;
				}
				else
				{
					throw TypeException("bool", cwhere[columnsWhere[i]][1]);
				}

				char value;

				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (value != 0) value = 1;

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					deleteRow = false;
				}
			}
			else if (typeColumn == "char(20)") // сделать регулярное выражение, для выделения длины строки
			{
				char value[20];

				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && string(value) != cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && string(value) == cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && string(value) <= cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && string(value) < cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && string(value) >= cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && string(value) > cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
			}
			else if (typeColumn == "char(100)") // сделать регулярное выражение, для выделения длины строки
			{
				char value[100];

				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && string(value) != cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && string(value) == cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && string(value) <= cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && string(value) < cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && string(value) >= cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && string(value) > cwhere[columnsWhere[i]][1])
				{
					deleteRow = false;
				}
			}
			else
			{
				throw UnknownType(typeColumn);
			}

			if (!deleteRow) break;
		}

		if (!deleteRow)
		{
			if (positionInTable != lastRowPositionEnd)
			{
				table.seekg(positionInTable);

				char *buffer = new char[getRowSize(tableName)];

				table.read(reinterpret_cast<char *>(buffer), getRowSize(tableName));

				table.seekp(lastRowPositionEnd);

				table.write(reinterpret_cast<char *>(buffer), getRowSize(tableName));

				delete[]buffer;
			}

			positionInTable += getRowSize(tableName);
			lastRowPositionEnd += getRowSize(tableName);

			table.seekg(positionInTable);

			table.get(); // для обноружения конца файла

			continue;
		}

		numberRowsDeleted++;

		positionInTable += getRowSize(tableName);

		table.seekg(positionInTable);

		table.get(); // для обноружения конца файла
	}

	table.close();

	filesystem::resize_file("Data\\" + tableName + ".bin", lastRowPositionEnd);

	return numberRowsDeleted;
}

list<map<string, string, less<string> > > SQL::SELECT(string tableName, vector<string> columns, map<string, array<string, 2>, less<string> > cwhere)
{
	if (!existsTable(tableName))
		throw TableException(tableName, "таблицы с названием " + tableName + " не существует");

	list<map<string, string, less<string> > > data;

	if (columns.size() == 0)
	{
		return data;
	}

	if (filesystem::file_size("Data\\" + tableName + ".bin") == 0)
	{
		return data;
	}

	vector<string> columnsWhere;

	map<string, array<string, 2>, less<string> >::iterator itercwhere = cwhere.begin();

	while (itercwhere != cwhere.end())
	{
		columnsWhere.push_back((*itercwhere++).first);
	}

	map<string, int, less<string> > columnsPosition = getColumnsPosition(tableName);
	map<string, int, less<string> > columnsSize     = getColumnsSize(tableName);

	map<string, string, less<string> > columnsType  = getColumnsType(tableName);

	ifstream table("Data\\" + tableName + ".bin", ios::binary);

	unsigned long long positionInTable = 0;

	while (table)
	{
		bool read = true;

		for (unsigned int i = 0; i < columnsWhere.size(); i++)
		{
			int columnPosition = columnsPosition[columnsWhere[i]];

			table.seekg(positionInTable + columnPosition);

			string typeColumn = columnsType[columnsWhere[i]];

			if (typeColumn == "int")
			{
				int valueWhere;

				try
				{
					valueWhere = stoi(cwhere[columnsWhere[i]][1]);
				}
				catch (const std::invalid_argument)
				{
					table.close();
					throw TypeException("int", cwhere[columnsWhere[i]][1]);
				}
				catch (const std::out_of_range)
				{
					table.close();
					throw TypeException("int", "Привышен диапазон значений.");
				}

				int value;
				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && value <= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && value < valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && value >= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && value > valueWhere)
				{
					read = false;
				}
			}
			else if (typeColumn == "float")
			{
				float valueWhere;

				try
				{
					valueWhere = stof(cwhere[columnsWhere[i]][1]);
				}
				catch (const std::invalid_argument)
				{
					table.close();
					throw TypeException("float", cwhere[columnsWhere[i]][1]);
				}
				catch (const std::out_of_range)
				{
					table.close();
					throw TypeException("float", "Привышен диапазон значений.");
				}

				float value;
				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && value <= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && value < valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && value >= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && value > valueWhere)
				{
					read = false;
				}
			}
			else if (typeColumn == "double")
			{
				double valueWhere;

				try
				{
					valueWhere = stod(cwhere[columnsWhere[i]][1]);
				}
				catch (const std::invalid_argument)
				{
					table.close();
					throw TypeException("double", cwhere[columnsWhere[i]][1]);
				}
				catch (const std::out_of_range)
				{
					table.close();
					throw TypeException("double", "Привышен диапазон значений.");
				}

				double value;
				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && value <= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && value < valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && value >= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && value > valueWhere)
				{
					read = false;
				}
			}
			else if (typeColumn == "bool")
			{
				char valueWhere;

				if (cwhere[columnsWhere[i]][1] == "false")
				{
					valueWhere = 0;
				}
				else if (cwhere[columnsWhere[i]][1] == "true")
				{
					valueWhere = 1;
				}
				else
				{
					table.close();
					throw TypeException("bool", cwhere[columnsWhere[i]][1]);
				}

				char value;

				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				if (value != 0) value = 1;

				if (cwhere[columnsWhere[i]][0] == "=" && value != valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && value == valueWhere)
				{
					read = false;
				}
			}
			else if (typeColumn == "char(20)") // сделать регулярное выражение, для выделения длины строки
			{
				char value[20];

				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				string valueFile(value);
				string valueWhere(cwhere[columnsWhere[i]][1]);

				if (cwhere[columnsWhere[i]][0] == "=" && valueFile != valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && valueFile == valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && valueFile <= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && valueFile < valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && valueFile >= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && valueFile > valueWhere)
				{
					read = false;
				}
			}
			else if (typeColumn == "char(100)") // сделать регулярное выражение, для выделения длины строки
			{
				char value[100];

				table.read(reinterpret_cast<char *>(&value), columnsSize[columnsWhere[i]]);

				string valueFile(value);
				string valueWhere(cwhere[columnsWhere[i]][1]);

				if (cwhere[columnsWhere[i]][0] == "=" && valueFile != valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && valueFile == valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && valueFile <= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && valueFile < valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && valueFile >= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && valueFile > valueWhere)
				{
					read = false;
				}if (cwhere[columnsWhere[i]][0] == "=" && valueFile != valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "!=" && valueFile == valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">" && valueFile <= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == ">=" && valueFile < valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<" && valueFile >= valueWhere)
				{
					read = false;
				}
				else if (cwhere[columnsWhere[i]][0] == "<=" && valueFile > valueWhere)
				{
					read = false;
				}
			}
			else
			{
				table.close();
				throw UnknownType(typeColumn);
			}

			if (!read) break;
		}

		if (!read)
		{
			positionInTable += getRowSize(tableName);

			table.seekg(positionInTable);

			table.get(); // для обноружения конца файла

			continue;
		}

		map<string, string, less<string> > rowData;

		for (unsigned int i = 0; i < columns.size(); i++)
		{
			string typeColumn = columnsType[columns[i]];

			int columnPosition = columnsPosition[columns[i]];

			table.seekg(positionInTable + columnPosition);

			if (typeColumn == "int")
			{
				int value;

				int sizelk = columnsSize[columns[i]];

				table.read(reinterpret_cast<char *>(&value), columnsSize[columns[i]]);

				rowData[columns[i]] = to_string(value);
			}
			else if (typeColumn == "float")
			{
				float value;

				table.read(reinterpret_cast<char *>(&value), columnsSize[columns[i]]);

				rowData[columns[i]] = to_string(value);
			}
			else if (typeColumn == "double")
			{
				double value;

				table.read(reinterpret_cast<char *>(&value), columnsSize[columns[i]]);

				rowData[columns[i]] = to_string(value);
			}
			else if (typeColumn == "bool")
			{
				char value;

				table.read(reinterpret_cast<char *>(&value), columnsSize[columns[i]]);

				if (value == 0)
				{
					rowData[columns[i]] = "false";
				}
				else 
				{
					rowData[columns[i]] = "true";
				}	
			}
			else if (typeColumn == "char(20)") // сделать регулярное выражение, для выделения длины строки
			{
				char value[20];

				table.read(reinterpret_cast<char *>(&value), columnsSize[columns[i]]);

				rowData[columns[i]] = string(value);
			}
			else if (typeColumn == "char(100)") // сделать регулярное выражение, для выделения длины строки
			{
				char value[100];

				table.read(reinterpret_cast<char *>(&value), columnsSize[columns[i]]);

				rowData[columns[i]] = string(value);
			}
			else
			{
				table.close();
				throw UnknownType(typeColumn);
			}
		}

		data.push_back(rowData);

		positionInTable += getRowSize(tableName);

		table.seekg(positionInTable);

		table.get(); // для обноружения конца файла
	}

	table.close();

	return data;
}