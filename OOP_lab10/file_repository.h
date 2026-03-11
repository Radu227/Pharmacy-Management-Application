#ifndef FILE_REPOSITORY_H
#define FILE_REPOSITORY_H

#include "repository.h"

class FileRepository : public Repository {
protected:
	std::string filename;
public:
	FileRepository(const std::string& filename) : filename(filename) {}
	virtual void load_from_file() = 0;
	virtual void save_to_file() = 0;

	void adauga_medicament(const Medicament& medicament) override {
		Repository::adauga_medicament(medicament);
		save_to_file();
	}

	void sterge_medicament(int id) override {
		Repository::sterge_medicament(id);
		save_to_file();
	}

	void modifica_medicament(int id, const std::string& denumire, const std::string& producator, float pret, const std::string& substantaActiva) override {
		Repository::modifica_medicament(id, denumire, producator, pret, substantaActiva);
		save_to_file();
	}
};

#endif