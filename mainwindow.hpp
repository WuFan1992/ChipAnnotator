#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QComboBox>
#include <QList>
#include <QPushButton>

#include "annotatorscene.h"
#include "annotatorview.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() = default;

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private:
    //ImageTagger* m_tagger;

    AnnotatorScene *annotateur;
    AnnotatorView *annotaview;
    QComboBox *sceneScaleCombo;


    QList<QGraphicsLineItem *> horizonLine_List;
    QList<QGraphicsLineItem *> verticalLine_List;

    void prePaintGrid();



    QString m_current_image_file_path;
    bool m_modified = false;

    void setupMenuBar();

    static bool isFileNameValid(const QString& filename);

    /**
     * @brief createAllFileNames
     * @pre isFileNameValid(filename)
     * @param filename
     * @return
     */
    static QStringList createAllFileNames(const QString& filename);

    /**
    * @brief ask to save if modified and return true if the program should continue, and false if it should cancel.
    */
    bool askToSaveAndProceed(const QString& action);

//private slots:
public slots:

    void onOpenClicked();

    void onSaveClicked();

    void onAnnotationModified();


    void sceneScaleChanged(const QString &scale);


    void PaintGrid(bool m_display_grid);

    void ShowItem();
   // void PaintAnnotation(bool m_display_annotations);
};
