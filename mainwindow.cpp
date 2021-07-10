#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QFile>

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
    QString fileName;
    QStringList tmp;
    int i;
    QFile file;
    QTableWidgetItem* item;
    fileName = QFileDialog::getOpenFileName(this, tr("Import"), "", tr("CSV File(*.csv);;All Files(*.*)"));
    if(fileName.isEmpty())
        return;
    file.setFileName(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    ui->regItemTable->clearContents();
    ui->regItemTable->setRowCount(0);
    while(true)
    {
        tmp = QString(file.readLine()).split(',');
        if(tmp.length() != 4)
            break;
        i = ui->regItemTable->rowCount();
        ui->regItemTable->insertRow(i);
        ui->regItemTable->setItem(i, 0, new QTableWidgetItem(tmp[0]));
        ui->regItemTable->setItem(i, 1, new QTableWidgetItem(tmp[1]));
        ui->regItemTable->setItem(i, 2, new QTableWidgetItem(tmp[2]));
    }
    file.close();
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
    QString fileName;
    QFile file;
    QTableWidgetItem* item;
    fileName = QFileDialog::getSaveFileName(this, tr("Export"), "", tr("CSV File(*.csv);;All Files(*.*)"));
    if(fileName.isEmpty())
        return;
    file.setFileName(fileName);
    file.open(QFile::WriteOnly | QFile::Text);
    for(int i = 0; i < ui->regItemTable->rowCount(); i++)
    {
        for(int j = 0; j < ui->regItemTable->columnCount(); j++)
        {
            item = ui->regItemTable->item(i, j);
            if(item != nullptr)
                file.write(item->text().toLatin1());
            file.write(QByteArray(","));
        }
        file.write(QByteArray("\n"));
    }
    file.close();
}

void MainWindow::on_regItemClearButton_clicked()
{
    ui->regItemTable->clearContents();
    ui->regItemTable->setRowCount(0);
}
