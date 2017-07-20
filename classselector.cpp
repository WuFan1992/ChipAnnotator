#include "classselector.hpp"

#include "classes.hpp"

#include <QButtonGroup>
#include <QPushButton>
#include <QScrollArea>
#include <QShortcut>
#include <QVBoxLayout>

ClassSelector::ClassSelector(QWidget* parent)
    : QDockWidget(parent)
{
    auto* scroll_area = new QScrollArea;
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setWidget(buildButtonWidget());
    setWidget(scroll_area);

    setMinimumWidth(230);
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    setupShortcuts();
}

QWidget* ClassSelector::buildButtonWidget()
{
    auto* w = new QWidget;
    auto* lay = new QVBoxLayout;
    m_button_group = new QButtonGroup(this);
    for(int i = 0; i < Classes::classes().size(); i++)
    {
        const auto& c = Classes::classes()[i];
        QPixmap p(QSize(40, 40));
        p.fill(c.color());
        auto* b = new QPushButton(p, c.name());
        b->setStyleSheet("margin: 5px; padding: 10px;");
        b->setCheckable(true);
        connect(b, &QPushButton::clicked, [this, i]() { emit classSelected(i); });
        m_button_group->addButton(b);
        lay->addWidget(b);
    }
    lay->addStretch();
    w->setLayout(lay);
    return w;
}

void ClassSelector::setupShortcuts()
{
    for(int i = 0; i < Classes::classes().size(); i++)
    {
        auto* shortcut = new QShortcut(QKeySequence(Qt::Key_F1 + i), this);
        shortcut->setContext(Qt::ApplicationShortcut);
        connect(shortcut, &QShortcut::activated, [this, i]() { m_button_group->buttons()[i]->click(); });
    }
}
