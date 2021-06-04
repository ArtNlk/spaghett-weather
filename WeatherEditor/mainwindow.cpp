#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFileButton_clicked()
{
    QFileDialog csvFileDialog(this);
    csvFileDialog.setFileMode(QFileDialog::ExistingFile);
    if(csvFileDialog.exec())
    {
        QFile csvFile(csvFileDialog.selectedFiles()[0]);
        if(csvFile.exists())
        {
            this->csvFileName = csvFileDialog.selectedFiles()[0];
            ui->fileNameLabel->setText(this->csvFileName);
        }
        else
        {
            ui->fileNameLabel->setText("Error opening file");
        }
    }
}

void MainWindow::on_appendRecordButton_clicked()
{
    QString rowString("");
    rowString.append('\"').append(ui->dateEdit->text()).append("\",");
    rowString.append('\"').append(QString::number(ui->nightTempMinSlider->value())).append(' ').append(QString::number(ui->nightTempMaxSlider->value())).append("\",");
    rowString.append('\"').append(QString::number(ui->dayTempMinSlider->value())).append(' ').append(QString::number(ui->dayTempMaxSlider->value())).append("\",");
    rowString.append('\"').append(QString::number(ui->feelslikeTempMinSlider->value())).append(' ').append(QString::number(ui->feelslikeTempMaxSlider->value())).append("\",");
    rowString.append('\"').append(QString::number(ui->precipitationamountValueSlider->value())).append("\",");
    rowString.append('\"').append(getStringFromWindDirSelector()).append("\",");
    rowString.append('\"').append(QString::number(ui->windspeedMinSlider->value())).append(' ').append(QString::number(ui->windspeedMaxSlider->value())).append("\",");
    rowString.append('\"').append(QString::number(ui->windGustSpeedSlider->value())).append("\",");
    rowString.append('\"').append(QString::number(ui->pressureSlider->value())).append("\",");

    QString flagString("");

    if(ui->rainCheckbox->isChecked())
    {
        flagString.append(" дождь");
    }

    if(ui->snowCheckbox->isChecked())
    {
        flagString.append(" снег");
    }

    if(ui->hailCheckbox->isChecked())
    {
        flagString.append(" град");
    }

    if(ui->frostCheckbox->isChecked())
    {
        flagString.append(" иней");
    }

    if(ui->icyroadsCheckbox->isChecked())
    {
        flagString.append(" гололед");
    }

    if(ui->fogCheckbox->isChecked())
    {
        flagString.append(" туман");
    }

    if(ui->stormCheckbox->isChecked())
    {
        flagString.append(" шторм");
    }

    if(ui->lightningCheckbox->isChecked())
    {
        flagString.append(" гроза");
    }

    if(ui->snowstormCheckbox->isChecked())
    {
        flagString.append(" метель");
    }

    if(ui->freezingCheckbox->isChecked())
    {
        flagString.append(" мороз");
    }

    if(ui->dustCheckbox->isChecked())
    {
        flagString.append(" пыль");
    }

    if(ui->smogCheckbox->isChecked())
    {
        flagString.append(" смог");
    }

    if(ui->icingCheckbox->isChecked())
    {
        flagString.append(" обледенение");
    }

    if(ui->emergencyCheckbox->isChecked())
    {
        flagString.append(" чс");
    }

    rowString.append('\"').append(flagString).append("\"\r\n");

    QFile file(this->csvFileName);
    if (file.open(QFile::Append))
    {
    QTextStream stream(&file);
    stream << rowString;
    ui->dateEdit->setDate(ui->dateEdit->date().addDays(1));
    }
    file.close();
}

QString MainWindow::getStringFromWindDirSelector()
{
    switch(ui->windDirComboBox->currentIndex())
    {
    case 0:
        return "с";
        break;
    case 1:
        return "св";
        break;
    case 2:
        return "сз";
        break;
    case 3:
        return "ю";
        break;
    case 4:
        return "юв";
        break;
    case 5:
        return "юз";
        break;
    case 6:
        return "в";
        break;
    case 7:
        return "з";
        break;
    default:
        return "неверное значение направления ветра";
        break;
    }
}

void MainWindow::on_dayTempMinSlider_valueChanged(int value)
{
    ui->daytempMinLabel->setText(QString::number(value));
}

void MainWindow::on_dayTempMaxSlider_valueChanged(int value)
{
    ui->daytempMaxLabel->setText(QString::number(value));
}

void MainWindow::on_nightTempMinSlider_valueChanged(int value)
{
    ui->nighttempMinLabel->setText(QString::number(value));
}

void MainWindow::on_nightTempMaxSlider_valueChanged(int value)
{
    ui->nighttempMaxLabel->setText(QString::number(value));
}

void MainWindow::on_feelslikeTempMinSlider_valueChanged(int value)
{
    ui->feelslikeMinLabel->setText(QString::number(value));
}

void MainWindow::on_feelslikeTempMaxSlider_valueChanged(int value)
{
    ui->feelslikeMaxLabel->setText(QString::number(value));
}

void MainWindow::on_precipitationamountValueSlider_valueChanged(int value)
{
    ui->precipitationLabel->setText(QString::number(value));
}

void MainWindow::on_windspeedMinSlider_valueChanged(int value)
{
    ui->windspeedMinLabel->setText(QString::number(value));
}

void MainWindow::on_windspeedMaxSlider_valueChanged(int value)
{
    ui->windspeedMaxLabel->setText(QString::number(value));
}

void MainWindow::on_windGustSpeedSlider_valueChanged(int value)
{
    ui->windgustLabel->setText(QString::number(value));
}

void MainWindow::on_pressureSlider_valueChanged(int value)
{
    ui->pressureLabel->setText(QString::number(value));
}
