/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layoutBttns;
    QLabel *label;
    QPushButton *btnLanguage;
    QSpacerItem *verticalSpacer;
    QPushButton *btnColumn;
    QPushButton *btnVigenere;
    QPushButton *btnStoreData;
    QPushButton *btnDecrypt;
    QPushButton *btnDecryptFromFile;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *layoutPlaintext;
    QLabel *labelPlaintext;
    QPlainTextEdit *editPlaintext;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *layoutED;
    QVBoxLayout *layoutD;
    QLabel *labelDecryption;
    QPlainTextEdit *editDecryption;
    QVBoxLayout *layoutE;
    QLabel *labelEncryption;
    QPlainTextEdit *editEncryption;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *layoutKey;
    QLabel *labelKey;
    QLineEdit *editKey;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1300, 650);
        MainWindow->setMinimumSize(QSize(1300, 650));
        MainWindow->setMaximumSize(QSize(1300, 650));
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 120, 371, 401));
        layoutBttns = new QVBoxLayout(verticalLayoutWidget);
        layoutBttns->setObjectName(QString::fromUtf8("layoutBttns"));
        layoutBttns->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        layoutBttns->addWidget(label);

        btnLanguage = new QPushButton(verticalLayoutWidget);
        btnLanguage->setObjectName(QString::fromUtf8("btnLanguage"));

        layoutBttns->addWidget(btnLanguage);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layoutBttns->addItem(verticalSpacer);

        btnColumn = new QPushButton(verticalLayoutWidget);
        btnColumn->setObjectName(QString::fromUtf8("btnColumn"));

        layoutBttns->addWidget(btnColumn);

        btnVigenere = new QPushButton(verticalLayoutWidget);
        btnVigenere->setObjectName(QString::fromUtf8("btnVigenere"));

        layoutBttns->addWidget(btnVigenere);

        btnStoreData = new QPushButton(verticalLayoutWidget);
        btnStoreData->setObjectName(QString::fromUtf8("btnStoreData"));

        layoutBttns->addWidget(btnStoreData);

        btnDecrypt = new QPushButton(verticalLayoutWidget);
        btnDecrypt->setObjectName(QString::fromUtf8("btnDecrypt"));

        layoutBttns->addWidget(btnDecrypt);

        btnDecryptFromFile = new QPushButton(verticalLayoutWidget);
        btnDecryptFromFile->setObjectName(QString::fromUtf8("btnDecryptFromFile"));

        layoutBttns->addWidget(btnDecryptFromFile);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(430, 20, 401, 581));
        layoutPlaintext = new QVBoxLayout(verticalLayoutWidget_2);
        layoutPlaintext->setObjectName(QString::fromUtf8("layoutPlaintext"));
        layoutPlaintext->setContentsMargins(0, 0, 0, 0);
        labelPlaintext = new QLabel(verticalLayoutWidget_2);
        labelPlaintext->setObjectName(QString::fromUtf8("labelPlaintext"));

        layoutPlaintext->addWidget(labelPlaintext);

        editPlaintext = new QPlainTextEdit(verticalLayoutWidget_2);
        editPlaintext->setObjectName(QString::fromUtf8("editPlaintext"));

        layoutPlaintext->addWidget(editPlaintext);

        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(860, 20, 411, 581));
        layoutED = new QVBoxLayout(verticalLayoutWidget_3);
        layoutED->setObjectName(QString::fromUtf8("layoutED"));
        layoutED->setContentsMargins(0, 0, 0, 0);
        layoutD = new QVBoxLayout();
        layoutD->setObjectName(QString::fromUtf8("layoutD"));
        labelDecryption = new QLabel(verticalLayoutWidget_3);
        labelDecryption->setObjectName(QString::fromUtf8("labelDecryption"));

        layoutD->addWidget(labelDecryption);

        editDecryption = new QPlainTextEdit(verticalLayoutWidget_3);
        editDecryption->setObjectName(QString::fromUtf8("editDecryption"));
        editDecryption->setReadOnly(true);

        layoutD->addWidget(editDecryption);


        layoutED->addLayout(layoutD);

        layoutE = new QVBoxLayout();
        layoutE->setObjectName(QString::fromUtf8("layoutE"));
        labelEncryption = new QLabel(verticalLayoutWidget_3);
        labelEncryption->setObjectName(QString::fromUtf8("labelEncryption"));

        layoutE->addWidget(labelEncryption);

        editEncryption = new QPlainTextEdit(verticalLayoutWidget_3);
        editEncryption->setObjectName(QString::fromUtf8("editEncryption"));
        editEncryption->setReadOnly(true);

        layoutE->addWidget(editEncryption);


        layoutED->addLayout(layoutE);

        verticalLayoutWidget_6 = new QWidget(centralwidget);
        verticalLayoutWidget_6->setObjectName(QString::fromUtf8("verticalLayoutWidget_6"));
        verticalLayoutWidget_6->setGeometry(QRect(40, 20, 371, 61));
        layoutKey = new QVBoxLayout(verticalLayoutWidget_6);
        layoutKey->setObjectName(QString::fromUtf8("layoutKey"));
        layoutKey->setContentsMargins(0, 0, 0, 0);
        labelKey = new QLabel(verticalLayoutWidget_6);
        labelKey->setObjectName(QString::fromUtf8("labelKey"));

        layoutKey->addWidget(labelKey);

        editKey = new QLineEdit(verticalLayoutWidget_6);
        editKey->setObjectName(QString::fromUtf8("editKey"));

        layoutKey->addWidget(editKey);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\250\320\270\321\204\321\200\320\260\321\202\320\276\321\200", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\241\320\274\320\265\320\275\320\270\321\202\321\214 \321\217\320\267\321\213\320\272:", nullptr));
        btnLanguage->setText(QCoreApplication::translate("MainWindow", "\320\240\321\203\321\201\321\201\320\272\320\270\320\271", nullptr));
        btnColumn->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\321\210\320\270\321\204\321\200\320\276\320\262\320\260\321\202\321\214 \321\201\321\202\320\276\320\273\320\261\321\206\320\276\320\262\321\213\320\274 \320\274\320\265\321\202\320\276\320\264\320\276\320\274", nullptr));
        btnVigenere->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\321\210\320\270\321\204\321\200\320\276\320\262\320\260\321\202\321\214 \320\274\320\265\321\202\320\276\320\264\320\276\320\274 \320\222\320\270\320\266\320\265\320\275\320\265\321\200\320\260 (\320\277\321\200\320\276\320\263\321\200. \320\272\320\273\321\216\321\207)", nullptr));
        btnStoreData->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\321\201\321\205\320\276\320\264\320\275\321\213\320\271 \321\202\320\265\320\272\321\201\321\202 \320\270\320\267 \321\204\320\260\320\271\320\273\320\260", nullptr));
        btnDecrypt->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\210\320\270\321\204\321\200\320\276\320\262\320\260\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\320\265\320\265", nullptr));
        btnDecryptFromFile->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\210\320\270\321\204\321\200\320\276\320\262\320\260\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265 \320\270\320\267 \321\204\320\260\320\271\320\273\320\260", nullptr));
        labelPlaintext->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\271 \321\202\320\265\320\272\321\201\321\202:", nullptr));
        labelDecryption->setText(QCoreApplication::translate("MainWindow", "\320\250\320\270\321\204\321\200\320\276\321\202\320\265\320\272\321\201\321\202:", nullptr));
        labelEncryption->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\210\320\270\321\204\321\200\320\276\320\262\320\260\320\275\320\275\321\213\320\271 \321\202\320\265\320\272\321\201\321\202:", nullptr));
        labelKey->setText(QCoreApplication::translate("MainWindow", "\320\232\320\273\321\216\321\207:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
