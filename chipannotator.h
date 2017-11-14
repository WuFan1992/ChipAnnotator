#ifndef CHIPANNOTATOR_H
#define CHIPANNOTATOR_H

#include <QHBoxLayout>
#include "annotatorscene.h"
#include "annotatorview.h"
#include "colorlayout.h"
#include "utils.hpp"
#include "classes.hpp"
#include "classselector.hpp"

class ChipAnnotator: public QWidget
{

       Q_OBJECT
public:
    ChipAnnotator(QWidget* parent = nullptr);
    virtual ~ChipAnnotator() = default;

    QHBoxLayout *layout;

public:
    AnnotatorScene *annotateur;
    AnnotatorView *annotaview;

    ColorLayout *colorlayout;

    QList<QGraphicsLineItem *> horizonLine_List;
    QList<QGraphicsLineItem *> verticalLine_List;





signals:
    void newCurrentClass(QString name);
    void modified();


public:
    void setAnnotatorScene();
    void setAnnotatorView();

    void prePaintGrid();

    void mouseActionControle();


public slots:

    void mouseMoveFunction( boost::optional<AnnotatorScene::Region> m_current_region);

    void mousePressFunction(AnnotatorScene::Region mousePressPos);

    void mouseReleaseFunction(AnnotatorScene::Region mouseReleasePos);

    void processClick(const AnnotatorScene::Region& pos);

    void tagRegion(const AnnotatorScene::Region& region, boost::optional<quint8> classes = {});

    void leaveViewFunction();

    void showAnnotation(bool m_display_annotation);



    void displayGrid();

    void Reset();

    quint8 classAtPosition(const AnnotatorScene::Region& pos) const;

    bool hasImagesLoaded() const;

    void sceneScaleChanged(const QString &scale);

    void PaintGrid(bool m_display_grid);


    /**
     * @brief createAllFileNames
     * @pre isFileNameValid(filename)
     * @param filename
     * @return
     */


    /**
    * @brief ask to save if modified and return true if the program should continue, and false if it should cancel.
    */



};








#endif // CHIPANNOTATOR_H
