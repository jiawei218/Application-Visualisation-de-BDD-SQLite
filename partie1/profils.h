#ifndef PROFILS_H
#define PROFILS_H
#include <QString>
#include <QDomDocument>
#include <QList>
#include <QMap>


class profils
{
public:
    profils();

    static int createXML(QString filePath);
    static int nombreProfilparUser(QString filePath, QString nomU, QString nomP);
    static QList<QString> readProfilListparUser(QString filePath, QString nomU); //read xml doc
    static QList<QString> readProfil(QString filePath, QString nomU, QString nomP);
    //add
    static int appendUser(QString filePath, QString nomU);  //when add a new user, add his information in profil doc
    static int appendProfilparUser(QString filePath, QString nomU,QString nomP);  //add new records
    static void writeProfil(QDomDocument &doc,QDomElement &root,QStringList &plist);
    //delete
    static int supprimerProfilparUser(QString filePath, QString nomU, QString nomP);  //add new records


};

#endif // PROFILS_H
