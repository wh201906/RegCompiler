#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gridLayout->addWidget(new RegItem("name", 0, 3, this));
    ui->gridLayout->addWidget(new RegItem("Name", 4, 8, this));
}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::on_regItemImportButton_clicked()
{

}

void MainWindow::on_regItemAddButton_clicked()
{
    ui->regItemTable->insertRow(ui->regItemTable->rowCount());
}

void MainWindow::on_regItemDeleteButton_clicked()
{
    ui->regItemTable->removeRow(ui->regItemTable->currentRow());
}

void MainWindow::on_regItemExportButton_clicked()
{

}
