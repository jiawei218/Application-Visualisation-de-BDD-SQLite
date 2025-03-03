#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "connection.h"
#include "gestionutilisateur.h"
#include "disconnecter.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initTreeView();


signals:
    void SendUserInformation(QString userNom, QString userPw);


private slots:

    void on_Disconnect_Button_clicked();
    void on_Gestion_Button_clicked();
    void RecvUserInf(QString userNom, QString userPw,QString priorite);
    void Notion();

    void on_Actualiser_clicked();

private:
    Ui::MainWindow *ui;
    Connection *connection;
    QString usernom;
    QString userpw;
    QString userpriorite;
    //point sur subwindow
    gestionUtilisateur *m_pgestion;
    disconnecter *m_pdiscon;
};
#endif // MAINWINDOW_H
