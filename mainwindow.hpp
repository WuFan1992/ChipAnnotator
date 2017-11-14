#pragma once

#include <QMainWindow>
//#include "chipannotator.h"

class ChipAnnotator;
class MenuAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() = default;

    ChipAnnotator *chipannotator;
    MenuAction *menuaction;


protected:
    virtual void closeEvent(QCloseEvent* event) override;

public:
   //QString m_current_image_file_path;
   //bool m_modified = false;

   void setupMenuBar();
   void setupClassSelector();

   //static bool isFileNameValid(const QString& filename);

    /**
     * @brief createAllFileNames
     * @pre isFileNameValid(filename)
     * @param filename
     * @return
     */
    //static QStringList createAllFileNames(const QString& filename);

    /**
    * @brief ask to save if modified and return true if the program should continue, and false if it should cancel.
    */
    bool askToSaveAndProceed(const QString& action);


public slots:

    //void onOpenClicked();

    void onSaveClicked();

    void onAnnotationModified();

    void displayAnnotation(QString &annoation);


};
