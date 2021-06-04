#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define TNIGHT_MIN_VAR_NAME " minNightTemp "
#define TDAY_MIN_VAR_NAME " minDayTemp "
#define FEELSLIKE_MIN_VAR_NAME " minFeelsLikeTemp "
#define WINDSPEED_MIN_VAR_NAME " minWindSpeed"

#define TNIGHT_MAX_VAR_NAME " maxNightTemp "
#define TDAY_MAX_VAR_NAME " maxDayTemp "
#define FEELSLIKE_MAX_VAR_NAME " maxFeelsLikeTemp "
#define WINDSPEED_MAX_VAR_NAME " maxWindSpeed "

#define DAYOFWEEK_VAR_NAME " DayName "
#define PRECIPITATIONAMOUNT_VAR_NAME " precipitationAmount "
#define WINDDIR_VAR_NAME " windDir "
#define WINDGUSTSPEED_VAR_NAME " windGustSpeed "
#define PRESSURE_VAR_NAME " pressure "

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

void MainWindow::on_addMessageButton_clicked()
{
    QString rowString("");
    rowString.append('\"').append(ui->msgTypeCombobox->currentText()).append("\",");
    rowString.append('\"').append(ui->messageTextEdit->toPlainText().remove('\"').replace('\n',"NL").remove('\r')).append("\",");

    rowString.append('\"').append(ui->minDaySpinbox->text()).append(' ').append(ui->maxDaySpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minMonthSpinbox->text()).append(' ').append(ui->maxMonthSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minDaytempSpinbox->text()).append(' ').append(ui->maxDaytempSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minNighttempSpinbox->text()).append(' ').append(ui->maxNighttempSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minFeelslikeSpinbox->text()).append(' ').append(ui->maxFeelslikeSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minPrecipitationSpinbox->text()).append(' ').append(ui->maxPrecipitationSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minWindspeedSpinbox->text()).append(' ').append(ui->maxWindspeedSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minWindgustSpinbox->text()).append(' ').append(ui->maxWindgustSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minPressureSpinbox->text()).append(' ').append(ui->maxPressureSpinbox->text()).append("\",");

    if(ui->prevDayRequiredCheckbox->isChecked())
    {
        rowString.append("\"да\",");
    }
    else
    {
        rowString.append("\"нет\",");
    }

    rowString.append('\"').append(ui->minPrevDaytempSpinbox->text()).append(' ').append(ui->maxPrevDaytempSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minPrevNighttempSpinbox->text()).append(' ').append(ui->maxPrevNighttempSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minPrevFeelslikeSpinbox->text()).append(' ').append(ui->maxPrevFeelslikeSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minPrevPrecipitationSpinbox->text()).append(' ').append(ui->maxPrevPrecipitationSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minPrevWindspeedSpinbox->text()).append(' ').append(ui->maxPrevWindspeedSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minPrevWindgustSpinbox->text()).append(' ').append(ui->maxPrevWindgustSpinbox->text()).append("\",");
    rowString.append('\"').append(ui->minPrevPressureSpinbox->text()).append(' ').append(ui->maxPrevPressureSpinbox->text()).append("\",");

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
    }
    file.close();
}

void MainWindow::on_insertPressureButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(PRESSURE_VAR_NAME));
}

void MainWindow::on_insertPrecipitationAmountButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(PRECIPITATIONAMOUNT_VAR_NAME));
}

void MainWindow::on_insertWindDirButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(WINDDIR_VAR_NAME));
}

void MainWindow::on_insertWindGustSpeedButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(WINDGUSTSPEED_VAR_NAME));
}

void MainWindow::on_insertMinWindSpeedButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(WINDSPEED_MIN_VAR_NAME));
}

void MainWindow::on_insertMaxWindSpeedButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(WINDSPEED_MAX_VAR_NAME));
}

void MainWindow::on_insertMinNightTempButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(TNIGHT_MIN_VAR_NAME));
}

void MainWindow::on_insertMaxNightTempButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(TNIGHT_MAX_VAR_NAME));
}

void MainWindow::on_insertMinDayTempButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(TDAY_MIN_VAR_NAME));
}

void MainWindow::on_insertMaxDayTempButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(TDAY_MAX_VAR_NAME));
}

void MainWindow::on_insertMinFeelslikeButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(FEELSLIKE_MIN_VAR_NAME));
}

void MainWindow::on_insertMaxFeelslikeButton_clicked()
{
    ui->messageTextEdit->setPlainText(ui->messageTextEdit->toPlainText().append(FEELSLIKE_MAX_VAR_NAME));
}
