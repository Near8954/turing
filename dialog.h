#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:
    void signal(QString, QString);
    void create_table();

private slots:
    void on_accept_button_clicked();

private:
    Ui::Dialog *ui;
    QWidget *par;
};

#endif // DIALOG_H
