#include "MyString.h"
#include <iostream>
#include <cstring>
#include <utility>

MyString::MyString() : MyString("")
{}

MyString::MyString(size_t capacity) :
    MyString("", capacity)
{
}

MyString::MyString(const std::string_view str) :
    MyString(str, str.size())
{
}

MyString::MyString(const std::string_view str, size_t capacity) :
    mSize(str.size()),
    mCapacity(std::max(capacity, str.size())),
    mFront{std::make_unique<char[]>(mCapacity+1)}
{
    std::memcpy(mFront.get(), str.data(), mSize);
    mFront[mSize] = '\0';
}

MyString::MyString(const MyString& str) :
    MyString(str.c_str())
{
}

MyString::MyString(MyString&& str) noexcept :
    mFront{std::move(str.mFront)},
    mSize{std::exchange(str.mSize, 0)},
    mCapacity{std::exchange(str.mCapacity, 0)}
{
    str.mFront = std::make_unique<char[]>(1);
    str.mFront[0] = '\0';

}

MyString& MyString::operator= (MyString&& str) 
{
    mFront = std::move(str.mFront);
    str.mFront = std::make_unique<char[]>(1);
    str.mFront[0] = '\0';
    mSize = std::exchange(str.mSize, 0);
    mCapacity = std::exchange(str.mCapacity, 0);
    
    return *this;
}

const char& MyString::operator[] (size_t pos) const
{
    if (pos >= mSize) 
        throw std::out_of_range("Index out of range");
    return mFront[pos];
}

char& MyString::operator[] (size_t pos)
{
    if (pos >= mSize) 
        throw std::out_of_range("Index out of range");
    return mFront[pos];
}

MyString& MyString::operator= (const MyString& previous)
{
    if (this == &previous) 
        return *this;
    mFront = std::make_unique<char[]>(previous.capacity() + 1);
    std::memcpy(mFront.get(), previous.c_str(), previous.size() + 1);
    mCapacity = previous.capacity();
    mSize = previous.size();
    return *this;
} 

size_t MyString::size() const
{
    return mSize;
}

size_t MyString::capacity() const
{
    return mCapacity;
}

const char* MyString::c_str() const
{
    return mFront.get();
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
    return os << str.c_str();
}

MyString& MyString::push_back(char c)
{
    if (mSize == mCapacity) {
        reserve(mSize + 1);
    }
    mFront[mSize] = c;
    mFront[mSize + 1] = '\0';
    mSize++;
    return *this;
}

MyString& MyString::append(const std::string_view str)
{
    size_t incomingSize {str.size()};
    if (mSize + incomingSize > mCapacity) {
        reserve(mSize + incomingSize);
    }
    std::memcpy(mFront.get() + mSize, str.data(), incomingSize);
    mSize += incomingSize;
    mFront[mSize] = '\0';
    return *this;
}

MyString& MyString::append(const MyString& str)
{
    append(str.c_str());
    return *this;
}

MyString MyString::operator+(const MyString& str) const
{
    MyString result(mSize + str.size());
    result.append(*this);
    result.append(str);
    return result;
}

void MyString::reserve(size_t desiredCapacity) {
    if (desiredCapacity <= mCapacity)
        return;
    auto nxt {std::make_unique<char[]>(desiredCapacity + 1)}; 
    std::memcpy(nxt.get(), mFront.get(), mSize+1);
    mFront = std::move(nxt);
    mCapacity = desiredCapacity;
}
