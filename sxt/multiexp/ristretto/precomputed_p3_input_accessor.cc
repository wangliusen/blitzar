#include "sxt/multiexp/ristretto/precomputed_p3_input_accessor.h"

#include <cassert>

namespace sxt::mtxrs {
//--------------------------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------------------------
precomputed_p3_input_accessor::precomputed_p3_input_accessor(
    basct::cspan<c21t::element_p3> elements) noexcept
    : elements_{elements} {}

//--------------------------------------------------------------------------------------------------
// get_element
//--------------------------------------------------------------------------------------------------
void precomputed_p3_input_accessor::get_element(c21t::element_p3& p, const void* /*data*/,
                                                size_t index) const noexcept {
  assert(index < elements_.size());
  p = elements_[index];
}
} // namespace sxt::mtxrs