#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
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
    qDebug() << getMask({0, 0});
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

void MainWindow::onMainValChanged(Field field, quint64 val)
{
    quint64 mask, newVal;
    QMapIterator<Field, RegItem*> it(*regMap);
    while(it.hasNext())
    {
        it.next();
        mask = getMask(it.key());
        newVal = val & mask;
        newVal >>= it.key().start;
        it.value()->setVal(newVal);
        it.value()->updateEdit(RegItem::VAL_BIN | RegItem::VAL_DEC | RegItem::VAL_HEX);
    }
}

void MainWindow::onSubValChanged(Field field, quint64 val)
{
    quint64 mainVal;
    quint64 mask;
    mainVal = mainReg->getVal();
    mask = getMask(field);
    mainVal &= ~mask;
    mainVal |= (val << field.start)&mask;
    mainReg->setVal(mainVal);
    mainReg->updateEdit(RegItem::VAL_BIN | RegItem::VAL_DEC | RegItem::VAL_HEX);
}

void MainWindow::on_regItemImportButton_clicked()
{
    QString fileName;
    QStringList tmp;
    int i;
    QFile file;
    fileName = QFileDialog::getOpenFileName(this, tr("Import"), "", tr("CSV File(*.csv);;All Files(*.*)"));
    if(fileName.isEmpty())
        return;
    file.setFileName(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open ") + fileName);
        return;
    }
    tmp = QString(file.readLine()).split(',');
    ui->nameEdit->setText(tmp[0]);
    ui->regLenBox->setValue(tmp[1].toInt());
    ui->regItemTable->clearContents();
    ui->regItemTable->setRowCount(0);
    i = 0;
    while(true)
    {
        tmp = QString(file.readLine()).split(',');
        if(tmp.length() < 3)
            break;
        ui->regItemTable->insertRow(i);
        ui->regItemTable->setItem(i, 0, new QTableWidgetItem(tmp[0]));
        ui->regItemTable->setItem(i, 1, new QTableWidgetItem(tmp[1]));
        ui->regItemTable->setItem(i, 2, new QTableWidgetItem(tmp[2]));
        i++;
    }
    file.close();
    if(fileName.contains('\\'))
        fileName = fileName.split('\\').last();
    else if(fileName.contains('/'))
        fileName = fileName.split('/').last();
    this->setWindowTitle(fileName);
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
    fileName = QFileDialog::getSaveFileName(this, tr("Export"), ui->nameEdit->text() + "_" + QString::number(ui->regLenBox->value()), tr("CSV File(*.csv);;All Files(*.*)"));
    if(fileName.isEmpty())
        return;
    file.setFileName(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open ") + fileName);
        return;
    }
    file.write(ui->nameEdit->text().toUtf8() + "," + QByteArray::number(ui->regLenBox->value()) + "\n");
    for(int i = 0; i < ui->regItemTable->rowCount(); i++)
    {
        for(int j = 0; j < ui->regItemTable->columnCount(); j++)
        {
            item = ui->regItemTable->item(i, j);
            if(item != nullptr)
                file.write(item->text().toUtf8());
            file.write(QByteArray(","));
        }
        file.write(QByteArray("\n"));
    }
    file.close();
    if(fileName.contains('\\'))
        fileName = fileName.split('\\').last();
    else if(fileName.contains('/'))
        fileName = fileName.split('/').last();
    this->setWindowTitle(fileName);
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
    Field field;
    QString name;
    RegItem* item;
    int column = ui->columnBox->value();
    removeAll();
    for(int i = 0; i < ui->regItemTable->rowCount(); i++)
    {
        field = {ui->regItemTable->item(i, 1)->text().toInt(), ui->regItemTable->item(i, 2)->text().toInt()};
        name = ui->regItemTable->item(i, 0)->text();
        item = new RegItem(name, field);
        regMap->insert(field, item);
        connect(item, &RegItem::valChanged, this, &MainWindow::onSubValChanged);
        itemGLayout->addWidget(item, i / column, i % column);
    }
}

void MainWindow::on_hideBox_stateChanged(int arg1)
{
    ui->leftFrame->setVisible(arg1 == Qt::Checked ? false : true);
    ui->countLabel->setVisible(arg1 == Qt::Checked ? false : true);
    ui->hideBox->setText(arg1 == Qt::Checked ? "" : tr("Hide Left"));
}

void MainWindow::on_nameEdit_textChanged(const QString &arg1)
{
    mainReg->setName(arg1);
}
