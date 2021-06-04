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
    QString csvFileName;

private slots:
    void on_openFileButton_clicked();

    void on_addMessageButton_clicked();

    void on_insertPressureButton_clicked();

    void on_insertPrecipitationAmountButton_clicked();

    void on_insertWindDirButton_clicked();

    void on_insertWindGustSpeedButton_clicked();

    void on_insertMinWindSpeedButton_clicked();

    void on_insertMaxWindSpeedButton_clicked();

    void on_insertMinNightTempButton_clicked();

    void on_insertMaxNightTempButton_clicked();

    void on_insertMinDayTempButton_clicked();

    void on_insertMaxDayTempButton_clicked();

    void on_insertMinFeelslikeButton_clicked();

    void on_insertMaxFeelslikeButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
