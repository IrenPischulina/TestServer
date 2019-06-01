#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

class FileDialog : public QObject
{
    Q_OBJECT
public:
    explicit FileDialog(QObject *parent = nullptr);

signals:

public slots:
    void openFile();
};

#endif // FILEDIALOG_H
