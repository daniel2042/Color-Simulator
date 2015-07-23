#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QColor>
#include <QMessageBox>
#include <QColorDialog>
#include <QThread>
#include <QPainter>
#include <QTimer>
#include <cmath>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPushButton *start;
    QLabel      *hue_label;
    QLabel      *lightness_label;
    QLabel      *delay_label;
    QLabel      *start_color_label;
    QLabel      *end_color_label;
    QLabel      *frame_amount_label;
    QLabel      *saturation_label;
    QColor       start_color;
    QColor       end_color;
    QColor       color;
    QColor       hsv;
    QTimer      *timer;
    QSpinBox    *hue_bits;
    QSpinBox    *lightness_bits;
    QSpinBox    *saturation_bits;
    QSpinBox    *delay;
    QSpinBox    *amount;
    QPushButton *end_color_button;
    QPushButton *start_color_button;

    void paintEvent(QPaintEvent *);
    void Set_Color(int R, int G, int B, QPainter *painter);
public:
    MainWindow();

public slots:
    void Start();
    void Start_Color_Pressed();
    void End_Color_Pressed();
    void Update();
};

#endif // MAINWINDOW_H
