#include "activate_gui.h"
#include "reteta_gui.h"
#include "reteta_readonly_gui.h"
#include <QMessageBox>

ActivateGUI::ActivateGUI(Service& srv) : service{ srv } {
	initGUI();
	connectSignalsSlots();
	reloadList(service.getall());
}

void ActivateGUI::initGUI() {
	auto lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	listView = new QListView;
	listModel = new MedicamentListModel;
	listView->setModel(listModel);
	lyMain->addWidget(listView);


	//tabel
	tabelaMedicamente = new QTableWidget;
	tabelaMedicamente->setColumnCount(5);
	QStringList headers;
	headers << "Id" << "Denumire" << "Pret" << "Producator" << "Substanta activa";
	tabelaMedicamente->setHorizontalHeaderLabels(headers);
	tabelaMedicamente->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	lyMain->addWidget(tabelaMedicamente);

	auto lyRight = new QVBoxLayout;

	auto formLayout = new QFormLayout;
	//campuri de input
	txtId = new QLineEdit;
	txtDenumire = new QLineEdit;
	txtPret = new QLineEdit;
	txtProducator = new QLineEdit;
	txtSubstantaActiva = new QLineEdit;
	//adaug fiecare camp in formular
	formLayout->addRow("Id", txtId);
	formLayout->addRow("Denumire", txtDenumire);
	formLayout->addRow("Pret", txtPret);
	formLayout->addRow("Producator", txtProducator);
	formLayout->addRow("Substanta activa", txtSubstantaActiva);
	lyRight->addLayout(formLayout);
	//butoane
	addButton = new QPushButton("Adauga");
	deleteButton = new QPushButton("Sterge");
	updateButton = new QPushButton("Modifica");
	filterButton = new QPushButton("Filtreaza dupa denumire");
	sorteazadenumireButton = new QPushButton("Sorteaza dupa denumire");
	sorteazapretButton = new QPushButton("Sorteaza dupa substanta activa si pret");
	sorteazaproducatorButton = new QPushButton("Sorteaza dupa producator");
	undoButton = new QPushButton("Undo");
	cautaButton = new QPushButton("Cauta medicament");
	filtraresumaButton = new QPushButton("Filtreaza dupa pret");
	retetaButton = new QPushButton("Adauga la reteta");

	lyRight->addWidget(addButton);
	lyRight->addWidget(deleteButton);
	lyRight->addWidget(updateButton);
	lyRight->addWidget(filterButton);
	lyRight->addWidget(undoButton);
	lyRight->addWidget(sorteazadenumireButton);
	lyRight->addWidget(sorteazapretButton);
	lyRight->addWidget(sorteazaproducatorButton);
	lyRight->addWidget(cautaButton);
	lyRight->addWidget(filtraresumaButton);
	lyRight->addWidget(retetaButton);

	dynamicSubstanceLayout = new QVBoxLayout;
	lyRight->addLayout(dynamicSubstanceLayout);

	readonlyButton = new QPushButton("Deschide fereastra readonly");
	lyRight->addWidget(readonlyButton);

	lyMain->addLayout(lyRight);
}

void ActivateGUI::connectSignalsSlots() {
	QObject::connect(addButton, &QPushButton::clicked, this, [&]() {
		if (
			txtId->text().isEmpty() ||
			txtDenumire->text().isEmpty() ||
			txtPret->text().isEmpty() ||
			txtProducator->text().isEmpty() ||
			txtSubstantaActiva->text().isEmpty()
			) {
			QMessageBox::warning(this, "Eroare", "Toate campurile trebuie completate!");
			return;
		}
		try {
			//citim din input
			int id = txtId->text().toInt();
			std::string denumire = txtDenumire->text().toStdString();
			float pret = txtPret->text().toFloat();
			std::string producator = txtProducator->text().toStdString();
			std::string substantaActiva = txtSubstantaActiva->text().toStdString();

			service.add(id, denumire, pret, producator, substantaActiva);
			//reinitializam campurile
			reloadList(service.getall());
			//golim inputurile
			txtId->clear();
			txtDenumire->clear();
			txtPret->clear();
			txtProducator->clear();
			txtSubstantaActiva->clear();
		}
		catch (const std::exception& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}
	});

	QObject::connect(deleteButton, &QPushButton::clicked, this, [&]() {
		if (txtId->text().isEmpty())
		{
			QMessageBox::warning(this, "Eroare", "Id-ul trebuie completat!");
			return;
		}
		try {
			//citim id-ul din input
			int id = txtId->text().toInt();
			service.sterge(id);
			//reinitializam campurile
			reloadList(service.getall());
			//golim inputurile
			txtId->clear();
		}
		catch (const std::exception& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}
	});

	QObject::connect(updateButton, &QPushButton::clicked, this, [&]() {
		if (
			txtId->text().isEmpty() ||
			txtDenumire->text().isEmpty() ||
			txtPret->text().isEmpty() ||
			txtProducator->text().isEmpty() ||
			txtSubstantaActiva->text().isEmpty()
			) {
			QMessageBox::warning(this, "Eroare", "Toate campurile trebuie completate!");
			return;
		}
		try {
			//citim din input
			int id = txtId->text().toInt();
			std::string denumire = txtDenumire->text().toStdString();
			float pret = txtPret->text().toFloat();
			std::string producator = txtProducator->text().toStdString();
			std::string substantaActiva = txtSubstantaActiva->text().toStdString();
			service.modifica(id, denumire, pret, producator, substantaActiva);
			//reinitializam campurile
			reloadList(service.getall());
			//golim inputurile
			txtId->clear();
			txtDenumire->clear();
			txtPret->clear();
			txtProducator->clear();
			txtSubstantaActiva->clear();
		}
		catch (const std::exception& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}
	});

	QObject::connect(sorteazadenumireButton, &QPushButton::clicked, this, [&]() {
		service.sortare_denumire();
		reloadList(service.getall());
	});

	QObject::connect(sorteazapretButton, &QPushButton::clicked, this, [&]() {
		service.sortare_s_a_pret();
		reloadList(service.getall());
	});

	QObject::connect(sorteazaproducatorButton, &QPushButton::clicked, this, [&]() {
		service.sortare_producator();
		reloadList(service.getall());
	});

	QObject::connect(undoButton, &QPushButton::clicked, this, [&]() {
		try {
			service.undo();
			reloadList(service.getall());
		}
		catch (const std::exception& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}
	});

	QObject::connect(filterButton, &QPushButton::clicked, this, [&]() {
		if (txtDenumire->text().isEmpty())
		{
			QMessageBox::warning(this, "Eroare", "Denumirea trebuie completata!");
			return;
		}
		QString denumire= txtDenumire->text();
		std::vector<Medicament> filtrate;
		for (const auto& medicament : service.getall())
		{
			if (medicament.getDenumire() == denumire.toStdString())
			{
				filtrate.push_back(medicament);
			}
		}
		if (filtrate.empty())
		{
			txtDenumire->clear();
			QMessageBox::warning(this, "Eroare", "Nu exista medicamente cu aceasta denumire!");
			return;
		}
		txtDenumire->clear();
		reloadList(filtrate);
	});
	QObject::connect(cautaButton, &QPushButton::clicked, this, [&]() {
		if (txtId->text().isEmpty())
		{
			QMessageBox::warning(this, "Eroare", "Id-ul trebuie completat!");
			return;
		}
		int id = txtId->text().toInt();
		vector<Medicament> cautate;
		for (const auto& medicament : service.getall())
		{
			if (medicament.getId() == id)
			{
				cautate.push_back(medicament);
				reloadList(cautate);
				txtId->clear();
				return;
			}
		}
		txtId->clear();

	});
	QObject::connect(filtraresumaButton, &QPushButton::clicked, this, [&]() {
		int suma = txtPret->text().toInt();
		if (txtPret->text().isEmpty())
		{
			QMessageBox::warning(this, "Eroare", "Pretul trebuie completat!");
			return;
		}
		std::vector<Medicament> filtrate;
		for (const auto& medicament : service.getall())
		{
			if (medicament.getPret() == suma)
			{
				filtrate.push_back(medicament);
			}
		}
		if (filtrate.empty())
		{
			QMessageBox::warning(this, "Eroare", "Nu exista medicamente cu acest pret!");
			txtPret->clear();
			return;
		}
		txtPret->clear();
		reloadList(filtrate);
	});
	QObject::connect(retetaButton, &QPushButton::clicked, this, [&]() {
		auto* retetaWindow = new reteta_gui(service);
		retetaWindow->setAttribute(Qt::WA_DeleteOnClose);
		retetaWindow->show();
	});
	QObject::connect(readonlyButton, &QPushButton::clicked, this, [&]() {
		auto* readonly = new RetetaReadOnlyGUI(service);
		readonly->show();
	});
}

void ActivateGUI::reloadList(const std::vector<Medicament>& meds) {
	listModel->setMeds(meds);
	//actualizam tabela
	tabelaMedicamente->clearContents();
	tabelaMedicamente->setRowCount(static_cast<int>(meds.size()));
	
	int row = 0;
	for (const auto& medicament : meds) {
		QString id = QString::number(medicament.getId());
		QString denumire = QString::fromStdString(medicament.getDenumire());
		QString pret = QString::number(medicament.getPret());
		QString producator = QString::fromStdString(medicament.getProducator());
		QString substantaActiva = QString::fromStdString(medicament.getSubstantaActiva());
		tabelaMedicamente->setItem(row, 0, new QTableWidgetItem(id));
		tabelaMedicamente->setItem(row, 1, new QTableWidgetItem(denumire));
		tabelaMedicamente->setItem(row, 2, new QTableWidgetItem(pret));
		tabelaMedicamente->setItem(row, 3, new QTableWidgetItem(producator));
		tabelaMedicamente->setItem(row, 4, new QTableWidgetItem(substantaActiva));
		row++;
	}
	updateSubstanceList();
	
}

void ActivateGUI::updateSubstanceList() {
	//sterg butoanele vechi
	for (auto& [subst, btn] : substanceButtons) {
		dynamicSubstanceLayout->removeWidget(btn);
		delete btn;
	}
	substanceButtons.clear();
	auto raport = service.raport_substante_activa();

	//creez butoanele noi
	for (const auto& [subst, count] : raport) {
		auto* btn = new QPushButton(QString::fromStdString(subst));
		dynamicSubstanceLayout->addWidget(btn);
		substanceButtons[subst] = btn;

		QObject::connect(btn, &QPushButton::clicked, this, [subst,count](){
			QMessageBox::information(nullptr, "Substanta activa", QString::fromStdString(subst + " apare in " + std::to_string(count.get_cnt()) + " medicamente."));
		});
	}
}
