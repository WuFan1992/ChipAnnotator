#include "mainwindow.hpp"

#include "classselector.hpp"
#include "imagetagger.hpp"

#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>

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

    m_tagger = new ImageTagger;
    setCentralWidget(m_tagger);
    auto* b = statusBar();
    connect(m_tagger, &ImageTagger::newCurrentClass, [b](QString name) { b->showMessage(name); });

    auto* dock = new ClassSelector;
    addDockWidget(Qt::RightDockWidgetArea, dock);

    connect(dock, &ClassSelector::classSelected, m_tagger, &ImageTagger::setClass);
    connect(dock, &ClassSelector::channelSelected, m_tagger, &ImageTagger::setChannel);
    connect(m_tagger, &ImageTagger::selectClass, dock, &ClassSelector::selectClass);

    connect(dock, &ClassSelector::resetClicked, m_tagger, &ImageTagger::resetContrastBrightness);
    connect(dock, &ClassSelector::autoClicked, m_tagger, &ImageTagger::autoContrastBrightness);
    connect(dock, &ClassSelector::moreContrastClicked, m_tagger, &ImageTagger::moreContrast);
    connect(dock, &ClassSelector::lessContrastClicked, m_tagger, &ImageTagger::lessContrast);
    connect(dock, &ClassSelector::moreBrightnessClicked, m_tagger, &ImageTagger::moreBrightness);
    connect(dock, &ClassSelector::lessBrightnessClicked, m_tagger, &ImageTagger::lessBrightness);
}

void MainWindow::setupMenuBar()
{
    auto* file_menu = menuBar()->addMenu(tr("&Files"));
    file_menu->addAction(tr("&Open"), this, &MainWindow::onOpenClicked, tr("Ctrl+O"));
    file_menu->addSeparator();
    file_menu->addAction(tr("&Save"), this, &MainWindow::onSaveClicked, tr("Ctrl+S"));

    auto* display_menu = menuBar()->addMenu(tr("&Display"));
    display_menu->addAction(tr("Toggle grid"), [this]() { m_tagger->setGridEnabled(!m_tagger->isGridEnabled()); },
                            tr("Ctrl+G"));
    display_menu->addAction(tr("Toggle annotations"),
                            [this]() { m_tagger->setAnnotationsEnabled(!m_tagger->areAnnotationsEnabled()); },
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

void MainWindow::onOpenClicked()
{
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
        m_tagger->display(loadImageStack(files), (QFileInfo::exists(annotation) ? annotation : ""));
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
