#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onButtonClicked();
    void clearClicked();
    void equalClicked();
private:
    bool calculate(double);
private:
    Ui::MainWindow *ui;
    QString currIn;
    QString currOperator;
    double firstNum;
    bool isUsedOperator;
};
#endif // MAINWINDOW_H
