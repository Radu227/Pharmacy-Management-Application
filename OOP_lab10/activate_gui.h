#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include "service.h"
#include "reteta_gui.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QListView>
#include "list_view.h"

class ActivateGUI : public QWidget {
	Q_OBJECT
private:
	Service& service;
	QListView* listView;
	MedicamentListModel* listModel;
	QLineEdit* txtId;
	QLineEdit* txtDenumire;
	QLineEdit* txtProducator;
	QLineEdit* txtPret;
	QLineEdit* txtSubstantaActiva;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* filterButton;
	QPushButton* sorteazadenumireButton;
	QPushButton* sorteazapretButton;
	QPushButton* sorteazaproducatorButton;
	QPushButton* undoButton;
	QPushButton* cautaButton;
	QPushButton* filtraresumaButton;
	QPushButton* retetaButton;
	QVBoxLayout* dynamicSubstanceLayout;
	QPushButton* readonlyButton;
	std::map<std::string, QPushButton*> substanceButtons;
	void updateSubstanceList();

	void initGUI();
	void connectSignalsSlots();
	void reloadList(const std::vector<Medicament>& meds);

	QTableWidget* tabelaMedicamente;
public:
	explicit ActivateGUI(Service& srv);
};
