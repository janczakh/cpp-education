#pragma once
#include <ostream>
#include <memory>

class MyString {
public:
    MyString();
    explicit MyString(size_t capacity);
    explicit MyString(const std::string_view str);
    explicit MyString(const std::string_view str, size_t capacity);
    MyString(const MyString& str);
    MyString& operator= (const MyString& previous);
    MyString(MyString&& str) noexcept;
    MyString& operator= (MyString&& str);
    const char& operator[] (size_t pos) const;
    char& operator[] (size_t pos);

    size_t size() const;
    size_t capacity() const;
    const char* c_str() const;
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);

    MyString& push_back(char c);
    MyString& append(const std::string_view str);
    MyString& append(const MyString& str);
    MyString operator+(const MyString& str) const;
    void reserve(size_t desiredCapacity);
    
private:

    size_t mSize;
    size_t mCapacity;
    std::unique_ptr<char[]> mFront;

};
