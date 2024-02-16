#include "Relation.h"

Relation::Relation(string name) : __relationName(name)
{
	//determined = false;
}

string Relation::getRelationName()
{
	return __relationName;
}

void Relation::setRelationName(string relationName)
{
	__relationName = relationName;
}