#include "downloader.h"
#include "ui_downloader.h"
#include <iostream>
int countWords(std::string sentence){
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


downloader::downloader(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::downloader)
{
    ui->setupUi(this);
    ui->urlBox->setText("http://qt.com");
    ui->textLabel->setWordWrap(true);
    ui->infoLabel->setWordWrap(true);
    ui->analyzeButton->setDefault(true);


    /*ui->quitButton->setAutoDefault(false);*/

    connect(ui->urlBox, SIGNAL(textChanged(QString)),
                    this, SLOT(enableAnalyzeButton()));
}

downloader::~downloader()
{
    delete ui;
}

void downloader::on_analyzeButton_clicked()
{
    manager = new QNetworkAccessManager(this);

    // get url
    url = (ui->urlBox->text());

    // used for progressDialog

    // download button disabled after requesting download
    ui->analyzeButton->setEnabled(false);

    startRequest(url);
}
void downloader::startRequest(QUrl url)
{
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
void downloader::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply

    text = QString::fromStdString(reply->readAll().toStdString());
    std::string textstr = text.toStdString();

    qDebug() << "lunghezza: " << text.size();
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

    //std::cout << std::to_string(countChars);
    std::string info = "frasi: " + std::to_string(countPhrase) + "\n"
            + "caratteri: " + std::to_string(countChars) + "\n"
            + "paragrafi: " + std::to_string(countPara) + "\n"
            + "parole: " + std::to_string(countWords(textstr)) + "\n"
            + "caratteri senza spazi: " + std::to_string(countChars -countSpace);
    //std::cout << info;
    ui->infoLabel->setText(QString::fromStdString(info));
}
