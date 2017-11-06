
#include "contrastadjustmentbuttons.hpp"

#include <QLabel>
#include <QPushButton>

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Misc
{

    template <class T> T* createLayout(int margin, int spacing, QWidget* parent = nullptr)
    {
        auto* layout = new T(parent);
        layout->setMargin(margin);
        layout->setSpacing(spacing);
        return layout;
    }
}

ContrastAdjustmentButtons::ContrastAdjustmentButtons(bool horizontal, QWidget* parent)
    : QWidget(parent)
    , m_keep_minimal_size(false)
{
    auto* group = new QGroupBox(tr("Contrast Adjustment"), this);

    QBoxLayout* btn_n_grid_layout = nullptr;
    QBoxLayout* btn_layout = nullptr;
    if(horizontal)
    {
        btn_n_grid_layout = Misc::createLayout<QHBoxLayout>(12, 10);
        btn_layout = new QVBoxLayout;
    }
    else
    {
        btn_n_grid_layout = Misc::createLayout<QVBoxLayout>(12, 6);
        btn_layout = new QHBoxLayout;
    }

    btn_n_grid_layout->addSpacing(4);
    btn_layout->setSpacing(4);
    m_auto_btn = new QPushButton(tr("Auto"));
    m_auto_btn->setCheckable(true);
    m_auto_btn->setChecked(false);
    m_auto_btn->setToolTip(tr("Adjusts the chamber image contrast automatically"));
    btn_layout->addWidget(m_auto_btn);
    m_reset_btn = new QPushButton(tr("Reset"));
    m_reset_btn->setCheckable(true);
    m_reset_btn->setChecked(true);
    m_reset_btn->setToolTip(tr("Restores the original chamber image"));
    btn_layout->addWidget(m_reset_btn);
    btn_n_grid_layout->addLayout(btn_layout);
    auto* grid_lay = createGridControls();
    btn_n_grid_layout->addLayout(grid_lay);

    auto* main_layout = Misc::createLayout<QHBoxLayout>(0, 0);
    group->setLayout(btn_n_grid_layout);
    group->setAlignment(Qt::AlignCenter);
    main_layout->addWidget(group);
    setLayout(main_layout);

    connect(m_reset_btn, &QPushButton::clicked, this, [this]() {
        emit resetClicked();
        m_reset_btn->setChecked(true);
        m_auto_btn->setChecked(false);
    });

    connect(m_auto_btn, &QPushButton::clicked, this, [this]() {
        emit autoClicked();
        m_reset_btn->setChecked(false);
        m_auto_btn->setChecked(true);
    });
}

QGridLayout* ContrastAdjustmentButtons::createGridControls()
{
    auto* grid_lay = Misc::createLayout<QGridLayout>(4, 4);

    auto* contrast_label = new QLabel(tr("Contrast"));
    auto* contrast_plus = new QPushButton;
    auto* contrast_minus = new QPushButton;
    grid_lay->addWidget(contrast_label, 0, 0);
    grid_lay->addWidget(contrast_plus, 0, 2);
    grid_lay->addWidget(contrast_minus, 0, 1);
    setPlusIcon(contrast_plus);
    setMinusIcon(contrast_minus);
    m_hideable_widgets.push_back(contrast_label);
    m_hideable_widgets.push_back(contrast_plus);
    m_hideable_widgets.push_back(contrast_minus);

    auto* brightness_label = new QLabel(tr("Brightness"));
    auto* brightness_plus = new QPushButton;
    auto* brightness_minus = new QPushButton;
    grid_lay->addWidget(brightness_label, 1, 0);
    grid_lay->addWidget(brightness_plus, 1, 2);
    grid_lay->addWidget(brightness_minus, 1, 1);
    setPlusIcon(brightness_plus);
    setMinusIcon(brightness_minus);
    m_hideable_widgets.push_back(brightness_label);
    m_hideable_widgets.push_back(brightness_plus);
    m_hideable_widgets.push_back(brightness_minus);

    connect(contrast_plus, &QPushButton::clicked, this, [this]() {
        emit moreContrastClicked();
        m_reset_btn->setChecked(false);
        m_auto_btn->setChecked(false);
    });

    connect(contrast_minus, &QPushButton::clicked, this, [this]() {
        emit lessContrastClicked();
        m_reset_btn->setChecked(false);
        m_auto_btn->setChecked(false);
    });

    connect(brightness_plus, &QPushButton::clicked, this, [this]() {
        emit moreBrightnessClicked();
        m_reset_btn->setChecked(false);
        m_auto_btn->setChecked(false);
    });

    connect(brightness_minus, &QPushButton::clicked, this, [this]() {
        emit lessBrightnessClicked();
        m_reset_btn->setChecked(false);
        m_auto_btn->setChecked(false);
    });

    return grid_lay;
}

void ContrastAdjustmentButtons::setPlusIcon(QPushButton* button)
{
    const auto icon_name = ":/images/List_Plus_1.png";
    QSize size(10, 10);
    button->setIcon(QIcon(QPixmap(icon_name).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    button->setIconSize(size);
}

void ContrastAdjustmentButtons::setMinusIcon(QPushButton* button)
{
    const auto icon_name = ":/images/List_Minus_1.png";
    QSize size(10, 10);
    button->setIcon(QIcon(QPixmap(icon_name).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    button->setIconSize(size);
}

void ContrastAdjustmentButtons::setMinimalSize()
{
    m_keep_minimal_size = true;
    for(auto widget : m_hideable_widgets)
    {
        widget->hide();
    }
}
