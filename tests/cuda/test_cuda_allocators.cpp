/** VecMem project, part of the ACTS project (R&D line)
 *
 * (c) 2021 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

// Local include(s).
#include "vecmem/allocators/allocator.hpp"
#include "vecmem/memory/memory_manager.hpp"
#include "vecmem/memory/cuda/arena_memory_manager.hpp"
#include "vecmem/memory/cuda/direct_memory_manager.hpp"

// System include(s).
#undef NDEBUG
#include <cassert>
#include <vector>

/// Custom vector type used in the tests
template< typename T >
using test_vector = std::vector< T, vecmem::allocator< T > >;

/// Function running tests with the active memory manager.
void run_host_tests() {

   // Create the test vector.
   test_vector< int > testv;

   // Manipulate it in some simple ways.
   for( int i = 0; i < 100; ++i ) {
      testv.push_back( i );
   }
   assert( testv.size() == 100 );
   for( int i = 0; i < 100; ++i ) {
      assert( testv.at( i ) == i );
   }
   testv.resize( 1000 );
   for( int i = 0; i < 100; ++i ) {
      assert( testv.at( i ) == i );
   }
   return;
}

/// Function running simple tests with the active memory manager.
void run_device_tests() {

   // Create the test vector.
   test_vector< int > testv;

   // Resize it in a few different ways.
   testv.resize( 100 );
   testv.reserve( 1000 );
   testv.resize( 10 );
   return;
}

int main() {

   // Run the tests with all available memory managers, that allow for access to
   // the memory from the host.
   vecmem::memory_manager::instance().set(
      std::make_unique< vecmem::cuda::arena_memory_manager >(
         vecmem::cuda::arena_memory_manager::memory_type::host ) );
   run_host_tests();
   vecmem::memory_manager::instance().set(
      std::make_unique< vecmem::cuda::arena_memory_manager >(
         vecmem::cuda::arena_memory_manager::memory_type::managed ) );
   run_host_tests();

   vecmem::memory_manager::instance().set(
      std::make_unique< vecmem::cuda::direct_memory_manager >(
         vecmem::cuda::direct_memory_manager::memory_type::host ) );
   run_host_tests();
   vecmem::memory_manager::instance().set(
      std::make_unique< vecmem::cuda::direct_memory_manager >(
         vecmem::cuda::direct_memory_manager::memory_type::managed ) );
   run_host_tests();

   // Run much simpler tests with the memory managers that only allocate memory
   // on the device(s).
   vecmem::memory_manager::instance().set(
      std::make_unique< vecmem::cuda::arena_memory_manager >(
         vecmem::cuda::arena_memory_manager::memory_type::device ) );
   run_device_tests();

   vecmem::memory_manager::instance().set(
      std::make_unique< vecmem::cuda::direct_memory_manager >(
         vecmem::cuda::direct_memory_manager::memory_type::device ) );
   run_device_tests();

   // Return gracefully.
   return 0;
}
