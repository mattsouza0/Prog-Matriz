#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<matriz.h>
#include<QString>
#include<QMessageBox>
#include <QMainWindow>
#include<QInputDialog>
#include<QWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonCriarMatA_clicked();

    void on_pushButtonCriarMatB_clicked();

    void on_pushButtonAdicionar_clicked();

    void on_pushButtonSubtrair_clicked();

    void on_pushButtonMultiplicar_clicked();

    void on_pushButtonTransposta_clicked();

    void on_pushButtonPotencia_clicked();

    void on_pushButtonMultiplicacaoPorK_clicked();

private:
    Ui::MainWindow *ui;
    tp2::Matriz *matA;
    tp2::Matriz *matB;
};
#endif // MAINWINDOW_H
