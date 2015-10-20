#include "FbxLoader.h"

int level = 0;

void PrintTabs()
{
	for (int i = 0; i < level; i++)
	{
		printf("\t");
	}
}