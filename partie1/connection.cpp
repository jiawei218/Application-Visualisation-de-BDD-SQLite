#include "connection.h"
#include "utilisateurs.h"
#include "ui_connection.h"
#include "profils.h"
#include <QMessageBox>
#include <iostream>

Connection::Connection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connection)
{
    ui->setupUi(this);

    ui->PwlineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->LogButton,SIGNAL(clicked()),this,SLOT(LogButton_clicked()));
    connect(ui->RegistreButton,SIGNAL(clicked()),this,SLOT(RegistreButton_clicked()));

   //close window
    connect(this,SIGNAL(close_window()),this,SLOT(close()));

    int isCreated=utilisateurs::createXML("../utilisateurs.xml");
    if(isCreated==0)
    {  //fichier n'existe pas, créér nouveau doc, disable login, enable registre
        ui->LogButton->setDisabled(true);
    }
    else if(isCreated==-1)
    {  //fichier deja existe, on verifie nb d'utilisateurs
        int nbUtilisateur=utilisateurs::nombreUtilsiateur("../utilisateurs.xml");
        if(nbUtilisateur>0)
        {   //has admin, maybe others
            //login enable, registre disable
            ui->LogButton->setDisabled(false);
            ui->RegistreButton->setDisabled(true);
        }
        else if(nbUtilisateur==0)
        {//pas de utilisateurs, il faut qqn registre
            ui->LogButton->setDisabled(true);  //disable login; need register
            ui->RegistreButton->setDisabled(false);
        }
        else if(nbUtilisateur==-1||nbUtilisateur==-2)
        {   //read fichier failed
            ui->LogButton->setDisabled(true);
            QMessageBox::information(this, tr("Échec du chargement"), tr("Redémarrage l'application, SVP"));
        }

    }
    else
    { //create failed
        ui->LogButton->setDisabled(true);
        ui->RegistreButton->setDisabled(true);
        QMessageBox::information(this, tr("Échec du chargement"), tr("Redémarrage l'aaplication, SVP"));

    }

    int isOk=profils::createXML("../profils.xml");
    if(isOk==-2)
    {
        //create failed
        QMessageBox::information(this, tr("Échec du chargement"), tr("Redémarrage l'aaplication, SVP"));
    }


}

Connection::~Connection()
{
    delete ui;
}

void Connection::LogButton_clicked()
{
    //get nom and passwd
    QString name = ui->NomlineEdit->text().trimmed();
    QString password = ui->PwlineEdit->text().trimmed();
    if( name.isEmpty() || password.isEmpty() )
    {
        QMessageBox::information(this, tr("check input"), tr("user nom ou mot de passe vide"));
    }
    else
    {
        //verify exist
        int isExist=utilisateurs::chercherUtilisateur("../utilisateurs.xml",name,password);
        if(isExist==-1)
        {
            QMessageBox::information(this, tr("login error"), tr("Problem lecture fichier"));
        }
        else if(isExist==0)
        {
            //log fail
            QMessageBox::information(this, tr("login error"), tr("Utilisateur n'existe pas ou nom incorrect"));


        }
        else if(isExist==1)
        {
            //correct, log in succeed!
            // envoyer open window signal
            emit login();
            QString priorite=utilisateurs::prioriteUtilisateur("../utilisateurs.xml",name);
            if(priorite!="#")
            {
                emit sendUserInf(name,password,priorite);
            }
            else
            {
                QMessageBox::information(this, tr("Priorite"), tr("Echec! Reconnecter,SVP"));
            }
            // envoyer close window signal
            emit close_window();
        }
        else if(isExist==2)
        {
            QMessageBox::information(this, tr("login error"), tr("mot de passe error"));
        }
        else if(isExist==-2)
        {
            QMessageBox::information(this, tr("login error"), tr("doc setcontext error"));
        }
        //clear input
        ui->NomlineEdit->clear();
        ui->PwlineEdit->clear();
    }


}


void Connection::RegistreButton_clicked()
{
    //get nom and passwd
    QString name = ui->NomlineEdit->text().trimmed();
    QString password = ui->PwlineEdit->text().trimmed();
    if( name.isEmpty() || password.isEmpty() )
    {
        QMessageBox::information(this, tr("check input"), tr("user nom ou mot de passe vide"));
    }
    else
    {
        //verify exist
        int isExist=utilisateurs::chercherUtilisateur("../utilisateurs.xml",name,password);
        if(isExist==1 ||isExist==2)  //exist ce nom
        {
            QMessageBox::information(this, tr("register error"), tr("L'utilisateur déja existe"));
        }
        else if(isExist==-1 ||isExist==-2)  //fichier open error
        {
            QMessageBox::information(this, tr("register error"), tr("Problem lecture fichier"));
        }
        else   //isExist=0, ce nom n'existe pas
        {
            QString prio="0";
            int result=utilisateurs::appendUtilisateur("../utilisateurs.xml",name,password,prio);  //insert
            if(result==0)
            {  //succes
                QMessageBox::information(this, tr("register succes"), tr("Registre succes"));
                ui->LogButton->setDisabled(false);  //enable login button
                ui->RegistreButton->setDisabled(true);
            }
            else
            {  //echec
                QMessageBox::information(this, tr("register error"), tr("Registre echec"));
            }
        }
        //clear
        ui->NomlineEdit->clear();
        ui->PwlineEdit->clear();
    }

}





