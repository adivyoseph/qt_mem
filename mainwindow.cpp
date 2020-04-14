#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList headers;
    headers << QString("Phys_addr") << QString("Attr") << QString("Memory");
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::SetMqtt(Mqtt *p_mqtt_arg){
    p_mqtt = p_mqtt_arg;

}


void MainWindow::slot_on_reset_event(void){
    struct Mqtt_msg msg;
    randID = rand();
    msg.msg_type = MSG_TYPE_REGISTER;
    msg.msg_node_type = MSG_NODE_TYPE_MC;
    strcpy(msg.msg_source, "mem");
    msg.msg_data_len = 2;
    msg.msg_data[0].key = KVD_TYPE_RADOM;
    msg.msg_data[0].value = randID;
    msg.msg_data[1].key = KVD_TYPE_PADD_SIZE;
    msg.msg_data[1].value = pa_size;
    qDebug() << " on_reset_event randID " << randID;
    msg.msg_len = MSG_LEN_FULL;
    p_mqtt->mqtt_pub_register(&msg);

    ;
}

void MainWindow::slot_on_start_event(struct Mqtt_msg *msg){
    qDebug() << "on_start_event my randID " << randID << " start " << msg->msg_data[2].value;
    if(msg->msg_data[0].value == randID){
         this->setWindowTitle(QString(msg->msg_source));
        pa_start = msg->msg_data[2].value;
        mem_set_pa();

    }


}


void     MainWindow::mem_set_pa(){
    //int addr = pa_start;
    int i;
    for(i = 0; i <= ui->tableWidget->rowCount(); i++){
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(pa_start+i)));
    }

}

