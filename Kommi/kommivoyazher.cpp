#include "kommivoyazher.h"
#include "ui_kommivoyazher.h"
#include <iostream>

int length [7][7];
bool *checked=new bool [7];
int min_path=1000;
int *min_way=new int [10];
int min_kol;
int way[10];
int startTown=0;

Kommivoyazher::Kommivoyazher(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Kommivoyazher)
{
    ui->setupUi(this);
    connect (ui->lineEdit, &QLineEdit::editingFinished, this, &Kommivoyazher::on_pushButton_start_clicked);

    for (int i=0;i<7;i++)
    {
        for (int j=0;j<7;j++)
        {
            length[i][j]=0;
        }
    }
    length[1][2]=28;
    length[1][3]=13;
    length[1][4]=15;
    length[1][6]=18;

    length[2][1]=28;
    length[2][4]=20;
    length[2][5]=21;

    length[3][1]=13;
    length[3][5]=30;

    length[4][1]=15;
    length[4][2]=20;
    length[4][5]=39;
    length[4][6]=31;

    length[5][2]=21;
    length[5][3]=30;
    length[5][4]=39;

    length[6][1]=18;
    length[6][4]=31;

    for (int i=1;i<7;i++)
    {
        checked[i]=false;
    }
    for (int i=0;i<10;i++)
    {
        min_way[i]=0;
        way[i]=0;
    }

    QPixmap pix("C:/Users/Sasha/Documents/QtProjects/komi4/myGr.png");
    int w=ui->graph->width();
    int h=ui->graph->height();
    ui->graph->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

Kommivoyazher::~Kommivoyazher()
{
    delete ui;
    delete [] checked;
    delete [] min_way;
}

void find_path(int n,int path,int kol)
{
    checked[n]=true;
    kol++;
    way[kol]=n;
    length[0][1]=0;
    path+=length[way[kol-1]][n];

    for (int i=1;i<=6;i++)
    {
        if ((length[n][i]!=0) and(checked[i]==false))
        {
            find_path(i,path,kol);
        }
    }
    int x=0;
    for (int i=1;i<7;i++)
    {
        if (checked[i]==true) x++;
    }

    if (x==6 && length[n][startTown]!=0)
    {
        path+=length[n][startTown];
        kol++;
        way[kol]=startTown;

        if (path<=min_path)
        {
            min_path=path;
            min_kol=kol;
            int i=1;
            while (way[i]!=0)
            {
                min_way[i]=way[i];
                i++;
            }
        }
    }
    checked[n]=false;
    way[kol]=0;
    kol--;

}

void Kommivoyazher::on_pushButton_start_clicked()
{
    if ((ui->lineEdit->text()).toInt()>=1 && (ui->lineEdit->text()).toInt()<=6)
    {
        for (int i=1;i<7;i++)
        {
            checked[i]=false;
        }
        for (int i=0;i<10;i++)
        {
            min_way[i]=0;
            way[i]=0;
        }

        ui->label_path->setText("Длина маршрута:");
        ui->label_way->setText("Маршрут:");

        startTown=(ui->lineEdit->text()).toInt();
        checked[startTown]=true;
        find_path(startTown,0,0);
        int i=1;
        ui->label_path->setText(ui->label_path->text()+" "+QString::number(min_path));
        while (min_way[i]!=0)
        {
            ui->label_way->setText(ui->label_way->text()+" "+QString::number(min_way[i]));
            i++;
        }
    }
    ui->lineEdit->clear();
}

