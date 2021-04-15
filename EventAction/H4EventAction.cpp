#include "H4EventAction.hpp"

//***************************//
// H4EventAction constructor //
//---------------------------//
//                           //
//      Do nothing.          //
//                           //
//***************************//
H4EventAction::H4EventAction ()
: G4UserEventAction(),
m_X({}),
m_Y({}),
m_Z({}),
m_r({}),
m_c({}) { }

//***********************************//
// H4EventAction constructor         //
//-----------------------------------//
//                                   //
// Delere root analysis instance.    //
//                                   //
//***********************************//
H4EventAction::~H4EventAction () {
  delete G4RootAnalysisManager::Instance();
}

//***************************//
//                           //
// Actions before the event. //
//                           //
//***************************//
void H4EventAction::BeginOfEventAction (const G4Event *event) {

  //<><><><><><><><><><><><><><><><><><><>//
  // Clear counters of photons production //
  //<><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  m_XGammaScintillator.clear();
  m_YGammaScintillator.clear();
  m_ZGammaScintillator.clear();
  m_rGammaScintillator.clear();
  m_cGammaScintillator.clear();

  // Counters for lead plates.
  m_XGammaLead.clear();
  m_YGammaLead.clear();
  m_ZGammaLead.clear();
  m_rGammaLead.clear();
  m_cGammaLead.clear();

  //<><><><><><><><><><><><><><><><><><><><>//
  // Clear counters of electrons production //
  //<><><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  m_XElectronScintillator.clear();
  m_YElectronScintillator.clear();
  m_ZElectronScintillator.clear();
  m_rElectronScintillator.clear();
  m_cElectronScintillator.clear();

  // Counters for lead plates.
  m_XElectronLead.clear();
  m_YElectronLead.clear();
  m_ZElectronLead.clear();
  m_rElectronLead.clear();
  m_cElectronLead.clear();

  //<><><><><><><><><><><><><><><><><><><>//
  //  Clear counters of energy deposition //
  //<><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  m_XEnergyScintillator.clear();
  m_YEnergyScintillator.clear();
  m_ZEnergyScintillator.clear();
  m_rEnergyScintillator.clear();
  m_cEnergyScintillator.clear();
  m_EEnergyScintillator.clear();

  // Counters for lead plates.
  m_XEnergyLead.clear();
  m_YEnergyLead.clear();
  m_ZEnergyLead.clear();
  m_rEnergyLead.clear();
  m_cEnergyLead.clear();
  m_EEnergyLead.clear();

}

//**************************//
//                          //
// Actions after the event. //
//                          //
//**************************//
void H4EventAction::EndOfEventAction (const G4Event *event) {
  // Get the analysis manager.
  G4RootAnalysisManager *analysis_manager = G4RootAnalysisManager::Instance();

  G4String particle =
  event->GetPrimaryVertex()->GetPrimary()
  ->GetParticleDefinition()->GetParticleName();

  G4double energy =
  event->GetPrimaryVertex()->GetPrimary()->GetTotalEnergy();

  for (int i = 0; i < m_X.size(); i++) {
    analysis_manager->FillH2(0, 40 - m_X[0], m_Y[1] - 20);
  }

  analysis_manager->FillNtupleIColumn(0, m_particlesID[particle]);

  // Add tupple row.
  analysis_manager->AddNtupleRow();

}

//
// H4EventAction.cpp ends here.
//
