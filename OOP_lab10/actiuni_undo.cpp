	#include "actiuni_undo.h"

UndoAdauga::UndoAdauga(Repository& repo, const Medicament& m) : repo(repo), medicament(m) {}

void UndoAdauga::doUndo() {
	repo.sterge_medicament(medicament.getId());
}

UndoSterge::UndoSterge(Repository& repo, const Medicament& m) : repo(repo), medicament(m) {}

void UndoSterge::doUndo() {
	repo.adauga_medicament(medicament);
}

UndoModifica::UndoModifica(Repository& repo, const Medicament& m) : repo(repo), medicamentVechi(m) {}

void UndoModifica::doUndo() {
	repo.modifica_medicament(medicamentVechi.getId(), medicamentVechi.getDenumire(), medicamentVechi.getProducator(), medicamentVechi.getPret(), medicamentVechi.getSubstantaActiva());
}