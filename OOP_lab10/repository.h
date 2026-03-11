#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include "domain.h"

class Repository {
private:
	std::vector<Medicament> medicamente;
	std::vector<Medicament> filtrare_pret;

public:
	virtual void adauga_medicament(const Medicament& m);
	const std::vector<Medicament>& get_All() const;
	std::vector<Medicament>& get_All();
	virtual void sterge_medicament(int id);
	const Medicament& cauta_id(int id) const;
	virtual ~Repository() = default;
	virtual void modifica_medicament(int id, const std::string& nume, const std::string& producator, float pret, const std::string& s_a);
};

#endif