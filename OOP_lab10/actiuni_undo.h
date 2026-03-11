#ifndef ACTIUNI_UNDO_H
#define ACTIUNI_UNDO_H

#include "domain.h"
#include "repository.h"
#include <memory>

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Repository& repo;
	Medicament medicament;
public:
	UndoAdauga(Repository& repo, const Medicament& medicament);
	void doUndo() override;
};

class UndoSterge : public ActiuneUndo {
private:
	Repository& repo;
	Medicament medicament;
public:
	UndoSterge(Repository& repo, const Medicament& medicament);
	void doUndo() override;
};

class UndoModifica : public ActiuneUndo {
private:
	Repository& repo;
	Medicament medicamentVechi;
public:
	UndoModifica(Repository& repo, const Medicament& medicamentVechi);
	void doUndo() override;
};

#endif