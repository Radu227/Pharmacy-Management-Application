#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>
#include <stdexcept>

class Medicament {
private:
	int id;
	std::string denumire;
	float pret;
	std::string producator;
	std::string SubstantaActiva;
	static int numarCopieri;

public:
	Medicament(int id, const std::string& denumire, float pret, const std::string& producator, const std::string& SubstantaActiva);
	Medicament(const Medicament& other);
	Medicament& operator=(const Medicament& other);
	//getters
	int getId() const;
	const std::string& getDenumire() const;
	float getPret() const;
	const std::string& getProducator() const;
	const std::string& getSubstantaActiva() const;
	//setters
	void setId(int id);
	void setDenumire(const std::string& denumire);
	void setPret(float pret);
	void setProducator(const std::string& producator);
	void setSubstantaActiva(const std::string& SubstantaActiva);
};

#endif