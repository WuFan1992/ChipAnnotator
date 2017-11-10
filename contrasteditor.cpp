#include "contrasteditor.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <algorithm>
#include <cmath>

namespace
{

    cv::Mat qImage2Mat(const QImage& src)
    {
        auto img = src.convertToFormat(QImage::Format_RGB888);
        cv::Mat tmp(img.height(), img.width(), CV_8UC3, (uchar*)img.bits(), img.bytesPerLine());
        cv::Mat result;
        cvtColor(tmp, result, CV_BGR2RGB);
        return result;
    }

    QImage mat2QImage(const cv::Mat& src)
    {
        cv::Mat temp(src);
        QImage dest((const uchar*)temp.data, temp.cols, temp.rows, (int)(temp.step), QImage::Format_RGB888);
        dest.bits();
        return dest;
    }
}

QImage ContrastEditor::modifyContrast(const QImage& input, double alpha_factor, double beta_factor)
{
    auto mat = qImage2Mat(input);
    cv::Mat contrasted_map;
    mat.convertTo(contrasted_map, CV_8UC3, alpha_factor, beta_factor);
    return mat2QImage(contrasted_map);
}

ContrastedImage ContrastEditor::autoAdjustContrast(const QImage& input)
{
    QImage converted_image = input.convertToFormat(QImage::Format_Indexed8);

    QVector<QRgb> color_table = converted_image.colorTable();

    auto histogram = ContrastEditor::buildHistogram(converted_image);
    std::pair<int, int> limits = ContrastEditor::findOnePercentLimits(histogram);

    std::transform(color_table.begin(), color_table.end(), color_table.begin(), [&limits](QRgb& pixel) {

        int value = qBlue(pixel);
        value = std::max(value, limits.first);
        value = std::min(value, limits.second);
        int gray = double(value - limits.first) / (limits.second - limits.first) * 255;

        return qRgb(gray, gray, gray);
    });

    ContrastedImage result;
    converted_image.setColorTable(color_table);
    result.m_image = converted_image;
    result.m_alpha = 255.0 / (limits.second - limits.first);
    result.m_beta = -result.m_alpha * limits.first;

    return result;
}

Histogram ContrastEditor::buildHistogram(const QImage& image)
{
    Histogram histogram;
    const int gray_level_count = 256;
    const int pixel_count = image.width() * image.height();

    histogram.resize(gray_level_count, 0);

    for(int i = 0; i < image.width(); i++)
    {
        for(int j = 0; j < image.height(); j++)
        {
            auto gray_level = qBlue(image.pixel(i, j));
            histogram[gray_level]++;
        }
    }
    std::transform(histogram.begin(), histogram.end(), histogram.begin(),
                   [&pixel_count](float& value) { return value / pixel_count; });
    return histogram;
}

std::pair<int, int> ContrastEditor::findOnePercentLimits(const Histogram& histogram)
{
    float cumulated_bins = 0.0;
    Histogram::const_iterator i1_it
        = std::find_if(histogram.begin(), histogram.end(), [&cumulated_bins](const float& nb_pixels) {
              cumulated_bins += nb_pixels;
              if(cumulated_bins > 0.01) return true;
              return false;
          });
    cumulated_bins = 0.0;
    Histogram::const_iterator i2_it
        = std::find_if(histogram.begin(), histogram.end(), [&cumulated_bins](const float& nb_pixels) {
              cumulated_bins += nb_pixels;
              if(cumulated_bins > 0.99) return true;
              return false;
          });
    int i1 = std::distance(histogram.begin(), i1_it);
    int i2 = std::distance(histogram.begin(), i2_it);
    return std::pair<int, int>(i1, i2);
}


