#include "QJsonTableModel.h"

QJsonTableModel::QJsonTableModel(const QJsonTableModel::Header& header, QObject * parent)
    : QAbstractTableModel(parent)
    , m_header(header)
{

}

bool QJsonTableModel::setJson(const Json::Value &array)
{
    beginResetModel();
    m_json = array;
    endResetModel();
    return true;
}

QVariant QJsonTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }

    switch(orientation)
    {
    case Qt::Horizontal:
        return m_header[section]["title"];
    case Qt::Vertical:
        //return section + 1;
        return QVariant();
    default:
        return QVariant();
    }

}

int QJsonTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_json.size();
}

int QJsonTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_header.size();
}


Json::Value QJsonTableModel::getJsonObject(const QModelIndex &index) const
{
    const Json::Value& value = m_json[index.row()];
    return value;
}

QVariant QJsonTableModel::data(const QModelIndex &index, int role ) const
{
    switch(role)
    {
    case Qt::DisplayRole:
    {
        Json::Value obj = getJsonObject(index);
        const std::string& key = m_header[index.column()]["index"].toStdString();
        if( !Json::Value(obj[key]).isNull())
        {
            Json::Value  v = obj[key];

            if(v.isString())
            {
                return QString::fromStdString(v.asString());
            }
            else if(v.isDouble())
            {
                return QString::number(v.asDouble(), 'g', 32); // 具体显示格式和精度视情况而定
            }
            else
            {
                return QVariant();
            }
        }
        else
        {
            return QVariant();
        }
    }
    case Qt::ToolTipRole:
        return QVariant();
    default:
        return QVariant();
    }
}
