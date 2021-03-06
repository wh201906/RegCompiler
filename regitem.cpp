#include "regitem.h"
#include "ui_regitem.h"

RegItem::RegItem(const QString& name, Field field, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RegItem)
{
    ui->setupUi(this);
    setName(name);
    setField(field);
}

RegItem::~RegItem()
{
    delete ui;
}

quint64 RegItem::getVal()
{
    return this->val;
}

void RegItem::setVal(quint64 newVal)
{
    this->val = newVal;
}

void RegItem::setName(const QString& name)
{
    ui->nameLabel->setText(name);
}

void RegItem::setField(Field field)
{
    this->field = field;
    len = field.end - field.start + 1;
    hexLen = (len - 1) / 4 + 1; // len should be bigger than 1
    ui->lenLabel->setText(QString("[%1:%2], %3").arg(field.end).arg(field.start).arg(len));
    ui->maskEdit->setText(QString("0x") + QString::number(getMask(field), 16).toUpper());
}

void RegItem::updateEdit(int type)
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
        tmp = QString::number(val, 16).toUpper(); // I prefer hex numbers look like 0xABCD
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
    quint64 tmp;
    tmp = arg1.toInt(&isOk, 2);
    if(isOk)
    {
        setVal(tmp);
        emit valChanged(field, val);
        updateEdit(VAL_DEC | VAL_HEX);
    }
}

void RegItem::on_hexEdit_textChanged(const QString &arg1)
{
    bool isOk;
    quint64 tmp;
    tmp = arg1.toInt(&isOk, 16);
    if(isOk)
    {
        setVal(tmp);
        emit valChanged(field, val);
        updateEdit(VAL_DEC | VAL_BIN);
    }
}

void RegItem::on_decEdit_textChanged(const QString &arg1)
{
    bool isOk;
    quint64 tmp;
    tmp = arg1.toInt(&isOk, 10);
    if(isOk)
    {
        setVal(tmp);
        emit valChanged(field, val);
        updateEdit(VAL_BIN | VAL_HEX);
    }
}
