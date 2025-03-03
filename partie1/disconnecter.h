#ifndef DISCONNECTER_H
#define DISCONNECTER_H

#include <QWidget>

namespace Ui {
class disconnecter;
}

class disconnecter : public QWidget
{
    Q_OBJECT

public:
    explicit disconnecter(QWidget *parent = nullptr);
    ~disconnecter();
signals:
    void close_win();

private slots:
    void on_Disconn_Button_clicked();
    void ReceiveUserIn(QString userNom, QString userPw);

private:
    Ui::disconnecter *ui;
    QString user_nom;
    QString user_pw;
};

#endif // DISCONNECTER_H
