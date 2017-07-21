#pragma once

#include <QMainWindow>

class ImageTagger;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() = default;

private:
    ImageTagger* m_tagger;
    QString m_current_image_file_path;

    void setupMenuBar();

    static bool isFileNameValid(const QString& filename);

    /**
     * @brief createAllFileNames
     * @pre isFileNameValid(filename)
     * @param filename
     * @return
     */
    static QStringList createAllFileNames(const QString& filename);

private slots:
    void onOpenClicked();

    void onSaveClicked();

    void onSaveAsClicked();
};
