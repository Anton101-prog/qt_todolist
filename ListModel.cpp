#include "ListModel.h"
#include "DataBase.h"

ListModel::ListModel(QObject * parent) :
    QSqlQueryModel(parent) {
    this->updateModel();
}

QVariant ListModel::data(const QModelIndex & index, int role) const {
    int columnId = role - Qt::UserRole -1;

    QModelIndex modelIndex = this->index(index.row(), columnId);

    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> ListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[InfoRole] = "info";
    return roles;
}

void ListModel::updateModel() {
    this->setQuery("SELECT id, " TABLE_INFO " FROM " TABLE);
}

int ListModel::getId(int row){
    return this->data(this->index(row, 0), IdRole).toInt();
}

QString ListModel::getStr(int row){
    return this->data(this->index(row, 1), IdRole).toString();
}
