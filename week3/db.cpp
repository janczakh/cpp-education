#include "db.h"

void Pool::acquireNewDbConnection()
{
    auto conn = std::make_shared<DbConnection>("conn_str");
    mConnections.push_back(conn);
}

std::shared_ptr<DbConnection> Pool::getObject()
{
    // Any ptr with use_count of 1 is not locked by another process
    for (auto& conn : mConnections) {
        if (conn.use_count() == 1) {
            return conn;
        }
    }
    acquireNewDbConnection();
    return mConnections.back();
}

std::vector<std::shared_ptr<DbConnection>>& Pool::getConnections() {
    return mConnections;
}
