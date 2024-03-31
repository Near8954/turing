#include "dialog.h"
#include "ui_dialog.h"
#include <set>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    par = parent;
}

Dialog::~Dialog()
{
    delete ui;
}

bool check(QString s1, QString s2) {
    std::string std_s1 = s1.toStdString();
    std::string std_s2 = s2.toStdString();
    std::set<char> st;
    for (auto e : std_s1) {
        st.insert(e);
    }
    if (st.size() != std_s1.size()) {
        return false;
    }
    st.clear();
    for (auto e : std_s2) {
        st.insert(e);
    }
    if (st.size() != std_s2.size()) {
        return false;
    }
    if (std_s1.size() > std_s2.size())
    {
        std::swap(std_s1, std_s2);
    }
    for (auto e : std_s1)
    {
        if (std_s2.find(e) != std::string::npos)
        {
            return false;
        }
    }
    return true;
}



void Dialog::on_accept_button_clicked()
{
    QString main = ui->lineEdit->text(), additional=ui->lineEdit_2->text();
    if (check(main, additional))
    {
        emit signal(main, additional);
        emit create_table();
        par->show();
        close();
    }
}

