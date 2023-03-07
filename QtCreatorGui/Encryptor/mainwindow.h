#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void saveDecryptedText();

    void saveCiphertext(QString method, QString key, QString alphabet, QString cipher);

private slots:
    void on_btnColumn_clicked();

    void on_btnLanguage_clicked();

    void on_btnVigenere_clicked();

    void on_btnDecrypt_clicked();

    void on_btnStoreData_clicked();

    void on_btnDecryptFromFile_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
