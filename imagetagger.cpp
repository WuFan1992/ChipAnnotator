#include "imagetagger.hpp"

#include "classes.hpp"

#include <QMouseEvent>
#include <QPainter>


const QSize ImageTagger::c_image_resolution(3264, 2304);
const QSize ImageTagger::c_annotation_resolution(51, 36);

ImageTagger::Region::Region(int x, int y)
    : QPoint(x, y)
{
}

ImageTagger::ImageTagger(QWidget* parent)
    : QLabel(parent)
    , m_result(c_annotation_resolution, QImage::Format_Grayscale8)
{
    m_result.fill(0);
    setMouseTracking(true);
    setMinimumSize(800, 600);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

void ImageTagger::display(const QPixmap& pixmap, const QString& annotation)
{
    if(pixmap.size() != c_image_resolution)
        throw std::runtime_error("Image resolution unsupported : " + std::to_string(pixmap.size().width()) + "x"
                                 + std::to_string(pixmap.size().height()));
    m_pixmap = pixmap;
    setPixmap(m_pixmap.scaled(size(), Qt::KeepAspectRatio));
    if(annotation.isEmpty())
        m_result.fill(0);
    else
    {
        m_result.load(annotation);
        m_result = m_result.copy(QRect(QPoint(0, 0), c_annotation_resolution));
    }
}

bool ImageTagger::isGridEnabled() const
{
    return m_display_grid;
}

void ImageTagger::setGridEnabled(const bool enabled)
{
    m_display_grid = enabled;
    update();
}

bool ImageTagger::areAnnotationsEnabled() const
{
    return m_display_annotations;
}

void ImageTagger::setAnnotationsEnabled(const bool enabled)
{
    m_display_annotations = enabled;
    update();
}

void ImageTagger::setClass(quint8 class_index)
{
    m_current_class = class_index;
}

const QImage& ImageTagger::result() const
{
    return m_result;
}

void ImageTagger::resizeEvent(QResizeEvent* evt)
{
    Q_UNUSED(evt);
    if(m_pixmap.isNull()) return;
    setPixmap(m_pixmap.scaled(size(), Qt::KeepAspectRatio));
}

void ImageTagger::paintEvent(QPaintEvent* evt)
{
    QLabel::paintEvent(evt);
    if(m_pixmap.isNull()) return;
    QPainter p(this);
    if(m_display_annotations) paintAnnotations(p);
    if(m_current_region) paintCurrentRegion(p);
    if(m_display_grid) paintGrid(p);
}

void ImageTagger::leaveEvent(QEvent* evt)
{
    Q_UNUSED(evt);
    m_current_region.reset();
    m_mouse_pressed = false;
    update();
}

void ImageTagger::mouseMoveEvent(QMouseEvent* evt)
{
    if(m_pixmap.isNull()) return;
    m_current_region = screenToRegion(evt->pos());
    if(m_mouse_pressed) tagRegion(screenToRegion(evt->pos()));
    update();
}

void ImageTagger::mousePressEvent(QMouseEvent* evt)
{
    if(m_pixmap.isNull()) return;
    m_mouse_pressed = true;
    tagRegion(screenToRegion(evt->pos()));
    update();
}

void ImageTagger::mouseReleaseEvent(QMouseEvent* evt)
{
    if(m_pixmap.isNull()) return;
    tagRegion(screenToRegion(evt->pos()));
    m_mouse_pressed = false;
    update();
}

auto ImageTagger::screenToRegion(const QPoint& pos) const -> Region
{
    assert(!m_pixmap.isNull());
    return Region(pos.x() / increment().x(), pos.y() / increment().y());
}

QPointF ImageTagger::increment() const
{
    assert(!m_pixmap.isNull());
    const auto grid_size = pixmap()->size();
    const auto x = (double)grid_size.width() / c_annotation_resolution.width();
    const auto y = (double)grid_size.height() / c_annotation_resolution.height();
    return {x, y};
}

void ImageTagger::paintAnnotations(QPainter& p)
{
    for(int x = 0; x < c_annotation_resolution.width(); x++)
        for(int y = 0; y < c_annotation_resolution.height(); y++)
        {
            const auto value = qGray(m_result.pixel(x, y));
            if(value == 0) continue;
            p.save();
            p.setPen(Qt::NoPen);
            auto color = Classes::classes()[value].color();
            color.setAlpha(150);
            p.setBrush(color);
            p.drawRect(increment().x() * x, increment().y() * y, increment().x(), increment().y());
            p.restore();
        }
}

void ImageTagger::paintGrid(QPainter& p)
{
    p.save();
    p.setPen(Qt::red);
    p.drawRect(QRect(QPoint(0, 0), pixmap()->size()));
    for(int x = 0; x < c_annotation_resolution.width(); x++)
        p.drawLine(increment().x() * (x + 1), 0, increment().x() * (x + 1), pixmap()->size().height());
    for(int y = 0; y < c_annotation_resolution.height(); y++)
        p.drawLine(0, increment().y() * (y + 1), pixmap()->size().width(), increment().y() * (y + 1));
    p.restore();
}

void ImageTagger::paintCurrentRegion(QPainter& p)
{
    p.save();
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255, 255, 255, 100));
    p.drawRect(increment().x() * m_current_region->x(), increment().y() * m_current_region->y(), increment().x(),
               increment().y());
    p.restore();
}

void ImageTagger::tagRegion(const Region& region)
{
    if(region.x() >= 0 && region.x() < m_result.width() && region.y() >= 0 && region.y() < m_result.height())
        m_result.setPixel(region.x(), region.y(), qRgb(m_current_class, m_current_class, m_current_class));
}
