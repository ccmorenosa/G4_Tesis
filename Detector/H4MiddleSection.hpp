#ifndef H4MIDDLE_SECTION_HG4
#define H4MIDDLE_SECTION_HG4

// Geant Headers.
#include "GeneralG4.hpp"

// Project Headers.
#include "H4Module.hpp"

//**********************************//
// Class: H4MiddleSection           //
//----------------------------------//
//                                  //
// This class build the middle      //
// modules of the detector.         //
//                                  //
//**********************************//
class H4MiddleSection : public H4Module {
public:

  H4MiddleSection (
    G4Material *lead_mat,
    G4Material *aerog_mat,
    G4Material *wls_mat
  );
  virtual ~H4MiddleSection ();

private:

  void BuildPlates (
    G4double radius = .6*mm,
    G4double pb_thickness = 1*mm,
    G4double sc_thickness = 2*mm
  ) override;

  void PlaceLargePlate (
    G4bool is_scintillator,
    G4RotationMatrix *rot,
    const G4ThreeVector &tlate,
    const G4String &name,
    G4LogicalVolume *mother_logical,
    G4bool many = false,
    G4int copy_no = 0,
    G4bool surf_chk = false
  ) override;

  void AddWLS (
    G4RotationMatrix *rot,
    const G4ThreeVector &tlate,
    const G4String &name,
    G4LogicalVolume *mother_logical,
    G4double pb_thickness = 1*mm,
    G4double sc_thickness = 2*mm,
    G4bool many = false,
    G4int copy_no = 0,
    G4bool surf_chk = false
  ) override;

};

#endif // H4MIDDLE_SECTION_HG4
