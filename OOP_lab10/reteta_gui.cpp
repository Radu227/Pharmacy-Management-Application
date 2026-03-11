#include "reteta_gui.h"
#include <QMessageBox>
#include <QFormLayout>

reteta_gui::reteta_gui(Service& srv) : service(srv) {
	initGUI();
	connectSignalsSlots();
	reloadlist();
	service.addObserver(this);
}

void reteta_gui::initGUI() {
	auto layout = new QVBoxLayout;
	setLayout(layout);

	listMedicamente = new QListWidget;
	layout->addWidget(listMedicamente);

	auto lyRight = new QVBoxLayout;

	auto formLayout = new QFormLayout;

	txtId = new QLineEdit;
	txtRandom = new QLineEdit;
	txtFisier = new QLineEdit;
	formLayout->addRow("Id", txtId);
	formLayout->addRow("Random", txtRandom);
	formLayout->addRow("Fisier", txtFisier);
	lyRight->addLayout(formLayout);

	addButton = new QPushButton("Adauga");
	deleteButton = new QPushButton("Sterge");
	randomButton = new QPushButton("Adauga random");
	exportButton = new QPushButton("Export");
	lyRight->addWidget(exportButton);
	lyRight->addWidget(addButton);
	lyRight->addWidget(deleteButton);
	lyRight->addWidget(randomButton);

	layout->addLayout(lyRight);
}

void reteta_gui::connectSignalsSlots() {
	QObject::connect(addButton, &QPushButton::clicked, this, [&]() {
		if (txtId->text().isEmpty()) {
			QMessageBox::warning(this, "Warning", "Id trebuie completat!");
			return;
		}
		try {
			int id = txtId->text().toInt();
			service.adauga_reteta(id);
			txtId->clear();
			reloadlist();
		}
		catch (const std::exception& ex) {
			QMessageBox::warning(this, "Warning", ex.what());
		}
	});

	QObject::connect(deleteButton, &QPushButton::clicked, this, [&]() {
		try {
			service.sterge_reteta();
			reloadlist();
		}
		catch (const std::exception& ex) {
			QMessageBox::warning(this, "Warning", ex.what());
		}
	});

	QObject::connect(randomButton, &QPushButton::clicked, this, [&]() {
		if (txtRandom->text().isEmpty()) {
			QMessageBox::warning(this, "Warning", "Numarul trebuie completat!");
			return;
		}
		try {
			int nr = txtRandom->text().toInt();
			service.adauga_random(nr);
			txtRandom->clear();
			reloadlist();
		}
		catch (const std::exception& ex) {
			QMessageBox::warning(this, "Warning", ex.what());
		}
	});
	QObject::connect(exportButton, &QPushButton::clicked, this, [&]() {
		if (txtFisier->text().isEmpty()) {
			QMessageBox::warning(this, "Warning", "Fisierul trebuie completat!");
			return;
		}
		try {
			std::string fisier = txtFisier->text().toStdString();
			service.exporta_CSV(fisier);
			txtFisier->clear();
		}
		catch (const std::exception& ex) {
			QMessageBox::warning(this, "Warning", ex.what());
		}
	});
}

void reteta_gui::reloadlist() {
	listMedicamente->clear();
	for (const auto& m : service.getReteta()) {
		QString item = QString::fromStdString(m.getDenumire() + " " +
			std::to_string(m.getPret()) + " " + m.getProducator() + " " +
			m.getSubstantaActiva());
		listMedicamente->addItem(item);
	}
}