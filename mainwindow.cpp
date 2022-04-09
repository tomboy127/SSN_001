#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "random.h"


// funkcja do zerowania wartosci + bias
// funkcja dodaj?ca addVal
// triger funkcji aktywacyjnej

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene1=make_scene_1();
    scene2=make_scene_2();
    out_map_scene=make_out_map_scene();


    ui->view_2->setScene(out_map_scene);
    ui->view_2->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    ui->view_1->setScene(scene1);
    ui->view_1->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);


    ui->sBox_inputs->setMaximum(MAX_INP);
    ui->sBox_layers->setMaximum(MAX_LR-2);
    ui->sBox_neurons->setMaximum(MAX_NR);
    ui->sBox_outputs->setMaximum(MAX_OUT);

    ui->sBox_inputs->setValue(INPS);
    ui->sBox_layers->setValue(LRS);
    ui->sBox_neurons->setValue(NRNS);
    ui->sBox_outputs->setValue(OUTS);

    ui->view_2->setMaximumSize(OUT_MAP_SIZE+2,OUT_MAP_SIZE+2);
    ui->view_2->setMinimumSize(OUT_MAP_SIZE+2,OUT_MAP_SIZE+2);



    //for(int i=0;i<10;i++)
    //    rnd11();
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
        QObject::connect(cell_ptrs[0][i], SIGNAL(object_selected(cell*)), this, SLOT(onObject_selected(cell*)));

        //QObject::connect(cell_ptrs[0][i], SIGNAL(object_deselected(cell*)), this, SLOT(on_object_deselected(cell*)));
        //QObject::connect(cell_ptrs[0][i], SIGNAL(object_selected(cell*)), this, SLOT(on_object_selected(cell*)));
    }

    for(int i=1;i<(layers-1);i++){
        for(int j=0;j<neurons;j++){
            cell_ptrs[i][j]=new neuron(i,j+1);
            QObject::connect(cell_ptrs[i][j], SIGNAL(setInfoTextUi(QString)), this, SLOT(setInfoText(QString)));
            QObject::connect(cell_ptrs[i][j], SIGNAL(object_selected(cell*)), this, SLOT(onObject_selected(cell*)));
        }
    }

    for(int i=0;i<(outputs);i++){
        cell_ptrs[layers-1][i]=new output(layers,i+1);
        QObject::connect(cell_ptrs[layers-1][i], SIGNAL(setInfoTextUi(QString)), this, SLOT(setInfoText(QString)));
        QObject::connect(cell_ptrs[layers-1][i], SIGNAL(object_selected(cell*)), this, SLOT(onObject_selected(cell*)));
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
    srand(time(0));
    timer.restart();
    if(network_generated){
        delete_cells();
        delete_axons();
        qDebug()<<"Previous config deleted.";
    }
    generate_neurons();
    generate_axons();
    align_neurons();
    align_axons();
    ui->sliderValue->setEnabled(0);
    ui->dial->setEnabled(0);
    ui->btnFire->setEnabled(1);
    ui->btnRnd->setEnabled(1);
    ui->label->setEnabled(1);
    ui->label_obj_info->setEnabled(1);
    ui->label_slider_name->setEnabled(1);

    qDebug() << "Network generated in" << timer.elapsed() << "milliseconds";
}

void MainWindow::generate_out_map()
{
    if(inputs>=2){
        timer.restart();
        QImage *image = new QImage(OUT_MAP_SIZE,OUT_MAP_SIZE,QImage::Format_RGB32);
        uint32_t color=0;
        int32_t color2=0;

        double step=2.0/OUT_MAP_SIZE;
        cell_ptrs[0][0]->delVal();
        cell_ptrs[0][0]->addVal(-1);
        cell_ptrs[0][1]->delVal();
        cell_ptrs[0][1]->addVal(-1);

        for(int i=0;i<OUT_MAP_SIZE;i++){
            for(int j=0;j<OUT_MAP_SIZE;j++){
                calculate_network();
                color2=qRound(cell_ptrs[layers-1][0]->getVal()*255);
                if(color2>0) color=color2<<8;
                else color=(color2*-1)<<16;
                //qDebug()<<color2;
                image->setPixelColor(i,j,color);
                cell_ptrs[0][0]->addVal(step);
            }
            cell_ptrs[0][1]->addVal(step);
            cell_ptrs[0][0]->delVal();
            cell_ptrs[0][0]->addVal(-1);
        }
        out_map_scene->addPixmap(QPixmap::fromImage(*image));
        ui->view_2->update();
        qDebug() << "Out map generated in" << timer.elapsed() << "milliseconds";
    }
    else
        qDebug() << "Out map not generated, not enough inputs.";
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
            axon_ptrs[0][i][j]->updateColor();
        }
    }

    for(int i=0;i<layers-3;i++) {
        for(int j=0;j<neurons;j++){
            for(int k=0;k<neurons;k++){
                axon_ptrs[i+1][j][k]->upPos();
                axon_ptrs[i+1][j][k]->updateColor();
            }
        }
    }

    for(int i=0;i<neurons;i++){
        for(int j=0;j<outputs;j++){
            axon_ptrs[layers-1][i][j]->upPos();
            axon_ptrs[layers-1][i][j]->updateColor();
        }
    }

    scene1->setSceneRect(QRectF(0,0,w,h));

}

void MainWindow::update_network_colors()
{

    for(int i=0;i<(inputs);i++){
        cell_ptrs[0][i]->updateColor();
    }

    for(int i=1;i<(layers-1);i++){
        for(int j=0;j<neurons;j++){
            cell_ptrs[i][j]->updateColor();
        }
    }

    for(int i=0;i<(outputs);i++){
        cell_ptrs[layers-1][i]->updateColor();

    }


    for(int i=0;i<inputs;i++){      //axon input-neuron
        for(int j=0;j<neurons;j++){
            axon_ptrs[0][i][j]->updateColor();
        }
    }

    for(int i=1;i<layers-2;i++) {   //axon neuron-neuron
        for(int j=0;j<neurons;j++){
            for(int k=0;k<neurons;k++){
                axon_ptrs[i][j][k]->updateColor();
            }
        }
    }

    for(int i=0;i<neurons;i++){     //axon neuron-output
        for(int j=0;j<outputs;j++){
            axon_ptrs[layers-1][i][j]->updateColor();
        }
    }
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

void MainWindow::onObject_selected(cell* ptr)
{
    cell_selected=ptr;

    if(!QString::compare(cell_selected->getType(),"Input"))
    {
        input_selected=ptr;

        ui->dial->setValue(1000*input_selected->getVal());
        ui->sliderValue->setValue(1000*input_selected->getVal());

        ui->label_slider_name->setText(input_selected->getType()+" "+input_selected->getGridPos().back()+":");

        ui->sliderValue->setEnabled(1);
        ui->dial->setEnabled(1);
    }

    //make_highlight();
}

/*
void MainWindow::on_object_deselected(cell* ptr)
{
    input_selected=ptr;

    delete_highlight();
}
*/

QGraphicsScene* MainWindow::make_scene_1()
{
    QGraphicsScene* scene_1= new QGraphicsScene();
    scene_1->setBackgroundBrush(Qt::black);
    //scene_1->setSceneRect(ui->view_1->width()/2.0,ui->view_1->height()/-2.0,ui->view_1->width()-2,ui->view_1->height()-2);
    //scene_1->setSceneRect(0,0,ui->view_1->width()-2,ui->view_1->height()-2);
    //scene_1->setSceneRect(0,0,0,0);

    //qDebug()<<ui->view_1->width()-2;
    return scene_1;
}

QGraphicsScene* MainWindow::make_scene_2()
{
    QGraphicsScene* scene_2= new QGraphicsScene();
    scene_2->setBackgroundBrush(Qt::red);
    scene_2->setSceneRect(0,0,ui->view_1->width()-2,ui->view_1->height()-2);
    return scene_2;
}

QGraphicsScene* MainWindow::make_out_map_scene()
{
    QGraphicsScene* scene= new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);
    scene->setSceneRect(0,0,OUT_MAP_SIZE,OUT_MAP_SIZE);
    return scene;
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
        generate_out_map();
        on_btnRnd_clicked();
        calculate_network();
        update_network_colors();
    }
    else if(QMessageBox::No){
        qDebug()<<"nie";
    }

}

void MainWindow::calculate_network()
{

    for(int i=0;i<(inputs);i++){
        //cell_ptrs[0][i]->updateColor();
    }

    for(int i=1;i<(layers-1);i++){
        for(int j=0;j<neurons;j++){
            cell_ptrs[i][j]->delVal();
            //cell_ptrs[i][j]->updateColor();
        }
    }

    for(int i=0;i<(outputs);i++){
        cell_ptrs[layers-1][i]->delVal();
        //cell_ptrs[layers-1][i]->updateColor();

    }


    for(int i=0;i<inputs;i++){      //axon input-neuron
        for(int j=0;j<neurons;j++){
            axon_ptrs[0][i][j]->fire();
            //axon_ptrs[0][i][j]->updateColor();

        }
    }

    for(int i=1;i<layers-2;i++) {   //axon neuron-neuron
        for(int j=0;j<neurons;j++){
            for(int k=0;k<neurons;k++){
               axon_ptrs[i][j][k]->fire();
              // axon_ptrs[i][j][k]->updateColor();
            }
        }
    }

    for(int i=0;i<neurons;i++){     //axon neuron-output
        for(int j=0;j<outputs;j++){
            axon_ptrs[layers-1][i][j]->fire();
            //axon_ptrs[layers-1][i][j]->updateColor();
        }
    }
}

void MainWindow::on_btnFire_clicked()
{
    timer.restart();
    calculate_network();
    qDebug() << "Network calculated in" << timer.elapsed() << "milliseconds";
    update_network_colors();
}

void MainWindow::on_btnRnd_clicked()
{
    for(int i=0;i<(inputs);i++){
        cell_ptrs[0][i]->delVal();
    }

    for(int i=0;i<(inputs);i++){
        cell_ptrs[0][i]->addVal(rnd11());
        //cell_ptrs[0][i]->updateColor();
    }

    timer.restart();
    calculate_network();
    qDebug() << "Network calculated in" << timer.elapsed() << "milliseconds";
    update_network_colors();

}

void MainWindow::on_dial_valueChanged(int position)
{
    ui->sliderValue->setValue(position);
    input_selected->setVal(position/1000.0);
    cell_selected->updateInfoBox();
    calculate_network();
    update_network_colors();

}

void MainWindow::on_sliderValue_valueChanged(int position)
{
    ui->dial->setValue(position);
    input_selected->delVal();
    input_selected->addVal(position/1000.0);
    cell_selected->updateInfoBox();
    calculate_network();
    update_network_colors();

}

void MainWindow::make_highlight(){
    highlight = new QGraphicsEllipseItem(nullptr);
    highlight->setRect(-DOTSIZE*HiGHLIGHT/2,-DOTSIZE*HiGHLIGHT/2,DOTSIZE*HiGHLIGHT/1,DOTSIZE*HiGHLIGHT/1);
    highlight->setPos(input_selected->getPos());
    QRadialGradient gradient = QRadialGradient(QPointF(0,0),DOTSIZE*HiGHLIGHT/2,QPointF(0,0),DOTSIZE/3);
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::yellow);

    QBrush brushFocus(gradient);
    highlight->setBrush(brushFocus);

    highlight->setOpacity(1);
    highlight->setZValue(-1);
    //highlight->setBrush(Qt::yellow);
    scene1->addItem(highlight);
}

void MainWindow::delete_highlight()
{
    scene1->removeItem(highlight);
}
