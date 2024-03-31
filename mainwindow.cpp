#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot(QString main_alphabet_t, QString additional_alphabet_t)
{
    main_alphabet = main_alphabet_t;
    additional_alphabet = additional_alphabet_t;
}

void MainWindow::table()
{
    QStringList lst;
    std::string std_main = main_alphabet.toStdString(), std_additional = additional_alphabet.toStdString();
    for (auto e : std_main)
    {
        std::string tmp = "";
        tmp += e;
        lst.push_back(QString::fromStdString(tmp));
    }
    std::string tmp = "";
    tmp += "Λ";
    lst.push_back(QString::fromStdString(tmp));
    for (auto e : std_additional)
    {
        std::string tmp = "";
        tmp += e;
        lst.push_back(QString::fromStdString(tmp));
    }
    ui->tableWidget->setColumnCount(std_main.size() + std_additional.size() + 1);
    ui->tableWidget->setRowCount(1);
    ++state_cnt;
    ui->tableWidget->setHorizontalHeaderLabels(lst);
}

void MainWindow::on_set_alphabet_button_clicked()
{
    alphabet_form = new Dialog(this);
    connect(alphabet_form, &Dialog::signal, this, &MainWindow::slot);
    connect(alphabet_form, &Dialog::create_table, this, &MainWindow::table);
    alphabet_form->show();
    this->hide();
}


void MainWindow::on_set_string_button_clicked()
{

}


void MainWindow::on_add_state_clicked()
{
    ui->tableWidget->insertRow(state_cnt++);
}


void MainWindow::on_delete_state_clicked()
{
    ui->tableWidget->removeRow(--state_cnt);
}

