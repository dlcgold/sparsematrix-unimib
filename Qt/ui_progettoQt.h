/********************************************************************************
** Form generated from reading UI file 'progettoQt.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGETTOQT_H
#define UI_PROGETTOQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_progettoQt
{
public:
    QLineEdit *urlBox;
    QPushButton *analyzeButton;
    QLabel *wordLabel;
    QTextBrowser *textBrowser;
    QLabel *charLabel;
    QLabel *noSpaceLabel;
    QLabel *phraseLabel;
    QLabel *paraLabel;

    void setupUi(QWidget *progettoQt)
    {
        if (progettoQt->objectName().isEmpty())
            progettoQt->setObjectName(QString::fromUtf8("progettoQt"));
        progettoQt->resize(801, 315);
        urlBox = new QLineEdit(progettoQt);
        urlBox->setObjectName(QString::fromUtf8("urlBox"));
        urlBox->setEnabled(true);
        urlBox->setGeometry(QRect(9, 9, 161, 23));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(255);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(urlBox->sizePolicy().hasHeightForWidth());
        urlBox->setSizePolicy(sizePolicy);
        urlBox->setSizeIncrement(QSize(15, 0));
        urlBox->setFrame(false);
        urlBox->setReadOnly(false);
        analyzeButton = new QPushButton(progettoQt);
        analyzeButton->setObjectName(QString::fromUtf8("analyzeButton"));
        analyzeButton->setGeometry(QRect(180, 10, 80, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(analyzeButton->sizePolicy().hasHeightForWidth());
        analyzeButton->setSizePolicy(sizePolicy1);
        analyzeButton->setAutoDefault(true);
        wordLabel = new QLabel(progettoQt);
        wordLabel->setObjectName(QString::fromUtf8("wordLabel"));
        wordLabel->setGeometry(QRect(550, 40, 181, 21));
        wordLabel->setFrameShape(QFrame::NoFrame);
        wordLabel->setFrameShadow(QFrame::Raised);
        wordLabel->setLineWidth(0);
        textBrowser = new QTextBrowser(progettoQt);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 40, 501, 271));
        charLabel = new QLabel(progettoQt);
        charLabel->setObjectName(QString::fromUtf8("charLabel"));
        charLabel->setGeometry(QRect(550, 70, 181, 21));
        noSpaceLabel = new QLabel(progettoQt);
        noSpaceLabel->setObjectName(QString::fromUtf8("noSpaceLabel"));
        noSpaceLabel->setGeometry(QRect(550, 100, 181, 21));
        phraseLabel = new QLabel(progettoQt);
        phraseLabel->setObjectName(QString::fromUtf8("phraseLabel"));
        phraseLabel->setGeometry(QRect(550, 130, 181, 21));
        paraLabel = new QLabel(progettoQt);
        paraLabel->setObjectName(QString::fromUtf8("paraLabel"));
        paraLabel->setGeometry(QRect(550, 160, 181, 21));

        retranslateUi(progettoQt);

        analyzeButton->setDefault(true);


        QMetaObject::connectSlotsByName(progettoQt);
    } // setupUi

    void retranslateUi(QWidget *progettoQt)
    {
        progettoQt->setWindowTitle(QCoreApplication::translate("progettoQt", "ProgettoQt", nullptr));
        urlBox->setText(QString());
        urlBox->setPlaceholderText(QCoreApplication::translate("progettoQt", "url", nullptr));
        analyzeButton->setText(QCoreApplication::translate("progettoQt", "Analizza", nullptr));
        wordLabel->setText(QString());
        charLabel->setText(QString());
        noSpaceLabel->setText(QString());
        phraseLabel->setText(QString());
        paraLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class progettoQt: public Ui_progettoQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGETTOQT_H
