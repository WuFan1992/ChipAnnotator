#include "classselector.hpp"

#include "classes.hpp"
#include "contrastadjustmentbuttons.hpp"
#include "utils.hpp"

#include <QButtonGroup>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPainter>
#include <QPushButton>
#include <QScrollArea>
#include <QShortcut>
#include <QVBoxLayout>
#include <QAction>
#include <QDebug>

namespace
{

    QPixmap createPixmapForClass(const Classes& c)
    {
        QPixmap p(QSize(60, 60));

        // QPainter pa(&p);
        // Utils::drawRectForClass(pa, c, p.rect());
        p.fill(c.color());

        return p;
    }
}

ClassSelector::ClassSelector(QWidget* parent)
    : QDockWidget(parent)
{

    auto* w = new QWidget;
    auto* lay = new QVBoxLayout;
    lay->setMargin(0);


    lay->addWidget(createChannelSelectionWidget());
    auto* contrast_editor = new ContrastAdjustmentButtons;
    lay->addWidget(contrast_editor);


    auto *drag_button = new QPushButton("Drag");
    drag_button->setCheckable(true);
    connect(drag_button,&QPushButton::clicked,this,&ClassSelector::DragOn);
    lay->addWidget(drag_button);

    auto* scroll_area = new QScrollArea;
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setWidget(buildButtonWidget());
    lay->addWidget(scroll_area);

    w->setLayout(lay);
    setWidget(w);

    setMinimumWidth(230);
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    setupShortcuts();
    selectClass(0);
    m_channels_button_group->buttons()[0]->click();

    connect(contrast_editor, &ContrastAdjustmentButtons::resetClicked, this, &ClassSelector::resetClicked);
    connect(contrast_editor, &ContrastAdjustmentButtons::autoClicked, this, &ClassSelector::autoClicked);
    connect(contrast_editor, &ContrastAdjustmentButtons::moreContrastClicked, this,
            &ClassSelector::moreContrastClicked);
    connect(contrast_editor, &ContrastAdjustmentButtons::lessContrastClicked, this,
            &ClassSelector::lessContrastClicked);
    connect(contrast_editor, &ContrastAdjustmentButtons::moreBrightnessClicked, this,
            &ClassSelector::moreBrightnessClicked);
    connect(contrast_editor, &ContrastAdjustmentButtons::lessBrightnessClicked, this,
            &ClassSelector::lessBrightnessClicked);

}
void ClassSelector::selectClass(quint8 class_index)
{
    m_classes_button_group->buttons()[class_index]->click();
}

QWidget* ClassSelector::buildButtonWidget()
{
    auto* w = new QWidget;
    auto* lay = new QVBoxLayout;
    lay->setMargin(7);
    lay->setSpacing(0);
    m_classes_button_group = new QButtonGroup(this);
    for(int i = 0; i < Classes::classes().size(); i++)
    {
        const auto& c = Classes::classes()[i];
        auto* b = new QPushButton(createPixmapForClass(c), c.name());
        b->setStyleSheet("margin: 5px; padding: 10px;");
        b->setCheckable(true);
        connect(b, &QPushButton::clicked, [this, i]() { emit classSelected(i); });
        m_classes_button_group->addButton(b);
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
        connect(shortcut, &QShortcut::activated, [this, i]() { ClassSelector::selectClass(i); });
    }
}

QWidget* ClassSelector::createChannelSelectionWidget()
{
    m_channels_button_group = new QButtonGroup;
    auto* w = new QGroupBox(tr("Channel Selection"));
    auto* lay = new QHBoxLayout;
    std::vector<QString> images
        = {":/images/Global_Blue_Dot.png", ":/images/Global_Green_Dot.png", ":/images/Global_Red_Dot.png"};
    for(quint8 i = 0; i < 3; i++)
    {
        auto* b = new QPushButton(QIcon(images[i]), "");
        m_channels_button_group->addButton(b);
        b->setCheckable(true);
        connect(b, &QPushButton::clicked, [this, i]() { emit channelSelected(i); });
        lay->addWidget(b);
    }
    w->setLayout(lay);
    return w;
}



