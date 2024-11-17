#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,currIn("")
    ,currOperator("")
    ,firstNum(0)
    ,isUsedOperator(false)
{
    ui->setupUi(this);

    QList<QPushButton*> buttons = {
        ui->zero, ui->one, ui->two, ui->three,
        ui->four, ui->five, ui->six, ui->seven,
        ui->eight, ui->nine, ui->add, ui->min,
        ui->multi, ui->divide, ui->equal
    };

    for (auto button : buttons) {
        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    }

    connect(ui->CE, &QPushButton::clicked, this, &MainWindow::clearClicked);
    connect(ui->equal, &QPushButton::clicked, this, &MainWindow::equalClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClicked()
{

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(!button){return;}
    QString buttonText = button->text();
    if(buttonText >= "0" && buttonText <= "9"){
        currIn += buttonText;
        ui->output->setText(ui->output->text()+buttonText);
    }else{
        if(currIn.isEmpty()){
            QMessageBox::warning(this, "Warnning", "please input number first!");
            return;
        }
        if(isUsedOperator){
            double secondOperand = currIn.toDouble();
            if(!calculate(secondOperand)){
                return;
            }
            ui->output->setText(QString::number(firstNum)+" "+buttonText+ " ");
        }else{
            firstNum = currIn.toDouble();
            ui->output->setText(ui->output->text()+" "+buttonText + " ");
        }
        currOperator = buttonText;
        isUsedOperator = true;
        currIn.clear();
    }
}

void MainWindow::clearClicked(){
    ui->output->clear();
    currIn.clear();
    currOperator.clear();
    firstNum=0;
    isUsedOperator=false;
}

void MainWindow::equalClicked(){
    if (currOperator.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please input a valid equation.");
        return;
    }

    double secondOperand = currIn.toDouble();
    if (!calculate(secondOperand)) {
        return;
    }

    // 显示最终结果
    ui->output->setText(QString::number(firstNum));

    currIn = QString::number(firstNum);
    currOperator.clear();
    isUsedOperator = false;
}

bool MainWindow::calculate(double secondOperand){
    if (currOperator == "+") {
        firstNum += secondOperand;
    } else if (currOperator == "-") {
        firstNum -= secondOperand;
    } else if (currOperator == "*") {
        firstNum *= secondOperand;
    } else if (currOperator == "/") {
        if (secondOperand == 0) {
            QMessageBox::critical(this, "Error", "Cannot Divide Zero!");
            return false;
        }
        firstNum /= secondOperand;
    }
    return true;
}
