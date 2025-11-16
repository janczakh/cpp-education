#pragma once
#include <iostream>
#include <utility>

struct ControlBlock {

int shared_refcount;
int weak_refcount; 

};

template <typename T>
class SharedPtr {
public:
    SharedPtr() :
        mResource(nullptr),
        mControlBlock(nullptr)
    {}

    explicit SharedPtr(T* res) :
        mResource(res),
        mControlBlock(new ControlBlock{1, 0})
    {}
    SharedPtr& operator= (const SharedPtr& other)
    {
        if (this == &other) return *this;
        release();
        mResource = other.mResource;
        mControlBlock = other.mControlBlock;
        if (other.mControlBlock)
            mControlBlock->shared_refcount++;
        return *this;
    }
    SharedPtr(const SharedPtr& other) :
        SharedPtr<T>()
    {
        *this = other;
    }

    SharedPtr(SharedPtr&& other) noexcept :
        mResource(std::exchange(other.mResource, nullptr)),
        mControlBlock(std::exchange(other.mControlBlock, nullptr))
        {}

    SharedPtr& operator= (SharedPtr&& other) noexcept
    {
        if (this == &other) return *this;
        release();
        mControlBlock = std::exchange(other.mControlBlock, nullptr);
        mResource = std::exchange(other.mResource, nullptr);
        
        return *this;
    }

    ~SharedPtr() {
        release();
    }

    // SharedPtr make_shared();
    explicit operator bool() const noexcept {
        return mResource != nullptr;
    }

    int use_count() const noexcept {
        return mControlBlock ? mControlBlock->shared_refcount : 0;
    }
    T& operator*() const noexcept {
        return *mResource;
    }
    T* operator->() const noexcept {
        return mResource;
    }

    void release() {
        if (!mControlBlock) {
            return;
        }
        if (--mControlBlock->shared_refcount == 0) {
            delete mResource;
            std::cout << "SharedPtr: Last reference removed, resource deleted\n";
            if (mControlBlock->weak_refcount == 0) {
                delete mControlBlock;
            }
        } else {
            std::cout << "SharedPtr Non-last reference removed, resource not deleted\n";
        }
        mResource = nullptr;
    }

private:
    T* mResource;
    ControlBlock* mControlBlock;
};
