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
    ui->view_1->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);


    ui->sBox_inputs->setMaximum(MAX_INP);
    ui->sBox_layers->setMaximum(MAX_LR);
    ui->sBox_neurons->setMaximum(MAX_NR);
    ui->sBox_outputs->setMaximum(MAX_OUT);

    ui->sBox_inputs->setValue(INPS);
    ui->sBox_layers->setValue(LRS);
    ui->sBox_neurons->setValue(NRNS);
    ui->sBox_outputs->setValue(OUTS);

    //generate_network();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generate_neurons()
{
    inputs=ui->sBox_inputs->value();
    layers=ui->sBox_layers->value()+2;
    neurons=ui->sBox_neurons->value();
    outputs=ui->sBox_outputs->value();

    for(int i=0;i<(inputs);i++){
        cell_ptrs[0][i]=new input(1,i+1);
        QObject::connect(cell_ptrs[0][i], SIGNAL(setInfoTextUi(QString)), this, SLOT(setInfoText(QString)));
    }

    for(int i=1;i<(layers-1);i++){
        for(int j=0;j<neurons;j++){
            cell_ptrs[i][j]=new neuron(i,j+1);
            QObject::connect(cell_ptrs[i][j], SIGNAL(setInfoTextUi(QString)), this, SLOT(setInfoText(QString)));
        }
    }

    for(int i=0;i<(outputs);i++){
        cell_ptrs[layers-1][i]=new output(layers,i+1);
        QObject::connect(cell_ptrs[layers-1][i], SIGNAL(setInfoTextUi(QString)), this, SLOT(setInfoText(QString)));
    }

    network_generated=1;
}

void MainWindow::generate_axons()
{
    for(int i=0;i<inputs;i++){      //axon input-neuron
        for(int j=0;j<neurons;j++){
            axon_ptrs[0][i][j] = new axon(cell_ptrs[0][i],cell_ptrs[1][j]);
            QObject::connect(axon_ptrs[0][i][j], SIGNAL(setInfoTextUi(QString)), this, SLOT(setInfoText(QString)));

        }
    }

    for(int i=1;i<layers-2;i++) {   //axon neuron-neuron
        for(int j=0;j<neurons;j++){
            for(int k=0;k<neurons;k++){
               //qDebug()<<i<<j<<k;
               axon_ptrs[i][j][k]= new axon(cell_ptrs[i][j],cell_ptrs[i+1][k]);
               QObject::connect(axon_ptrs[i][j][k], SIGNAL(setInfoTextUi(QString)), this, SLOT(setInfoText(QString)));
            }
        }
    }

    for(int i=0;i<neurons;i++){     //axon neuron-output
        for(int j=0;j<outputs;j++){
            axon_ptrs[layers-1][i][j]= new axon(cell_ptrs[layers-2][i],cell_ptrs[layers-1][j]);
            QObject::connect(axon_ptrs[layers-1][i][j], SIGNAL(setInfoTextUi(QString)), this, SLOT(setInfoText(QString)));
        }
    }

}

void MainWindow::generate_network()
{
    if(network_generated){
        delete_cells();
        delete_axons();
        qDebug()<<"Previous config deleted.";
    }
    generate_neurons();
    generate_axons();
    align_neurons();
    align_axons();

}

void MainWindow::align_neurons()
{
    double w=ui->view_1->width()-2;
    double h=ui->view_1->height()-2;

    int columns=layers;

    for(int i=0;i<(inputs);i++){
        cell_ptrs[0][i]->setPos((w/(columns+1)),((h/(inputs+1))+(h/(inputs+1))*i));
        scene1->addItem(cell_ptrs[0][i]);
    }

    for(int i=1;i<(layers-1);i++){
        for(int j=0;j<neurons;j++){
            cell_ptrs[i][j]->setPos(((w/(columns+1))*(i+1)),((h/(neurons+1))+(h/(neurons+1))*j));
            scene1->addItem(cell_ptrs[i][j]);
        }
    }

    for(int i=0;i<(outputs);i++){
        cell_ptrs[layers-1][i]->setPos(((w/(columns+1))*columns),((h/(outputs+1))+(h/(outputs+1))*i));
        scene1->addItem(cell_ptrs[layers-1][i]);
    }

    scene1->setSceneRect(QRectF(0,0,w,h));
}

void MainWindow::align_axons()
{
    for(int i=0;i<inputs;i++){
        for(int j=0;j<neurons;j++){
            axon_ptrs[0][i][j]->upPos();
            scene1->addItem(axon_ptrs[0][i][j]);
        }
    }

    for(int i=1;i<layers-2;i++) {
        for(int j=0;j<neurons;j++){
            for(int k=0;k<neurons;k++){
                axon_ptrs[i][j][k]->upPos();
                scene1->addItem(axon_ptrs[i][j][k]);
            }
        }
    }

    for(int i=0;i<neurons;i++){
        for(int j=0;j<outputs;j++){
            axon_ptrs[layers-1][i][j]->upPos();
            scene1->addItem(axon_ptrs[layers-1][i][j]);
        }
    }

    //scene1->setSceneRect(QRectF(0,0,w,h));
}

void MainWindow::update_aligments()
{
    double w=ui->view_1->width()-2;
    double h=ui->view_1->height()-2;

    int columns=layers;

    for(int i=0;i<(inputs);i++){
        cell_ptrs[0][i]->setPos((w/(columns+1)),((h/(inputs+1))+(h/(inputs+1))*i));
    }

    for(int i=1;i<(layers-1);i++){
        for(int j=0;j<neurons;j++){
            cell_ptrs[i][j]->setPos(((w/(columns+1))*(i+1)),((h/(neurons+1))+(h/(neurons+1))*j));
        }
    }

    for(int i=0;i<(outputs);i++){
        cell_ptrs[layers-1][i]->setPos(((w/(columns+1))*columns),((h/(outputs+1))+(h/(outputs+1))*i));
    }


    for(int i=0;i<inputs;i++){
        for(int j=0;j<neurons;j++){
            axon_ptrs[0][i][j]->upPos();
        }
    }

    for(int i=0;i<layers-3;i++) {
        for(int j=0;j<neurons;j++){
            for(int k=0;k<neurons;k++){
                axon_ptrs[i+1][j][k]->upPos();
            }
        }
    }

    for(int i=0;i<neurons;i++){
        for(int j=0;j<outputs;j++){
            axon_ptrs[layers-1][i][j]->upPos();
        }
    }

    scene1->setSceneRect(QRectF(0,0,w,h));

}

void MainWindow::delete_cells()
{
    for(int i=0;i<layers;i++){
        for(int j=0;j<inputs && i==0;j++){
            cell_ptrs[i][j]->del_obj();
            cell_ptrs[i][j]=nullptr;
        }
        for(int k=0;k<neurons && i>0 && i<(layers-1);k++){
            cell_ptrs[i][k]->del_obj();
            cell_ptrs[i][k]=nullptr;
        }
        for(int l=0;l<outputs && i==(layers-1);l++){
            cell_ptrs[i][l]->del_obj();
            cell_ptrs[i][l]=nullptr;
        }
    }
}

void MainWindow::delete_axons()
{
    for(int i=0;i<inputs;i++){
        for(int j=0;j<neurons;j++){
            axon_ptrs[0][i][j]->del_obj();
            axon_ptrs[0][i][j]=nullptr;
        }
    }

    for(int i=1;i<layers-2;i++) {
        for(int j=0;j<neurons;j++){
            for(int k=0;k<neurons;k++){
                axon_ptrs[i][j][k]->del_obj();
                axon_ptrs[i][j][k]=nullptr;
            }
        }
    }

    for(int i=0;i<neurons;i++){
        for(int j=0;j<outputs;j++){
            axon_ptrs[layers-1][i][j]->del_obj();
            axon_ptrs[layers-1][i][j]=nullptr;
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    if(network_generated) update_aligments();
}

void MainWindow::setInfoText(QString str)
{
    ui->label_obj_info->setText(str);
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
        generate_network();
    }
    else if(QMessageBox::No){
        qDebug()<<"nie";
    }

}


