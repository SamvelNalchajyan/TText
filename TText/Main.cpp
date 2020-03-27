#include <iostream>
#include <clocale>
#include <cstdlib>
#include "TText.h"

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	/*...........................................*/
	TText t;
	t.Read("..\FILE.txt");
	/*...........................................*/
	system("pause");
	return 0;
}