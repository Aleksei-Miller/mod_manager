#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //
    _settings = new QSettings(QApplication::applicationDirPath() + "/config.ini",
                              QSettings::IniFormat);

    _mod_path = _settings->value("mod_path").toString();

    //Models
    _model = new ModModel(_mod_path);
    _proxy_model = new QSortFilterProxyModel(this);

    _proxy_model->setSourceModel(_model);

    //Search
    _proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);

    //
    ui->tableViewMods->setModel(_proxy_model);

    //Header
    QHeaderView *header = new QHeaderView(Qt::Horizontal, ui->tableViewMods);

    ui->tableViewMods->setHorizontalHeader(header);
    ui->tableViewMods->resizeColumnToContents(0);

    header->setSectionHidden(2, true);
    header->setSectionHidden(3, true);
    header->setSectionHidden(4, true);
    header->setSectionHidden(5, true);
    header->setSectionHidden(6, true);
    header->setSectionHidden(7, true);

    header->setStretchLastSection(true);

    //
    ui->labelLogo->setPixmap(QPixmap(QApplication::applicationDirPath() + "/logo.png"));

    ui->frameSearch->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableViewMods_clicked(const QModelIndex &index)
{
    //Logo
    QPixmap logo = _model->logo(_proxy_model->mapToSource(index));

    if (!logo.isNull())
        ui->labelLogo->setPixmap(logo);
    else
        ui->labelLogo->setPixmap(QPixmap(QApplication::applicationDirPath() + "/logo.png"));

    //Url
    QString url = _proxy_model->index(index.row(), ModInfo::Url).data().toString();

    if (url.endsWith("/"))
        url.remove(url.length() - 1, 1);

    ui->labelUrl->setText(tr("Site:") + " <a href=" + url + ">" + url + "</a>");

    //Version
    QString version = _proxy_model->index(index.row(), ModInfo::Version).data().toString();
    ui->labelVersion->setText(tr("Version:") + " " + version);

    //
    ui->textBrowserAbout->clear();

    //Description
    QString description = _proxy_model->index(index.row(), ModInfo::Description).data().toString();

    if (description != "")
    {
        ui->textBrowserAbout->append(tr("Description:"));
        ui->textBrowserAbout->append("    " + description);
    }

    //Authors
    QString authors = _proxy_model->index(index.row(), ModInfo::AuthorList).data().toString();

    if (authors != "")
    {
        ui->textBrowserAbout->append("");
        ui->textBrowserAbout->append(tr("Authors:"));

        ui->textBrowserAbout->append("    " + authors);
    }

    //Credits
    QString credits = _proxy_model->index(index.row(), ModInfo::Credits).data().toString();

    if (credits != "")
    {
        ui->textBrowserAbout->append("");
        ui->textBrowserAbout->append(tr("Credits:"));

        ui->textBrowserAbout->append("    " + credits);
    }
}

void MainWindow::on_actionInstall_Mod_triggered()
{
    QStringList file_path_list = QFileDialog::getOpenFileNames(this, tr("Install Mod"), "", "*.jar");

    foreach(auto file_path, file_path_list)
        _model->append(file_path);
}

void MainWindow::on_actionDelete_Mod_triggered()
{
    QModelIndex current_index = ui->tableViewMods->currentIndex();

    if (!current_index.isValid())
        return;

    QModelIndex index = _proxy_model->mapToSource(current_index);

    _model->remove(index);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    _proxy_model->setFilterFixedString(arg1);
}

void MainWindow::on_actionFind_triggered()
{
    if (ui->frameSearch->isHidden())
    {
        ui->frameSearch->show();
        ui->lineEdit->setFocus();
    }
    else
    {
        ui->frameSearch->hide();
        ui->tableViewMods->setFocus();
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->frameSearch->hide();
}


void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,
                             tr("About Minecraft Mod Manager"),
                             tr("Version") + ": " + product_version + "<br/>" +
                             tr("Site") + ": " + "<a href=" + product_site + ">" + product_site + "</a>");

}

void MainWindow::on_actionMod_Directory_triggered()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Select Mod Directory"), "");

    if (path != "")
    {
        _mod_path = path;

        _settings->setValue("mod_path", _mod_path);

        _model->setPath(_mod_path);

        ui->tableViewMods->resizeColumnToContents(0);
    }
}
