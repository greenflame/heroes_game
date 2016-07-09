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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QAction *actionPlay_fast_10_games;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_5;
    QTextEdit *textEdit_log;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_programm_1;
    QCheckBox *checkBox_mono_1;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_programm_2;
    QCheckBox *checkBox_mono_2;
    QLabel *label_6;
    QLineEdit *lineEdit_defPath;
    QLabel *label_7;
    QLineEdit *lineEdit_monoPath;
    QLabel *label_2;
    QTextEdit *textEdit_info;
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
        actionPlay_fast_10_games = new QAction(MainWindow);
        actionPlay_fast_10_games->setObjectName(QStringLiteral("actionPlay_fast_10_games"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(label);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        textEdit_log = new QTextEdit(centralWidget);
        textEdit_log->setObjectName(QStringLiteral("textEdit_log"));
        textEdit_log->setMinimumSize(QSize(0, 200));

        verticalLayout->addWidget(textEdit_log);

        verticalLayout->setStretch(0, 8);
        verticalLayout->setStretch(2, 2);

        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit_programm_1 = new QLineEdit(centralWidget);
        lineEdit_programm_1->setObjectName(QStringLiteral("lineEdit_programm_1"));

        horizontalLayout->addWidget(lineEdit_programm_1);

        checkBox_mono_1 = new QCheckBox(centralWidget);
        checkBox_mono_1->setObjectName(QStringLiteral("checkBox_mono_1"));

        horizontalLayout->addWidget(checkBox_mono_1);


        verticalLayout_2->addLayout(horizontalLayout);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_2->addWidget(label_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit_programm_2 = new QLineEdit(centralWidget);
        lineEdit_programm_2->setObjectName(QStringLiteral("lineEdit_programm_2"));

        horizontalLayout_2->addWidget(lineEdit_programm_2);

        checkBox_mono_2 = new QCheckBox(centralWidget);
        checkBox_mono_2->setObjectName(QStringLiteral("checkBox_mono_2"));
        checkBox_mono_2->setChecked(true);
        checkBox_mono_2->setTristate(false);

        horizontalLayout_2->addWidget(checkBox_mono_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_2->addWidget(label_6);

        lineEdit_defPath = new QLineEdit(centralWidget);
        lineEdit_defPath->setObjectName(QStringLiteral("lineEdit_defPath"));

        verticalLayout_2->addWidget(lineEdit_defPath);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_2->addWidget(label_7);

        lineEdit_monoPath = new QLineEdit(centralWidget);
        lineEdit_monoPath->setObjectName(QStringLiteral("lineEdit_monoPath"));

        verticalLayout_2->addWidget(lineEdit_monoPath);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        textEdit_info = new QTextEdit(centralWidget);
        textEdit_info->setObjectName(QStringLiteral("textEdit_info"));
        textEdit_info->setMinimumSize(QSize(250, 0));
        textEdit_info->setMaximumSize(QSize(1000000, 16777215));
        textEdit_info->setContextMenuPolicy(Qt::PreventContextMenu);
        textEdit_info->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_2->addWidget(textEdit_info);


        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_3->setStretch(0, 7);
        horizontalLayout_3->setStretch(1, 3);
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
        menuDraw_test->addAction(actionPlay_fast_10_games);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionStart->setText(QApplication::translate("MainWindow", "Start", 0));
        actionLoad_map->setText(QApplication::translate("MainWindow", "Load map", 0));
        actionStop->setText(QApplication::translate("MainWindow", "Stop", 0));
        actionPlay_fast_10_games->setText(QApplication::translate("MainWindow", "Play fast 10 games", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_5->setText(QApplication::translate("MainWindow", "Log:", 0));
        label_3->setText(QApplication::translate("MainWindow", "First programm(green):", 0));
        lineEdit_programm_1->setText(QApplication::translate("MainWindow", "alex", 0));
        checkBox_mono_1->setText(QApplication::translate("MainWindow", "Mono", 0));
        label_4->setText(QApplication::translate("MainWindow", "Second programm(red):", 0));
        lineEdit_programm_2->setText(QApplication::translate("MainWindow", "anton", 0));
        checkBox_mono_2->setText(QApplication::translate("MainWindow", "Mono", 0));
        label_6->setText(QApplication::translate("MainWindow", "Default path:", 0));
        lineEdit_defPath->setText(QApplication::translate("MainWindow", "/Users/Alexander/Desktop/heroes_game/data_folder/", 0));
        label_7->setText(QApplication::translate("MainWindow", "Mono path:", 0));
        lineEdit_monoPath->setText(QApplication::translate("MainWindow", "/usr/local/Cellar/mono/4.2.3.4/bin/mono", 0));
        label_2->setText(QApplication::translate("MainWindow", "Troops info:", 0));
        menuDraw_test->setTitle(QApplication::translate("MainWindow", "Game", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
