#ifndef SERVICE_H
#define SERVICE_H

#include "repository.h"
#include "exeption.h"
#include "reteta.h"
#include <map>
#include <stack>
#include <memory>
#include "actiuni_undo.h"

class objectDTO {
private:
	std::string subst_activa;
	int cnt;
public:
	objectDTO() : subst_activa(""), cnt(0) {}
	objectDTO(std::string subst_activa, int cnt) : subst_activa(subst_activa), cnt(cnt) {}
	std::string get_substanta() const { return subst_activa; }
	int get_cnt() const { return cnt; }
};

class ServiceException :public Exception {
public:
	explicit ServiceException(string message) :Exception(message) {}
};

class Service {
private:
	Repository& repo;
	Reteta& lista_reteta;
	std::stack<std::unique_ptr<ActiuneUndo>> istoric_undo;;

public:
	Repository& getRepo() { return repo; }
	void undo();
	void clear_undo();
	explicit Service(Repository& repo, Reteta& reteta);
	const std::vector<Medicament>& getall() const;
	std::vector<Medicament> filtrare_suma(float pret) const;
	std::vector<Medicament> filtrare_s_a(const std::string& substanta);
	void sterge(const int id);
	void sortare_denumire();
	void sortare_producator();
	void sortare_s_a_pret();
	const Medicament& cautare(const int id) const;
	void modifica(const int id, const std::string& nume, const float pret, const std::string& producator, const std::string& substanta);
	void add(int id, std::string denumire, float pret, std::string producator, std::string substanta);
	void adauga_reteta(const int id);
	void sterge_reteta();
	const std::vector<Medicament>& getReteta() const;
	void adauga_random(const int nr);
	std::map<std::string, objectDTO> raport_substante_activa() const;
	void exporta_CSV(const std::string& filename) const;
	void addObserver(Observer* obs);
	void removeObserver(Observer* obs);


};

#endif