#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addWidget(m_pEpisodeTableView);
    QWidget *centerWindow = new QWidget(this);
    this->setCentralWidget(centerWindow);
    centerWindow->setLayout(vbox);
}

MainWindow::~MainWindow()
{
    delete m_pEpisodeTableView;
    delete m_pEpisodes;
    delete ui;
}

void MainWindow::init()
{
    QJsonTableModel::Header header;
    // map的初始化和编译器、c++版本、qt版本 相关，c++98可能不支持大括号初始化列表，qt5编译不需要小括号
    header.push_back( QJsonTableModel::Heading( { {"title","Title"},    {"index","title"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title","Season"},   {"index","season"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title","Episode"},  {"index","episode"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title","Air Date"}, {"index","air_date"} }) );

    m_pEpisodeTableView = new QTableView;
    m_pEpisodes = new QJsonTableModel(header);
    m_pEpisodeTableView->setModel(m_pEpisodes);

    //QString lineStr = readJson("qJson.txt"); // 从文件读取json
    QString lineStr = "[{\"series\":\"Black Sails\",\"season\":357001177406901,\"episode\":1,\"title\":\"I.\",\"air_date\":\"2014-01-25\"},{\"series\":\"Black Sails\",\"season\":1,\"episode\":2,\"title\":\"II.\",\"air_date\":\"2014-02-01\"}]";

    Json::Reader read;
    Json::Value jsonvalue;

    std::string strMeterData = lineStr.toStdString();

    /// Json格式字符串解析
    if(!read.parse(strMeterData, jsonvalue))
    {
        qDebug() << "jSon failed!";
    }

    m_pEpisodes->setJson(jsonvalue);
}

QString MainWindow::readJson(QString sPath)
{
    QFile f(sPath);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << f.errorString() ;
        return QString();
    }

    QTextStream txtInput(&f);
    QString lineStr;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
    }
    f.close();
    return lineStr;
}
