#include "H4MiddleSection.hpp"

//****************************//
// H4MiddleSection constructor //
//----------------------------//
//                            //
//       Do nothing           //
//                            //
//****************************//
H4MiddleSection::H4MiddleSection () {}

//****************************//
// H4MiddleSection destructor  //
//----------------------------//
//                            //
//       Do nothing           //
//                            //
//****************************//
H4MiddleSection::~H4MiddleSection () {}

//**************************************//
//                                      //
// Build the complete module            //
//                                      //
//**************************************//
void H4MiddleSection::BuildModule (
  G4Material *sc_plate_mat,
  G4Material *hole_mat,
  G4Material *wls_mat,
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  G4LogicalVolume *mother_logical,
  G4double pb_thickness,
  G4double sc_thickness,
  const G4String &pb_log_name,
  const G4String &sc_log_name,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {

  // Build plates
  PlacePbScPlates(
    sc_plate_mat,
    hole_mat,
    rot,
    tlate,
    name,
    mother_logical,
    pb_thickness,
    sc_thickness,
    pb_log_name,
    sc_log_name,
    many,
    copy_no,
    surf_chk
  );

  // Build Recovery
  AddRecovery (
    rot,
    tlate,
    name,
    mother_logical,
    pb_thickness,
    sc_thickness,
    many,
    copy_no,
    surf_chk
  );

  // Build WLS wire
  AddWLS (
    wls_mat,
    rot,
    tlate,
    name,
    mother_logical,
    pb_thickness,
    sc_thickness,
    many,
    copy_no,
    surf_chk
  );

}

//**************************************//
//                                      //
// Construct a squared panel with holes //
//                                      //
//**************************************//
void H4MiddleSection::PlaceHolePlate (
  G4Material *plate_mat,
  G4Material *hole_mat,
  G4double thickness,
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  const G4String &log_name,
  G4LogicalVolume *mother_logical,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {

  // Main box.
  G4Box *main_box = new G4Box("Main Box", 3.03*cm, 3.03*cm, thickness);

  G4LogicalVolume *plate_log = new G4LogicalVolume(
    main_box,
    plate_mat,
    log_name
  );

  // Holes tube.
  G4Tubs *hole_tube = new G4Tubs("Hole", 0, .7*mm, thickness, 0.*deg, 360.*deg);

  G4LogicalVolume *hole_log = new G4LogicalVolume(
    hole_tube,
    hole_mat,
    "Hole_Log"
  );

  // Place the volumes
  new G4PVPlacement(
    rot,
    tlate,
    plate_log,
    name,
    mother_logical,
    many,
    copy_no,
    surf_chk
  );

  // Place the volumes
  new G4PVPlacement(
    0,
    G4ThreeVector(0, 0, 0),
    hole_log,
    name + " - middle hole",
    plate_log,
    false,
    0,
    surf_chk
  );

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {

      new G4PVPlacement(
        0,
        G4ThreeVector(
          -3.03*cm + (0.5 + i) * 1.01*cm,
          -3.03*cm + (0.5 + j) * 1.01*cm,
          0
        ),
        hole_log,
        name + " - hole - row_hole: " + std::to_string(i) +
        " - col_hole: " + std::to_string(j),
        plate_log,
        false,
        0,
        surf_chk
      );

    }
  }

}

//**************************************//
//                                      //
// Construct a squared panel of nine    //
// little hole panels                   //
//                                      //
//**************************************//
void H4MiddleSection::PlaceLargePlate (
  G4Material *plate_mat,
  G4Material *hole_mat,
  G4double thickness,
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  const G4String &log_name,
  G4LogicalVolume *mother_logical,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {


  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {

      PlaceHolePlate (
        plate_mat,
        hole_mat,
        thickness,
        rot,
        tlate + G4ThreeVector((i-0.5) * 6.06 * cm, (j-0.5) * 6.06 * cm, 0.0),
        name + " - row: " + std::to_string(i) + " - col: " + std::to_string(j),
        log_name,
        mother_logical,
        many,
        copy_no,
        surf_chk
      );

    }
  }

}

//**************************************//
//                                      //
// Construct a squared panel of nine    //
// little hole panels                   //
//                                      //
//**************************************//
void H4MiddleSection::PlacePbScPlates (
  G4Material *sc_plate_mat,
  G4Material *hole_mat,
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  G4LogicalVolume *mother_logical,
  G4double pb_thickness,
  G4double sc_thickness,
  const G4String &pb_log_name,
  const G4String &sc_log_name,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {

  // Manager for NIST db, for material searching
  G4NistManager *nist = G4NistManager::Instance();

  // Get the definition of lead as a material
  G4Material *lead_mat = nist->FindOrBuildMaterial("G4_Pb");

  for (int i = 0; i < 67; i++) {

    PlaceLargePlate (
      sc_plate_mat,
      hole_mat,
      sc_thickness,
      rot,
      tlate + G4ThreeVector(
        0,
        0,
        (i - 33) * (2 * (pb_thickness + sc_thickness))
      ),
      name + " - scintillator tile: " + std::to_string(i),
      sc_log_name,
      mother_logical,
      many,
      copy_no,
      surf_chk
    );

  }

  for (int i = 0; i < 66; i++) {

    PlaceLargePlate (
      lead_mat,
      hole_mat,
      pb_thickness,
      rot,
      tlate + G4ThreeVector(
        0,
        0,
        (i - 33) * (2 * (pb_thickness + sc_thickness)) + sc_thickness + pb_thickness
      ),
      name + " - lead tile: " + std::to_string(i),
      pb_log_name,
      mother_logical,
      many,
      copy_no,
      surf_chk
    );

  }

}

//**************************************//
//                                      //
// Add steel recovery for the module    //
//                                      //
//**************************************//
void H4MiddleSection::AddRecovery (
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  G4LogicalVolume *mother_logical,
  G4double pb_thickness,
  G4double sc_thickness,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {

  // Manager for NIST db, for material searching
  G4NistManager *nist = G4NistManager::Instance();

  // Get the definition of lead as a material
  G4Material *steel_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

  // Vertical box.
  G4Box *vertical_box = new G4Box(
    "Main Box", 0.05*cm, 6.06*cm,
    sc_thickness * 67 + pb_thickness * 66
  );

  // Horizontal box.
  G4Box *horizontal_box = new G4Box(
    "Main Box", 6.06*cm, 0.05*cm,
    sc_thickness * 67 + pb_thickness * 66
  );

  G4LogicalVolume *vertical_log = new G4LogicalVolume(
    vertical_box,
    steel_mat,
    "Cover_Sheet"
  );

  G4LogicalVolume *horizontal_log = new G4LogicalVolume(
    horizontal_box,
    steel_mat,
    "Cover_Sheet"
  );

  // Place the volumes
  new G4PVPlacement(
    rot,
    tlate + G4ThreeVector(0.05*cm + 6.06*cm, 0., 0.),
    vertical_log,
    name + " - cover left",
    mother_logical,
    many,
    copy_no,
    surf_chk
  );

  new G4PVPlacement(
    rot,
    tlate + G4ThreeVector(-0.05*cm - 6.06*cm, 0., 0.),
    vertical_log,
    name + " - cover right",
    mother_logical,
    many,
    copy_no,
    surf_chk
  );

  // Place the volumes
  new G4PVPlacement(
    rot,
    tlate + G4ThreeVector(0., 0.05*cm + 6.06*cm, 0.),
    horizontal_log,
    name + " - cover top",
    mother_logical,
    many,
    copy_no,
    surf_chk
  );

  new G4PVPlacement(
    rot,
    tlate + G4ThreeVector(0., -0.05*cm - 6.06*cm, 0.),
    horizontal_log,
    name + " - cover bottom",
    mother_logical,
    many,
    copy_no,
    surf_chk
  );

}

//***************//
//               //
// Add WLS wires //
//               //
//***************//
void H4MiddleSection::AddWLS (
  G4Material *wls_mat,
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  G4LogicalVolume *mother_logical,
  G4double pb_thickness,
  G4double sc_thickness,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {

  // Wire tube.
  G4Tubs *wire_tube = new G4Tubs("Hole", 0, .6*mm,
  sc_thickness * 67 + pb_thickness * 66, 0.*deg, 360.*deg);

  // Wire logical volume.
  G4LogicalVolume *wire_log = new G4LogicalVolume(
    wire_tube,
    wls_mat,
    "WLS"
  );

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {

      new G4PVPlacement(
        rot,
        tlate +
        G4ThreeVector((i - 0.5) * 6.06 * cm, (j - 0.5) * 6.06 * cm, 0.0),
        wire_log,
        name + " - Plate - row: " + std::to_string(i) + " - col: " +
        std::to_string(j) + " - wire - middle",
        mother_logical,
        false,
        0,
        true
      );

      for (int I = 0; I < 6; I++) {
        for (int J = 0; J < 6; J++) {

          new G4PVPlacement(
            rot,
            tlate +
            G4ThreeVector((i - 0.5) * 6.06 * cm, (j - 0.5) * 6.06 * cm, 0.0) +
            G4ThreeVector(
              -3.03*cm + (0.5 + I) * 1.01*cm,
              -3.03*cm + (0.5 + J) * 1.01*cm,
              0
            ),
            wire_log,
            name + " - Plate - row: " + std::to_string(i) + " - col: " +
            std::to_string(j) + " - wire - row_hole: " + std::to_string(I) +
            " - col_hole: " + std::to_string(J),
            mother_logical,
            many,
            copy_no,
            surf_chk
          );

        }
      }

    }
  }

}

//
// H4MiddleSection.cpp end here
//
