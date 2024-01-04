#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XusoryEditor.h"

class XusoryEditor : public QMainWindow
{
    Q_OBJECT

public:
    XusoryEditor(QWidget *parent = nullptr);
    ~XusoryEditor();

private:
    Ui::XusoryEditorClass ui;
};
