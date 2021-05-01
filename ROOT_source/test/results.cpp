#include "results.hpp"

void save_scintillator_values(
  std::vector<Double_t> data, TString output_file
) {

  std::ofstream data_file(output_file, std::ios::out);

  if (data_file.is_open()) {

    for (size_t x = 0; x < 3*6; x++) {
      for (size_t y = 0; y < 3*4; y++) {
        for (size_t z = 0; z < 67; z++) {

          data_file << "(" << x << ", " << y << ", " << z << ")\t"
          << data[x*4*3*66 + y*67 + z] << "\n";

        }
      }
    }
    data_file.close();
  }

}

void save_lead_values(
  std::vector<Double_t> data, TString output_file
) {

  std::ofstream data_file(output_file, std::ios::out);

  if (data_file.is_open()) {

    for (size_t x = 0; x < 6; x++) {
      for (size_t y = 0; y < 4; y++) {
        for (size_t z = 0; z < 66; z++) {

          data_file << "(" << x << ", " << y << ", " << z << ")\t"
          << data[x*4*66 + y*66 + z] << "\n";

        }
      }
    }
    data_file.close();
  }

}

//
// test.cpp ends here.
//
