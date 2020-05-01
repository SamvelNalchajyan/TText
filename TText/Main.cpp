#include <iostream>
#include <clocale>
#include <cstdlib>
#include "TText.h"

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	/*...........................................*/
	TTextLink::InitMem();
	TText t;
	t.Read("../FILE_in.txt");
	t.Write("../FILE_out.txt");
	/*...........................................*/
	system("pause");
	return 0;
}