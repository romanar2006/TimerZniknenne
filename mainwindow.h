#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui {
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
    void updateTimer();
    void startTimer();
    void stopTimer();
    void resumeTimer();
    void updateCurrentTime();
    void fadeOut();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *currentTimeTimer;
    QTime timeLeft;
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation *animation;
};
#endif // MAINWINDOW_H
