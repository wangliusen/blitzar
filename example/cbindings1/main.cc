#include <iostream>
#include <cstddef>

#include "sxt/seqcommit/cbindings/pedersen_capi.h"

int main() {
  const sxt_config config = {SXT_BACKEND_GPU};

  if (sxt_init(&config) != 0) {
    std::cerr << "sxt_init failed\n";
    return -1;
  }
  const uint64_t n1 = 3;
  const uint8_t n1_num_bytes = 1;
  uint8_t data_bytes_1[n1_num_bytes * n1] = {1, 2, 3};
  sxt_dense_sequence_descriptor descriptor1 = {
      n1_num_bytes,  // number bytes
      n1,            // number rows
      data_bytes_1   // data pointer
  };
  const int num_sequences = 1;
  const sxt_sequence_descriptor descriptors[num_sequences] = {
      {SXT_DENSE_SEQUENCE_TYPE, descriptor1},
  };
  sxt_ristretto_element commitments[num_sequences];
  auto rcode =
      sxt_compute_pedersen_commitments(commitments, num_sequences, descriptors);
  if (rcode != 0) {
    std::cerr << "sxt_compute_pedersen_commitments failed\n";
    return -1;
  }
  auto commitments_data = reinterpret_cast<unsigned char*>(commitments);
  for (size_t i=0; i<sizeof(commitments); ++i) {
    std::cout << std::hex << static_cast<unsigned>(commitments_data[i]);
  }
  std::cout << "\n";
  return 0;
}