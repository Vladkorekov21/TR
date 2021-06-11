#ifndef KOMMIVOYAZHER_H
#define KOMMIVOYAZHER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Kommivoyazher; }
QT_END_NAMESPACE

class Kommivoyazher : public QMainWindow
{
    Q_OBJECT

public:
    Kommivoyazher(QWidget *parent = nullptr);
    ~Kommivoyazher();

private:
    Ui::Kommivoyazher *ui;
private slots:

    void on_pushButton_start_clicked();

};
#endif // KOMMIVOYAZHER_H
