#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilisateurs.h"
#include <QTreeWidgetItem>
#include <QMessageBox>
#include "profils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connection = new Connection;
       //show login window
       connection->show();


       //receive login, show main window
       connect(connection,SIGNAL(login()),this,SLOT(show()));


       //click button in connection, receive message
       connect(connection,SIGNAL(sendUserInf(QString,QString,QString)),this,SLOT(RecvUserInf(QString,QString,QString)));
       //click button in connection, clear show window
       connect(connection,SIGNAL(sendUserInf(QString,QString,QString)),ui->profillist,SLOT(clear()));
       //click button in connection, reload button gestion
    //   connect(connection,SIGNAL(sendUserInf(QString,QString,QString)),ui->Gestion_Button,SLOT(setDisabled(false)));
       //creer new subwindow
       m_pdiscon = new disconnecter(NULL);
       m_pgestion=new gestionUtilisateur(NULL);
       connect(this,SIGNAL(SendUserInformation(QString,QString)),m_pdiscon,SLOT(ReceiveUserIn(QString,QString)));
       //connect(this,SIGNAL(SendUserInformation(QString,QString)),m_pgestion,SLOT(ReceiveUserInfo(QString,QString)));

       //disconnect
       connect(m_pdiscon,SIGNAL(close_win()),this,SLOT(close()));
       connect(m_pdiscon,SIGNAL(close_win()),connection,SLOT(show()));

       connect(connection,SIGNAL(sendUserInf(QString,QString,QString)),this,SLOT(Notion()));

       ui->profillist->setColumnCount(1);
       ui->profillist->setHeaderLabel(tr("Profil"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Disconnect_Button_clicked()
{
    //click button, open disconnect window, send nom et pw
    emit SendUserInformation(usernom,userpw);
    m_pdiscon->show();
    m_pdiscon->raise();

}

void MainWindow::Notion()
{
    QMessageBox::information(this, tr("Attention"), tr("Click button 'Autoriser' SVP pour afficher les utilisateurs et leurs profils!"));
}


void MainWindow::on_Gestion_Button_clicked()
{  //if priorite=1, normal user; button disabled
   //else p=0, admin, open gestion window
    //si utilisateur normal, disable GestionUtilisateur Button
    if(userpriorite=="1")
    {
        ui->Gestion_Button->setDisabled(true);
        QMessageBox::information(this, tr("Authentification"), tr("Vous n'avez pas cette autorisation."));
        ui->Gestion_Button->setDisabled(false);
    }
    else
    {
        m_pgestion->show();
        m_pgestion->raise();
    }

}

/* recevoir des donnees*/
void MainWindow::RecvUserInf(QString userNom, QString userPw,QString userPriorite)
{
    usernom=userNom;
    userpw=userPw;
    userpriorite=userPriorite;

}

void MainWindow::initTreeView()
{
    //clear old record
    ui->profillist->clear();
   // QTreeWidgetItem user;
    //obtenir utilisateurs list
    QList<QString> userlist=utilisateurs::readUtilisateurList("../utilisateurs.xml");

   // ui->profillist->addTopLevelItem(&oneuser);
  if(userpriorite=="0")   //admin login, show all users and their profils
    {
      if(!userlist.isEmpty())
      {
          //add list user
          for(int i=0;i<userlist.count();i++)
          {
              QTreeWidgetItem* newTopItem = new QTreeWidgetItem();
              const QString nomItem=userlist.at(i);

              newTopItem->setText(0,nomItem);
              ui->profillist->addTopLevelItem(newTopItem);
              //already add one user, check and add his profils as child node
              QList<QString> profilList=profils::readProfilListparUser("../profils.xml",nomItem);
              if(profilList.isEmpty())
              {
                //in profil doc, no record of this user
                  QMessageBox::information(this, tr("Attention"), tr("Cet utilisateur n'existe pas dans le doc, verifier le doc profil SVP!"));

              }
              else if(profilList.first()=="*")
              {
                  //file operation fail
                  QMessageBox::information(this, tr("Attention"), tr("Fichier operations échec, actualisez SVP!"));
              }
              else if(profilList.first()=="#")
              {
                  //have this user record but has 0 profils
                  //do nothing
              }
              else
              {
                  //has some profil
                  for(int j=0;j<profilList.count();j++)
                  {
                      QTreeWidgetItem* newprofilItem = new QTreeWidgetItem();
                      const QString nomProf=profilList.at(j);
                      newprofilItem->setText(0,nomProf);
                      newTopItem->addChild(newprofilItem);

                  }
              }
          }

      }
      else
      {
          QMessageBox::information(this, tr("Attention"), tr("Maintenant pas de utilisateur general!"));
      }

    }
    else  //priorite=1, user login, show his profils
    {
       QTreeWidgetItem *newTopItem = new QTreeWidgetItem();
       const QString loginnom=usernom;
       newTopItem->setText(0,loginnom);
       ui->profillist->addTopLevelItem(newTopItem);
       //already add one user, check and add his profils as child node
       QList<QString> profilList=profils::readProfilListparUser("../profils.xml",loginnom);
       if(profilList.isEmpty())
       {
         //in profil doc, no record of this user
           QMessageBox::information(this, tr("Attention"), tr("Cet utilisateur n'existe pas dans le doc, verifier le doc profil SVP!"));

       }
       else if(profilList.first()=="*")
       {
           //file operation fail
           QMessageBox::information(this, tr("Attention"), tr("Fichier operations échec, actualisez SVP!"));
       }
       else if(profilList.first()=="#")
       {
           //have this user record but has 0 profils
           //do nothing
       }
       else
       {
           //has some profil
           for(int j=0;j<profilList.count();j++)
           {
               QTreeWidgetItem* newprofilItem = new QTreeWidgetItem();
               const QString nomProf=profilList.at(j);
               newprofilItem->setText(0,nomProf);
               newTopItem->addChild(newprofilItem);

           }
       }

    }

}

void MainWindow::on_Actualiser_clicked()
{
    initTreeView();
}


