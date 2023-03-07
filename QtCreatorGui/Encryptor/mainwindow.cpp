#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Encryptions.h"

encryption::ColumnMethod                objColumnMthod;
encryption::Vigenere                    objVigenere;
encryption::alphabets::possibleAlphabet currentAlphabet = encryption::alphabets::possibleAlphabet::russian;
bool isColumnMthod = true;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveDecryptedText()
{
    QFile file("/home/dumonten/Documents/GitHub/TI-4-term/QtCreatorGui/decryptedText.txt");

    if (!file.open(QIODevice::WriteOnly))
         QMessageBox::information(this, tr("Предупреждение"), tr("Ошибка: файл расшифрованного текста поврежден."));

    QTextStream stream(&file);
    stream << ui->editEncryption->toPlainText();
    file.close();
}

void MainWindow::saveCiphertext(QString method, QString key, QString alphabet, QString cipher)
{
    QFile file("/home/dumonten/Documents/GitHub/TI-4-term/QtCreatorGui/cipher.txt");

    if (!file.open(QIODevice::WriteOnly))
        QMessageBox::information(this, tr("Предупреждение"), tr("Ошибка: файл шифротекста поврежден."));

    QTextStream stream(&file);

    stream << method << "\n" << key << "\n" << alphabet << "\n" << cipher;

    file.close();
}

void MainWindow::on_btnColumn_clicked()
{
    /*clear*/
    ui->editEncryption->setPlainText("");
    /**/

    isColumnMthod = true;

    QString qStr = ui->editPlaintext->toPlainText();
    std::wstring basicString = qStr.toStdWString();
    qStr = ui->editKey->text();
    std::wstring key = qStr.toStdWString();

    objColumnMthod.setAlphabet(currentAlphabet);
    objColumnMthod.setKey(key);
    objColumnMthod.setPlaintext(basicString);

    try
    {
        std::wstring cipherText = objColumnMthod.encrypt();
        qStr = QString::fromStdWString(cipherText);

        //output
        ui->editDecryption->setPlainText(qStr);

        //save
        QString qMthd = "column", qKey = QString::fromStdWString(key), qAlph, qCipher;
        if (currentAlphabet == encryption::alphabets::possibleAlphabet::russian)
            qAlph = "russian";
        else if (currentAlphabet == encryption::alphabets::possibleAlphabet::english)
            qAlph = "english";
        qCipher = qStr;
        saveCiphertext(qMthd, qKey, qAlph, qCipher);
    }
    catch(Error& e)
    {
        QMessageBox::critical(this, tr("Ошибка"), tr(e.error()));
    }
}

void MainWindow::on_btnLanguage_clicked()
{
    /*clear*/
    ui->editDecryption->setPlainText("");
    ui->editEncryption->setPlainText("");
    /**/
    if (ui->btnLanguage->text() == "Русский")
    {
        currentAlphabet = encryption::alphabets::possibleAlphabet::english;
        ui->btnLanguage->setText("Английский");
    }
    else
    {
        currentAlphabet = encryption::alphabets::possibleAlphabet::russian;
        ui->btnLanguage->setText("Русский");
    }

}

void MainWindow::on_btnVigenere_clicked()
{
    /*clear*/
    ui->editEncryption->setPlainText("");
    /**/

    isColumnMthod = false;

    QString qStr = ui->editPlaintext->toPlainText();
    std::wstring basicString = qStr.toStdWString();
    qStr = ui->editKey->text();
    std::wstring key = qStr.toStdWString();

    objVigenere.setAlphabet(currentAlphabet);
    objVigenere.setKey(key);
    objVigenere.setPlaintext(basicString);

    try
    {
        std::wstring cipherText = objVigenere.encrypt();
        qStr = QString::fromStdWString(cipherText);

        //output
        ui->editDecryption->setPlainText(qStr);

        //save
        QString qMthd = "vigenere", qKey = QString::fromStdWString(key), qAlph, qCipher;
        if (currentAlphabet == encryption::alphabets::possibleAlphabet::russian)
            qAlph = "russian";
        else if (currentAlphabet == encryption::alphabets::possibleAlphabet::english)
            qAlph = "english";
        qCipher = qStr;
        saveCiphertext(qMthd, qKey, qAlph, qCipher);
    }
    catch(Error& e)
    {

        QMessageBox::critical(this, tr("Ошибка"), tr(e.error()));
    }
}

void MainWindow::on_btnDecrypt_clicked()
{
    QString qStr = ui->editDecryption->toPlainText();
    std::wstring cipherText = qStr.toStdWString();
    try
    {
        std::wstring plaintext = isColumnMthod ? objColumnMthod.decrypt(cipherText) : objVigenere.decrypt(cipherText);
        qStr = QString::fromStdWString(plaintext);
        ui->editEncryption->setPlainText(qStr);
        saveDecryptedText();
    }
    catch(Error& e)
    {
        QMessageBox::critical(this, tr("Ошибка"), tr(e.error()));
    }
}

void MainWindow::on_btnStoreData_clicked()
{
    QFile file("/home/dumonten/Documents/GitHub/TI-4-term/QtCreatorGui/plaintext.txt");
    if (!file.open(QIODevice::ReadOnly))
        QMessageBox::information(this, tr("Предупреждение"), tr("Ошибка: файл исходного текста поврежден."));

    QTextStream stream(&file);
    /*clear*/
    ui->editEncryption->setPlainText("");
    ui->editDecryption->setPlainText("");
    /**/
    ui->editPlaintext->setPlainText(stream.readAll());
    file.close();
}

void MainWindow::on_btnDecryptFromFile_clicked()
{
    QFile file("/home/dumonten/Documents/GitHub/TI-4-term/QtCreatorGui/cipher.txt");
    if (!file.open(QIODevice::ReadOnly))
        QMessageBox::information(this, tr("Предупреждение"), tr("Ошибка: файл исходного текста поврежден."));

    QTextStream stream(&file);

    QString method   = stream.readLine();
    QString key      = stream.readLine();
    QString alphabet = stream.readLine();
    QString cipher   = stream.readAll();

    if (alphabet == "russian")
    {
        currentAlphabet = encryption::alphabets::possibleAlphabet::russian;
        ui->btnLanguage->setText("Русский");
    } else if (alphabet == "english")
    {
        currentAlphabet = encryption::alphabets::possibleAlphabet::english;
        ui->btnLanguage->setText("Английский");
    }

    ui->editKey->setText(key);
    ui->editEncryption->setPlainText("");
    ui->editPlaintext->setPlainText(" ШИФРОТЕКСТ ИЗ ФАЙЛА! ");
    ui->editDecryption->setPlainText(cipher);

    std::wstring plaintext;

    if (method == "column")
    {
        objColumnMthod.setAlphabet(currentAlphabet);
        objColumnMthod.setKey(key.toStdWString());
        objColumnMthod.setPlaintext(cipher.toStdWString());
        try
        {
            plaintext = objColumnMthod.decrypt(cipher.toStdWString());
        }
        catch(Error& e)
        {
            QMessageBox::critical(this, tr("Ошибка"), tr("Шифротекст проврежден."));
        }

    }
    else if (method == "vigenere")
    {
        objVigenere.setAlphabet(currentAlphabet);
        objVigenere.setKey(key.toStdWString());
        objVigenere.setPlaintext(cipher.toStdWString());
        try
        {
            plaintext = objVigenere.decrypt(cipher.toStdWString());
        }
        catch(Error& e)
        {
            QMessageBox::critical(this, tr("Ошибка"), tr("Шифротекст проврежден."));
        }
    }

    QString qStr = QString::fromStdWString(plaintext);
    ui->editEncryption->setPlainText(qStr);
    saveDecryptedText();

    file.close();
}

