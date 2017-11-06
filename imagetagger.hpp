#pragma once

#include <array>

#include <QLabel>

#include <boost/optional.hpp>

class ImageTagger : public QLabel
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

    explicit ImageTagger(QWidget* parent = nullptr);

    static const QSize c_image_resolution;
    static const QSize c_annotation_resolution;

    void display(const ImageStack_t& images, const QString& annotation = "");

    bool isGridEnabled() const;

    void setGridEnabled(const bool enabled);

    bool areAnnotationsEnabled() const;

    void setAnnotationsEnabled(const bool enabled);

    void setClass(quint8 class_index);

    const QImage& result() const;

    void setChannel(quint8 channel_index);

    void resetContrastBrightness();
    void autoContrastBrightness();
    void moreContrast();
    void lessContrast();
    void moreBrightness();
    void lessBrightness();

signals:
    void newCurrentClass(QString name);

    void selectClass(quint8 class_id);

    void modified();

protected:
    virtual void resizeEvent(QResizeEvent* evt) override;

    virtual void paintEvent(QPaintEvent* evt) override;

    virtual void leaveEvent(QEvent* evt) override;

    virtual void mouseMoveEvent(QMouseEvent* evt) override;

    virtual void mousePressEvent(QMouseEvent* evt) override;

    virtual void mouseReleaseEvent(QMouseEvent* evt) override;

private:
    enum class Button
    {
        Left,
        Right,
        Wheel
    };

    QImage m_result;
    bool m_display_grid = true;
    bool m_display_annotations = true;
    boost::optional<Button> m_current_button_pressed;
    quint8 m_current_class = 0;
    ImageStack_t m_images;
    boost::optional<Region> m_current_region;
    quint8 m_current_channel = 0;
    DoubleStack_t m_alpha_level = {1., 1., 1.};
    DoubleStack_t m_beta_level = {0., 0., 0.};

    /**
    * @pre m_pixmap is valid
    */
    Region screenToRegion(const QPoint& pos) const;

    /**
    * @pre m_pixmap is valid
    */
    QPointF increment() const;

    void paintAnnotations(QPainter& p);

    void paintGrid(QPainter& p);

    void paintCurrentRegion(QPainter& p);

    void tagRegion(const Region& region, boost::optional<quint8> classes = {});

    /**
     * @brief processClick
     * @param pos
     * @pre m_current_button_pressed is set
     */
    void processClick(const Region& pos);

    quint8 classAtPosition(const Region& pos) const;

    bool hasImagesLoaded() const;

    void updateBackgroundImage();
};
