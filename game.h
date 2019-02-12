#ifndef GAME_H
#define GAME_H

#include <string>
#include "board.h"

enum SIGN {SGN_CIRCLE = 'O', SGN_CROSS = 'X'};

class Gra
{
	private:
		SIGN g_AktualnyGracz;
		Plansza Plansza1;

		struct Gracz
		{
			std::string strImie;
			int nWon;
			int nDraw;
			int nLose;
			bool byl;
			int nSrednia;
			Gracz() { strImie = '0'; nWon = 0; nDraw = 0; nLose = 0; byl = false; nSrednia = 0; };
		};

		std::string strGracz1;
		std::string strGracz2;

	public:
		Gra();
		~Gra();

		bool StartGry();
		bool LosujGracza();
		int Ruch(unsigned);
		void Sortowanie(int* aTablicaWynikow, int lewy, int prawy);
		bool game();
		bool KoniecGry(int c);
};

#endif