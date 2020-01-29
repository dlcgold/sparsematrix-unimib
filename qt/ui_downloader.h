/********************************************************************************
** Form generated from reading UI file 'downloader.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADER_H
#define UI_DOWNLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_downloader
{
public:
    QLineEdit *urlBox;
    QPushButton *analyzeButton;
    QLabel *wordLabel;
    QTextBrowser *textLabel;
    QLabel *charLabel;
    QLabel *noSpaceLabel;
    QLabel *phraseLabel;
    QLabel *paraLabel;

    void setupUi(QWidget *downloader)
    {
        if (downloader->objectName().isEmpty())
            downloader->setObjectName(QStringLiteral("downloader"));
        downloader->resize(801, 315);
        urlBox = new QLineEdit(downloader);
        urlBox->setObjectName(QStringLiteral("urlBox"));
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
        analyzeButton = new QPushButton(downloader);
        analyzeButton->setObjectName(QStringLiteral("analyzeButton"));
        analyzeButton->setGeometry(QRect(180, 10, 80, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(analyzeButton->sizePolicy().hasHeightForWidth());
        analyzeButton->setSizePolicy(sizePolicy1);
        analyzeButton->setAutoDefault(true);
        wordLabel = new QLabel(downloader);
        wordLabel->setObjectName(QStringLiteral("wordLabel"));
        wordLabel->setGeometry(QRect(550, 40, 181, 21));
        wordLabel->setFrameShape(QFrame::NoFrame);
        wordLabel->setFrameShadow(QFrame::Raised);
        wordLabel->setLineWidth(0);
        textLabel = new QTextBrowser(downloader);
        textLabel->setObjectName(QStringLiteral("textLabel"));
        textLabel->setGeometry(QRect(10, 40, 501, 271));
        charLabel = new QLabel(downloader);
        charLabel->setObjectName(QStringLiteral("charLabel"));
        charLabel->setGeometry(QRect(550, 70, 181, 21));
        noSpaceLabel = new QLabel(downloader);
        noSpaceLabel->setObjectName(QStringLiteral("noSpaceLabel"));
        noSpaceLabel->setGeometry(QRect(550, 100, 181, 21));
        phraseLabel = new QLabel(downloader);
        phraseLabel->setObjectName(QStringLiteral("phraseLabel"));
        phraseLabel->setGeometry(QRect(550, 130, 181, 21));
        paraLabel = new QLabel(downloader);
        paraLabel->setObjectName(QStringLiteral("paraLabel"));
        paraLabel->setGeometry(QRect(550, 160, 181, 21));

        retranslateUi(downloader);

        analyzeButton->setDefault(true);


        QMetaObject::connectSlotsByName(downloader);
    } // setupUi

    void retranslateUi(QWidget *downloader)
    {
        downloader->setWindowTitle(QApplication::translate("downloader", "ProgettoQt", Q_NULLPTR));
        urlBox->setText(QString());
        urlBox->setPlaceholderText(QApplication::translate("downloader", "url", Q_NULLPTR));
        analyzeButton->setText(QApplication::translate("downloader", "Analizza", Q_NULLPTR));
        wordLabel->setText(QString());
        charLabel->setText(QString());
        noSpaceLabel->setText(QString());
        phraseLabel->setText(QString());
        paraLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class downloader: public Ui_downloader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADER_H
