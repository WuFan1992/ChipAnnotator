#include "mainwindow.hpp"
#include "chipannotator.h"
#include "menuaction.h"

#include <QCloseEvent>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMenuBar>
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

   chipannotator = new ChipAnnotator;
   setupMenuBar();
   menuaction = new MenuAction;
   setupClassSelector();

   QWidget *widget = new QWidget;
   widget->setLayout(chipannotator->layout);
   setCentralWidget(widget);

   connect(menuaction,&MenuAction::displayImageSignal,chipannotator->annotateur,&AnnotatorScene::displayImage);

}


void MainWindow::setupMenuBar()
{
    auto* file_menu = menuBar()->addMenu(tr("&Files"));
    file_menu->addAction(tr("&Open"), this, &MainWindow::onOpenClicked, tr("Ctrl+O"));
    file_menu->addSeparator();
    file_menu->addAction(tr("&Save"), this, &MainWindow::onSaveClicked, tr("Ctrl+S"));

    auto* display_menu = menuBar()->addMenu(tr("&Display"));

    display_menu->addAction(tr("Toggle grid"), [this]() { chipannotator->annotateur->setGridEnabled(!chipannotator->annotateur->isGridEnabled());},
                            tr("Ctrl+G"));
    display_menu->addAction(tr("Toggle annotations"),
                            [this]() { chipannotator->annotateur->setAnnotationsEnabled(!chipannotator->annotateur->areAnnotationsEnabled()); },
                            tr("Ctrl+D"));
}

void MainWindow::setupClassSelector()
{
    auto* dock = new ClassSelector;
    addDockWidget(Qt::RightDockWidgetArea, dock);

    connect(dock, &ClassSelector::classSelected, chipannotator->annotateur, &AnnotatorScene::setClass);
    connect(dock, &ClassSelector::channelSelected, chipannotator->annotateur, &AnnotatorScene::setChannel);
    connect(chipannotator->annotateur, &AnnotatorScene::selectClass, dock, &ClassSelector::selectClass);


    connect(dock, &ClassSelector::resetClicked, chipannotator->annotateur, &AnnotatorScene::resetContrastBrightness);
    connect(dock, &ClassSelector::autoClicked, chipannotator->annotateur, &AnnotatorScene::autoContrastBrightness);
    connect(dock, &ClassSelector::moreContrastClicked, chipannotator->annotateur, &AnnotatorScene::moreContrast);
    connect(dock, &ClassSelector::lessContrastClicked, chipannotator->annotateur, &AnnotatorScene::lessContrast);
    connect(dock, &ClassSelector::moreBrightnessClicked, chipannotator->annotateur, &AnnotatorScene::moreBrightness);
    connect(dock, &ClassSelector::lessBrightnessClicked, chipannotator->annotateur, &AnnotatorScene::lessBrightness);

    connect(dock,&ClassSelector::DragOn,chipannotator->annotaview,&AnnotatorView::DragFunction);

}

/*
bool MainWindow::isFileNameValid(const QString& filename)
{
    return filename.endsWith("_1.tif") || filename.endsWith("_2.tif") || filename.endsWith("_3.tif");
}
*/
/*
QStringList MainWindow::createAllFileNames(const QString& filename)
{
    assert(isFileNameValid(filename));
    const auto root = filename.left(filename.size() - 5);
    return QStringList() << root + "1.tif" << root + "2.tif" << root + "3.tif";
}
*/
/*
bool MainWindow::askToSaveAndProceed(const QString& action)
{
    if(m_modified)
    {
        const auto res
            = QMessageBox::question(this, tr("You have unsaved work"),
                                    "You are about to " + action + " but you have unsaved work.\nDo you want to save?",
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(res == QMessageBox::Cancel) return false;
        if(res == QMessageBox::Yes) onSaveClicked();
    }
    return true;
}
*/

/*
void MainWindow::onOpenClicked()
{
    if(!askToSaveAndProceed("open a new image")) return;

    auto file = QFileDialog::getOpenFileName(this, tr("Select an image to open"), {}, "*.tif");
    if(!isFileNameValid(file)) return;
    chipannotator->Reset();
    const auto files = createAllFileNames(file);
    for(const auto& f : files)
        if(!QFileInfo(f).exists()) return;
    try
    {
        auto annotation = files.front();
        annotation.chop(4);
        annotation += ".dat";
        m_current_image_file_path = files.front();

       chipannotator->annotateur->displayImage(loadImageStack(files));
       displayAnnotation((QFileInfo::exists(annotation) ? annotation : ""));
       chipannotator->displayGrid();

        setWindowTitle(QFileInfo(m_current_image_file_path).fileName());
        m_modified = false;
    }
    catch(const std::runtime_error& ex)
    {
        m_current_image_file_path.clear();
        QMessageBox::critical(this, tr("Unable to open image"), ex.what());
    }
}
*/

void MainWindow::onSaveClicked()
{


    if(m_current_image_file_path.isEmpty()) return;
    auto output_file_path = m_current_image_file_path;
    output_file_path.chop(4);
    output_file_path += ".dat";
    Utils::saveAnnotation(chipannotator,output_file_path);
    setWindowTitle(QFileInfo(m_current_image_file_path).fileName());
    m_modified = false;

}




void MainWindow::onAnnotationModified()
{
    m_modified = true;
    setWindowTitle(QFileInfo(m_current_image_file_path).fileName() + "*");
}


void MainWindow::displayAnnotation(QString &annoation)
{

    if(!annoation.isEmpty())
    {
        auto output_file_path = m_current_image_file_path;
        output_file_path.chop(4);
        output_file_path += ".dat";
        QFile file(output_file_path);
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        QString str_x,str_y,str_rectindex;
        qint32 rectindex;

        for(qint32 y=0;y<AnnotatorScene::c_annotation_resolution.height();y++)
        {
            for(qint32 x=0;x<AnnotatorScene::c_annotation_resolution.width();x++)
            {
                in>>str_x>>x>>str_y>>y>>str_rectindex>>rectindex;
                if(rectindex!=0)
                    chipannotator->colorlayout->TotalList.at(rectindex-1).at(y*chipannotator->annotateur->c_annotation_resolution.width()+x)->setVisible(true);

            }

        }


    }


}

void MainWindow::closeEvent(QCloseEvent* event)
{
    const auto res = askToSaveAndProceed("close");
    if(res)
        event->accept();
    else
        event->ignore();
}

