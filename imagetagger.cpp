#include "imagetagger.hpp"

#include "classes.hpp"
#include "utils.hpp"

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

void ImageTagger::display(const ImageStack_t& images, const QString& annotation)
{
    for(const auto& pixmap : images)
        if(pixmap.size() != c_image_resolution)
            throw std::runtime_error("Image resolution unsupported : " + std::to_string(pixmap.size().width()) + "x"
                                     + std::to_string(pixmap.size().height()));
    m_images = images;
    updateBackgroundImage();
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

void ImageTagger::setChannel(quint8 channel_index)
{
    m_current_channel = channel_index;
    updateBackgroundImage();
}

void ImageTagger::resizeEvent(QResizeEvent* evt)
{
    Q_UNUSED(evt);
    if(!hasImagesLoaded()) return;
    setPixmap(m_images[m_current_channel].scaled(size(), Qt::KeepAspectRatio));
}

void ImageTagger::paintEvent(QPaintEvent* evt)
{
    QLabel::paintEvent(evt);
    if(!hasImagesLoaded()) return;
    QPainter p(this);
    if(m_display_annotations) paintAnnotations(p);
    if(m_current_region) paintCurrentRegion(p);
    if(m_display_grid) paintGrid(p);
}

void ImageTagger::leaveEvent(QEvent* evt)
{
    Q_UNUSED(evt);
    m_current_region.reset();
    m_current_button_pressed.reset();
    update();
}

void ImageTagger::mouseMoveEvent(QMouseEvent* evt)
{
    if(!hasImagesLoaded()) return;
    m_current_region = screenToRegion(evt->pos());
    if(m_result.rect().contains(m_current_region->x(), m_current_region->y()))
    {
        emit newCurrentClass(Classes::classes()[classAtPosition(*m_current_region)].name());
    }
    if(m_current_button_pressed) processClick(*m_current_region);
    update();
}

void ImageTagger::mousePressEvent(QMouseEvent* evt)
{
    if(!hasImagesLoaded()) return;
    if(evt->button() == Qt::LeftButton)
        m_current_button_pressed = Button::Left;
    else if(evt->button() == Qt::RightButton)
        m_current_button_pressed = Button::Right;
    else if(evt->button() == Qt::MiddleButton)
        m_current_button_pressed = Button::Wheel;
    processClick(screenToRegion(evt->pos()));
    update();
}

void ImageTagger::mouseReleaseEvent(QMouseEvent* evt)
{
    if(!hasImagesLoaded()) return;
    processClick(screenToRegion(evt->pos()));
    m_current_button_pressed.reset();
    update();
}

auto ImageTagger::screenToRegion(const QPoint& pos) const -> Region
{
    assert(hasImagesLoaded());
    return Region(pos.x() / increment().x(), pos.y() / increment().y());
}

QPointF ImageTagger::increment() const
{
    // assert(!m_pixmap.isNull());
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
            Utils::drawRectForClass(p, Classes::classes()[value],
                                    QRect(increment().x() * x, increment().y() * y, increment().x(), increment().y()));
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

void ImageTagger::tagRegion(const Region& region, boost::optional<quint8> classes)
{
    if(!classes) classes = m_current_class;
    if(region.x() >= 0 && region.x() < m_result.width() && region.y() >= 0 && region.y() < m_result.height())
        m_result.setPixel(region.x(), region.y(), qRgb(*classes, *classes, *classes));
}

void ImageTagger::processClick(const Region& pos)
{
    assert(m_current_button_pressed);
    switch(*m_current_button_pressed)
    {
    case Button::Left:
        tagRegion(pos);
        return;
    case Button::Right:
        tagRegion(pos, 0);
        return;
    case Button::Wheel:
        const auto class_id = classAtPosition(*m_current_region);
        emit selectClass(class_id);
        return;
    }
}

quint8 ImageTagger::classAtPosition(const Region& pos) const
{
    return qRed(m_result.pixel(pos.x(), pos.y()));
    ;
}

bool ImageTagger::hasImagesLoaded() const
{
    return m_images.size() == 3 && !m_images.front().isNull();
}

void ImageTagger::updateBackgroundImage()
{
    const auto& img = m_images[m_current_channel];
    if(!img.isNull()) setPixmap(img.scaled(size(), Qt::KeepAspectRatio));
    update();
}
