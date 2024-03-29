#include "results.hpp"

//**************************************************//
// Save the values in the data vector according the //
// coordinates of the scintillator plates in the    //
// detector.                                        //
//**************************************************//
void save_scintillator_values(
  std::vector<Double_t> data, TString output_file
) {

  // Open the output file.
  std::ofstream data_file(output_file, std::ios::out);

  if (data_file.is_open()) {

    // Write the columns title.
    data_file << "Coordinates" << "value";

    // Write the data.
    for (size_t x = 0; x < 3*6; x++) {
      for (size_t y = 0; y < 3*4; y++) {
        for (size_t z = 0; z < 67; z++) {

          data_file << "\"(" << x << ", " << y << ", " << z << ")\","
          << data[x*4*3*67 + y*67 + z] << "\n";

        }
      }
    }

    // Close the file.
    data_file.close();
  }

}

//**************************************************//
// Save the values in the data vector according the //
// coordinates of the lead plates in the detector.  //
//**************************************************//
void save_lead_values (
  std::vector<Double_t> data, TString output_file
) {

  // Open the output file.
  std::ofstream data_file(output_file, std::ios::out);

  if (data_file.is_open()) {

    // Write the columns title.
    data_file << "Coordinates" << "value";

    // Write the data.
    for (size_t x = 0; x < 6; x++) {
      for (size_t y = 0; y < 4; y++) {
        for (size_t z = 0; z < 66; z++) {

          data_file << "\"(" << x << ", " << y << ", " << z << ")\","
          << data[x*4*66 + y*66 + z] << "\n";

        }
      }
    }

    // Close the file.
    data_file.close();
  }

}

//*************************************//
// Save the values in the data vector. //
//*************************************//
void save_significative_cells(
  std::vector<TString> data,
  TString output_file
) {

  // Open the output file.
  std::ofstream data_file(output_file, std::ios::out);

  if (data_file.is_open()) {

    // Write the data.
    for (size_t row = 0; row < data.size(); row++) {
      data_file << data[row] << "\n";
    }

    // Close the file.
    data_file.close();

  }

}


//
// test.cpp ends here.
//
