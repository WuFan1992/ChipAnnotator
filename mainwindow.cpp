#include "mainwindow.hpp"
#include "chipannotator.h"
#include "menuaction.h"

#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QWidget>

#include <QPointF>

#include <QDebug>
#include <QString>
#include <QDataStream>

#define TOTAL_TYPE 18



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
   m_chipannotator = new ChipAnnotator;
   m_menuaction = new MenuAction;
   setupMenuBar();
   setupClassSelector();

   QWidget *widget = new QWidget;
   widget->setLayout(m_chipannotator->layout);
   setCentralWidget(widget);

   auto* b = statusBar();
   connect(m_chipannotator,&ChipAnnotator::statusType,[b](QString type_name){b->showMessage(type_name);});

   connect(m_menuaction,&MenuAction::resetScene,m_chipannotator,&ChipAnnotator::Reset);
   connect(m_menuaction,&MenuAction::displayImageSignal,m_chipannotator->m_annotateur,&AnnotatorScene::displayImage);
   connect(m_menuaction,&MenuAction::displayAnnotationSignal,m_chipannotator,&ChipAnnotator::displayAnnotation);
   connect(m_menuaction,&MenuAction::displayGridSignal,m_chipannotator,&ChipAnnotator::displayGrid);
   connect(m_menuaction,&MenuAction::setWindowTitleSignal,[this](QString title_name){setWindowTitle(title_name);});
   connect(m_menuaction,&MenuAction::saveAnnotationSignal,m_chipannotator,&ChipAnnotator::saveAnnotation);

}


void MainWindow::setupMenuBar()
{
    auto* file_menu = menuBar()->addMenu(tr("&Files"));
    file_menu->addAction(tr("&Open"), m_menuaction, &MenuAction::onOpenClicked, tr("Ctrl+O"));
    file_menu->addSeparator();
    file_menu->addAction(tr("&Save"), m_menuaction, &MenuAction::onSaveClicked, tr("Ctrl+S"));

    auto* display_menu = menuBar()->addMenu(tr("&Display"));

    display_menu->addAction(tr("Toggle grid"), [this]() { m_chipannotator->m_annotateur->setGridEnabled(!m_chipannotator->m_annotateur->isGridEnabled());},
                            tr("Ctrl+G"));
    display_menu->addAction(tr("Toggle annotations"),
                            [this]() { m_chipannotator->m_annotateur->setAnnotationsEnabled(!m_chipannotator->m_annotateur->areAnnotationsEnabled()); },
                            tr("Ctrl+D"));
}

void MainWindow::setupClassSelector()
{
    auto* dock = new ClassSelector;
    addDockWidget(Qt::RightDockWidgetArea, dock);

    connect(dock, &ClassSelector::classSelected, m_chipannotator->m_annotateur, &AnnotatorScene::setClass);
    connect(dock, &ClassSelector::channelSelected, m_chipannotator->m_annotateur, &AnnotatorScene::setChannel);
    connect(m_chipannotator->m_annotateur, &AnnotatorScene::selectClass, dock, &ClassSelector::selectClass);


    connect(dock, &ClassSelector::resetClicked, m_chipannotator->m_annotateur, &AnnotatorScene::resetContrastBrightness);
    connect(dock, &ClassSelector::autoClicked, m_chipannotator->m_annotateur, &AnnotatorScene::autoContrastBrightness);
    connect(dock, &ClassSelector::moreContrastClicked, m_chipannotator->m_annotateur, &AnnotatorScene::moreContrast);
    connect(dock, &ClassSelector::lessContrastClicked, m_chipannotator->m_annotateur, &AnnotatorScene::lessContrast);
    connect(dock, &ClassSelector::moreBrightnessClicked, m_chipannotator->m_annotateur, &AnnotatorScene::moreBrightness);
    connect(dock, &ClassSelector::lessBrightnessClicked, m_chipannotator->m_annotateur, &AnnotatorScene::lessBrightness);

    connect(dock,&ClassSelector::DragOn,m_chipannotator->m_annotaview,&AnnotatorView::DragFunction);

}


