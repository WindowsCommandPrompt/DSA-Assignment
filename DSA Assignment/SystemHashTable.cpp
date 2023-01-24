#include "SystemHashTable.h"

SystemHashTable::SystemHashTable(void) {
	//array but using linked list from LinkedListTrackPost.
	this->size = 0; 
}

int SystemHashTable::hash(KeyType key) 
{
	//int characters;
	//int len = key.length();
	//if (key.length() < 2) {
	//	characters = charvalue(key[0]);
	//	return characters;
	//}
	//characters = (charvalue(key[0]) * 52 + charvalue(key[1]))%MAX_SIZE;

	//for (int c = 1; c + 1 < len; c++) 
	//{
	//	if (c + 1 != key.length())
	//	{
	//		characters = (characters * 52 + charvalue(key[c + 1])) % MAX_SIZE;
	//	}
	//}
	//return 	characters % MAX_SIZE;
}