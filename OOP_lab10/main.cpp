#include <QApplication>
#include "activate_gui.h"
#include "repository.h"
#include "service.h"
#include "csv_repository.h"

void testAll();

int main(int argc, char* argv[]) {
	testAll();
	CSVrepository repo("medicamente.csv");
	Reteta reteta;
	Service service(repo, reteta);
	QApplication a(argc, argv);
	ActivateGUI gui(service);
	gui.show();
	return a.exec();
}
