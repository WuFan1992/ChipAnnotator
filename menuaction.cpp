#include "menuaction.h"

#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
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

MenuAction::MenuAction(QWidget* parent)
{
    m_current_image_file_path ="";
    m_modified = false;
}



bool MenuAction::isFileNameValid(const QString& filename)
{
    return filename.endsWith("_1.tif") || filename.endsWith("_2.tif") || filename.endsWith("_3.tif");
}

QStringList MenuAction::createAllFileNames(const QString& filename)
{
    assert(isFileNameValid(filename));
    const auto root = filename.left(filename.size() - 5);
    return QStringList() << root + "1.tif" << root + "2.tif" << root + "3.tif";
}

bool MenuAction::askToSaveAndProceed(const QString& action)
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


void MenuAction::onOpenClicked()
{
    if(!askToSaveAndProceed("open a new image")) return;

    auto file = QFileDialog::getOpenFileName(this, tr("Select an image to open"), {}, "*.tif");
    if(!isFileNameValid(file)) return;

    emit resetScene();
    const auto files = createAllFileNames(file);
    for(const auto& f : files)
        if(!QFileInfo(f).exists()) return;
    try
    {
        auto annotation = files.front();
        annotation.chop(4);
        annotation += ".dat";
        m_current_image_file_path = files.front();

        emit displayImageSignal(loadImageStack(files));
        emit displayAnnotationSignal((QFileInfo::exists(annotation) ? annotation : ""));
        emit displayGridSignal();

        emit setWindowTitleSignal(QFileInfo(m_current_image_file_path).fileName());

       m_modified = false;
    }
    catch(const std::runtime_error& ex)
    {
        m_current_image_file_path.clear();
        QMessageBox::critical(this, tr("Unable to open image"), ex.what());
    }
}

void MenuAction::onSaveClicked()
{


    if(m_current_image_file_path.isEmpty()) return;
    auto output_file_path = m_current_image_file_path;
    output_file_path.chop(4);
    output_file_path += ".dat";

    emit saveAnnotationSignal(output_file_path);

     emit setWindowTitleSignal(QFileInfo(m_current_image_file_path).fileName());
    m_modified = false;

}

void MenuAction::onAnnotationModified()
{
    m_modified = true;
    emit setWindowTitleSignal(QFileInfo(m_current_image_file_path).fileName());

}

void MenuAction::closeEvent(QCloseEvent* event)
{
    const auto res = askToSaveAndProceed("close");
    if(res)
        event->accept();
    else
        event->ignore();
}

