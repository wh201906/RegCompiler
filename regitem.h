#ifndef REGITEM_H
#define REGITEM_H

#include <QFrame>
#include "common.hpp"

namespace Ui
{
class RegItem;
}

class RegItem : public QFrame
{
    Q_OBJECT

public:
    explicit RegItem(const QString& name, Field field, QWidget *parent = nullptr);
    ~RegItem();
    enum valueType
    {
        VAL_BIN = 1,
        VAL_DEC = 2,
        VAL_HEX = 4
    };
    quint64 getVal();
    void setVal(quint64 newVal);

    void setField(Field field);
    void updateEdit(int type);
    void setName(const QString &name);
private slots:
    void on_binEdit_textChanged(const QString &arg1);

    void on_hexEdit_textChanged(const QString &arg1);

    void on_decEdit_textChanged(const QString &arg1);
private:
    Ui::RegItem *ui;
    quint64 val = 0;
    Field field;
    int len, hexLen;
signals:
    void valChanged(Field field, quint64 val);
};

#endif // REGITEM_H
