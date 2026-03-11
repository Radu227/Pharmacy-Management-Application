#pragma once
#include <QWidget>
#include <QPainter>
#include "observer.h"
#include "service.h"

class RetetaReadOnlyGUI : public QWidget, public Observer {
    Service& service;
public:
    RetetaReadOnlyGUI(Service& srv) : service{ srv } {
        service.addObserver(this);
        setAttribute(Qt::WA_DeleteOnClose);
    }

    void paintEvent(QPaintEvent*) override {
        QPainter p{ this };
        int y = 10;
        for (const auto& m : service.getReteta()) {
            QRect rect(10, y, 150, 20);
            p.drawRect(rect);
            y += 30;
        }
    }

    void update() override {
        repaint();
    }

    ~RetetaReadOnlyGUI() {
        service.removeObserver(this);
    }
};