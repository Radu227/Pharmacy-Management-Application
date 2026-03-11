#pragma once
#include <QAbstractListModel>
#include <QList>
#include <QVector>
#include "domain.h"

class MedicamentListModel : public QAbstractListModel {
    QList<Medicament> meds;

public:
    MedicamentListModel(QObject* parent = nullptr) : QAbstractListModel(parent) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return meds.size();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && index.isValid()) {
            const auto& m = meds.at(index.row());
            return QString::fromStdString(
                std::to_string(m.getId()) + " " + m.getDenumire() + " " +
                std::to_string(m.getPret()) + " " + m.getProducator() + " " + m.getSubstantaActiva()
            );
        }
        return {};
    }

    void setMeds(const std::vector<Medicament>& newMeds) {
        beginResetModel();
        QList<Medicament> converted;
        for (const auto& m : newMeds) {
            converted.append(m);
        }
        meds = converted;
        endResetModel();
    }

};
