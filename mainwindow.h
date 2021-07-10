#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_regItemImportButton_clicked();

    void on_regItemAddButton_clicked();

    void on_regItemDeleteButton_clicked();

    void on_regItemExportButton_clicked();

    void on_regItemClearButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
