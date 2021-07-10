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
    itemGLayout = new QGridLayout(this);
    regMap = new QMap<Field, RegItem*>;
    mainReg = new RegItem("main", {0, 0}, this);
    ui->itemVLayout->addWidget(mainReg);
    ui->itemVLayout->addLayout(itemGLayout);
    connect(mainReg, &RegItem::valChanged, this, &MainWindow::onMainValChanged);
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::removeAll()
{
    QMapIterator<Field, RegItem*> it(*regMap);
    while(it.hasNext())
    {
        it.next();
        delete it.value();
        regMap->remove(it.key());
    }
}

void MainWindow::onMainValChanged(Field field, int val)
{

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

void MainWindow::on_regLenBox_valueChanged(int arg1)
{
    mainReg->setField({0, arg1 - 1});
}

void MainWindow::on_changeButton_clicked()
{
    int i;
    Field field;
    QString name;
    RegItem* item;
    removeAll();
    for(int i = 0; i < ui->regItemTable->rowCount(); i++)
    {
        field = {ui->regItemTable->item(i, 1)->text().toInt(), ui->regItemTable->item(i, 2)->text().toInt()};
        name = ui->regItemTable->item(i, 0)->text();
        item = new RegItem(name, field);
        regMap->insert(field, item);
        itemGLayout->addWidget(item, i / 3, i % 3);
    }
}
