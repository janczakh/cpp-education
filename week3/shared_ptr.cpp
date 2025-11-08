#include "shared_ptr.h"
#include <iostream>
#include <utility>

SharedPtrInt::SharedPtrInt() :
    mResource(nullptr),
    mControlBlock(nullptr)
    {}

SharedPtrInt::SharedPtrInt(int* res) :
    mResource(res),
    mControlBlock(new ControlBlock{1, 0})
    {}

SharedPtrInt& SharedPtrInt::operator= (const SharedPtrInt& other)
    {
    if (this == &other) return *this;
    release();
    mResource = other.mResource;
    mControlBlock = other.mControlBlock;
    if (other.mControlBlock)
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
    mControlBlock(std::exchange(other.mControlBlock, nullptr))
    {}

SharedPtrInt& SharedPtrInt::operator=(SharedPtrInt&& other) noexcept
    {
        if (this == &other) return *this;
        release();
        mControlBlock = std::exchange(other.mControlBlock, nullptr);
        mResource = std::exchange(other.mResource, nullptr);
        
        return *this;
    }

void SharedPtrInt::release() {
    if (!mControlBlock) {
        return;
    }
    if (--mControlBlock->shared_refcount == 0) {
        delete mResource;
        std::cout << "SharedPtrInt: Last reference removed, resource deleted\n";
        if (mControlBlock->weak_refcount == 0) {
            delete mControlBlock;
        }
    } else {
        std::cout << "SharedPtrInt Non-last reference removed, resource not deleted\n";
    }
    mResource = nullptr;
    mControlBlock = nullptr;
}

int SharedPtrInt::use_count() const noexcept {
    return mControlBlock ? mControlBlock->shared_refcount : 0;
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
