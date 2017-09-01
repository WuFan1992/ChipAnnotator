#pragma once

#include <QMainWindow>

class ImageTagger;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() = default;

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private:
    ImageTagger* m_tagger;
    QString m_current_image_file_path;
    bool m_modified = false;

    void setupMenuBar();

    static bool isFileNameValid(const QString& filename);

    /**
     * @brief createAllFileNames
     * @pre isFileNameValid(filename)
     * @param filename
     * @return
     */
    static QStringList createAllFileNames(const QString& filename);

    /**
    * @brief ask to save if modified and return true if the program should continue, and false if it should cancel.
    */
    bool askToSaveAndProceed(const QString& action);

private slots:
    void onOpenClicked();

    void onSaveClicked();

    void onAnnotationModified();
};
