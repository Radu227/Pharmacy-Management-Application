#ifndef CSV_REPOSITORY_H
#define CSV_REPOSITORY_H

#include "file_repository.h"
#include <fstream>

class CSVrepository : public FileRepository {
public:
	CSVrepository(const std::string& filename) : FileRepository(filename) {
		load_from_file();
	}
	void load_from_file() override {
		std::ifstream f(filename);

		std::string line;
		while (std::getline(f, line))
		{

			std::vector<std::string> tokens;
			size_t start = 0;
			size_t end = line.find(',');
			while (end != std::string::npos)
			{
				tokens.push_back(line.substr(start, end - start));
				start = end + 1;
				end = line.find(',', start);
			}
			tokens.push_back(line.substr(start, end));
			if (tokens.size() == 5)
			{
				int id = std::stoi(tokens[0]);
				std::string denumire = tokens[1];
				float pret = std::stof(tokens[2]);
				std::string producator = tokens[3];
				std::string substantaActiva = tokens[4];

				Medicament medicament(id, denumire, pret, producator, substantaActiva);
				Repository::adauga_medicament(medicament);
			}
		}
		f.close();
	}

	void save_to_file() override {
		std::ofstream g(filename);
		const auto& medicamente = Repository::get_All();
		for (const auto& medicament : medicamente)
		{
			g << medicament.getId() << "," << medicament.getDenumire() << "," << medicament.getPret() << ","
				<< medicament.getProducator() << "," << medicament.getSubstantaActiva() << "\n";
		}
		g.close();
	}
};

#endif