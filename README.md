"# QJsonTableModel" 
thanks for  poulh .
if you are using qJsonDocument, check his git : [https://github.com/poulh/qjsontablemodel](https://github.com/poulh/qjsontablemodel)
```c++
    QJsonTableModel::Header header;
    // map的初始化和编译器、c++版本、qt版本 相关，c++98可能不支持大括号初始化列表，qt5编译不需要小括号
    header.push_back( QJsonTableModel::Heading( { {"title","Title"},    {"index","title"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title","Season"},   {"index","season"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title","Episode"},  {"index","episode"} }) );
    header.push_back( QJsonTableModel::Heading( { {"title","Air Date"}, {"index","air_date"} }) );

    m_pEpisodeTableView = new QTableView;
    m_pEpisodes = new QJsonTableModel(header);
    m_pEpisodeTableView->setModel(m_pEpisodes);

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
```
