#include "classselector.hpp"

#include "classes.hpp"

#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>

ClassSelector::ClassSelector(QWidget* parent)
    : QDockWidget(parent)
{
    auto* w = new QWidget;
    auto* lay = new QVBoxLayout;
    auto* group = new QButtonGroup(this);
    for(int i = 0; i < Classes::classes().size(); i++)
    {
        const auto& c = Classes::classes()[i];
        QPixmap p(QSize(40, 40));
        p.fill(c.color());
        auto* b = new QPushButton(p, c.name());
        b->setStyleSheet("margin: 20px; padding: 10px;");
        b->setCheckable(true);
        connect(b, &QPushButton::clicked, [this, i]() { emit classSelected(i); });
        group->addButton(b);
        lay->addWidget(b);
    }
    lay->addStretch();
    w->setLayout(lay);
    setWidget(w);
    setMinimumWidth(200);
}
