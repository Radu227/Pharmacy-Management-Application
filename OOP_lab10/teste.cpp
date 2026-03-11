#include <cassert>
#include <iostream>
#include "domain.h"
#include "repository.h"
#include "service.h"
#include <fstream>

void testDomain() {
    // Test constructor și getters
    Medicament m1(1, "Paracetamol", 5.0, "Zentiva", "Paracetamol");
    assert(m1.getId() == 1);
    assert(m1.getDenumire() == "Paracetamol");
    assert(m1.getPret() == 5.0);
    assert(m1.getProducator() == "Zentiva");
    assert(m1.getSubstantaActiva() == "Paracetamol");

    // Test setters
    m1.setId(2);
    m1.setDenumire("Nurofen");
    m1.setPret(10.0);
    m1.setProducator("Reckitt");
    m1.setSubstantaActiva("Ibuprofen");
    assert(m1.getId() == 2);
    assert(m1.getDenumire() == "Nurofen");
    assert(m1.getPret() == 10.0);
    assert(m1.getProducator() == "Reckitt");
    assert(m1.getSubstantaActiva() == "Ibuprofen");

    // Test constructor de copiere
}

void testRepository() {
    Repository repo;

    // Test adaugare
    repo.adauga_medicament(Medicament(1, "Paracetamol", 5.0, "Zentiva", "Paracetamol"));
    repo.adauga_medicament(Medicament(2, "Nurofen", 10.0, "Reckitt", "Ibuprofen"));
    assert(repo.get_All().size() == 2);

    // Test stergere
    repo.sterge_medicament(1);
    assert(repo.get_All().size() == 1);
    assert(repo.get_All()[0].getId() == 2);

    // Test modificare
    repo.modifica_medicament(2, "Nurofen Forte", "Reckitt", 15.0, "Ibuprofen");
    auto med = repo.cauta_id(2);
    assert(med.getDenumire() == "Nurofen Forte");
    assert(med.getPret() == 15.0);

    // Test cautare
    bool exceptie = false;
    try {
        repo.cauta_id(99);
    }
    catch (...) {
        exceptie = true;
    }
    assert(exceptie);

}

void testsortaresapret()
{
    Repository repo;
    Reteta reteta;
    Service service(repo, reteta);

    // Adăugăm medicamente pentru test
    service.add(1, "Med1", 15.0, "Prod1", "SubstantaA");
    service.add(2, "Med2", 10.0, "Prod2", "SubstantaB");
    service.add(3, "Med3", 20.0, "Prod3", "SubstantaA");
    service.add(4, "Med4", 5.0, "Prod4", "SubstantaA");

    service.sortare_s_a_pret();
    auto sorted = service.getall();
    assert(sorted[0].getId() == 4);
    assert(sorted[0].getSubstantaActiva() == "SubstantaA");
    assert(sorted[0].getPret() == 5.0);

    assert(sorted[1].getId() == 1);
    assert(sorted[1].getSubstantaActiva() == "SubstantaA");
    assert(sorted[1].getPret() == 15.0);

    assert(sorted[2].getId() == 3);
    assert(sorted[2].getSubstantaActiva() == "SubstantaA");
    assert(sorted[2].getPret() == 20.0);

    assert(sorted[3].getId() == 2);
    assert(sorted[3].getSubstantaActiva() == "SubstantaB");
    assert(sorted[3].getPret() == 10.0);
}

void testSortareProducator() {
    Repository repo;
    Reteta reteta;
    Service service(repo, reteta);

    // Adăugăm medicamente pentru test
    service.add(1, "Med1", 15.0, "Zentiva", "SubstantaA");
    service.add(2, "Med2", 10.0, "Bayer", "SubstantaB");
    service.add(3, "Med3", 20.0, "Reckitt", "SubstantaC");
    service.add(4, "Med4", 5.0, "AstraZeneca", "SubstantaD");

    // Testăm sortarea
    service.sortare_producator();
    auto sorted = service.getall();

    // Verificăm ordinea corectă (alfabetică după producător)
    assert(sorted[0].getProducator() == "AstraZeneca");
    assert(sorted[1].getProducator() == "Bayer");
    assert(sorted[2].getProducator() == "Reckitt");
    assert(sorted[3].getProducator() == "Zentiva");

    // Verificăm că ID-urile corespund (nu s-au pierdut date)
    assert(sorted[0].getId() == 4);
    assert(sorted[1].getId() == 2);
    assert(sorted[2].getId() == 3);
    assert(sorted[3].getId() == 1);
}

void testFiltrareSubstantaActiva() {
    Repository repo;
    Reteta reteta;
    Service service(repo, reteta);

    // Adăugăm medicamente de test
    service.add(1, "Nurofen", 10.0, "Reckitt", "Ibuprofen");
    service.add(2, "Paracetamol", 5.0, "Zentiva", "Paracetamol");
    service.add(3, "Ibuprofen", 8.0, "Bayer", "Ibuprofen"); // Același principiu activ ca Nurofen
    service.add(4, "Aspirina", 7.0, "Bayer", "Acid acetilsalicilic");

    // Test 1: Filtrare pentru "Ibuprofen"
    auto filtrat1 = service.filtrare_s_a("Ibuprofen");
    assert(filtrat1.size() == 2);
    assert(filtrat1[0].getId() == 1);
    assert(filtrat1[1].getId() == 3);

    // Test 2: Filtrare pentru "Paracetamol"
    auto filtrat2 = service.filtrare_s_a("Paracetamol");
    assert(filtrat2.size() == 1);
    assert(filtrat2[0].getId() == 2);

    // Test 3: Filtrare pentru substanță inexistentă
    auto filtrat3 = service.filtrare_s_a("Nexist");
    assert(filtrat3.empty());

    // Test 4: Verificare că obiectele returnate sunt copii corecte
    const std::string nume_original = filtrat2[0].getDenumire();
    service.modifica(2, "Paracetamol Forte", 6.0, "Zentiva", "Paracetamol");
    assert(filtrat2[0].getDenumire() == nume_original);
}

void testService() {
    Repository repo;
    Reteta reteta;
    Service service(repo, reteta);

    // Test adaugare
    service.add(1, "Paracetamol", 5.0, "Zentiva", "Paracetamol");
    service.add(2, "Nurofen", 10.0, "Reckitt", "Ibuprofen");
    assert(service.getall().size() == 2);

    // Test stergere
    service.sterge(1);
    assert(service.getall().size() == 1);

    // Test modificare
    service.modifica(2, "Nurofen Forte", 15.0, "Reckitt", "Ibuprofen");
    auto med = service.cautare(2);
    assert(med.getDenumire() == "Nurofen Forte");
    assert(med.getPret() == 15.0);

    // Test filtrare
    service.add(3, "Aspirina", 10.0, "Bayer", "Acid acetilsalicilic");
    auto filtrat = service.filtrare_suma(10.0);
    assert(filtrat.size() == 1);

    // Test sortare
    service.sortare_denumire();
    assert(service.getall()[0].getDenumire() == "Aspirina");

    service.add(1, "Paracetamol", 5.0, "Zentiva", "Paracetamol");
    service.add(2, "Nurofen", 10.0, "Reckitt", "Ibuprofen");

    // Test adaugare reteta
    service.adauga_reteta(1);
    service.adauga_reteta(2);
    assert(service.getReteta().size() == 2);
    assert(service.getReteta()[0].getId() == 1);

    // Test stergere reteta
    service.sterge_reteta();
    assert(service.getReteta().size() == 0);

    // Test adauga random
    service.sterge_reteta();  // goala
    service.adauga_random(1);
    const auto& r1 = service.getReteta();
    assert(r1.size() == 1);
    assert(r1[0].getId() == 1);
    service.sterge_reteta(); // curăță rețeta
    service.add(10, "FixMed", 9.99, "FixProd", "FixSub");
    service.adauga_reteta(10); // ID-ul maxim este 10

    service.adauga_random(3); // ar trebui să adauge 3 medicamente cu ID-uri 11, 12, 13

    const auto& retetaNoua = service.getReteta();
    assert(retetaNoua.size() == 4);

    assert(retetaNoua[1].getId() == 11);
    assert(retetaNoua[2].getId() == 12);
    assert(retetaNoua[3].getId() == 13);


}

void testUndoAndRetetaExtra() {
    Repository repo;
    Reteta reteta;
    Service service(repo, reteta);

    // Test undo pentru adaugare
    service.add(1, "Paracetamol", 5.0, "Zentiva", "Paracetamol");
    assert(service.getall().size() == 1);
    service.undo();
    assert(service.getall().size() == 0);

    // Test undo pentru stergere
    service.add(1, "Paracetamol", 5.0, "Zentiva", "Paracetamol");
    service.sterge(1);
    assert(service.getall().size() == 0);
    service.undo();
    assert(service.getall().size() == 1);

    // Test undo pentru modificare
    service.modifica(1, "Nurofen", 10.0, "Reckitt", "Ibuprofen");
    assert(service.cautare(1).getDenumire() == "Nurofen");
    service.undo();
    assert(service.cautare(1).getDenumire() == "Paracetamol");

    // Test clear_undo
    service.clear_undo();  // trebuie să golească stiva, nu se poate testa direct, dar să nu crape
    service.undo();
}

void testExportCSVandRaport() {
    Repository repo;
    Reteta reteta;
    Service service(repo, reteta);

    service.add(1, "Paracetamol", 5.0, "Zentiva", "Paracetamol");
    service.add(2, "Nurofen", 10.0, "Reckitt", "Ibuprofen");
    service.adauga_reteta(1);
    service.adauga_reteta(2);

    // Test export CSV
    std::string file = "test_export.csv";
    service.exporta_CSV(file);

    std::ifstream in(file);
    assert(in.is_open());
    std::string line;
    int lineCount = 0;
    while (std::getline(in, line)) {
        ++lineCount;
    }
    assert(lineCount == 2);
    in.close();

    // Test raport substanțe active
    auto raport = service.raport_substante_activa();
    assert(raport["Paracetamol"].get_cnt() == 1);
    assert(raport["Ibuprofen"].get_cnt() == 1);
}

void testRetetaMethodsDirect() {
    Medicament m1(1, "Paracetamol", 5.0, "Zentiva", "Paracetamol");
    Medicament m2(2, "Nurofen", 10.0, "Reckitt", "Ibuprofen");

    Reteta reteta;
    reteta.adauga_medicament(m1);
    reteta.adauga_medicament(m2);

    assert(reteta.get_Alll().size() == 2);
    reteta.sterge_reteta();
    assert(reteta.get_Alll().empty());

    reteta.adauga_medicament(m1);
    reteta.export_CSV("reteta_test.csv");

    std::ifstream in("reteta_test.csv");
    assert(in.is_open());
    std::string line;
    std::getline(in, line);
    assert(!line.empty());
    in.close();
}

void testMedicamentCopy() {
    Medicament m1(1, "Paracetamol", 5.0, "Zentiva", "Paracetamol");
    Medicament m2 = m1;  // constructor de copiere
    assert(m2.getId() == 1);
    assert(m2.getDenumire() == "Paracetamol");

    Medicament m3(3, "Alt", 10.0, "AltProd", "AltSub");
    m3 = m1;  // operator=
    assert(m3.getDenumire() == "Paracetamol");
    assert(m3.getPret() == 5.0);
}

void testAll() {
    testsortaresapret();
    testSortareProducator();
    testFiltrareSubstantaActiva();
    testDomain();
    testRepository();
    testService();
    testUndoAndRetetaExtra();
    testExportCSVandRaport();
    testRetetaMethodsDirect();
    testMedicamentCopy();
    std::cout << "Toate testele au fost trecute cu succes!\n";
}