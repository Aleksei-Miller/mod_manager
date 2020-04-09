#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include <QSortFilterProxyModel>

#include <QSettings>

#include <QDebug>

#include "modmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tableViewMods_clicked(const QModelIndex &index);

    void on_actionInstall_Mod_triggered();

    void on_actionDelete_Mod_triggered();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_actionFind_triggered();

    void on_pushButton_clicked();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionMod_Directory_triggered();

    void on_actionAbout_Qt_triggered();

private:
    Ui::MainWindow *ui;

    ModModel *_model;
    QSortFilterProxyModel *_proxy_model;

    QString _mod_path;

    QSettings *_settings;

    const QString product_version = "0.1";
    const QString product_site = "https://github.com/Aleksei-Miller/mod_manager";
};

#endif
