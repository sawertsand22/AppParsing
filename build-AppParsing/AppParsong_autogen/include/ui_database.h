/********************************************************************************
** Form generated from reading UI file 'database.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASE_H
#define UI_DATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataBase
{
public:
    QLabel *label;
    QPushButton *pushButton_2;
    QSplitter *splitter;
    QComboBox *comboBox;
    QPushButton *pushButton;

    void setupUi(QWidget *DataBase)
    {
        if (DataBase->objectName().isEmpty())
            DataBase->setObjectName(QString::fromUtf8("DataBase"));
        DataBase->resize(800, 600);
        label = new QLabel(DataBase);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 181, 17));
        pushButton_2 = new QPushButton(DataBase);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 550, 89, 25));
        splitter = new QSplitter(DataBase);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(0, 70, 801, 25));
        splitter->setOrientation(Qt::Horizontal);
        comboBox = new QComboBox(splitter);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        splitter->addWidget(comboBox);
        pushButton = new QPushButton(splitter);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        splitter->addWidget(pushButton);

        retranslateUi(DataBase);

        QMetaObject::connectSlotsByName(DataBase);
    } // setupUi

    void retranslateUi(QWidget *DataBase)
    {
        DataBase->setWindowTitle(QCoreApplication::translate("DataBase", "Form", nullptr));
        label->setText(QCoreApplication::translate("DataBase", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214 : Admin", nullptr));
        pushButton_2->setText(QCoreApplication::translate("DataBase", "\320\276\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        pushButton->setText(QCoreApplication::translate("DataBase", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataBase: public Ui_DataBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASE_H
