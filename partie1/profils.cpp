#include "profils.h"
#include <QFile>
#include <iostream>
#include <QDomText>
#include <QDomElement>
#include <QDebug>
#include <iostream>
#include <QStringList>
#include <QString>
#include <QTextStream>

profils::profils()
{

}

int profils::createXML(QString filePath)
{
    QFile file(filePath);
    if(file.exists()==true)
    {//fichier existe
        std::cout<<"fichier deja existe";
        return -1;

    }
    else
    {
        //fichier no existe, creer le doc
        bool isOK=file.open(QIODevice::WriteOnly);
        if(isOK==true)
        {
            //open succeed
                QDomDocument doc;
                //root
                QDomElement root;
                QDomProcessingInstruction ins;
                ins=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
                doc.appendChild(ins);
                //root
                root=doc.createElement("ProfilsList");
                doc.appendChild(root);

                //save

                QTextStream stream(&file);
                doc.save(stream,4);
                file.close();
        }
        else
        {
            //open failed
            return -2;
        }
    }
    return 0;
}


QList<QString> profils::readProfilListparUser(QString filePath, QString nomU)
{
    //open doc
    QDomDocument doc;
    QList<QString> listProfilparUser;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
       listProfilparUser.append("*");  //show that doc operation fail
       return listProfilparUser;
    }
    if (!doc.setContent(&file))
    {
        listProfilparUser.append("*");
        return listProfilparUser;
    }
    file.close();
    //read racine note
    QDomElement root = doc.documentElement();  //ProfilsList ;racine
    if(root.hasChildNodes()==true)
    {
        QDomNodeList listProfil = root.childNodes();  //get list of all users
         for(int i=0;i<listProfil.count();i++)
         {
             //get node in list, check its attribue owner
             QDomNode profils=listProfil.at(i);
             QDomAttr a = profils.toElement().attributeNode("owner");
             if(a.value()==nomU)  //we find profils for user demande
             {
                 //get childnode: profils of this user
                 QDomNodeList listProfilofUser=profils.childNodes();
                 if(!listProfilofUser.isEmpty())  //for this user, he has >0 profil
                 {
                     for(int j=0;j<listProfilofUser.count();j++)
                     {
                         //for every profil
                         QDomNode prof=listProfilofUser.at(j);
                         // get information of this profil, now just profilnom, so we get directly
                         QDomNodeList contenu=prof.childNodes();
                         QString nomP=contenu.at(0).toElement().text();
                         listProfilparUser.append(nomP);
                     }

                 }
                 else //exist this user mais hs has 0 profil
                 {
                     listProfilparUser.append("#");
                 }

             }
         }
    }

    return listProfilparUser;
}

int profils::appendUser(QString filePath, QString nomU)
{
    QDomDocument doc;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return -1;
    if (!doc.setContent(&file)) {
        return -1;
    }
    file.close();
    //root
    QDomElement root = doc.documentElement();  //root node:profillist
    QDomElement newprofil_user=doc.createElement("Profils");
    newprofil_user.setAttribute("owner",nomU);
    root.appendChild(newprofil_user);
    if (!file.open(QIODevice::WriteOnly))
    {
        return -1;
    }
    else
    {
        QTextStream stream(&file);
        doc.save(stream,4);
        file.close();

    }
    return 0;

}
