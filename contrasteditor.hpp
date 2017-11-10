#pragma once

#include <vector>

#include <QImage>

typedef std::vector<float> Histogram;

struct ContrastedImage
{
    QImage m_image;
    double m_alpha;
    double m_beta;
};

class ContrastEditor
{

public:
    ContrastEditor() = default;

    virtual ~ContrastEditor() = default;

    static QImage modifyContrast(const QImage& input, double alpha_factor, double beta_factor);

    static ContrastedImage autoAdjustContrast(const QImage& input);

    static Histogram buildHistogram(const QImage& image);

    static std::pair<int, int> findOnePercentLimits(const Histogram& histogram);
};


