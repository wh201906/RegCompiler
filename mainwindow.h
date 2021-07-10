#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QMap>
#include "regitem.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onMainValChanged(Field field, quint64 val);
    void onSubValChanged(Field field, quint64 val);
private slots:
    void on_regItemImportButton_clicked();

    void on_regItemAddButton_clicked();

    void on_regItemDeleteButton_clicked();

    void on_regItemExportButton_clicked();

    void on_regItemClearButton_clicked();

    void on_regLenBox_valueChanged(int arg1);

    void on_changeButton_clicked();

private:
    Ui::MainWindow *ui;
    QGridLayout* itemGLayout;
    QMap<Field, RegItem*> *regMap;
    RegItem* mainReg;
    void removeAll();
};
#endif // MAINWINDOW_H
