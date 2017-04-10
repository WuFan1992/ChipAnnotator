#include "mainwindow.hpp"

#include "classselector.hpp"
#include "imagetagger.hpp"

#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupMenuBar();
    setupStatusBar();

    m_tagger = new ImageTagger;
    setCentralWidget(m_tagger);

    auto* dock = new ClassSelector;
    addDockWidget(Qt::RightDockWidgetArea, dock);

    connect(dock, &ClassSelector::classSelected, m_tagger, &ImageTagger::setClass);
}

void MainWindow::setupMenuBar()
{
    auto* file_menu = menuBar()->addMenu(tr("&Files"));
    auto* open_action = file_menu->addAction(tr("&Open"), this, &MainWindow::onOpenClicked);
    open_action->setShortcut(tr("Ctrl+O"));
    file_menu->addSeparator();
    auto* save_action = file_menu->addAction(tr("&Save"), this, &MainWindow::onSaveClicked);
    save_action->setShortcut(tr("Ctrl+S"));
    auto* save_as_action = file_menu->addAction(tr("&Save As"), this, &MainWindow::onSaveAsClicked);
    save_as_action->setShortcut(tr("Ctrl+Shift+S"));

    auto* display_menu = menuBar()->addMenu(tr("&Display"));
    auto* toggle_grid_action = display_menu->addAction(
        tr("Toggle grid"), [this]() { m_tagger->setGridEnabled(!m_tagger->isGridEnabled()); });
    toggle_grid_action->setShortcut(tr("Ctrl+G"));
    auto* toggle_annotations_action = display_menu->addAction(
        tr("Toggle annotations"), [this]() { m_tagger->setAnnotationsEnabled(!m_tagger->areAnnotationsEnabled()); });
    toggle_annotations_action->setShortcut(tr("Ctrl+D"));
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
        m_tagger->display(file, annotation);
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
