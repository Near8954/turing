#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void slot(QString main_alphabet, QString additional_alphabet);
    void table();
private slots:
    void on_set_alphabet_button_clicked();

    void on_set_string_button_clicked();

    void on_add_state_clicked();

    void on_delete_state_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *alphabet_form;
    QString main_alphabet, additional_alphabet;
    int state_cnt = 0;
};
#endif // MAINWINDOW_H
