#ifndef ANNOTATORSCENE_H
#define ANNOTATORSCENE_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <array>
#include <boost/optional.hpp>



class AnnotatorScene : public QGraphicsScene
{
    Q_OBJECT

public:
    class Region : private QPoint
    {
    public:
        explicit Region(int x, int y);

        using QPoint::x;
        using QPoint::y;
    };


    using ImageStack_t = std::array<QPixmap, 3>;
    using DoubleStack_t
    = std::array<double, 3>;

    explicit AnnotatorScene();

    static const QSize c_image_resolution;
    static const QSize c_annotation_resolution;
    void display(const ImageStack_t& images, const QString& annotation = "");

public:
    void resetContrastBrightness();
    void autoContrastBrightness();
    void moreContrast();
    void lessContrast();
    void moreBrightness();
    void lessBrightness();

    bool isGridEnabled() const;

    void setGridEnabled(const bool enabled);

    bool areAnnotationsEnabled() const;

    void setAnnotationsEnabled(const bool enabled);

    void setClass(quint8 class_index);

    void setChannel(quint8 channel_index);

    QPointF increment() const;


     const QPixmap result() const;


signals:
    void newCurrentClass(QString name);

    void selectClass(quint8 class_id);

    void modified();

    void gridOn(bool enabled);

    void AnnotationOn(bool enabled);



public:
    QGraphicsScene *scene;



public:
    QPixmap *m_result;

    ImageStack_t m_images;



    bool m_display_grid = true;
    bool m_display_annotations = true;


    quint8 m_current_class = 0;
    quint8 m_current_channel = 0;
    DoubleStack_t m_alpha_level = {1., 1., 1.};
    DoubleStack_t m_beta_level = {0., 0., 0.};



    bool hasImagesLoaded() const;

    void updateBackgroundImage();


    quint8 classAtPosition(const Region &pos) const ;


};




#endif // ANNOTATORSCENE_H
