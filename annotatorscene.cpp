#include "annotatorscene.h"

#include "classes.hpp"
#include "contrasteditor.hpp"
#include "utils.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QBrush>

const QSize AnnotatorScene::c_image_resolution(3264, 2304);
const QSize AnnotatorScene::c_annotation_resolution(51, 36);

AnnotatorScene::Region::Region(int x, int y)
    : QPoint(x, y)
{
}

AnnotatorScene::AnnotatorScene()
    : QGraphicsScene()
{
    m_result = new QPixmap;
    m_result->scaled(c_annotation_resolution);
    m_result->fill(QColor(0,0,0));

}

void AnnotatorScene::display(const ImageStack_t &images, const QString &annotation)
{
    for(const auto& pixmap : images)
        if(pixmap.size() != c_image_resolution)
            throw std::runtime_error("Image resolution unsupported : " + std::to_string(pixmap.size().width()) + "x"
                                     + std::to_string(pixmap.size().height()));
    m_images = images;
    for(auto& a : m_alpha_level)
        a = 1.0f;
    for(auto& b : m_beta_level)
        b = 0.0f;

    updateBackgroundImage();

    if(annotation.isEmpty())
        m_result->fill(QColor(0,0,0));
    else
    {
        m_result->load(annotation);
        //*m_result = m_result->copy(QRect(QPoint(0, 0), c_annotation_resolution));
    }

}

bool AnnotatorScene::isGridEnabled() const
{
    return m_display_grid;
}

void AnnotatorScene::setGridEnabled(const bool enabled)
{
    if (m_display_grid != enabled)
        emit gridOn(m_display_grid);
    m_display_grid = enabled;
    update();
}

bool AnnotatorScene::areAnnotationsEnabled() const
{
    return m_display_annotations;
}

void AnnotatorScene::setAnnotationsEnabled(const bool enabled)
{
    m_display_annotations = enabled;
    update();
}

void AnnotatorScene::setClass(quint8 class_index)
{
    m_current_class = class_index;
}

const QPixmap AnnotatorScene::result() const
{
    return *m_result;
}

void AnnotatorScene::setChannel(quint8 channel_index)
{
    m_current_channel = channel_index;
    updateBackgroundImage();
}


void AnnotatorScene::resetContrastBrightness()
{
    m_alpha_level[m_current_channel] = 1.0f;
    m_beta_level[m_current_channel] = 0.0f;
    updateBackgroundImage();
}

void AnnotatorScene::autoContrastBrightness()
{
    if(!hasImagesLoaded()) return;
    const auto result = ContrastEditor::autoAdjustContrast(m_images[m_current_channel].toImage());
    m_alpha_level[m_current_channel] = result.m_alpha;
    m_beta_level[m_current_channel] = result.m_beta;
    updateBackgroundImage();
}

void AnnotatorScene::moreContrast()
{
    m_alpha_level[m_current_channel] *= 1.6;
    updateBackgroundImage();
}

void AnnotatorScene::lessContrast()
{
    m_alpha_level[m_current_channel] *= 0.625;
    updateBackgroundImage();
}

void AnnotatorScene::moreBrightness()
{
    m_beta_level[m_current_channel] += 10;
    updateBackgroundImage();
}

void AnnotatorScene::lessBrightness()
{
    m_beta_level[m_current_channel] -= 10;
    updateBackgroundImage();
}


bool AnnotatorScene::hasImagesLoaded() const
{
    return m_images.size() == 3 && !m_images.front().isNull();
}


quint8 AnnotatorScene::classAtPosition( const Region& pos) const
{
    return qRed(m_result->toImage().pixel(pos.x(), pos.y()));
    ;
}

void AnnotatorScene::updateBackgroundImage()
{
    const auto& pix = m_images[m_current_channel];
    if(!pix.isNull())
    {
        //const auto img = pix.scaled(size(), Qt::KeepAspectRatio).toImage();


       const auto img = pix.scaled(pix.size(),Qt::KeepAspectRatio).toImage();
        const auto processed_image
            = ContrastEditor::modifyContrast(img, m_alpha_level[m_current_channel], m_beta_level[m_current_channel]);
        //scene->setBackgroundBrush(QPixmap::fromImage(processed_image));
        QBrush *brushbackground = new QBrush(QPixmap::fromImage(processed_image));
        setBackgroundBrush(*brushbackground);
        setSceneRect(QRectF(0, 0, 3264, 2304));

    }
    update();
}




