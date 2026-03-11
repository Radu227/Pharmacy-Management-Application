#include "repository.h"
#include "domain.h"
#include <algorithm>

void Repository::adauga_medicament(const Medicament& m)
{
    medicamente.push_back(std::move(m));
}

std::vector<Medicament>& Repository::get_All()
{
    return medicamente;
}

void Repository::sterge_medicament(int id) {
    auto it = std::find_if(medicamente.begin(), medicamente.end(), [id](const Medicament& m) { return m.getId() == id; });
    if (it != medicamente.end()) {
        *it = std::move(medicamente.back());
        medicamente.pop_back();
    }

}




void Repository::modifica_medicament(int id, const std::string& nume, const std::string& producator, float pret, const std::string& s_a)
{
    auto it = std::find_if(medicamente.begin(), medicamente.end(), [id](const Medicament& m) { return m.getId() == id; });
    if (it != medicamente.end())
    {
        it->setDenumire(nume);
        it->setProducator(producator);
        it->setPret(pret);
        it->setSubstantaActiva(s_a);
    }
}

const Medicament& Repository::cauta_id(int id) const
{
    auto it = std::find_if(medicamente.begin(), medicamente.end(), [id](const Medicament& m) { return m.getId() == id; });
    if (it == medicamente.end())
    {
        throw std::runtime_error("Medicamentul nu a fost gasit");
    }
    return *it;
}

