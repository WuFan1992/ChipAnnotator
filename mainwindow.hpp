#pragma once

#include <QMainWindow>
//#include "chipannotator.h"

class ChipAnnotator;
class MenuAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() = default;

    ChipAnnotator *m_chipannotator;
    MenuAction *m_menuaction;


   void setupMenuBar();
   void setupClassSelector();


};
