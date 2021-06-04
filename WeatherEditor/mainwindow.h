#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
QString getStringFromWindDirSelector();
    QString csvFileName;

private slots:
    void on_openFileButton_clicked();

    void on_appendRecordButton_clicked();

    void on_dayTempMinSlider_valueChanged(int value);

    void on_dayTempMaxSlider_valueChanged(int value);

    void on_nightTempMinSlider_valueChanged(int value);

    void on_nightTempMaxSlider_valueChanged(int value);

    void on_feelslikeTempMinSlider_valueChanged(int value);

    void on_feelslikeTempMaxSlider_valueChanged(int value);

    void on_precipitationamountValueSlider_valueChanged(int value);

    void on_windspeedMinSlider_valueChanged(int value);

    void on_windspeedMaxSlider_valueChanged(int value);

    void on_windGustSpeedSlider_valueChanged(int value);

    void on_pressureSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
