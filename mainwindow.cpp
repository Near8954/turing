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

bool string_check(std::string s1, std::string s2) {
    for (auto e : s1) {
        if (s2.find(e) == std::string::npos) {
            return false;
        }
    }
    return true;
}

void MainWindow::rend() {
    for (int i = 0; i < 11; ++i) {
        this->tape[i]->setText(tape_data[pos + i]);
    }
}

void MainWindow::on_set_string_button_clicked()
{
    std::string string = ui->lineEdit->text().toStdString();
    if (string_check(string, main_alphabet.toStdString())) {
        tape_data.resize(2e5, "Λ");
        tape.push_back(ui->label_1);
        tape.push_back(ui->label_2);
        tape.push_back(ui->label_3);
        tape.push_back(ui->label_4);
        tape.push_back(ui->label_5);
        tape.push_back(ui->label_6);
        tape.push_back(ui->label_7);
        tape.push_back(ui->label_8);
        tape.push_back(ui->label_9);
        tape.push_back(ui->label_10);
        tape.push_back(ui->label_11);
        for (auto e : string) {
            tape_data[pos] = e;
            ++pos;
        }
        pos = 1e5;
        rend();
    }

}


void MainWindow::on_add_state_clicked()
{
    ui->tableWidget->insertRow(state_cnt++);
}


void MainWindow::on_delete_state_clicked()
{
    ui->tableWidget->removeRow(--state_cnt);
}

bool MainWindow::table_check()
{
    QList<QTableWidgetItem* > lst = ui->tableWidget->findItems("!", Qt::MatchContains);
    if (lst.size() == 0) {
        return false;
    }
    return true;
}

void MainWindow::on_step_button_clicked()
{
    if (table_check()) {
        ui->tableWidget->horizontalHeaderItem();
    }
}

