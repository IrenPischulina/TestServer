#include "setip.h"
#include "ui_setip.h"
#include "receiver.h"

SetIP::SetIP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetIP)
{
    ui->setupUi(this);

    connect(ui -> okayButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(okaySlot()));

    connect(ui -> cancelButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(cancelSlot()));

    oldIP = Receiver::getDefaultIP();
    oldPort = Receiver::getDefaultPort();
    ui -> ipLineEdit -> setText(oldIP);
    ui -> portLineEdit -> setText(QString::number(oldPort));

}

SetIP::~SetIP()
{
    delete ui;
}

void SetIP::okaySlot()
{
    oldIP = ui -> ipLineEdit -> text();
    oldPort = ui -> portLineEdit->text().toInt();
    hide();
    okaySignal(oldIP, oldPort);
}

void SetIP::cancelSlot()
{
    ui -> ipLineEdit -> setText(oldIP);
    ui -> portLineEdit -> setText(QString::number(oldPort));
    hide();
}
