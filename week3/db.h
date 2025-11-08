#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class DbConnection {
public: 
    explicit DbConnection(std::string_view str) : connection_string(str) {}
    ~DbConnection() {
        std::cout << "DbConnection: Deleting dbconnection\n";
    }
private:
    std::string connection_string;
    //...
};

class Pool {
public:
    Pool() = default;
    ~Pool() = default;
    std::shared_ptr<DbConnection> getObject();
    std::vector<std::shared_ptr<DbConnection>>& getConnections();

private:
    void acquireNewDbConnection();
    std::vector<std::shared_ptr<DbConnection>> mConnections;
};
