#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene1=make_scene_1();
    scene2=make_scene_2();

    ui->view_1->setScene(scene1);

    ui->sBox_inputs->setMaximum(MAX_INP);
    ui->sBox_layers->setMaximum(MAX_LR);
    ui->sBox_neurons->setMaximum(MAX_NR);
    ui->sBox_outputs->setMaximum(MAX_OUT);

    ui->sBox_inputs->setValue(INPS);
    ui->sBox_layers->setValue(LRS);
    ui->sBox_neurons->setValue(NRNS);
    ui->sBox_outputs->setValue(OUTS);

    //generate_neurons();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generate_neurons()
{
    if(neurons_generated){
        for(int i=0;i<inputs;i++){
            input_ptrs[i]->del_obj();
            input_ptrs[i]=nullptr;
        }

        for(int i=0;i<layers;i++){
            for(int j=0;j<neurons;j++){
                neuron_ptrs[i][j]->del_obj();
                neuron_ptrs[i][j]=nullptr;
            }
        }

        for(int i=0;i<outputs;i++){
            output_ptrs[i]->del_obj();
            output_ptrs[i]=nullptr;
        }
         qDebug()<<"Previous config deleted.";
    }


    inputs=ui->sBox_inputs->value();
    layers=ui->sBox_layers->value();
    neurons=ui->sBox_neurons->value();
    outputs=ui->sBox_outputs->value();

    for(int i=0;i<inputs;i++){
        input_ptrs[i]=new input();
        qDebug()<<"Inp"<<i+1<<"rdy";
    }

    for(int i=0;i<layers;i++){
        for(int j=0;j<neurons;j++){
            neuron_ptrs[i][j]=new neuron();
            qDebug()<<"Lr"<<i+1<<"nrn"<<j+1<<"rdy";
        }
    }

    for(int i=0;i<outputs;i++){
        output_ptrs[i]=new output();
        qDebug()<<"Out"<<i+1<<"rdy";
    }
    neurons_generated=1;
    align_neurons();
}

void MainWindow::align_neurons()
{
    double w=ui->view_1->width()-2;
    double h=ui->view_1->height()-2;

    int columns=layers+2;


    for(int i=0;i<inputs;i++){
        input_ptrs[i]->setPos((w/(columns+1)),((h/(inputs+1))+(h/(inputs+1))*i));
        scene1->addItem(input_ptrs[i]);
    }

    for(int i=0;i<layers;i++){
        for(int j=0;j<neurons;j++){
            neuron_ptrs[i][j]->setPos((((w/(columns+1)))+(w/(columns+1))*(i+1)),((h/(neurons+1))+(h/(neurons+1))*j));
            scene1->addItem(neuron_ptrs[i][j]);
        }
    }
    for(int i=0;i<outputs;i++){
        output_ptrs[i]->setPos(((w/(columns+1))*columns),((h/(outputs+1))+(h/(outputs+1))*i));
        scene1->addItem(output_ptrs[i]);
    }

    scene1->setSceneRect(QRectF(0,0,w,h));
}

void MainWindow::update_aligment()
{
    double w=ui->view_1->width()-2;
    double h=ui->view_1->height()-2;

    int columns=layers+2;


    for(int i=0;i<inputs;i++){
        input_ptrs[i]->setPos((w/(columns+1)),((h/(inputs+1))+(h/(inputs+1))*i));
    }

    for(int i=0;i<layers;i++){
        for(int j=0;j<neurons;j++){
            neuron_ptrs[i][j]->setPos((((w/(columns+1)))+(w/(columns+1))*(i+1)),((h/(neurons+1))+(h/(neurons+1))*j));
        }
    }
    for(int i=0;i<outputs;i++){
        output_ptrs[i]->setPos(((w/(columns+1))*columns),((h/(outputs+1))+(h/(outputs+1))*i));
    }
    scene1->setSceneRect(QRectF(0,0,w,h));
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    if(neurons_generated) update_aligment();
}

QGraphicsScene* MainWindow::make_scene_1()
{
    QGraphicsScene* scene_1= new QGraphicsScene();
    scene_1->setBackgroundBrush(Qt::black);
    //scene_1->setSceneRect(ui->view_1->width()/2.0,ui->view_1->height()/-2.0,ui->view_1->width()-2,ui->view_1->height()-2);
    //scene_1->setSceneRect(0,0,ui->view_1->width()-2,ui->view_1->height()-2);
    //scene_1->setSceneRect(0,0,0,0);

    qDebug()<<ui->view_1->width()-2;
    return scene_1;
}

QGraphicsScene* MainWindow::make_scene_2()
{
    QGraphicsScene* scene_2= new QGraphicsScene();
    scene_2->setBackgroundBrush(Qt::red);
    scene_2->setSceneRect(0,0,ui->view_1->width()-2,ui->view_1->height()-2);
    return scene_2;
}


void MainWindow::on_btn_scene_change_1_clicked()
{
    ui->view_1->setScene(scene1);
}

void MainWindow::on_btn_scene_change_2_clicked()
{
    ui->view_1->setScene(scene2);
}

void MainWindow::on_btn_gen_network_clicked()
{
    QMessageBox confBox;
    confBox.setWindowTitle("New network generation");
    confBox.setText("Are you sure you want to generate new network?");
    //confBox.setStandardButtons(QMessageBox::Yes);
    confBox.addButton(QMessageBox::Yes);
    confBox.addButton(QMessageBox::No);
    confBox.setDefaultButton(QMessageBox::No);

    if(confBox.exec()== QMessageBox::Yes){
        generate_neurons();
    }
    else if(QMessageBox::No){
        qDebug()<<"nie";
    }

}


