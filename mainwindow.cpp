#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCameraInfo>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _camera(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::resizeEvent(QResizeEvent * ev)
{
    const QSize size = ev->size();
    ui->scroller->resize(size.width() - (721 - 691), size.height() - (596 - 501));
}

void
MainWindow::on_refresh_clicked()
{
    // refresh the camera list
    cameraList = QCameraInfo::availableCameras();
    QStringList names;
    for (const auto i : cameraList) {
        names << i.description();
    }
    // update combox
    ui->cameraInfo->clear();
    ui->cameraInfo->addItems(names);
}

void
MainWindow::on_connect_clicked()
{
    const int selected = ui->cameraInfo->currentIndex();
    const auto c = cameraList.at(selected);

    if (_camera != nullptr) {
        _camera->stop();
    }

    _camera = new QCamera(c, this);

    _finder = new QCameraViewfinder(ui->scrollAreaWidgetContents);
    _finder->setGeometry(0, 0, 1280, 960);
    ui->scroller->ensureWidgetVisible(_finder);
    _finder->show();

    _camera->setViewfinder(_finder);

    _capture = new QCameraImageCapture(_camera);
    connect(_capture, SIGNAL(readyForCaptureChanged(bool)), ui->save, SLOT(setEnabled(bool)));
    connect(_capture, SIGNAL(error(int,QCameraImageCapture::Error,QString)), this, SLOT(capError(int,QCameraImageCapture::Error,QString)));

    _camera->setCaptureMode(QCamera::CaptureStillImage);
    _camera->start();
}

void
MainWindow::on_save_clicked()
{
    _capture->capture(ui->filename->text());
    ui->filename->setValue(1 + ui->filename->value());
}

void
MainWindow::capError(int id, QCameraImageCapture::Error error, const QString &errorString)
{
    ui->err->setText(errorString);
}
