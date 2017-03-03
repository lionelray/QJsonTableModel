#include "QJsonTableModel.h"

QJsonTableModel::QJsonTableModel(const QJsonTableModel::Header& header, QObject * parent)
    : QAbstractTableModel(parent)
    , m_header(header)
{

}

bool QJsonTableModel::setJson(Document &array)
{
    beginResetModel();
    m_json.Swap(array);
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
        return QString::fromStdString(m_header[section]["title"]);
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
    if (!m_json.IsArray())
    {
        return 0;
    }
    return m_json.Size();
}

int QJsonTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_header.size();
}

const Value &QJsonTableModel::getJsonObject(const QModelIndex &index) const
{
    return m_json[index.row()];
}

QVariant QJsonTableModel::data(const QModelIndex &index, int role ) const
{
    switch(role)
    {
    case Qt::DisplayRole:
    {
        const Value &obj = getJsonObject(index);
        if(obj.IsObject())
        {
            const Value &v = obj[m_header[index.column()]["index"].c_str()];

            if(v.IsString())
            {
                return QString::fromLocal8Bit(v.GetString());
            }
            else if(v.IsDouble())
            {
                return v.GetDouble();
            }
            else if(v.IsInt())
            {
                return qint64(v.GetInt());
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
