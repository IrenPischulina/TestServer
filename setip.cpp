#include "setip.h"
#include "ui_setip.h"

SetIP::SetIP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetIP)
{
    ui->setupUi(this);

    oldIP = "";
    oldPort = 0;

    connect(ui -> okayButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(okaySlot()));
    connect(ui -> cancelButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(cancelSlot()));
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
    ui -> portLineEdit ->setText(QString::number(oldPort));
    hide();
}
