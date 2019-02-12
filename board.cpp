#include "board.h"
#include <iostream>

using namespace std;

const int Plansza::LINIE[8] [3] [2] = { { { 0,0 }, { 0,1 }, { 0,2 } },
											  { { 1,0 }, { 1,1 }, { 1,2 } },
											  { { 2,0 }, { 2,1 }, { 2,2 } },
											  { { 0,0 }, { 1,0 }, { 2,0 } },
											  { { 0,1 }, { 1,1 }, { 2,1 } },
											  { { 0,2 }, { 1,2 }, { 2,2 } },
											  { { 0,0 }, { 1,1 }, { 2,2 } },
											  { { 2,0 }, { 1,1 }, { 0,2 } } };

Plansza::Plansza()
{
	for (int i = 0; i < WymiarPlanszy; ++i)
		for (int j = 0; j < WymiarPlanszy; ++j)
			g_aPlansza[i][j] = FLD_EMPTY;
}

Plansza::~Plansza()
{

}

bool Plansza::CzyszczeniePlanszy()
{
	for (int i = 0; i < WymiarPlanszy; ++i)
		for (int j = 0; j < WymiarPlanszy; ++j)
			g_aPlansza[i][j] = FLD_EMPTY;
	return true;
}

int Plansza::SprawdzaniePlanszy()
{
	for (int i = 0; i < WymiarPlanszy * 2 + 2; ++i) // sprawdzdenie mo¿liwych kombinacji (8)
	{
		Pole = ZgodnePole = FLD_EMPTY;
		uLiczbaZgodnychPol = 0;
		
		for (int j = 0; j < WymiarPlanszy; ++j)
		{
			Pole = g_aPlansza[LINIE[i] [j] [0]] [LINIE [i] [j] [1]]; // i która kobinacja jest sprawdzana j pole kombinacji 0 - oœ x 1 - oœ y

			if (Pole != ZgodnePole)	//do Pole przypisywany jest znak pola jeœki znak Pole jest ró¿ny od znaku ZgodnePole
			{
				ZgodnePole = Pole;	// do ZgodnePole przypisywany jest znak pole
				uLiczbaZgodnychPol = 1;
			}
			else
				++uLiczbaZgodnychPol; //inaczej znaki s¹ takie same wiêc nale¿y powiêkszyæ liczbê zgodnych pól

		}

		if (uLiczbaZgodnychPol == WymiarPlanszy && ZgodnePole != FLD_EMPTY) // jeœli liczba zgodnych pól jest równa wielkoœci planszy i zgodne pola nie s¹ puste
		{
			return 1; // wygrana
		}
	}
	
	unsigned uLiczbaZapelnionychPol = 0;

	for (int i = 0; i < WymiarPlanszy; ++i) // sprawdza czy wszystkie pola nie s¹ zape³nione
		for (int j = 0; j < WymiarPlanszy; ++j)
			if (g_aPlansza[i] [j] != FLD_EMPTY)
				++uLiczbaZapelnionychPol;

	if (uLiczbaZapelnionychPol == WymiarPlanszy*WymiarPlanszy) // jeœli tak
	{
		return 2; // to wtedy jest remis
	}
	return 0;
}

bool Plansza::RysujPlansze(string strImie, string strSign)
{
	system ("cls");

	cout <<"   KÓ£KO I KRZY¯YK   "<<endl;
	cout <<"---------------------"<<endl;
	cout <<endl;

	cout <<"        -----"<<endl;
	for (int i = 0; i < WymiarPlanszy; ++i)
	{
		cout <<"        |";

		for (int j = 0; j < WymiarPlanszy; ++j)
		{
			if (g_aPlansza[i] [j] == FLD_EMPTY)
				cout << i * WymiarPlanszy + j + 1;
			else
				cout <<static_cast<char>(g_aPlansza[i] [j]); // rzutowanie na typ char
					
			if (j == 3)
			{
				cout <<"|"<<endl;
				cout <<"|";
			}
		}

		cout <<"|"<<endl;
	}

	cout <<"        -----"<<endl;
	cout << endl;
	cout << strImie <<" podaj numer pola, w którym chcesz postawiæ "<< strSign <<": "<<endl;
	return true;
}

bool Plansza::AktualizowaniePlanszy(FIELD sign, int x, int y)
{
	if (g_aPlansza [y] [x] == FLD_EMPTY)
		g_aPlansza [y] [x] = sign;	// do pola y x przypisywany jest znak
	else
		return false;
	return true;
}
