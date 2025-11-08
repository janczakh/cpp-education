#pragma once
struct ControlBlock {

int shared_refcount;
int weak_refcount; 

};

class SharedPtrInt {
public:
    SharedPtrInt();
    explicit SharedPtrInt(int* res);
    SharedPtrInt& operator= (const SharedPtrInt& other);
    SharedPtrInt(const SharedPtrInt& other);
    SharedPtrInt(SharedPtrInt&& other) noexcept;
    SharedPtrInt& operator= (SharedPtrInt&& other) noexcept;
    ~SharedPtrInt();

    // SharedPtrInt make_shared();
    explicit operator bool() const noexcept;
    int use_count() const noexcept;
    int& operator*() const noexcept;
    int* operator->() const noexcept;
    void release();
private:
    int* mResource;
    ControlBlock* mControlBlock;
};
