#include <iostream>
#include <memory>
#include "shared_ptr.h"
#include "db.h"

void printSharedPtrInt(SharedPtrInt& ptr) {
    if (ptr)
        std::cout << "SharedPtrInt<mResource: " << *ptr << ", Refcount: " << ptr.use_count() << ">\n"; 
    else
        std::cout << "SharedPtrInt<mResource: null, Refcount: " << ptr.use_count() << ">\n"; 
}

void printDbConnectionPool(Pool& pool) {
    std::cout << "DbConnectionPool<";
    for (const auto& conn : pool.getConnections()) {
        std::cout << "Conn<Locks:" << conn.use_count() << ">";
    }
    std::cout << ">\n";
}

void runSharedPtrIntPresentation() {
    int* resource = new int{9};
    std::cout << "Creating shared ptr:\n";
    auto ptr {SharedPtrInt(resource)};
    printSharedPtrInt(ptr);
    {
        std::cout << "\nCopy constructing second shared ptr\n";
        auto ptr2 {ptr};
        std::cout << "Ptr1 unmodified apart from control block:\n";
        printSharedPtrInt(ptr);
        std::cout << "Ptr2 points to same value:\n";
        printSharedPtrInt(ptr2);
        std::cout << "\nModifying ptr2 changes value ptr1 points to:\n";
        *ptr2 = 5;
        printSharedPtrInt(ptr);
        printSharedPtrInt(ptr2);
        std::cout << "\nPtr2 out of scope, ptr1 still owns the resouce:\n";


    }
    printSharedPtrInt(ptr);
    std::cout << "\nTesting move semantics.\n";
    std::cout << "Copy constructing ptr to ptr2 to ensure at the end it didn't lose its reference\n";
    auto ptr2 {ptr};
    printSharedPtrInt(ptr2);
    std::cout << "\nMove constructing ptr to ptr3\n";
    auto ptr3 {std::move(ptr)};
    std::cout << "Ptr in valid undefined state:\n";
    printSharedPtrInt(ptr);
    std::cout << "Ptr3 owns the resource, resource count remains 2:\n";
    printSharedPtrInt(ptr3);

    std::cout << "\nMove assignment ptr3 to empty ptr4\n";
    SharedPtrInt ptr4;
    ptr4 = std::move(ptr3);

    std::cout << "Ptr3 in valid undefined state:\n";
    printSharedPtrInt(ptr3);
    std::cout << "Ptr4 owns the resource, resource count remains 2:\n";
    printSharedPtrInt(ptr4);

    std::cout << "Ptr2 unaffected by the enitre process:\n";
    printSharedPtrInt(ptr2);

}

void runDbConnectionPoolPresentation() {
    std::cout << "Creating pool\n";
    Pool pool;
    printDbConnectionPool(pool);
    std::cout << "\nCreating two consumers\n";
    auto dbCons1 {pool.getObject()};
    {
        auto dbCons2 {pool.getObject()};
        printDbConnectionPool(pool);
        std::cout << "\nReleasing one of the consumers\n";
    }
    printDbConnectionPool(pool);
    std::cout << "\nCreating new consumer, expecting to relock the previous connection\n";
    auto dbCons2 {pool.getObject()};
    printDbConnectionPool(pool);
    std::cout << "\nDeleting pool, only now the dbconnections get released:\n";

}

int main() {
    runSharedPtrIntPresentation();
    std::cout << "\n---\n";
    runDbConnectionPoolPresentation();
 

    
}
