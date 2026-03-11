#include "ui.h"
#include "service.h"
#include<stdexcept>
#include "csv_repository.h"

#include <iostream>

ConsoleUI::ConsoleUI(Service& srv) : service(srv) {}

void ConsoleUI::afisare_meniu()
{
	std::cout << "~~~~~~~~~~~~~~~Meniu~~~~~~~~~~~~~~~\n";
	std::cout << "1.Adauga medicament\n";
	std::cout << "2.Afiseaza toate medicamentele\n";
	std::cout << "3.Sterge medicament\n";
	std::cout << "4.Modifica medicament\n";
	std::cout << "5.Filtrare medicamente dupa suma\n";
	std::cout << "6.Filtrare medicamente dupa substanta activa\n";
	std::cout << "7.Sortare medicamente dupa denumire\n";
	std::cout << "8.Sortare medicamente dupa producator\n";
	std::cout << "9.Sortare medicamente dupa substanta activa si pret\n";
	std::cout << "10.Cauata si afiseaza medicament\n";
	std::cout << "11.Adauga medicament la reteta\n";
	std::cout << "12.Afiseaza reteta\n";
	std::cout << "13.Sterge reteta\n";
	std::cout << "14.Adauga medicamente random\n";
	std::cout << "15.Afiseaza raport substante active\n";
	std::cout << "16.Export medicamente in fisier CSV\n";
	std::cout << "17.Undo\n";
	std::cout << "18.Iesire\n";
}

void ConsoleUI::adaugare_medicament()
{
	std::cout << "Dati id-ul medicamentului: ";
	int id;
	std::cin >> id;
	std::cout << "Dati numele medicamentului: ";
	std::string nume;
	std::cin >> nume;
	std::cout << "Dati producatorul medicamentului: ";
	std::string producator;
	std::cin >> producator;
	std::cout << "Dati pretul medicamentului: ";
	float pret;
	std::cin >> pret;
	std::cout << "Dati substanta activa a medicamentului: ";
	std::string substanta_activa;
	std::cin >> substanta_activa;
	service.add(id, nume, pret, producator, substanta_activa);
}
void ConsoleUI::afisare_medicamente()
{
	const auto& medicamente = service.getall();
	for (const auto& medicament : medicamente)
	{
		std::cout << "Id: " << medicament.getId() << "  " << "Denumire: " << medicament.getDenumire() << "  " << "Pret: " << medicament.getPret() << "  " << "Producator: " << medicament.getProducator() << "  " << "Substanta Activa: " << medicament.getSubstantaActiva() << "\n";
	}
}

void ConsoleUI::afisare_medicamente_filtrate_suma()
{
	std::cout << "Dati suma: ";
	float suma;
	std::cin >> suma;
	const auto& medicamente = service.filtrare_suma(suma);
	for (const auto& medicament : medicamente)
	{
		std::cout << "Id: " << medicament.getId() << "  " << "Denumire: " << medicament.getDenumire() << "  " << "Pret: " << medicament.getPret() << "  " << "Producator: " << medicament.getProducator() << "  " << "Substanta Activa: " << medicament.getSubstantaActiva() << "\n";
	}
}

void ConsoleUI::afisare_medicamente_filtrate_substanta()
{
	std::cout << "Dati substanta: ";
	std::string substanta;
	std::cin >> substanta;
	const auto& medicamente = service.filtrare_s_a(substanta);
	for (const auto& medicament : medicamente)
	{
		std::cout << "Id: " << medicament.getId() << "  " << "Denumire: " << medicament.getDenumire() << "  " << "Pret: " << medicament.getPret() << "  " << "Producator: " << medicament.getProducator() << "  " << "Substanta Activa: " << medicament.getSubstantaActiva() << "\n";
	}
}
void ConsoleUI::stergere_medicament()
{
	std::cout << "Dati id-ul medicamentului pe care doriti sa il stergeti: ";
	int id;
	std::cin >> id;
	service.sterge(id);
}

void ConsoleUI::modificare_medicament()
{
	std::cout << "Dati id-ul medicamentului pe care doriti sa il modificati: ";
	int id;
	std::cin >> id;
	std::cout << "Dati numele medicamentului nou: ";
	std::string nume;
	std::cin >> nume;
	std::cout << "Dati producatorul medicamentului nou: ";
	std::string producator;
	std::cin >> producator;
	std::cout << "Dati pretul medicamentului nou: ";
	float pret;
	std::cin >> pret;
	std::cout << "Dati substanta activa a medicamentului nou: ";
	std::string substanta_activa;
	std::cin >> substanta_activa;
	service.modifica(id, nume, pret, producator, substanta_activa);
}

void ConsoleUI::sortare_denumire()
{
	service.sortare_denumire();
}

void ConsoleUI::sortare_producator()
{
	service.sortare_producator();
}

void ConsoleUI::sortare_s_a_pret()
{
	service.sortare_s_a_pret();
}

void ConsoleUI::adauga_predefinite()
{
	service.add(1, "Nurofen", 10, "Reckitt Benckiser", "Ibuprofen");
	service.add(2, "Paracetamol", 5, "Zentiva", "Ibuprofen");
	service.add(3, "Aspirina", 7, "Bayer", "Acid acetilsalicilic");
	service.add(4, "Claritine", 15, "Bayer", "Loratadina");
}

void ConsoleUI::cauta_medicament()
{
	std::cout << "Dati id-ul medicamentului pe care doriti sa il cautati: ";
	int id;
	std::cin >> id;
	const auto& medicament = service.cautare(id);
	std::cout << "Id: " << medicament.getId() << "  " << "Denumire: " << medicament.getDenumire() << "  " << "Pret: " << medicament.getPret() << "  " << "Producator: " << medicament.getProducator() << "  " << "Substanta Activa: " << medicament.getSubstantaActiva() << "\n";
}

void ConsoleUI::adauga_la_reteta_ui()
{
	std::cout << "Dati id-ul medicamentului pe care doriti sa il adaugati la reteta: ";
	int id;
	std::cin >> id;
	try {
		service.adauga_reteta(id);
		std::cout << "Medicamentul a fost adaugat la reteta.\n";
	}
	catch (const std::exception& e) {
		std::cout << "Eroare: " << e.what() << "\n";
	}
	const auto& reteta = service.getReteta();
	std::cout << "Reteta contine " << reteta.size() << " medicamente.\n";
}

void ConsoleUI::afisare_reteta_ui()
{
	int nr = 1;
	const auto& reteta = service.getReteta();
	if (!reteta.empty())
	{
		for (const auto& medicament : reteta)
		{
			std::cout << nr << ". " << "Denumire: " << medicament.getDenumire() << "  " << "Pret: " << medicament.getPret() << "  " << "Producator: " << medicament.getProducator() << "  " << "Substanta Activa: " << medicament.getSubstantaActiva() << "\n";
			nr++;
		}
	}
	else
	{
		std::cout << "Reteta este goala!\n";
	}

}

void ConsoleUI::sterge_reteta()
{
	service.sterge_reteta();
	const auto& reteta = service.getReteta();
	std::cout << "Reteta contine " << reteta.size() << " medicamente.\n";
}

void ConsoleUI::adauga_random_ui()
{
	std::cout << "Dati numarul de medicamente pe care doriti sa le adaugati: ";
	int nr;
	std::cin >> nr;
	if (nr <= 0 || nr > 100)
	{
		std::cout << "Numarul de medicamente trebuie sa fie pozitiv si mai mic decat 100!\n";
		return;
	}
	service.adauga_random(nr);
	const auto& reteta = service.getReteta();
	std::cout << "Medicamentele au fost adaugate la reteta.\n";
	std::cout << "Reteta contine " << reteta.size() << " medicamente.\n";
}

void ConsoleUI::afisare_raport_ui() {
	const auto& raport = service.raport_substante_activa();

	std::cout << "RAPORT SUBSTANTE ACTIVE:\n";
	for (const auto& pair : raport) {
		std::cout << pair.first << ": " << pair.second.get_cnt() << " medicamente\n";
	}
	std::cout << "\n";
}

void ConsoleUI::exporta_ui()
{
	std::cout << "Dati numele fisierului: ";
	std::string filename;
	std::cin >> filename;
	service.exporta_CSV(filename);
	std::cout << "Export realizat cu succes!\n";
}

void ConsoleUI::undo_ui()
{
	service.undo();
}

//void ConsoleUI::salveaza_in_fisier() {
//	std::string nume;
//	std::cout<<"Dati numele fisierului: ";
//	std::cin>>nume;
//	CSVrepository temp_repo(nume);
//	const auto& medicamente = service.getall();
//	for (const auto& medicament : medicamente)
//	{
//		temp_repo.adauga_medicament(medicament);
//	}
//	std::cout<<"Salvare in fisier realizata cu succes!\n";
//}

//void ConsoleUI::incarca_din_fisier() {
//	std::string nume;
//	std::cout<<"Dati numele fisierului: ";
//	std::cin>>nume;
//	CSVrepository& repo = dynamic_cast<CSVrepository&>(service.getRepo());
//	repo = CSVrepository(nume);
//	repo.load_from_file();
//	std::cout<<"Incarcare din fisier realizata cu succes!\n";
//}



void ConsoleUI::run()
{
	//adauga_predefinite();
	service.clear_undo();
	while (true)
	{
		afisare_meniu();
		int optiune;
		std::cout << "Alegeti o optiune: ";
		std::cin >> optiune;
		if (optiune == 1)
		{
			adaugare_medicament();
		}
		else if (optiune == 2)
		{
			afisare_medicamente();
		}
		else if (optiune == 3)
		{
			stergere_medicament();
		}
		else if (optiune == 4)
		{
			modificare_medicament();
		}
		else if (optiune == 5)
		{
			afisare_medicamente_filtrate_suma();
		}
		else if (optiune == 6)
		{
			afisare_medicamente_filtrate_substanta();
		}
		else if (optiune == 7)
		{
			sortare_denumire();
		}
		else if (optiune == 8)
		{
			sortare_producator();
		}
		else if (optiune == 9)
		{
			sortare_s_a_pret();
		}
		else if (optiune == 10)
		{
			cauta_medicament();
		}
		else if (optiune == 11)
		{
			adauga_la_reteta_ui();
		}
		else if (optiune == 12)
		{
			afisare_reteta_ui();
		}
		else if (optiune == 13)
		{
			sterge_reteta();
		}
		else if (optiune == 14)
		{
			adauga_random_ui();
		}
		else if (optiune == 15)
		{
			afisare_raport_ui();
		}
		else if (optiune == 16)
		{
			exporta_ui();
		}
		else if (optiune == 17)
		{
			undo_ui();
		}
		/*else if (optiune == 18)
		{
			salveaza_in_fisier();
		}*/
		/*else if (optiune == 19)
		{
			incarca_din_fisier();
		}*/
		else if (optiune == 18)
		{
			std::cout << "La revedere!\n";
			break;
		}
		else
		{
			std::cout << "Optiune invalida! Incercati din nou.\n";
		}
	}
}

