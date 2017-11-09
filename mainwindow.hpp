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
#include "classes.hpp"
#include "colorlayout.h"
#include "utils.hpp"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() = default;

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private:

    AnnotatorScene *annotateur;
    AnnotatorView *annotaview;
   // QComboBox *sceneScaleCombo;


    QList<QGraphicsLineItem *> horizonLine_List;
    QList<QGraphicsLineItem *> verticalLine_List;


    ColorLayout *colorlayout;

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

signals:
    void newCurrentClass(QString name);
    void modified();


public slots:

    void onOpenClicked();

    void onSaveClicked();

    void onAnnotationModified();

    void sceneScaleChanged(const QString &scale);

    void PaintGrid(bool m_display_grid);

    bool hasImagesLoaded() const;

    void mouseMoveFunction( boost::optional<AnnotatorScene::Region> m_current_region);

    void mousePressFunction(AnnotatorScene::Region mousePressPos);

    void mouseReleaseFunction(AnnotatorScene::Region mouseReleasePos);

    quint8 classAtPosition(const AnnotatorScene::Region& pos) const;

     void processClick(const AnnotatorScene::Region& pos);

     void tagRegion(const AnnotatorScene::Region& region, boost::optional<quint8> classes = {});


   // void PaintAnnotation(bool m_display_annotations);


};
