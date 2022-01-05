#include <stdlib.h>
#include <memory_resource>

#pragma once

class NodeResource : public std::pmr::memory_resource {
    public:
        NodeResource(std::pmr::memory_resource *parent = std::pmr::get_default_resource());

    private:
        std::pmr::memory_resource *parent_;
        void *do_allocate(size_t bytes, size_t align) override;
        void do_deallocate(void *p, size_t bytes, size_t align) override;
        bool do_is_equal(std::pmr::memory_resource const &other) const noexcept override;
};

NodeResource::NodeResource(std::pmr::memory_resource* parent)
: parent_(parent)
{}

void* NodeResource::do_allocate(size_t bytes, size_t align)
{
    std::cout << "do_allocate()" <<std::endl;
    return parent_->allocate(bytes, align);
}

void NodeResource::do_deallocate(void *p, size_t bytes, size_t align)
{
    std::cout << "do_deallocate()" <<std::endl;
    parent_->deallocate(p, bytes, align);
}

bool NodeResource::do_is_equal(std::pmr::memory_resource const &other) const noexcept
{
    std::cout << "do_is_equal()" <<std::endl;
    return parent_->is_equal(other);
}