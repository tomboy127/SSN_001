#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QtDebug>
#include <QElapsedTimer>
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
    QGraphicsScene* out_map_scene;

    void generate_neurons();
    void generate_axons();
    void generate_network();
    void generate_out_map();
    void make_highlight();
    void delete_highlight();

    void align_neurons();
    void align_axons();
    void update_aligments();
    void update_network_colors();
    void calculate_network();

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
    cell* input_selected=nullptr;
    cell* cell_selected=nullptr;

    axon* axon_ptrs[MAX_LR][MAX_NR][MAX_NR];

    QGraphicsEllipseItem* highlight=nullptr;
    void resizeEvent(QResizeEvent*);

    QElapsedTimer timer;

public slots:
    void setInfoText(QString);
    void onObject_selected(cell*);
    //void on_object_deselected(cell*);

private slots:
    void on_btn_scene_change_1_clicked();
    void on_btn_scene_change_2_clicked();
    void on_btn_gen_network_clicked();
    void on_btnFire_clicked();
    void on_btnRnd_clicked();

    void on_dial_valueChanged(int value);
    void on_sliderValue_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *make_scene_1();
    QGraphicsScene *make_scene_2();
    QGraphicsScene *make_out_map_scene();

    //QGraphicsView *view_1;
};
#endif // MAINWINDOW_H
