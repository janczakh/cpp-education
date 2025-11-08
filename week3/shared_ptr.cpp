#include "shared_ptr.h"
#include <iostream>
#include <utility>

SharedPtrInt::SharedPtrInt() :
    mResource(nullptr),
    mControlBlock(new ControlBlock{1, 0})
    {}

SharedPtrInt::SharedPtrInt(int* res) :
    mResource(res),
    mControlBlock(new ControlBlock{1, 0})
    {}

SharedPtrInt& SharedPtrInt::operator= (const SharedPtrInt& other)
    {
    mResource = other.mResource;
    mControlBlock = other.mControlBlock;
    mControlBlock->shared_refcount++;
    return *this;
    }

SharedPtrInt::SharedPtrInt(const SharedPtrInt& other) :
    SharedPtrInt()
    {
        *this = other;
    }

SharedPtrInt::~SharedPtrInt() {
    release();

}

SharedPtrInt::SharedPtrInt(SharedPtrInt&& other) noexcept :
    mResource(std::exchange(other.mResource, nullptr)),
    mControlBlock(std::exchange(other.mControlBlock, new ControlBlock{1, 0}))
    {}

SharedPtrInt& SharedPtrInt::operator=(SharedPtrInt&& other) noexcept
    {
        if (this == &other) return *this;
        release();
        mControlBlock = std::exchange(other.mControlBlock, new ControlBlock{1, 0}),
        mResource = std::exchange(other.mResource, nullptr);
        
        return *this;
    }

void SharedPtrInt::release() {
    mControlBlock->shared_refcount--;
    if (mControlBlock->shared_refcount == 0) {
        delete mResource;
        std::cout << "SharedPtrInt: Last reference removed, resource deleted\n";
        return;
    }
    std::cout << "SharedPtrInt Non-last reference removed, resource not deleted\n";
}

int SharedPtrInt::use_count() const noexcept {
    return mControlBlock->shared_refcount;
}

int* SharedPtrInt::operator->() const noexcept {
    return mResource;
}

int& SharedPtrInt::operator*() const noexcept {
    return *mResource;
}

SharedPtrInt::operator bool() const noexcept {
    return mResource != nullptr;
}

// mypointer->x == (*mypointer).x
