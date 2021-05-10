#include "significative_cells.hpp"

//***********************************************//
// Get the cells of the detector with low (below //
// a threshold) kolmogorov test results between  //
// the files in the variables "photons",         //
// "electrons", "E" and "SL".                    //
// This cells will be used in the implementation //
// of the artifical nteligence.                  //
//***********************************************//
std::vector<TString> get_significative_cells(
  std::vector<TTree *> trees,
  TString label,
  bool save,
  Double_t threshold
) {

  // Create the vectors for the materials and the particles.
  std::vector<TString> materials = {"scintillator", "lead"};
  std::vector<TString> particles = {"photons", "electrons"};

  // Set the maximun values of the coordinates for each material.
  std::map<TString, Int_t> x_max = {
    {"scintillator", 3*6},
    {"lead", 6}
  };
  std::map<TString, Int_t> y_max = {
    {"scintillator", 3*4},
    {"lead", 4}
  };
  std::map<TString, Int_t> z_max = {
    {"scintillator", 67},
    {"lead", 66}
  };

  // Create a map to store the results.
  std::map< TString, std::vector<Double_t> > test_results;

  // Create the vectore to store the values. The values will be stored as
  // strings.
  std::vector<TString> significative_cells = {
    "material,position,photons,electrons,SL,E"
  };

  std::cout << "-- Info: Total trees compared: " << trees.size() << '\n';

  // Loop over the trees. The tree_b is one unit above to avoid the camporison
  // of a tree with itself.
  for (size_t tree_a = 0; tree_a < trees.size(); tree_a++) {
    for (size_t tree_b = tree_a + 1; tree_b < trees.size(); tree_b++) {

      // Loop over the materials.
      for (size_t material_index = 0; material_index < 2; material_index++) {

        // Loop over the particles.
        for (size_t particle_index = 0; particle_index < 2; particle_index++) {

          // Get the result of the kolmogorov test for the particle counter.
          test_results[particles[particle_index]] = kolmogorov_test_counter(
            trees[tree_a], trees[tree_b], particles[particle_index],
            materials[material_index], "", false
          );

        }

        // Get the result of the kolmogorov test for the step length.
        test_results["SL"] = kolmogorov_test_step_lenght(
          trees[tree_a], trees[tree_b], materials[material_index], "", false
        );
        // Get the result of the kolmogorov test for the energy deposited in
        // the detector plates.
        test_results["E"] = kolmogorov_test_energy(
          trees[tree_a], trees[tree_b], materials[material_index], "", false
        );

        // Match the result with the plate material and coordiantes.
        for (Int_t x = 0; x < x_max[materials[material_index]]; x++) {
          for (Int_t y = 0; y < y_max[materials[material_index]]; y++) {
            for (Int_t z = 0; z < z_max[materials[material_index]]; z++) {
              // Index of the cell.
              Int_t cell =
              x*y_max[materials[material_index]]*z_max[materials[material_index]] +
              y*z_max[materials[material_index]] +
              z;

              // Create the cell information, with the coordinates and the
              // material.
              TString entry = materials[material_index] + TString(",") +
              TString("\"(") + std::to_string(x).c_str() + TString(",") +
              std::to_string(y).c_str() + TString(",") +
              std::to_string(z).c_str() + TString(")\",");

              // Add bools, if the test result is above the threshold, it adds
              // a True value, add False otherwise.

              // Loop over the materials.
              for (size_t particle_index = 0; particle_index < 2; particle_index++) {

                if (test_results[particles[particle_index]][cell] < threshold) {

                  entry += "True,";

                } else {

                  entry += "False,";

                }

              }

              if (test_results["SL"][cell] < threshold) {

                entry += "True,";

              } else {

                entry += "False,";

              }

              if (test_results["E"][cell] < threshold) {

                entry += "True";

              } else {

                entry += "False";

              }

              // Append the information of the plate.
              significative_cells.push_back(entry);
            }
          }
        }

      }

    }
  }

  // Save the cells information if
  if (save) {
    save_significative_cells(
      significative_cells, label + "_significative_cells.csv"
    );
  }

  return significative_cells;

}

//
// significative_cells.cpp ends here.
//