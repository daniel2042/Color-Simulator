#include "mainwindow.h"

MainWindow::MainWindow()
{

    start_color = QColor(0xFF,0xFF,0x00);
    end_color   = QColor(0xFF,0x00,0xFF);
    color       = start_color;

    this->setGeometry(100,100,400,360);
    this->setFixedSize(400,360);
    this->setWindowTitle("HSL Color Simulator @Daniel Majchrzycki");
    this->setWindowIcon(QIcon(":/color.ico"));

    start = new QPushButton(this);
    start->setGeometry(10,10,60,20);
    start->setText("Start");

    hue_label = new QLabel(this);
    hue_label->setGeometry(10,30,100,20);
    hue_label->setText("Hue bits");

    hue_bits = new QSpinBox(this);
    hue_bits->setGeometry(10,50,50,20);
    hue_bits->setMaximum(9);
    hue_bits->setMinimum(0);
    hue_bits->setValue(6);

    lightness_label = new QLabel(this);
    lightness_label->setGeometry(10,70,100,20);
    lightness_label->setText("Lightness bits");

    lightness_bits = new QSpinBox(this);
    lightness_bits->setGeometry(10,90,50,20);
    lightness_bits->setMaximum(8);
    lightness_bits->setMinimum(0);
    lightness_bits->setValue(4);

    saturation_label = new QLabel(this);
    saturation_label->setGeometry(10,110,100,20);
    saturation_label->setText("Saturation bits");

    saturation_bits = new QSpinBox(this);
    saturation_bits->setGeometry(10,130,50,20);
    saturation_bits->setMaximum(8);
    saturation_bits->setMinimum(0);
    saturation_bits->setValue(2);

    delay_label = new QLabel(this);
    delay_label->setGeometry(10,150,100,20);
    delay_label->setText("Delay");

    delay = new QSpinBox(this);
    delay->setGeometry(10,170,60,20);
    delay->setMinimum(50);
    delay->setMaximum(1000);
    delay->setSingleStep(50);

    frame_amount_label = new QLabel(this);
    frame_amount_label->setGeometry(10,190,100,20);
    frame_amount_label->setText("Frame amount");

    amount = new QSpinBox(this);
    amount->setGeometry(10,210,50,20);
    amount->setMinimum(2);
    amount->setValue(10);

    start_color_label = new QLabel(this);
    start_color_label->setGeometry(10,230,100,20);
    start_color_label->setText("Start color");

    start_color_button = new QPushButton(this);
    start_color_button->setGeometry(10,250,40,40);
    start_color_button->setStyleSheet("background-color: rgb(" + QString::number(start_color.red()) + "," + QString::number(start_color.green()) + "," + QString::number(start_color.blue()) + ");  border: none;");

    end_color_label = new QLabel(this);
    end_color_label->setGeometry(10,290,100,20);
    end_color_label->setText("End color");

    end_color_button = new QPushButton(this);
    end_color_button->setGeometry(10,310,40,40);
    end_color_button->setStyleSheet("background-color: rgb(" + QString::number(end_color.red()) + "," + QString::number(end_color.green()) + "," + QString::number(end_color.blue()) + ");  border: none;");

    end_color_label = new QLabel(this);
    end_color_label->setGeometry(250,330,140,20);
    end_color_label->setText("R: " + QString::number(color.red()) + " G: " + QString::number(color.green()) + " B: " + QString::number(color.blue()));

    timer = new QTimer(this);
    timer->setInterval(delay->value());

    connect(timer              , SIGNAL(timeout()), this, SLOT(Update()));
    connect(start              , SIGNAL(clicked()), this, SLOT(Start()));
    connect(start_color_button , SIGNAL(clicked()), this, SLOT(Start_Color_Pressed()));
    connect(end_color_button   , SIGNAL(clicked()), this, SLOT(End_Color_Pressed()));

    this->Update();
}


void MainWindow::Update()
{
    static int number = 0;

    color.setRgb(color.red() + (end_color.red() - start_color.red())/ amount->value(), color.green() + (end_color.green() - start_color.green())/ amount->value(),color.blue() + (end_color.blue() - start_color.blue())/ amount->value());

    hsv.setHsl((color.hue() / (int)pow(2.0f, 9 - hue_bits->value()) ) * (int)pow(2.0f, 9 - hue_bits->value()) , color.saturation() / (int)pow(2.0f, 8 - saturation_bits->value()) * (int)pow(2.0f, 8 - saturation_bits->value()), color.lightness() / (int)pow(2.0f, 8 - lightness_bits->value()) * (int)pow(2.0f, 8 - lightness_bits->value()) );

    this->update();

    number++;
    if(number == amount->value())
    {
        timer->stop();
        number = 0;
        start->setDisabled(false);
    }
}
void MainWindow::Start()
{
    timer->setInterval(delay->value());
    timer->start();

    color = start_color;
    this->update();

    start->setDisabled(true);
}



void MainWindow::Set_Color(int R, int G, int B, QPainter *painter)
{

   QColor col;

   col.setRgb(R,G,B);
   painter->fillRect(110,10,130,340,col);
   painter->fillRect(240,10,150,320,col);
   painter->setPen(QColor(0x808080));
   painter->drawLine(100,0,100,360);
   end_color_label->setText("R: " + QString::number(col.red()) + " G: " + QString::number(col.green()) + " B: " + QString::number(col.blue()));
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    Set_Color(this->hsv.red(), this->hsv.green(), this->hsv.blue(), &painter);
}
void MainWindow::Start_Color_Pressed()
{
    QColorDialog selected_color;

    selected_color.setCurrentColor(start_color);
    selected_color.exec();

    start_color = selected_color.currentColor();
    start_color_button->setStyleSheet("background-color: rgb(" + QString::number(start_color.red()) + "," + QString::number(start_color.green()) + "," + QString::number(start_color.blue()) + ");  border: none;");
    color = start_color;
    this->Update();
}

void MainWindow::End_Color_Pressed()
{
    QColorDialog selected_color;
    selected_color.setCurrentColor(end_color);
    selected_color.exec();

    end_color = selected_color.currentColor();

    end_color_button->setStyleSheet("background-color: rgb(" + QString::number(end_color.red()) + "," + QString::number(end_color.green()) + "," + QString::number(end_color.blue()) + ");  border: none;");
}
