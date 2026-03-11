#include "domain.h"
#include <iostream>

int Medicament::numarCopieri = 0;


Medicament::Medicament(int id, const std::string& denumire, float pret,
	const std::string& producator, const std::string& substantaActiva)
	: id(id), denumire(denumire), pret(pret), producator(producator), SubstantaActiva(substantaActiva)
{
}

Medicament& Medicament::operator=(const Medicament& other) {
	if (this != &other) {
		id = other.id;
		denumire = other.denumire;
		pret = other.pret;
		producator = other.producator;
		SubstantaActiva = other.SubstantaActiva;
	}
	return *this;
}

Medicament::Medicament(const Medicament& other)
	: id(other.id), denumire(other.denumire), pret(other.pret),
	producator(other.producator), SubstantaActiva(other.SubstantaActiva)
{
	numarCopieri++;
	//std::cout << "S-a efectuat o copiere. Total copieri: " << numarCopieri << std::endl;
}


const std::string& Medicament::getDenumire() const {
	return denumire;
}

void Medicament::setDenumire(const std::string& denumire1) {
	denumire = denumire1;
}

const std::string& Medicament::getProducator() const {
	return producator;
}

void Medicament::setProducator(const std::string& producator1) {
	producator = producator1;
}

const std::string& Medicament::getSubstantaActiva() const {
	return SubstantaActiva;
}

void Medicament::setSubstantaActiva(const std::string& SubstantaActiva1) {
	SubstantaActiva = SubstantaActiva1;
}

float Medicament::getPret() const {
	return pret;
}

void Medicament::setPret(float pret1) {
	pret = pret1;
}

int Medicament::getId() const {
	return id;
}

void Medicament::setId(int id1) {
	id = id1;
}
