#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QCameraInfo>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QList<QCameraInfo> cameraList;
    QCamera * _camera;
    QCameraImageCapture * _capture;
    QCameraViewfinder * _finder;

protected:
    void resizeEvent(QResizeEvent * ev);

private slots:
    void on_refresh_clicked();
    void on_connect_clicked();
    void on_save_clicked();
    void capError(int id, QCameraImageCapture::Error error, const QString &errorString);
};

#endif // MAINWINDOW_H
