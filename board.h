#ifndef BOARD_H
#define BOARD_H

#include <string>

enum FIELD {FLD_EMPTY, FLD_CIRCLE = 'O', FLD_CROSS = 'X' };

class Plansza
{
	private:
		static const int WymiarPlanszy = 3;
		FIELD g_aPlansza[WymiarPlanszy][WymiarPlanszy];
		FIELD Pole, ZgodnePole;
		unsigned uLiczbaZgodnychPol;

		static const int LINIE[8] [WymiarPlanszy] [2];	// linie do sprawdzania wygranej

	public:
		Plansza();
		~Plansza();

		bool RysujPlansze(std::string strImie, std::string strSign);
		bool CzyszczeniePlanszy();
		int SprawdzaniePlanszy();
		bool AktualizowaniePlanszy(FIELD sign, int x, int y);

		int GetSize() {return WymiarPlanszy;};
};

#endif