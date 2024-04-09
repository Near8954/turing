#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), SLOT(on_step_button_clicked()));
    animation = new QPropertyAnimation(ui->label, "geometry");
    ui->step_button->setEnabled(false);
    ui->stop_button->setEnabled(false);
    ui->pause_button->setEnabled(false);
    ui->start_button->setEnabled(false);
    ui->set_string_button->setEnabled(false);
    ui->lineEdit_2->hide();
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
    if (!ver_header.empty() && !hor_header.empty()) {

    }
    ver_header.push_back(QString::fromStdString("q" + std::to_string(state_cnt)));
    ui->tableWidget->setColumnCount(std_main.size() + std_additional.size() + 1);
    ui->tableWidget->setRowCount(1);
    hor_header = lst;
    ui->tableWidget->setHorizontalHeaderLabels(hor_header);
    ui->tableWidget->setVerticalHeaderLabels(ver_header);
    ++state_cnt;
}

void MainWindow::on_set_alphabet_button_clicked()
{
    alphabet_form = new Dialog(this);
    connect(alphabet_form, &Dialog::signal, this, &MainWindow::slot);
    connect(alphabet_form, &Dialog::create_table, this, &MainWindow::table);
    alphabet_form->show();
    this->hide();
    ui->set_string_button->setEnabled(true);
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
    ui->start_button->setEnabled(true);
    ui->stop_button->setEnabled(true);
    ui->lineEdit_2->setText(main_alphabet);
    if (string_check(string, main_alphabet.toStdString())) {
        tape_data.resize(2e5, "Λ");
        ui->step_button->setEnabled(true);
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
    ver_header.push_back(QString::fromStdString("q" + std::to_string(state_cnt)));
    ui->tableWidget->insertRow(state_cnt++);
    ui->tableWidget->setVerticalHeaderLabels(ver_header);

}


void MainWindow::on_delete_state_clicked()
{
    ui->tableWidget->removeRow(--state_cnt);
    ver_header.pop_back();
}

bool MainWindow::table_check()
{
    QList<QTableWidgetItem* > lst = ui->tableWidget->findItems("!", Qt::MatchContains);
    if (lst.size() == 0) {
        return false;
    }
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
            if (ui->tableWidget->item(i, j) == 0) {
                return false;
            }
            QString item = ui->tableWidget->item(i, j)->text();
            if (item.count(',') != 2) {
                return false;
            }
            QStringList list = item.split(',');
            if (list[0].size() > 1) {
                return false;
            }
            if (list[0].size() == 0) {
                continue;
            }
            if (main_alphabet.toStdString().find(list[0].toStdString()) == std::string::npos &&
                additional_alphabet.toStdString().find(list[0].toStdString()) == std::string::npos) {
                return false;
            }
        }
    }
    return true;
}

void MainWindow::move_right()
{
    if (head_pos == 10)
    {
        animation->setDuration(50);
        animation->setStartValue(ui->label->geometry());
        animation->setEndValue(QRect(20, 160, 60, 60));
        animation->start();
        head_pos = 0;
        pos += 11;
        rend();
    }
    else
    {
        head_pos++;
        animation->setDuration(speed - speed / 10);
        animation->setStartValue(ui->label->geometry());
        animation->setEndValue(QRect(ui->label->pos().x() + 60, 160, 60, 60));
        animation->start();
    }
}

void MainWindow::move_left()
{
    if (head_pos == 0)
    {
        animation->setDuration(50);
        animation->setStartValue(ui->label->geometry());
        animation->setEndValue(QRect(620, 160, 60, 60));
        animation->start();
        head_pos = 10;
        pos -= 11;
        rend();
    }
    else
    {
        head_pos--;
        animation->setDuration(speed - speed / 10);
        animation->setStartValue(ui->label->geometry());
        animation->setEndValue(QRect(ui->label->pos().x() - 60, 160, 60, 60));
        animation->start();
    }
}


void MainWindow::on_step_button_clicked()
{
    if (table_check()) {
        QString s = ui->tableWidget->item(state, hor_header.indexOf(tape_data[header_pos]))->text();
        ui->lineEdit_2->setText(QString::fromStdString(std::to_string(prev_row)));
        int tmp = hor_header.indexOf(tape_data[header_pos]);
        if (prev_row != -1 && prev_col != -1) {
            ui->tableWidget->item(prev_row, prev_col)->setBackground(Qt::white);
        }
        ui->tableWidget->item(state, hor_header.indexOf(tape_data[header_pos]))->setBackground(Qt::yellow);
        QStringList list = s.split(',');
        qDebug() << list[0];
        if (list[0] != "") {
            tape_data [header_pos] = list[0];
        }
        if (list[1] != "") {
            if (list[1] == "R") {
                move_right();
                ++header_pos;
            } else {
                move_left();
                --header_pos;
            }
        }
        if (list[2] == "!") {
            on_pause_button_clicked();
        }
        if (list[2] != "") {
            QString st_num;
            for (auto e : list[2]) {
                if (e.isDigit()) {
                    st_num += e;
                }
            }
            state = st_num.toInt();
        }
        prev_row = state;
        prev_col = tmp;
        rend();
    }
}


void MainWindow::on_stop_button_clicked()
{
    pos = 1e5;
    header_pos = 1e5;
    rend();
    animation->setDuration(50);
    animation->setStartValue(ui->label->geometry());
    animation->setEndValue(QRect(20, 160, 60, 60));
    animation->start();
    head_pos = 0;
    timer.stop();
    if (prev_col != -1 && prev_row != -1) {
        ui->tableWidget->item(prev_row, prev_col)->setBackground(Qt::white);
    }
    ui->tableWidget->setEnabled(true);
}


void MainWindow::on_start_button_clicked()
{
    timer.start(speed);
    ui->pause_button->setEnabled(true);
    ui->tableWidget->setEnabled(false);
}


void MainWindow::on_pause_button_clicked()
{
    timer.stop();
    ui->tableWidget->setEnabled(true);
    ui->pause_button->setEnabled(false);
}


void MainWindow::on_increase_speed_clicked()
{
    if (speed > 100) {
        speed -= 100;
    }
}


void MainWindow::on_reduce_speed_clicked()
{
    speed += 100;
}

