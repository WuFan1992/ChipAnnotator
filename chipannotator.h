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
    AnnotatorScene *m_annotateur;
    AnnotatorView *m_annotaview;

    ColorLayout *m_colorlayout;

    QList<QGraphicsLineItem *> m_horizonline_list;
    QList<QGraphicsLineItem *> m_verticalline_list;





signals:
    void newCurrentClass(QString name);
    void modified();
    void statusType(QString type_name);


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

    void displayAnnotation(QString &annoation);

    void displayGrid();

    void Reset();

    quint8 classAtPosition(const AnnotatorScene::Region& pos) const;

    bool hasImagesLoaded() const;

    void sceneScaleChanged(const QString &scale);

    void PaintGrid(bool m_display_grid);

    void saveAnnotation(QString& output_file_path);

    void showRectType(boost::optional<AnnotatorScene::Region> m_current_region);


};








#endif // CHIPANNOTATOR_H
