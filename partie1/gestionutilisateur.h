#ifndef GESTIONUTILISATEUR_H
#define GESTIONUTILISATEUR_H

#include <QWidget>

namespace Ui {
class gestionUtilisateur;
}

class gestionUtilisateur : public QWidget
{
    Q_OBJECT

public:
    explicit gestionUtilisateur(QWidget *parent = nullptr);
    ~gestionUtilisateur();
    void UpdateListShow();

private slots:
 //   void ReceiveUserInfo(QString userNom, QString userPw);

    void on_Supprimer_clicked();

    void on_Ajouter_clicked();

    void on_Actualiser_clicked();

private:
    Ui::gestionUtilisateur *ui;
    QList<QString> listUser;

};

#endif // GESTIONUTILISATEUR_H
