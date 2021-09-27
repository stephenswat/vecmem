/**
 * VecMem project, part of the ACTS project (R&D line)
 *
 * (c) 2021 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#pragma once

#include <cstddef>

#include "vecmem/memory/memory_resource.hpp"

namespace vecmem {
/**
 * @brief This memory resource does nothing, but it does nothing for a purpose.
 *
 * This allocator has little practical use, but can be useful for defining some
 * conditional allocation schemes.
 *
 * Reimplementation of `std::pmr::null_memory_resource`, but can accept another
 * memory resource in its constructor.
 */
class terminal_memory_resource : public memory_resource {
public:
    /**
     * @brief Constructs the terminal memory resource, without an upstream
     * resource.
     */
    terminal_memory_resource(void);

    /**
     * @brief Constructs the terminal memory resource, with an upstream
     * resource.
     *
     * @param[in] upstream The upstream memory resource to use.
     */
    terminal_memory_resource(memory_resource& upstream);

private:
    virtual void* do_allocate(std::size_t, std::size_t) override;

    virtual void do_deallocate(void* p, std::size_t, std::size_t) override;

    virtual bool do_is_equal(const memory_resource&) const noexcept override;

    memory_resource* m_upstream;
};
}  // namespace vecmem
