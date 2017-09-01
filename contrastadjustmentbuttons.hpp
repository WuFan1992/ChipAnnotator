#include <QGridLayout>
#include <QPointer>
#include <QWidget>

#include <vector>

class QPushButton;

class ContrastAdjustmentButtons : public QWidget
{
    Q_OBJECT
public:
    explicit ContrastAdjustmentButtons(bool horizontal = false, QWidget* parent = nullptr);
    ~ContrastAdjustmentButtons() = default;

    void setMinimalSize();

private:
    std::vector<QPointer<QWidget>> m_hideable_widgets;
    bool m_keep_minimal_size;
    QPushButton* m_auto_btn;
    QPushButton* m_reset_btn;

    QGridLayout* createGridControls();
    void setPlusIcon(QPushButton* button);
    void setMinusIcon(QPushButton* button);

signals:
    void resetClicked();
    void autoClicked();

    void moreContrastClicked();
    void lessContrastClicked();
    void moreBrightnessClicked();
    void lessBrightnessClicked();
};
