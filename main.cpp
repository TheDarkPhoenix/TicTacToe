/*
Copyright (c) 2019 Maciej Stępień
Licensed under the MIT license: 
http://www.opensource.org/licenses/mit-license.php
*/

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <locale>
#include <conio.h>
#include "game.h"

using namespace std;

locale myloc ("Polish");
locale oldloc = locale::global (myloc);

int main()
{
	Gra Gra1;
 	Gra1.game();
	return 0;
}