#ifndef CONNECTION_H
#define CONNECTION_H

#include <QWidget>

namespace Ui {
class Connection;
}

class Connection : public QWidget
{
    Q_OBJECT

public:
    explicit Connection(QWidget *parent = nullptr);
    ~Connection();

signals:
    void login(); //open mainwindow
    void close_window(); //close mainwindow
    void sendUserInf(QString nom,QString pw,QString priorite);

private slots:
    void LogButton_clicked();

    void RegistreButton_clicked();

private:
    Ui::Connection *ui;
};

#endif // CONNECTION_H
