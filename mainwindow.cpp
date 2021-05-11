#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      matA(0),
      matB(0)
{
    ui->setupUi(this);
    ui->tableWidget->setDisabled(true);
}

MainWindow::~MainWindow()
{
    if(matA) delete matA;
    if(matB) delete matB;
    delete ui;
}


void MainWindow::on_pushButtonCriarMatA_clicked()
{
    try {
        int linhas = ui->lineEditLinhasMatA->text().toInt();
        int colunas = ui->lineEditColunasMatA->text().toInt();
        matA = new tp2::Matriz(linhas,colunas);
        for(int l=0; l < linhas ; l++){
            for(int c=0; c < colunas; c++){
                int elemento =  QInputDialog::getInt(this , "Leitura",
                                "Matriz A [ "+ QString::number(l) + ", "+
                                QString::number(c) + "] = ");
                matA->setElemento(elemento,l,c);
            }
        }
        ui->textEditSaidaMatA->setText(matA->getMatriz());

        QString saida;
        QTableWidgetItem *item1;

        if(matA->triangularSuperior())
            saida="Sim";
        else saida="Não";
        item1 = new QTableWidgetItem(saida);
        ui->tableWidget->setItem(0,0,item1);

        if(matA->triangularInferior())
            saida="Sim";
        else saida="Nao";
        item1 = new QTableWidgetItem(saida);
        ui->tableWidget->setItem(1,0,item1);

        if(matA->simetrica())
            saida="Sim";
        else saida="Não";
        item1 = new QTableWidgetItem(saida);
        ui->tableWidget->setItem(2,0,item1);

        if(matA->identidade())
            saida="Sim";
        else saida="Não";
        item1 = new QTableWidgetItem(saida);
        ui->tableWidget->setItem(3,0,item1);

        if(matB){
            if(*matA == matB)
                saida="Sim";
            else saida="Não";
            item1 = new QTableWidgetItem(saida);
            ui->tableWidget->setItem(4,0,item1);
            QTableWidgetItem *item2 = new QTableWidgetItem(saida);
            ui->tableWidget->setItem(4,1,item2);
        }

        if(matB){
            if(*matA != matB)
                saida ="Sim";
            else saida ="Não";
            item1 = new QTableWidgetItem(saida);
            ui->tableWidget->setItem(5,0,item1);
            QTableWidgetItem *item2 = new QTableWidgetItem(saida);
            ui->tableWidget->setItem(5,1,item2);
        }

        if(matA->ortogonal())
            saida="Sim";
        else saida="Não";
        item1 = new QTableWidgetItem(saida);
        ui->tableWidget->setItem(6,0,item1);

        if(matA->permutacao())
            saida="Sim";
        else saida="Não";
        item1 = new QTableWidgetItem(saida);
        ui->tableWidget->setItem(7,0,item1);

    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }    catch(std::bad_alloc&){
        QMessageBox::information(this,"ERRO","Matriz A nao Criada");
    }
}

void MainWindow::on_pushButtonCriarMatB_clicked()
{
    try {
        int linhas = ui->lineEditLinhasMatB->text().toInt();
        int colunas = ui->lineEditColunasMatB->text().toInt();
        matB = new tp2::Matriz(linhas,colunas);
        for(int l=0; l < linhas ; l++){
            for(int c=0; c < colunas; c++){
                int elemento =  QInputDialog::getInt(this , "Leitura",
                                "Matriz A [ "+ QString::number(l) + ", "+
                                QString::number(c) + "] = ");
                matB->setElemento(elemento,l,c);
            }
        }
        ui->textEditSaidaMatB->setText(matB->getMatriz());

        QString saida;
        QTableWidgetItem *item1;

        if(matB->triangularSuperior())
            saida="Sim";
        else saida="Não";
        item1 = new QTableWidgetItem(saida);
        ui->tableWidget->setItem(0,1,item1);

        if(matB->triangularInferior())
            saida ="sim";
        else saida ="Não";
        item1 = new QTableWidgetItem(saida);
        ui->tableWidget->setItem(1,1,item1);

        if(matB->simetrica())
             saida ="Sim";
        else saida="Não";
        item1 = new QTableWidgetItem(saida);
        ui->tableWidget->setItem(2,1,item1);

        if(matB->identidade())
            saida="Sim";
        else saida="Não";
        item1=new QTableWidgetItem(saida);
        ui->tableWidget->setItem(3,1,item1);

        if(matA){
            if(*matA == matB)
                saida ="Sim";
            else saida="Não";
            item1 = new QTableWidgetItem(saida);
            ui->tableWidget->setItem(4,0,item1);
            QTableWidgetItem *item2 = new QTableWidgetItem(saida);
            ui->tableWidget->setItem(4,1,item2);
        }

        if(matA){
            if(*matA != matB)
                saida="Sim";
            else saida="Não";
            item1 = new QTableWidgetItem(saida);
            ui->tableWidget->setItem(5,0,item1);
            QTableWidgetItem *item2 = new QTableWidgetItem(saida);
            ui->tableWidget->setItem(5,1,item2);
        }

        if(matA->ortogonal())
            saida="Sim";
        else saida="Não";
        item1 = new QTableWidgetItem(saida);
        ui->tableWidget->setItem(6,1,item1);

        if(matB->permutacao())
            saida="Sim";
        else saida="nÃO";
        item1 = new QTableWidgetItem(saida);
        ui->tableWidget->setItem(7,1,item1);

    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }catch(std::bad_alloc&){
        QMessageBox::information(this,"ERRO","Matriz B nao Criada");
    }

}

void MainWindow::on_pushButtonAdicionar_clicked()
{
    try {
        tp2::Matriz *matAdicao = *matA + matB ;
        ui->textEditSaida->setText(matAdicao->getMatriz());
        delete matAdicao;
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void MainWindow::on_pushButtonSubtrair_clicked()
{
    try {
        tp2::Matriz *matSubtracao = *matA - matB;
        ui->textEditSaida->setText(matSubtracao->getMatriz());
        delete matSubtracao;
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void MainWindow::on_pushButtonMultiplicar_clicked()
{
    try {
        if(!matA || !matB)
            throw QString("Precisa de duas matrizes para multiplicar");
        tp2::Matriz *matMult = *matA * matB;
        ui->textEditSaida->setText(matMult->getMatriz());
        delete matMult;
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void MainWindow::on_pushButtonTransposta_clicked()
{
    try {
        QString saida;
        if(matA){
        tp2::Matriz *matT = matA->transposta();
        saida +=matT->getMatriz()+"\n";
        delete matT;
       }
        if(matB){
            tp2::Matriz *matBT = matB->transposta();
            saida +=matBT->getMatriz()+"\n";
            delete matBT;
        }
        ui->textEditSaida->setText(saida);
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void MainWindow::on_pushButtonPotencia_clicked()
{
    try {
        if(!matA && !matB)
            throw QString("Nao foi enseriada nenhuma matriz");
        int ex=QInputDialog::getInt(this,"Expoente","Coloque um valor");
        QString saida;
        if(matA){
            tp2::Matriz *matAPot = matA->potencia(ex);
            saida +=matAPot->getMatriz()+"\n";
            delete matAPot;
        }
        if(matB){
            tp2::Matriz *matBPot = matB->potencia(ex);
            saida+=matBPot->getMatriz()+"\n";
            delete matBPot;
        }
        ui->textEditSaida->setText(saida);
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void MainWindow::on_pushButtonMultiplicacaoPorK_clicked()
{
    try {
        if(!matA && !matB)
            throw QString("Nao foi enserida nenhuma matriz");
        QString saida;
        int seguido =QInputDialog::getInt(this,"Constante","Insira um valor");
        if(matA){
            tp2::Matriz *matAMultK = matA->multiplicacaoPorK(seguido);
            saida+=matAMultK->getMatriz()+"\n";
            delete matAMultK;
        }
        if(matB){
            tp2::Matriz *matBMultK = matB->multiplicacaoPorK(seguido);
            saida+=matBMultK->getMatriz()+"\n";
            delete matBMultK;
        }
        ui->textEditSaida->setText(saida);
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}
