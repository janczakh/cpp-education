#include <iostream>
#include <memory>
#include "shared_ptr.h"

template <typename T>
void printSharedPtr(SharedPtr<T>& ptr) {
    if (ptr)
        std::cout << "SharedPtr<mResource: " << *ptr << ", Refcount: " << ptr.use_count() << ">\n"; 
    else
        std::cout << "SharedPtr<mResource: null, Refcount: " << ptr.use_count() << ">\n"; 
}

void runSharedPtrPresentation() {
    std::string* resource = new std::string("I'm a string!");
    std::cout << "Creating shared ptr:\n";
    auto ptr {SharedPtr(resource)};
    printSharedPtr(ptr);
    {
        std::cout << "\nCopy constructing second shared ptr\n";
        auto ptr2 {ptr};
        std::cout << "Ptr1 unmodified apart from control block:\n";
        printSharedPtr(ptr);
        std::cout << "Ptr2 points to same value:\n";
        printSharedPtr(ptr2);
        std::cout << "\nModifying ptr2 changes value ptr1 points to:\n";
        *ptr2 = "So am I!";
        printSharedPtr(ptr);
        printSharedPtr(ptr2);
        std::cout << "\nPtr2 out of scope, ptr1 still owns the resouce:\n";


    }
    printSharedPtr(ptr);
    std::cout << "\nTesting move semantics.\n";
    std::cout << "Copy constructing ptr to ptr2 to ensure at the end it didn't lose its reference\n";
    auto ptr2 {ptr};
    printSharedPtr(ptr2);
    std::cout << "\nMove constructing ptr to ptr3\n";
    auto ptr3 {std::move(ptr)};
    std::cout << "Ptr in valid undefined state:\n";
    printSharedPtr(ptr);
    std::cout << "Ptr3 owns the resource, resource count remains 2:\n";
    printSharedPtr(ptr3);

    std::cout << "\nMove assignment ptr3 to empty ptr4\n";
    SharedPtr<std::string> ptr4;
    ptr4 = std::move(ptr3);

    std::cout << "Ptr3 in valid undefined state:\n";
    printSharedPtr(ptr3);
    std::cout << "Ptr4 owns the resource, resource count remains 2:\n";
    printSharedPtr(ptr4);

    std::cout << "Ptr2 unaffected by the enitre process:\n";
    printSharedPtr(ptr2);

}

int main() {
    runSharedPtrPresentation();    
}
