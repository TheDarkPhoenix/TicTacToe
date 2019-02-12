#include "game.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <string>

using namespace std;

Gra::Gra()
{

}

Gra::~Gra()
{

}

void Gra::Sortowanie(int* aTablicaWynikow, int pierw, int ost) //szybkie sortowanie pierw - indeks pocz¹tkowy, ost koñcowy
{
	int i,j,p;
	i = (pierw + ost) / 2; // i = po³owa tablicy
	p = aTablicaWynikow[i]; // p ma wartoœæ œrodkowego elementu tablicy
	aTablicaWynikow[i] = aTablicaWynikow[ost]; // przypisujemy œrodkowemu elementowi wartoœæ ostatniego
	for(j = i = pierw; i < ost; i++)
		if(aTablicaWynikow[i] < p) // jeœli wartoœæ aktualnego elementu jest mniejsza od p
		{
			swap(aTablicaWynikow[i], aTablicaWynikow[j]); // zamieniamy wartoœci elementów i j
			j++; // zwiêkzamy j
		}
	aTablicaWynikow[ost] = aTablicaWynikow[j]; // ostatniemu elementowi przypisujemy wartoœæ j elementu tablicy
	aTablicaWynikow[j] = p;	// j element tablicy = p
	if(pierw < j - 1) // jeœli j-1 jest wiêksze od pierwszego indeksu
		Sortowanie(aTablicaWynikow, pierw, j - 1);	// wywo³ujemy rekurencyjnie z ostatnim indeksem pomniejszonym o 1
	if(j + 1 < ost) // jeœli j+1 jest mniejsze od ostatniego indeksu
		Sortowanie(aTablicaWynikow, j + 1, ost);	// wywo³ujemy rekurencyjnie z pierwszym indeksem powiêkszonym o 1
}

bool Gra::StartGry()
{
	Plansza1.CzyszczeniePlanszy();
	LosujGracza();
	return true;
}

bool Gra::LosujGracza()
{
	cout <<"Podaj imiê pierwszego gracza: ";
	cin >> strGracz1;
	cout <<"Podaj imiê drugiego gracza: ";
	cin >> strGracz2;
	srand (static_cast<unsigned>(time(NULL)));
	g_AktualnyGracz = (rand() % 2 == 0 ? SGN_CIRCLE : SGN_CROSS);
	return true;
}

int Gra::Ruch(unsigned uNumerPola)
{
	if(!(uNumerPola >= 1 && uNumerPola <= Plansza1.GetSize() * Plansza1.GetSize())) return -1;

	unsigned uY = (uNumerPola - 1) / Plansza1.GetSize();	// numer pola w osi y
	unsigned uX = (uNumerPola - 1) % Plansza1.GetSize();	// numer pola w osi x

	if (!Plansza1.AktualizowaniePlanszy(static_cast<FIELD>(g_AktualnyGracz), uX, uY))
		return -1;

	int i = Plansza1.SprawdzaniePlanszy();

	g_AktualnyGracz = (g_AktualnyGracz == SGN_CIRCLE ? SGN_CROSS : SGN_CIRCLE);	// zmiana gracza
		
	return i;
}

bool Gra::game()
{
	int a = 0, b = 0;
	for (;a != '-1';)
	{
		system("cls");
		cout << "Wybierz opcjê: " << endl;
		cout << "1. Nowa gra." << endl;
		cout << "2. Ranking. " << endl;
		cout << "-1. Wyjœcie. " << endl;
		cin >> a;
		switch (a)
		{
			case 1:
				b = 0;
				StartGry();
				for ( ; ; )
				{
					Plansza1.RysujPlansze((g_AktualnyGracz == SGN_CIRCLE ? strGracz1 : strGracz2 ), (g_AktualnyGracz == SGN_CIRCLE ? "kolko" : "krzyzyk"));
					
					if (b == 0 || b == -1)
					{
						unsigned uNumerPola;
						cin >> uNumerPola;
						if (uNumerPola == -1)
							break;
						else if (cin.good())
							b = Ruch(uNumerPola);
						else
						{
							cout << "Z³y znak." << endl;
							cin.clear();
							cin.sync();
							getch();
						}
					}
					else if (b == 1 || b == 2)
					{	
						KoniecGry(b);
						break;
					}
				}
				break;
			case 2:
				{
				int n;
				system("cls");
				cout << "RANKING" << endl;
				cout << "--------------" << endl;
				fstream Ranking;
				Ranking.open("ranking.txt", ios::in | ios::out);
				string str;
				if (Ranking.good())
				{
					Ranking >> n; // liczba graczy
					Ranking.seekg(2, ios::cur);
					for (int i = 1; i <= 10; ++i)
					{
						cout << i << ". ";
						if (!Ranking.eof())
						{
							getline(Ranking, str);
							cout << str;
						}
						cout << endl;	
					}
				}
				else
					cout << "B³¹d";
				getch();
				Ranking.close();
				break;
				}
			case -1:
				return 0;
		}
	}
}

bool Gra::KoniecGry(int c)
{
	fstream Ranking;
	Ranking.open("ranking.txt", ios::in | ios::out);
	int n = 0, a;
	if (Ranking.good())
		Ranking >> n;
	Gracz* ranking = new Gracz[n+2];
	a = n;
	string strWygrany, strPrzegrany;
	if (c == 1)
	{
		cout <<"Wygral ";
		if (g_AktualnyGracz == SGN_CROSS)
		{
			strWygrany = strGracz1;
			strPrzegrany = strGracz2;
		}
		else
		{
			strWygrany = strGracz2;
			strPrzegrany = strGracz1;
		}
		cout << strWygrany <<"!"<<endl;
		getch();
		if (Ranking.good())
		{
			int b[2] = {0}; // b[0] zwyciêzca b[1] przegrany
			for (int i = 0; i < n; ++i)
			{
				if (!Ranking.eof())
				{
					Ranking >> ranking[i].strImie >> ranking[i].nWon >> ranking[i].nDraw >> ranking[i].nLose; // pobieramy dotychczasowy ranking z pliku
					if (strWygrany == ranking[i].strImie) // jeœli wygrany gracz wyst¹pi³ ju¿ w rankingu
						++ranking[i].nWon;	// zwiêkszamy liczbê wygranych
					else
						++b[0];	// jeœli nie zwiêkszamy liczbê sprawdzonych indeksów
					if (strPrzegrany == ranking[i].strImie)	// to samo co wy¿ej tylko sprawdzamy gracza który przegra³
						++ranking[i].nLose;
					else
						++b[1];	
				}
			}
			if (b[0] == n) // jeœli liczba sprawdzonych indeksów równa jest liczbie graczy w rankingu dodajemy nowego gracza
			{
				ranking[n].strImie = strWygrany;
				ranking[n].nWon = 1;
				ranking[n].nDraw = 0;
				ranking[n].nLose = 0;
				++a;
			}
			if (b[1] == n)
			{
				ranking[n+1].strImie = strPrzegrany;
				ranking[n+1].nWon = 0;
				ranking[n+1].nDraw = 0;
				ranking[n+1].nLose = 1;
				++a;
			}
		}
	}
	else if (c == 2)
	{
		cout <<"Remis!"<<endl;
		getch();
		if (Ranking.good())
		{
			int b[2] = {0};
			for (int i = 0; i < n; ++i)
			{
				if (!Ranking.eof())
				{
					Ranking >> ranking[i].strImie >> ranking[i].nWon >> ranking[i].nDraw >> ranking[i].nLose;
					if (strGracz1 == ranking[i].strImie) // to samo co w przypadku zakoñczenia gry zwyciêstwem ale w razie znalezienia gracza zwiêkszamy liczbê remisów
						++ranking[i].nDraw;
					else
						++b[0];
					if (strGracz2 == ranking[i].strImie)
						++ranking[i].nDraw;
					else
						++b[1];

				}
			}
			if (b[0] == n)
			{
				ranking[n].strImie = strGracz1;
				ranking[n].nWon = 0;
				ranking[n].nDraw = 1;
				ranking[n].nLose = 0;
				++a;
			}
			if (b[1] == n)
			{
				ranking[n+1].strImie = strGracz2;
				ranking[n+1].nWon = 0;
				ranking[n+1].nDraw = 1;
				ranking[n+1].nLose = 0;
				++a;
			}
		}
	}
	if (c == 1 || c == 2)
	{
		int* aTablicaWynikow = new int[a]; // tablica wyników która bêdzie póŸniej sortowana
		Ranking.close();
		for (int i = 0; i < a; ++i) // wyliczanie punktów
		{
			if ((ranking[i].nDraw + ranking[i].nLose) != 0 && ranking[i].nWon)
				ranking[i].nSrednia = (ranking[i].nWon * 100) / (ranking[i].nDraw + ranking[i].nLose);
			else if (!ranking[i].nDraw && !ranking[i].nWon)
			{
				ranking[i].nSrednia = 0;
				ranking[i].nSrednia -= ranking[i].nLose;
			}
			else
				ranking[i].nSrednia = ranking[i].nWon * 100;
			aTablicaWynikow[i] = ranking[i].nSrednia;
			ranking[i].byl = false;
		}
		Sortowanie(aTablicaWynikow, 0, a);
		Ranking.open("ranking.txt", ios::in | ios::out | ios::trunc); // czyœcimy ranking
		Ranking << a << endl; // zapisanie liczby graczy wystêpuj¹cych w rankingu
		for (int i = a; i >= 0; --i)
			for (int j = 0; j < a; ++j)
				if (aTablicaWynikow[i] == ranking[j].nSrednia && ranking[j].byl == false)
				{
					Ranking << ranking[j].strImie << ' ' << ranking[j].nWon << ' ' << ranking[j].nDraw << ' ' << ranking[j].nLose << endl; // zapisanie danych gracza
					ranking[j].byl = true;
					break;
				}
	}
	Ranking.close();
	return true;
}