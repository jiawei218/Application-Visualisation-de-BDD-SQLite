#include "disconnecter.h"
#include "ui_disconnecter.h"
#include <QMessageBox>

disconnecter::disconnecter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::disconnecter)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);

}

disconnecter::~disconnecter()
{
    delete ui;
}

void disconnecter::on_Disconn_Button_clicked()
{
    QString pw_input=ui->Password->text().trimmed();
    if( pw_input.isEmpty())
    {
        QMessageBox::information(this, tr("check input"), tr("mot de passe vide"));
    }
    else
    {
        if(pw_input==user_pw)
        {
            //close windows
            emit close_win();
            close();
        }
        else
        {
            QMessageBox::information(this, tr("Disconnexion"), tr("Mot de passe incorrect, ressayez SVP"));
        }
        ui->Password->clear();
    }

}


void disconnecter::ReceiveUserIn(QString userNom, QString userPw)
{
    user_nom=userNom;
    user_pw=userPw;

}

