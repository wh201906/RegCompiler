#include "regitem.h"
#include "ui_regitem.h"

RegItem::RegItem(const QString& name, int startBit, int stopBit, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RegItem)
{
    ui->setupUi(this);
    this->setLayout(ui->mainLayout);
    ui->nameLabel->setText(name);
    len = stopBit - startBit + 1;
    hexLen = (len - 1) / 4 + 1;
    ui->lenLabel->setText(QString("[%1:%2], %3").arg(stopBit).arg(startBit).arg(len));

}

RegItem::~RegItem()
{
    delete ui;
}

int RegItem::getVal()
{
    return this->val;
}

void RegItem::setVal(int newVal)
{
    this->val = newVal;
}

void RegItem::updataEdit(int type)
{
    QString tmp;
    ui->binEdit->blockSignals(true);
    ui->hexEdit->blockSignals(true);
    ui->decEdit->blockSignals(true);
    if(type & VAL_BIN)
    {
        tmp = QString::number(val, 2);
        if(tmp.length() < len)
            ui->binEdit->setText(QString(len - tmp.length(), '0') + tmp);
        else
            ui->binEdit->setText(tmp);
    }
    if(type & VAL_HEX)
    {
        tmp = QString::number(val, 16);
        if(tmp.length() < hexLen)
            ui->hexEdit->setText(QString(hexLen - tmp.length(), '0') + tmp);
        else
            ui->hexEdit->setText(tmp);
    }
    if(type & VAL_DEC)
    {
        ui->decEdit->setText(QString::number(val, 10));
    }
    ui->binEdit->blockSignals(false);
    ui->hexEdit->blockSignals(false);
    ui->decEdit->blockSignals(false);
}

void RegItem::on_binEdit_textChanged(const QString &arg1)
{
    bool isOk;
    int tmp;
    tmp = arg1.toInt(&isOk, 2);
    if(isOk)
    {
        setVal(tmp);
        updataEdit(VAL_DEC | VAL_HEX);
    }
}

void RegItem::on_hexEdit_textChanged(const QString &arg1)
{
    bool isOk;
    int tmp;
    tmp = arg1.toInt(&isOk, 16);
    if(isOk)
    {
        setVal(tmp);
        updataEdit(VAL_DEC | VAL_BIN);
    }
}

void RegItem::on_decEdit_textChanged(const QString &arg1)
{
    bool isOk;
    int tmp;
    tmp = arg1.toInt(&isOk, 10);
    if(isOk)
    {
        setVal(tmp);
        updataEdit(VAL_BIN | VAL_HEX);
    }
}
