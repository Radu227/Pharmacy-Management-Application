#include "reteta.h"
#include <fstream>

using namespace std;

void Reteta::sterge_reteta() {
	lista_medicamente.clear();
	notify();
}

void Reteta::adauga_medicament(const Medicament& medicament) {
	lista_medicamente.push_back(medicament);
	notify();
}

const vector<Medicament>& Reteta::get_Alll() const {
	return lista_medicamente;
}

void Reteta::export_CSV(const std::string& filename) const {
	ofstream fout(filename);
	for (const auto& medicament : lista_medicamente) {
		fout << medicament.getId() << "," << medicament.getDenumire() << "," << medicament.getPret() << ","
			<< medicament.getProducator() << "," << medicament.getSubstantaActiva() << "\n";
	}
	fout.close();
}