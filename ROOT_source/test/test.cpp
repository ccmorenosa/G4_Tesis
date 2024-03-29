#include "test.hpp"

std::vector<Double_t> kolmogorov_test(
  std::vector< std::vector<double> > data_a,
  std::vector< std::vector<double> > data_b
) {
  std::vector<Double_t> results;

  for (size_t i = 0; i < data_a.size(); i++) {

    if (data_a[i].size() <= 2 || data_b[i].size() <= 2) {
      results.push_back(-1500);
      continue;
    }

    double a[data_a[i].size()], b[data_b[i].size()];
    std::sort(data_a[i].begin(), data_a[i].end());
    std::sort(data_b[i].begin(), data_b[i].end());

    for (int j = 0; j < data_a[i].size(); j++) {a[j] = data_a[i][j];}
    for (int j = 0; j < data_b[i].size(); j++) {b[j] = data_b[i][j];}

    results.push_back(TMath::KolmogorovTest(
      data_a[i].size(),
      a,
      data_b[i].size(),
      b,
      ""
    ));

  }

  return results;
}

std::vector<Double_t> kolmogorov_test_counter(
  TTree *tree_a,
  TTree *tree_b,
  TString particle,
  TString material,
  TString label,
  bool save
) {

  std::vector<Double_t> data;

  if (material.EqualTo("scintillator")) {

    std::vector< std::vector<double> > data_a =
    get_matrix_data_scintillator(tree_a, particle);
    std::vector< std::vector<double> > data_b =
    get_matrix_data_scintillator(tree_b, particle);

    data = kolmogorov_test(data_a, data_b);

    if (save) {
      save_scintillator_values(
        data,
        label + "_" + particle + "_counter_scintillator.csv"
      );
    }

  } else {

    std::vector< std::vector<double> > data_a =
    get_matrix_data_lead(tree_a, particle);
    std::vector< std::vector<double> > data_b =
    get_matrix_data_lead(tree_b, particle);

    data = kolmogorov_test(data_a, data_b);

    if (save) {
      save_lead_values(
        data,
        label + "_" + particle + "_counter_lead.csv"
      );
    }

  }

  return data;
}

std::vector<Double_t> kolmogorov_test_energy(
  TTree *tree_a,
  TTree *tree_b,
  TString material,
  TString label,
  bool save
) {

  std::vector<Double_t> data;

  if (material.EqualTo("scintillator")) {

    std::vector< std::vector<double> > data_a =
    get_matrix_data_scintillator(tree_a, "E");
    std::vector< std::vector<double> > data_b =
    get_matrix_data_scintillator(tree_b, "E");

    data = kolmogorov_test(data_a, data_b);

    if (save) {
      save_scintillator_values(
        data,
        label + "_scintillator_E.csv"
      );
    }

  } else {

    std::vector< std::vector<double> > data_a =
    get_matrix_data_lead(tree_a, "E");
    std::vector< std::vector<double> > data_b =
    get_matrix_data_lead(tree_b, "E");

    data = kolmogorov_test(data_a, data_b);

    if (save) {
      save_lead_values(
        data,
        label + "_lead_E.csv"
      );
    }

  }

  return data;
}

std::vector<Double_t> kolmogorov_test_step_lenght(
  TTree *tree_a,
  TTree *tree_b,
  TString material,
  TString label,
  bool save
) {

  std::vector<Double_t> data;

  if (material.EqualTo("scintillator")) {

    std::vector< std::vector<double> > data_a =
    get_matrix_data_scintillator(tree_a, "SL");
    std::vector< std::vector<double> > data_b =
    get_matrix_data_scintillator(tree_b, "SL");

    data = kolmogorov_test(data_a, data_b);

    if (save) {
      save_scintillator_values(
        data,
        label + "_scintillator_SL.csv"
      );
    }

  } else {

    std::vector< std::vector<double> > data_a =
    get_matrix_data_lead(tree_a, "SL");
    std::vector< std::vector<double> > data_b =
    get_matrix_data_lead(tree_b, "SL");

    data = kolmogorov_test(data_a, data_b);

    if (save) {
      save_lead_values(
        data,
        label + "_lead_SL.csv"
      );
    }

  }

  return data;
}

//
// test.cpp ends here.
//
