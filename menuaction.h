#ifndef MENUACTION_H
#define MENUACTION_H
#include "chipannotator.h"


class MenuAction: public QWidget
{
    Q_OBJECT
public:

    MenuAction(QWidget* parent = nullptr);
    virtual ~MenuAction() = default;

    QString m_current_image_file_path;
    bool m_modified = false;

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private:
    static bool isFileNameValid(const QString& filename);
    static QStringList createAllFileNames(const QString& filename);
    bool askToSaveAndProceed(const QString& action);

signals:
    void resetScene();
    void displayImageSignal(std::array<QPixmap, 3> res);
    void displayAnnotationSignal(QString& file_path);
    void displayGridSignal();
    void setWindowTitleSignal(QString& file_name);
    void saveAnnotationSignal(QString& file_name);

public slots:
    void onOpenClicked();
    void onSaveClicked();
    void onAnnotationModified();

};



#endif // MENUACTION_H
