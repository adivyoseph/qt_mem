#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Mqtt myMqtt;
    w.SetMqtt(&myMqtt);
    myMqtt.mqtt_init(&w);
    QObject::connect(&myMqtt, SIGNAL(mqtt_signal_reset(void)), &w, SLOT(slot_on_reset_event(void)));
    QObject::connect(&myMqtt, SIGNAL(mqtt_signal_start(struct Mqtt_msg *)), &w, SLOT(slot_on_start_event(struct Mqtt_msg *)));

    w.show();

    return a.exec();
}
