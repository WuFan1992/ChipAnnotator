#include "menuaction.h"

#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>


namespace
{

    auto loadImageStack(const QStringList& files)
    {
        std::array<QPixmap, 3> res;
        std::copy(files.begin(), files.end(), res.begin());
        return res;
    }
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

        emit displayImageSignal(loadImageStack(files));

        //chipannotator->annotateur->displayImage(loadImageStack(files));
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

void MenuAction::onSaveClicked()
{


    if(m_current_image_file_path.isEmpty()) return;
    auto output_file_path = m_current_image_file_path;
    output_file_path.chop(4);
    output_file_path += ".dat";
    Utils::saveAnnotation(chipannotator,output_file_path);
    setWindowTitle(QFileInfo(m_current_image_file_path).fileName());
    m_modified = false;

}
