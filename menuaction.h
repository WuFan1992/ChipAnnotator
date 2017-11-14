#ifndef MENUACTION_H
#define MENUACTION_H
#include "chipannotator.h"


class MenuAction
{

public:
    QString m_current_image_file_path;
    bool m_modified = false;

private:
    static bool isFileNameValid(const QString& filename);
    static QStringList createAllFileNames(const QString& filename);
    bool askToSaveAndProceed(const QString& action);

signals:
    void displayImageSignal(std::array<QPixmap, 3> res);

public slots:
    void onOpenClicked();
    void onSaveClicked();





};



#endif // MENUACTION_H
