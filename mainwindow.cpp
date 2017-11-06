#include "mainwindow.hpp"

#include "classselector.hpp"

//#include "imagetagger.hpp"
#include "annotatorscene.h"
#include "annotatorview.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QHBoxLayout>

#include <QPointF>

#include <QDebug>



namespace
{

    auto loadImageStack(const QStringList& files)
    {
        std::array<QPixmap, 3> res;
        std::copy(files.begin(), files.end(), res.begin());
        return res;
    }
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{

    setupMenuBar();


    //m_tagger = new ImageTagger;
    annotateur = new AnnotatorScene;

    annotateur->setSceneRect(QRectF(0, 0, 800, 564));

    //setCentralWidget(m_tagger);
     QHBoxLayout *layout = new QHBoxLayout;
     annotaview = new AnnotatorView(annotateur);
     annotaview->fitInView(0,0,800,564);
     annotaview->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

     layout->addWidget(annotaview);


   // auto* b = statusBar();
   //connect(m_tagger, &ImageTagger::newCurrentClass, [b](QString name) { b->showMessage(name); });


     sceneScaleCombo = new QComboBox;
     QStringList scales;
     scales <<tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
     sceneScaleCombo->addItems(scales);
     sceneScaleCombo->setCurrentIndex(2);
     layout->addWidget(sceneScaleCombo);
     connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
             this, SLOT(sceneScaleChanged(QString)));


    auto* dock = new ClassSelector;
    //layout->addWidget(dock);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);



    connect(dock, &ClassSelector::classSelected, annotateur, &AnnotatorScene::setClass);
    connect(dock, &ClassSelector::channelSelected, annotateur, &AnnotatorScene::setChannel);
    connect(annotateur, &AnnotatorScene::selectClass, dock, &ClassSelector::selectClass);


    connect(dock, &ClassSelector::resetClicked, annotateur, &AnnotatorScene::resetContrastBrightness);
    connect(dock, &ClassSelector::autoClicked, annotateur, &AnnotatorScene::autoContrastBrightness);
    connect(dock, &ClassSelector::moreContrastClicked, annotateur, &AnnotatorScene::moreContrast);
    connect(dock, &ClassSelector::lessContrastClicked, annotateur, &AnnotatorScene::lessContrast);
    connect(dock, &ClassSelector::moreBrightnessClicked, annotateur, &AnnotatorScene::moreBrightness);
    connect(dock, &ClassSelector::lessBrightnessClicked, annotateur, &AnnotatorScene::lessBrightness);

    connect(annotateur, &AnnotatorScene::modified, this, &MainWindow::onAnnotationModified);

    prePaintGrid();


    connect (annotateur,&AnnotatorScene::gridOn,this,&MainWindow::PaintGrid);

}

void MainWindow::closeEvent(QCloseEvent* event)
{
    const auto res = askToSaveAndProceed("close");
    if(res)
        event->accept();
    else
        event->ignore();
}

void MainWindow::setupMenuBar()
{
    auto* file_menu = menuBar()->addMenu(tr("&Files"));
    file_menu->addAction(tr("&Open"), this, &MainWindow::onOpenClicked, tr("Ctrl+O"));
    file_menu->addSeparator();
    file_menu->addAction(tr("&Save"), this, &MainWindow::onSaveClicked, tr("Ctrl+S"));

    auto* display_menu = menuBar()->addMenu(tr("&Display"));

    display_menu->addAction(tr("Toggle grid"), [this]() { annotateur->setGridEnabled(!annotateur->isGridEnabled()); },
                            tr("Ctrl+G"));
    display_menu->addAction(tr("Toggle annotations"),
                            [this]() { annotateur->setAnnotationsEnabled(!annotateur->areAnnotationsEnabled()); },
                            tr("Ctrl+D"));
}

bool MainWindow::isFileNameValid(const QString& filename)
{
    return filename.endsWith("_1.tif") || filename.endsWith("_2.tif") || filename.endsWith("_3.tif");
}

QStringList MainWindow::createAllFileNames(const QString& filename)
{
    assert(isFileNameValid(filename));
    const auto root = filename.left(filename.size() - 5);
    return QStringList() << root + "1.tif" << root + "2.tif" << root + "3.tif";
}

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

void MainWindow::onOpenClicked()
{
    if(!askToSaveAndProceed("open a new image")) return;
    auto file = QFileDialog::getOpenFileName(this, tr("Select an image to open"), {}, "*.tif");
    if(!isFileNameValid(file)) return;
    const auto files = createAllFileNames(file);
    for(const auto& f : files)
        if(!QFileInfo(f).exists()) return;
    try
    {
        auto annotation = files.front();
        annotation.chop(4);
        annotation += "_mask.tif";
        m_current_image_file_path = files.front();


        annotateur->display(loadImageStack(files), (QFileInfo::exists(annotation) ? annotation : ""));

        setWindowTitle(QFileInfo(m_current_image_file_path).fileName());
        m_modified = false;
    }
    catch(const std::runtime_error& ex)
    {
        m_current_image_file_path.clear();
        QMessageBox::critical(this, tr("Unable to open image"), ex.what());
    }
}

void MainWindow::onSaveClicked()
{
    if(m_current_image_file_path.isEmpty()) return;
    auto output_file_path = m_current_image_file_path;
    output_file_path.chop(4);
    output_file_path += "_mask.tif";


    annotateur->result().save(output_file_path);

    setWindowTitle(QFileInfo(m_current_image_file_path).fileName());
    m_modified = false;
}

void MainWindow::onAnnotationModified()
{
    m_modified = true;
    setWindowTitle(QFileInfo(m_current_image_file_path).fileName() + "*");
}

void MainWindow::prePaintGrid()
{
    int block_width = AnnotatorScene::c_image_resolution.width()/AnnotatorScene::c_annotation_resolution.width();
    int block_height = AnnotatorScene::c_image_resolution.height()/AnnotatorScene::c_annotation_resolution.height();





        for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
        {
              QGraphicsLineItem *horizon_line = annotateur->addLine((x+1)*block_width,0,(x+1)*block_width,AnnotatorScene::c_image_resolution.height(),QPen(QColor(255,0,0)));
              horizonLine_List.append(horizon_line);
              horizon_line->setVisible(false);

        }

        for (int y = 0; y < AnnotatorScene::c_annotation_resolution.height();y++)
        {
             QGraphicsLineItem *vertical_line = annotateur->addLine(0,(y+1)*block_height,AnnotatorScene::c_image_resolution.width(),(y+1)*block_height,QPen(QColor(255,0,0)));
             verticalLine_List.append(vertical_line);
             vertical_line->setVisible(false);

        }




}

void MainWindow::PaintGrid(bool m_display_grid)
{


         for (int x = 0; x < AnnotatorScene::c_annotation_resolution.width();x++)
             horizonLine_List.at(x)->setVisible(m_display_grid);
         for (int y = 0; y < AnnotatorScene::c_annotation_resolution.height();y++)
             verticalLine_List.at(y)->setVisible(m_display_grid);

    update();
}

void MainWindow::ShowItem()
{
    qDebug()<< "hello Fan WU";
}
/*
void MainWindow::PaintAnnotation()
{



}
*/
void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = annotaview->matrix();
    annotaview->resetMatrix();
    annotaview->translate(oldMatrix.dx(), oldMatrix.dy());
    annotaview->scale(newScale, newScale);
}
