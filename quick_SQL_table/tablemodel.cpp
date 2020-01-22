#include "tablemodel.h"
#include <string>

#include "mysql_connection.h"

#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>


sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;




TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{


    try
    {
        driver = get_driver_instance();
        con=driver->connect("localhost","mike", "mikeworks");
        con->setAutoCommit(0);
        con->setSchema("newbase");
    }
    catch(sql::SQLException &ex)
    {
          printf("Exception occurred %d \n",ex.getErrorCode());
    }



    try
    {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT clients.name, clients.phone, clients.address FROM newbase.clients");

        table.append({"name","phone","address"});
        while(res->next())
        {
            std::string the_name = res->getString("name");
            std::string the_phone = res->getString("phone");
            std::string the_address = res->getString("address");

            //printf("the_name = %s \n", the_name.c_str());
            //cout << "name = " << the_name << "\n";

            table.append({the_name.c_str(),the_phone.c_str(),the_address.c_str()});

        }
    }
    catch(sql::SQLException &ex)
    {

    }



}

int TableModel::rowCount(const QModelIndex &) const
{
    return table.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return table.at(0).size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case TableDataRole:
    {
        return table.at(index.row()).at(index.column());
    }
    case HeadingRole:
    {
        if(index.row()==0){
            return true;
        }else{
            return false;
        }
    }
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[TableDataRole] = "tabledata";
    roles[HeadingRole] = "heading";
    return roles;
}
