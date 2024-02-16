#include <iostream>
#include <string>

using namespace std;

class Relation
{
private:
	string __relationName;
public:
	Relation(string name);

	string getRelationName();

	void setRelationName(string relationName);

	int INSERT();
	//bool DELETE();
	
};