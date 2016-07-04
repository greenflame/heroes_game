/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStart;
    QAction *actionLoad_map;
    QAction *actionStop;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextEdit *textEdit_info;
    QTextEdit *textEdit_log;
    QMenuBar *menuBar;
    QMenu *menuDraw_test;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(767, 538);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        actionLoad_map = new QAction(MainWindow);
        actionLoad_map->setObjectName(QStringLiteral("actionLoad_map"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(label);

        textEdit_info = new QTextEdit(centralWidget);
        textEdit_info->setObjectName(QStringLiteral("textEdit_info"));
        textEdit_info->setMinimumSize(QSize(0, 150));

        verticalLayout->addWidget(textEdit_info);

        verticalLayout->setStretch(0, 8);
        verticalLayout->setStretch(1, 2);

        horizontalLayout->addLayout(verticalLayout);

        textEdit_log = new QTextEdit(centralWidget);
        textEdit_log->setObjectName(QStringLiteral("textEdit_log"));
        textEdit_log->setMinimumSize(QSize(250, 0));
        textEdit_log->setMaximumSize(QSize(1000000, 16777215));

        horizontalLayout->addWidget(textEdit_log);

        horizontalLayout->setStretch(0, 7);
        horizontalLayout->setStretch(1, 3);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 767, 22));
        menuBar->setNativeMenuBar(false);
        menuDraw_test = new QMenu(menuBar);
        menuDraw_test->setObjectName(QStringLiteral("menuDraw_test"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuDraw_test->menuAction());
        menuDraw_test->addAction(actionStart);
        menuDraw_test->addAction(actionStop);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionStart->setText(QApplication::translate("MainWindow", "Start", 0));
        actionLoad_map->setText(QApplication::translate("MainWindow", "Load map", 0));
        actionStop->setText(QApplication::translate("MainWindow", "Stop", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        menuDraw_test->setTitle(QApplication::translate("MainWindow", "Game", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
