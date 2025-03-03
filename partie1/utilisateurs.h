#ifndef UTILISATEURS_H
#define UTILISATEURS_H
#include <QDomDocument>
#include <QStringList>

class utilisateurs
{
public:
    utilisateurs();
//utilisateurs
    static int createXML(QString filePath);
    static int nombreUtilsiateur(QString filePath);
    static QString prioriteUtilisateur(QString filePath,QString nom);

    static QList<QString> readUtilisateurList(QString filePath); //read xml doc

    static int chercherUtilisateur(QString filePath, QString nom,QString passwd); //chercher un utilisateur dans xml doc
    //add
    static int appendUtilisateur(QString filePath, QString nom,QString passwd, QString priorite);  //add new records
    static void writeUtilisateur(QDomDocument &doc,QDomElement &root,QStringList &plist);
    //delete
    static int supprimerUtilisateur(QString filePath, QString nom);  //add new records

};

#endif // UTILISATEURS_H
