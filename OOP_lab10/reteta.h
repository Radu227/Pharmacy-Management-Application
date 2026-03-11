#pragma once

#include "domain.h"
#include "observable.h"
#include <vector>

using std::vector;

class Reteta : public Observable {
private:
	vector<Medicament> lista_medicamente;
public:
	void sterge_reteta();
	void adauga_medicament(const Medicament& medicament);
	const vector<Medicament>& get_Alll() const;
	void export_CSV(const std::string& filename) const;

};