#include "MyString.h"
#include <iostream>

void printStringInfo(MyString& str) 
{
    std::cout << "MyString<" << str.size() << ", " << str.capacity() << ", " << str << ">\n";

}

int main() 
{
    std::cout << "Constructing\n";
    MyString s {"Opti"};
    std::cout << "Calling getters:\n";
    printStringInfo(s);
    std::cout << "Default + copy constructing\n";
    MyString s2;
    s2 = s;
    std::cout << "Old string, unchanged:\n";
    printStringInfo(s);
    std::cout << "New string, assignment constructed:\n";
    printStringInfo(s2);

    std::cout << "Reserve 7 in S:\n";
    s.reserve(7);
    printStringInfo(s);
    std::cout << "push_back S:\n";
    s.push_back('S');
    printStringInfo(s);

    std::cout << "append tring:\n";
    s.append("tring");
    printStringInfo(s);

    std::cout << "operator+ MyString(\"test\"):\n";
    MyString s3{"Test"};
    MyString s4 {s + s3};
    printStringInfo(s4);
    std::cout << "Checking that MyString(\"test\") and MyString(\"OptiString\") are unchanged:\n";
    printStringInfo(s);
    printStringInfo(s3);
    std::cout << "Creating string \"Finished\" with copy constructor and appending:\n";
    MyString s5{"Finished", 10};
    MyString s6{s5};
    s4.append(s6);
    printStringInfo(s4);

    std::cout << "\n\nUsing move ctr:\n";
    MyString s7{std::move(s4)};
    printStringInfo(s7);
    std::cout << "Verifying prev string is in undefined but valid state:\n";
    printStringInfo(s4);

    std::cout << "Using move assignment:\n";
    MyString s8;
    s8 = {std::move(s7)};
    printStringInfo(s8);
    std::cout << "Verifying prev string is in undefined but valid state:\n";
    printStringInfo(s7);



};


