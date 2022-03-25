#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QtDebug>
#include <config.h>
#include "input.h"
#include "output.h"
#include "neuron.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene* scene1;
    QGraphicsScene* scene2;

    void generate_neurons();
    void align_neurons();
    void update_aligment();
    int inputs=INPS;
    int layers=LRS;
    int neurons=NRNS;
    int outputs=OUTS;
    bool neurons_generated=0;

    input* input_ptrs[MAX_INP];
    neuron* neuron_ptrs[MAX_LR][MAX_NR];
    output* output_ptrs[MAX_OUT];

    void resizeEvent(QResizeEvent*);

private slots:

    void on_btn_scene_change_1_clicked();
    void on_btn_scene_change_2_clicked();
    void on_btn_gen_network_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *make_scene_1();
    QGraphicsScene *make_scene_2();
    //QGraphicsView *view_1;
};
#endif // MAINWINDOW_H
