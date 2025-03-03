#include "gestionutilisateur.h"
#include "ui_gestionutilisateur.h"
#include "utilisateurs.h"
#include <QMessageBox>
#include "profils.h"
#include <iostream>
#include <QListWidget>
#include <QListWidgetItem>

gestionUtilisateur::gestionUtilisateur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gestionUtilisateur)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    UpdateListShow();

}

gestionUtilisateur::~gestionUtilisateur()
{
    delete ui;
}


/*void gestionUtilisateur::ReceiveUserInfo(QString userNom, QString userPw)
{

}
*/

/*supprimer utilisateur choisi*/
void gestionUtilisateur::on_Supprimer_clicked()
{
    int nCurRow = ui->listUsers->currentRow();
        if( nCurRow < 0)
        {
            //no choix
            QMessageBox::information(this, tr("Supprimer echec"), tr("Choix incorrect"));

        }
        else
        {  //choisir le ligne on veut supprimer
            QString utilisateurChoisi=ui->listUsers->currentItem()->text();  //obtenir nom de l'utilisateur choisi
            int isOk=utilisateurs::supprimerUtilisateur("../utilisateurs.xml",utilisateurChoisi);
            if(isOk==0)
            {
                QMessageBox::information(this, tr("Supprimer succes"), tr("Supprimer Succes"));
                UpdateListShow();
            }
            else if(isOk==-1 ||isOk==-2)
            {
                QMessageBox::information(this, tr("Supprimer echec"), tr("Problem lecture fichier"));
            }

        }
}

/* ajouter utilisateur*/
void gestionUtilisateur::on_Ajouter_clicked()
{

    //get nom and passwd for new user
    QString name = ui->nom->text().trimmed();
    QString password = ui->password->text().trimmed();
    if( name.isEmpty() || password.isEmpty() )
    {
        QMessageBox::information(this, tr("check input"), tr("user nom ou mot de passe vide"));
    }
    else
    {

        int isExiste=utilisateurs::chercherUtilisateur("../utilisateurs.xml",name,password);
        if(isExiste==1||isExiste==2)  //utilisateur deja existe
        {
            QMessageBox::information(this, tr("ajoute echec"), tr("L'utilisateur déja existe"));
        }
        else if(isExiste==-1 ||isExiste==-2)  //lire fichier echec
        {
            QMessageBox::information(this, tr("ajoute echec"), tr("Problem lecture fichier"));
        }
        else
        {
            //utilisateur n'existe pas
            QString prio="1";
            int result=utilisateurs::appendUtilisateur("../utilisateurs.xml",name,password,prio);  //insert
            if(result==0)
            {  //succes
                QMessageBox::information(this, tr("ajoute succes"), tr("Ajoute succes"));
                UpdateListShow();
                int result_profil=profils::appendUser("../profils.xml",name);
                if(result_profil!=0)
                {
                    QMessageBox::information(this, tr("ajoute profil echec"), tr("ajoute profil echec!"));
                }
            }
            else
            {  //echec
                QMessageBox::information(this, tr("ajoute echec"), tr("Ajoute echec, ressayez SVP"));
            }

        }
        //clear
        ui->nom->clear();
        ui->password->clear();
    }


}

/* update list des utilisateurs pour afficher dans listWidget */
void gestionUtilisateur::UpdateListShow()
{
    //clear old list
        ui->listUsers->clear();
        listUser=utilisateurs::readUtilisateurList("../utilisateurs.xml");
        if(!listUser.isEmpty())
        {
            ui->listUsers->addItems(listUser);
        }


}



/* actualiser list des utilisateurs */
void gestionUtilisateur::on_Actualiser_clicked()
{
    UpdateListShow();
}

