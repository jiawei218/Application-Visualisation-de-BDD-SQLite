#include "utilisateurs.h"
#include <QFile>
#include <iostream>
#include <QDomText>
#include <QDomElement>
#include <QDebug>
#include <iostream>
#include <QStringList>
#include <QString>
#include <QTextStream>
utilisateurs::utilisateurs()
{

}

/*create utilisateurs xml doc*/
int utilisateurs::createXML(QString filePath)
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
            //element
            QDomElement melement;
            //element
            QDomElement childelement;
            //text
            QDomText text;
            //xml title
            QDomProcessingInstruction ins;
            ins=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
            doc.appendChild(ins);
            //root
            root=doc.createElement("utilisateurList");
            doc.appendChild(root);
        //admin
/*
            //element
            melement=doc.createElement("utilisateur");
            //nom
            childelement=doc.createElement("nom");
            text=doc.createTextNode("admin");
            childelement.appendChild(text);
            melement.appendChild(childelement);
            root.appendChild(melement);
            //passwd
            childelement=doc.createElement("password");
            text=doc.createTextNode("password");
            childelement.appendChild(text);
            melement.appendChild(childelement);
            root.appendChild(melement);
            //priorite
            childelement=doc.createElement("priorite");
            text=doc.createTextNode("0");
            childelement.appendChild(text);
            melement.appendChild(childelement);
            root.appendChild(melement);
*/
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

QList<QString> utilisateurs::readUtilisateurList(QString filePath)
{
    QDomDocument doc;
    QList<QString> listUtilisateurs;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
       return listUtilisateurs;
    if (!doc.setContent(&file)) {
        return listUtilisateurs;
    }
    file.close();
    QDomElement root = doc.documentElement();  //utilsiateurs list;racine
    QDomNodeList list = root.childNodes();  //get list of users
    if(!list.isEmpty())  //avoir utilisateurs
        {
            for(int i=0; i<list.count(); i++)
            {
                QDomNodeList attribus=list.at(i).toElement().childNodes();  //obtenir attribus de l'utilisateur
                if (!attribus.isEmpty() && attribus.at(2).toElement().text()!="0")  //has attribus and priorite!=0(not admin)
                {
                    QString nom=attribus.at(0).toElement().text();  //obtenir nom
                    listUtilisateurs.append(nom);
                }

            }
        }
    return listUtilisateurs;
}

int utilisateurs::chercherUtilisateur(QString filePath, QString nom,QString passwd)
{
    QDomDocument doc;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return -1;
    if (!doc.setContent(&file)) {
        return -2;
    }
    file.close();

    //root
    QDomElement root = doc.documentElement();  //root node
    QDomNodeList list = root.childNodes();  //get list of users
    if(!list.isEmpty())
        {
            for(int i=0; i<list.count(); i++)
            {
                QDomNodeList attribus=list.at(i).toElement().childNodes();  //get attribues
                if (!attribus.isEmpty())
                {
                    QString nom_save=attribus.at(0).toElement().text();
                    QString passwd_save=attribus.at(1).toElement().text();
                    if(nom_save==nom)
                    {
                        if(passwd_save==passwd)
                        {
                            return 1;
                        }
                        else
                        {
                            return 2;
                        }

                    }
                }

            }
        }

    //le nom n'existe pas
    return 0;
}

int utilisateurs::appendUtilisateur(QString filePath, QString nom,QString passwd, QString priorite)
{
    QStringList plist;
    plist.append(nom);
    plist.append(passwd);
    plist.append(priorite);

    QDomDocument doc;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return -1;
    if (!doc.setContent(&file)) {
        return -2;
    }
    file.close();

    //root
    QDomElement root = doc.documentElement();  //root node:utilisateurlist
    if(root.hasChildNodes()==true)  //has utilisateurs
    {
        QDomNode dernier=root.lastChild();  //utilisateur dernier
        QDomElement der_user=dernier.toElement();
        QDomNodeList attribus=der_user.childNodes();
        if(!attribus.isEmpty())
        {
        //write info of new user
            writeUtilisateur(doc,root,plist);
        }
        else
        {
            std::cout<<"manque donnees";
            return -3;
        }
    }
    else
    {  //pas de utilisateur
        writeUtilisateur(doc,root,plist);
    }

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

void utilisateurs::writeUtilisateur(QDomDocument &doc,QDomElement &root,QStringList &plist)
{
    //utilisateur element
    QDomElement melement=doc.createElement("utilisateur");
    root.appendChild(melement);
    //attribus
    QDomElement nomE;
    QDomElement nomPw;
    QDomElement nomP;
    //text
    QDomText text;
    //nom
    nomE=doc.createElement("nom");
    text=doc.createTextNode(plist.at(0));
    nomE.appendChild(text);
    melement.appendChild(nomE);

    //passwd
    nomPw=doc.createElement("password");
    text=doc.createTextNode(plist.at(1));
    nomPw.appendChild(text);
    melement.appendChild(nomPw);

    //priorite
    nomP=doc.createElement("priorite");
    text=doc.createTextNode(plist.at(2));
    nomP.appendChild(text);
    melement.appendChild(nomP);

}


int utilisateurs::nombreUtilsiateur(QString filePath)
{
    int nbU=-1;
    QDomDocument doc;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return -1;
    if (!doc.setContent(&file)) {
        return -2;
    }
    file.close();
    QDomElement root = doc.documentElement();  //root node:utilisateurlist
    if(root.hasChildNodes()==true)  //has utilisateurs
    {
        QDomNodeList listUtilisateur=root.childNodes();
        nbU=listUtilisateur.count();

    }
    return nbU;
}


QString utilisateurs::prioriteUtilisateur(QString filePath, QString nom)
{
    QString priorite="#";
    QDomDocument doc;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        std::cout<<"ReadOnly error";
    if (!doc.setContent(&file)) {
        std::cout<<"Setcontext error";
    }
    file.close();
    QDomElement root = doc.documentElement();  //root node:utilisateurlist
    if(root.hasChildNodes()==true)  //has utilisateurs
    {
        QDomNodeList listUtilisateur=root.childNodes();
        for(int i=0;i<listUtilisateur.count();i++)
        {
            QDomNodeList attribulist=listUtilisateur.at(i).childNodes();  //attribus de l'utilisateur
            if(attribulist.at(0).toElement().text()==nom)
            {
                return attribulist.at(2).toElement().text();
            }
        }

    }
    return priorite;
}

int utilisateurs::supprimerUtilisateur(QString filePath, QString nom)
{
    QDomDocument doc;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return -1;
    if (!doc.setContent(&file)) {
        return -2;
    }
    file.close();

    //root
    QDomElement root = doc.documentElement();  //root node
    QDomNodeList list = root.childNodes();  //get list of users
    if(!list.isEmpty())
        {
            for(int i=0; i<list.count(); i++)
            {
                QDomNodeList attribus=list.at(i).toElement().childNodes();  //get attribues
                if (!attribus.isEmpty())
                {
                    QString nom_save=attribus.at(0).toElement().text();  //GET nom
                    if(nom_save==nom)
                    {
                        if(!root.removeChild(list.at(i)).isNull()) //remove this user from childlist of utilisateurlist(root)
                        {
                           //return!=null, remove succeed
                            break;
                        }
                    }
                }

            }
        }
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
    //le nom n'existe pas
    return 0;
}
