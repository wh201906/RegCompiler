#ifndef REGITEM_H
#define REGITEM_H

#include <QFrame>

namespace Ui
{
class RegItem;
}

class RegItem : public QFrame
{
    Q_OBJECT

public:
    explicit RegItem(const QString& name, int startBit, int stopBit, QWidget *parent = nullptr);
    ~RegItem();
    int getVal();
    void setVal(int newVal);

private slots:
    void on_binEdit_textChanged(const QString &arg1);

    void on_hexEdit_textChanged(const QString &arg1);

    void on_decEdit_textChanged(const QString &arg1);

private:
    enum valueType
    {
        VAL_BIN = 1,
        VAL_DEC = 2,
        VAL_HEX = 4
    };
    Ui::RegItem *ui;
    int val;
    int len, hexLen;
    void updataEdit(int type);
};

#endif // REGITEM_H
