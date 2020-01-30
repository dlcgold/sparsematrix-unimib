#include "progettoQt.h"
#include "ui_progettoQt.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <iostream>




int countWords(std::string sentence) {
    int numberOfWords = 0;
    size_t i;

    if (isalpha(sentence[0])) {
        numberOfWords++;
    }

    for (i = 1; i < sentence.length(); i++) {
        if ((isalpha(sentence[i])) && (!isalpha(sentence[i-1]))) {
            numberOfWords++;
        }
    }

    return numberOfWords;
}


progettoQt::progettoQt(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::progettoQt) {
    //ui->setupUi(parent->resize(30, 40));
    //ui->setupUi(this);

    ui->setupUi(this);
    this->resize(270, 40);
    ui->urlBox->setPlaceholderText("insert url");


    ui->textLabel->setText("");
    //ui->info->setWordWrap(true);
    ui->wordLabel->setWordWrap(true);
    ui->charLabel->setWordWrap(true);
    ui->noSpaceLabel->setWordWrap(true);
    ui->phraseLabel->setWordWrap(true);
    ui->analyzeButton->setDefault(true);
    ui->analyzeButton->setAutoDefault(true);
    ui->analyzeButton->setEnabled(false);
    ui->urlBox->returnPressed();



    connect(ui->urlBox, SIGNAL(textChanged(QString)),
            this, SLOT(enableAnalyzeButton()));

}

progettoQt::~progettoQt() {
    delete ui;
}

void progettoQt::enableAnalyzeButton() {
    ui->analyzeButton->setEnabled(!(ui->urlBox->text()).isEmpty());
}

void progettoQt::on_analyzeButton_clicked() {
    manager = new QNetworkAccessManager(this);

    // get url
    url = (ui->urlBox->text());

    // used for progressDialog


    ui->analyzeButton->setEnabled(false);

    //this->move(this->pos().x()-200, this->pos().y()-100);

    //

    startRequest(url);
}

void progettoQt::startRequest(QUrl url) {
    // get() method posts a request
    // to obtain the contents of the target request
    // and returns a new QNetworkReply object
    // opened for reading which emits
    // the readyRead() signal whenever new data arrives.
    reply = manager->get(QNetworkRequest(url));


    // Whenever more data is received from the network,
    // this readyRead() signal is emitted
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));

    // This signal is emitted when the reply has finished processing.
    // After this signal is emitted,
    // there will be no more updates to the reply's data or metadata.
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpDownloadFinished()));


}
void progettoQt::httpReadyRead() {
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply

    text += reply->readAll();

}

void progettoQt::httpDownloadFinished() {

    if(reply->error()){
        QMessageBox replyError;

        replyError.setText("<p align='center'>url errato</p");
        ui->urlBox->setText("");

        replyError.exec();
        replyError.deleteLater();


    }else{

        this->resize(800, 320);
        this->setGeometry(QStyle::alignedRect(
                              Qt::LeftToRight,
                              Qt::AlignCenter,
                              this->size(),
                              qApp->desktop()->availableGeometry()
                              )
                          );
        ui->urlBox->resize(ui->textLabel->size().width() -
                           ui->analyzeButton->size().width() - 19,
                           ui->urlBox->size().height());
        ui->analyzeButton->move(ui->urlBox->size().width() +19,
                                ui->analyzeButton->pos().y());
        // download finished normally
        std::string textstr = text.toStdString();

        //qDebug() << "lunghezza: " << text.size();
        ui->textLabel->setText(text);
        int countPhrase = 0;
        int countChars = 0;
        int countSpace = 0;
        int countPara = 0;
        //int countNoChar = 0;

        for(auto i: textstr){
            if(i == '.' || i == '?' || i == '!' || i == ';')
                countPhrase++;
            if(i == ' ')
                countSpace++;
            if(i == '\n' || i == '\t')
                countPara++;
            countChars++;
        }



        QString infoPhrase =
                "<font color=\"green\"><b>Frasi: </b><font color=\"black\">"
                + QString::fromStdString(std::to_string(countPhrase))+
                QString::fromStdString("\n");
        //ui->infoLabel->setText(QString::fromStdString(info));
        ui->phraseLabel->setText(infoPhrase);

        QString infoWord =
                "<font color=\"green\"><b>Parole: </b><font color=\"black\">"
                + QString::fromStdString(std::to_string(countWords(textstr)))+
                QString::fromStdString("\n");
        ui->wordLabel->setText(infoWord);

        QString infoChar =
                "<font color=\"green\"><b>Caratteri: </b><font color=\"black\">"
                + QString::fromStdString(std::to_string(countChars))+
                QString::fromStdString("\n");
        //ui->infoLabel->setText(QString::fromStdString(info));
        ui->charLabel->setText(infoChar);

        QString infoNoSpace =
                "<font color=\"green\"><b>Caratteri senza spazi: </b><font color=\"black\">"
                + QString::fromStdString(std::to_string(countChars - countSpace))+
                QString::fromStdString("\n");
        ui->noSpaceLabel->setText(infoNoSpace);

        QString infoPara =
                "<font color=\"green\"><b>Paragrafi: </b><font color=\"black\">"
                + QString::fromStdString(std::to_string(countPara))+
                QString::fromStdString("\n");
        ui->paraLabel->setText(infoPara);

        reply->deleteLater();
        manager->deleteLater();
        infoPhrase.clear();
        infoWord.clear();
        infoChar.clear();
        infoNoSpace.clear();
        infoPara.clear();
        reply = 0;
        manager = 0;

        text = "";
        ui->analyzeButton->setEnabled(false);

        ui->urlBox->setPlaceholderText("insert url");
        //this->move(this->pos().x()+200, this->pos().y()+100);
    }
}