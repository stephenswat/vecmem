/**
 * VecMem project, part of the ACTS project (R&D line)
 *
 * (c) 2021 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#include "vecmem/memory/terminal_memory_resource.hpp"

#include <cstddef>
#include <stdexcept>

#include "vecmem/memory/memory_resource.hpp"

namespace vecmem {
terminal_memory_resource::terminal_memory_resource(void)
    : m_upstream(nullptr) {}

terminal_memory_resource::terminal_memory_resource(memory_resource &upstream)
    : m_upstream(&upstream) {}

void *terminal_memory_resource::do_allocate(std::size_t size,
                                            std::size_t align) {
    /*
     * Allocation always fails.
     */
    throw std::bad_alloc();
}

void terminal_memory_resource::do_deallocate(void *ptr, std::size_t size,
                                             std::size_t align) {
    /*
     * Deallocation is a no-op.
     */
    return;
}

bool terminal_memory_resource::do_is_equal(
    const memory_resource &other) const noexcept {
    /*
     * All terminal resources are equal.
     */
    return dynamic_cast<const terminal_memory_resource *>(&other) != nullptr;
}
}  // namespace vecmem
