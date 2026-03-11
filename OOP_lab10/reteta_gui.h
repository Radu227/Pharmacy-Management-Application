#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include "service.h"

class reteta_gui : public QWidget,public Observer {
	Q_OBJECT
private:
	void update() override {
		reloadlist();
	}
	Service& service;
	QListWidget* listMedicamente;
	QLineEdit* txtId;
	QLineEdit* txtRandom;
	QLineEdit* txtFisier;
	QPushButton* exportButton;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* randomButton;

	void initGUI();
	void connectSignalsSlots();
	void reloadlist();
public:
	explicit reteta_gui(Service& srv);
};
