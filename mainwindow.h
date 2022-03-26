#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QtDebug>
#include <config.h>
#include "cell.h"
#include "input.h"
#include "output.h"
#include "neuron.h"
#include "axon.h"



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
    void generate_axons();
    void generate_network();

    void align_neurons();
    void align_axons();
    void update_aligments();

    void delete_cells();
    void delete_axons();

    int inputs=INPS;
    int layers=LRS;
    int neurons=NRNS;
    int outputs=OUTS;

    bool network_generated=0;

    //cell* input_ptrs[MAX_INP];
    cell* cell_ptrs[MAX_LR][MAX_NR];
    //cell* output_ptrs[MAX_OUT];

    axon* axon_ptrs[MAX_LR][MAX_NR][MAX_NR];

    void resizeEvent(QResizeEvent*);

public slots:
    void setInfoText(QString text);

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
