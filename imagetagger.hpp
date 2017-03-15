#pragma once

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

    explicit ImageTagger(QWidget* parent = nullptr);

    static const QSize c_image_resolution;
    static const QSize c_annotation_resolution;

    void display(const QPixmap& pixmap);

    bool isGridEnabled() const;

    void setGridEnabled(const bool enabled);

    bool areAnnotationsEnabled() const;

    void setAnnotationsEnabled(const bool enabled);

    void setClass(quint8 class_index);

    const QImage& result() const;

protected:
    virtual void resizeEvent(QResizeEvent* evt) override;

    virtual void paintEvent(QPaintEvent* evt) override;

    virtual void leaveEvent(QEvent* evt) override;

    virtual void mouseMoveEvent(QMouseEvent* evt) override;

    virtual void mousePressEvent(QMouseEvent* evt) override;

    virtual void mouseReleaseEvent(QMouseEvent* evt) override;

private:
    QImage m_result;
    bool m_display_grid = true;
    bool m_display_annotations = true;
    quint8 m_current_class = 0;
    QPixmap m_pixmap;
    boost::optional<Region> m_current_region;

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
};
