#include "mainwindow.hpp"

#include "classselector.hpp"
#include "imagetagger.hpp"

#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupMenuBar();
    setupStatusBar();

    m_tagger = new ImageTagger;
    setCentralWidget(m_tagger);
    auto* b = statusBar();
    connect(m_tagger, &ImageTagger::newCurrentClass, [b](QString name) { b->showMessage(name); });

    auto* dock = new ClassSelector;
    addDockWidget(Qt::RightDockWidgetArea, dock);

    connect(dock, &ClassSelector::classSelected, m_tagger, &ImageTagger::setClass);
}

void MainWindow::setupMenuBar()
{
    auto* file_menu = menuBar()->addMenu(tr("&Files"));
    file_menu->addAction(tr("&Open"), this, &MainWindow::onOpenClicked, tr("Ctrl+O"));
    file_menu->addSeparator();
    file_menu->addAction(tr("&Save"), this, &MainWindow::onSaveClicked, tr("Ctrl+S"));
    file_menu->addAction(tr("&Save As"), this, &MainWindow::onSaveAsClicked, tr("Ctrl+Shift+S"));

    auto* display_menu = menuBar()->addMenu(tr("&Display"));
    display_menu->addAction(tr("Toggle grid"), [this]() { m_tagger->setGridEnabled(!m_tagger->isGridEnabled()); },
                            tr("Ctrl+G"));
    display_menu->addAction(tr("Toggle annotations"),
                            [this]() { m_tagger->setAnnotationsEnabled(!m_tagger->areAnnotationsEnabled()); },
                            tr("Ctrl+D"));
}

void MainWindow::setupStatusBar()
{
}

void MainWindow::onOpenClicked()
{
    const auto file = QFileDialog::getOpenFileName(this, tr("Select an image to open"), {}, "*.tif");
    if(file.isEmpty()) return;
    try
    {
        auto annotation = file;
        annotation.chop(4);
        annotation += "_mask.tif";
        m_current_image_file_path = file;
        m_tagger->display(file, (QFileInfo::exists(annotation) ? annotation : ""));
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
    m_tagger->result().save(output_file_path);
}

void MainWindow::onSaveAsClicked()
{
    qDebug() << "MainWindow::onSaveAsClicked()";
}
