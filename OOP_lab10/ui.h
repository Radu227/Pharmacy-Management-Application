#ifndef UI_H
#define UI_H

#include "service.h"
#include <iostream>

class ConsoleUI {
private: Service& service;
	   void afisare_meniu();
	   void afisare_medicamente();
	   void afisare_medicamente_filtrate_suma();
	   void afisare_medicamente_filtrate_substanta();
	   void adauga_predefinite();

public:
	void adaugare_medicament();
	explicit ConsoleUI(Service& service);
	void run();
	void stergere_medicament();
	void modificare_medicament();
	void sortare_denumire();
	void sortare_producator();
	void sortare_s_a_pret();
	void cauta_medicament();
	void adauga_la_reteta_ui();
	void afisare_reteta_ui();
	void sterge_reteta();
	void adauga_random_ui();
	void afisare_raport_ui();
	void exporta_ui();
	void undo_ui();
	void salveaza_in_fisier();
	void incarca_din_fisier();
};

#endif