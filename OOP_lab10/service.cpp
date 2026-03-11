#include "service.h"
#include "domain.h"
#include "repository.h"
#include <iostream>
#include "repository.h"
#include <random>
#include <string>

Service::Service(Repository& repository, Reteta& reteta) : repo(repository), lista_reteta(reteta) {}

const std::vector<Medicament>& Service::getall() const
{
	return repo.get_All();
}

void Service::add(int id, std::string denumire, float pret, std::string producator, std::string substanta)
{
	Medicament m(id, denumire, pret, producator, substanta);
	repo.adauga_medicament(m);
	istoric_undo.push(std::make_unique<UndoAdauga>(repo, m));
}

void Service::sterge(int id)
{
	Medicament m = repo.cauta_id(id);
	repo.sterge_medicament(id);
	istoric_undo.push(std::make_unique<UndoSterge>(repo, m));
}

void Service::modifica(const int id, const std::string& nume, const float pret, const std::string& producator, const std::string& substanta)
{
	Medicament m = repo.cauta_id(id);
	repo.modifica_medicament(id, nume, producator, pret, substanta);
	istoric_undo.push(std::make_unique<UndoModifica>(repo, m));
}

std::vector<Medicament> Service::filtrare_suma(float pret) const
{
	std::vector<Medicament> medicamente = repo.get_All();
	std::vector<Medicament> rez;
	for (const auto& m : medicamente)
	{
		if (m.getPret() == pret)
			rez.push_back(m);
	}
	return rez;
}

std::vector<Medicament> Service::filtrare_s_a(const std::string& substanta)
{
	std::vector<Medicament> medicamente1 = repo.get_All();
	std::vector<Medicament> rez1;
	for (const auto& m : medicamente1)
	{
		if (m.getSubstantaActiva() == substanta)
			rez1.push_back(m);
	}
	return rez1;
}

void Service::sortare_denumire() {
	auto& medicamente = repo.get_All();

	std::sort(medicamente.begin(), medicamente.end(),
		[](const Medicament& a, const Medicament& b) {
			return a.getDenumire() < b.getDenumire();
		});
}

void Service::sortare_producator() {
	auto& medicamente = repo.get_All();

	std::sort(medicamente.begin(), medicamente.end(),
		[](const Medicament& a, const Medicament& b) {
			return a.getProducator() < b.getProducator();
		});
}

void Service::sortare_s_a_pret() {
	auto& medicamente = repo.get_All();

	std::sort(medicamente.begin(), medicamente.end(),
		[](const Medicament& a, const Medicament& b) {
			if (a.getSubstantaActiva() != b.getSubstantaActiva())
				return a.getSubstantaActiva() < b.getSubstantaActiva();
			return a.getPret() < b.getPret();
		});
}

const Medicament& Service::cautare(int id) const
{
	return repo.cauta_id(id);
}

void Service::adauga_reteta(const int id)
{
	const Medicament& medicament = repo.cauta_id(id);
	if (medicament.getId() == id)
	{
		lista_reteta.adauga_medicament(medicament);
	}
	else
	{
		throw ServiceException("Medicamentul nu a fost gasit!");
	}
}

void Service::sterge_reteta()
{
	lista_reteta.sterge_reteta();
}

const std::vector<Medicament>& Service::getReteta() const {
	return lista_reteta.get_Alll();
}

void Service::adauga_random(const int nr)
{
	const auto& reteta = getReteta();
	size_t m = reteta.size();
	int id;
	if (m > 0)
		id = reteta[m - 1].getId() + 1;
	else
		id = 1;
	float pret;
	std::string denumire;
	std::string producator;
	std::string substanta;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(1, 100);
	std::string denumiri[] = { "Nurofen", "Paracetamol", "Aspirina", "Claritine", "Ibuprofen" };
	std::string producatori[] = { "Reckitt Benckiser", "Zentiva", "Bayer", "GSK", "Pfizer" };
	std::string substante[] = { "Ibuprofen", "Acid acetilsalicilic", "Loratadina", "Paracetamol", "Diclofenac" };
	std::uniform_int_distribution<int> dist1(0, 4);
	for (int i = 0; i < nr; i++)
	{
		denumire = denumiri[dist1(mt)];
		producator = producatori[dist1(mt)];
		substanta = substante[dist1(mt)];
		pret = dist(mt);
		lista_reteta.adauga_medicament(Medicament(id, std::move(denumire), pret, std::move(producator), std::move(substanta)));
		id++;
	}
}

std::map<std::string, objectDTO> Service::raport_substante_activa() const {
	std::map<std::string, objectDTO> raport;
	const auto& medicamente = repo.get_All();
	std::map<std::string, int> temporar;
	for (const auto& medicament : medicamente)
	{
		const std::string substanta = medicament.getSubstantaActiva();
		temporar[substanta]++;
	}

	for (const auto& pair : temporar)
	{
		const std::string& substanta = pair.first;
		int count = pair.second;
		raport[substanta] = objectDTO(substanta, count);
	}
	return raport;
}

void Service::exporta_CSV(const std::string& filename) const {
	lista_reteta.export_CSV(filename);
}

void Service::undo()
{
	if (istoric_undo.empty())
	{
		std::cout << "Nu mai exista operatii de undo!\n";
		return;
	}

	istoric_undo.top()->doUndo();
	istoric_undo.pop();
}

void Service::clear_undo()
{
	while (!istoric_undo.empty())
	{
		istoric_undo.pop();
	}
}

void Service::addObserver(Observer* obs) {
	lista_reteta.addObserver(obs);
}

void Service::removeObserver(Observer* obs) {
	lista_reteta.removeObserver(obs);
}


