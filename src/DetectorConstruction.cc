#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "DetectorConstruction.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4SDParticleFilter.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalBorderSurface.hh"
DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();

	auto matPlastic = nist -> FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

    auto matShell = nist-> FindOrBuildMaterial("G4_Pyrex_Glass");

	std::vector<G4String> elPMT = {"K", "Cs", "Sb"};
	std::vector<G4int> nPMT = {2, 1, 1};

	auto matPMT = nist -> ConstructNewMaterial("matPMT", elPMT, nPMT, 4.2 *g/cm3);
	auto matScreen = nist -> FindOrBuildMaterial("G4_Al");
	auto matFoil = nist -> FindOrBuildMaterial("G4_Al");

	//===== Optical Properties ====================================
	std::vector <G4double> energy = {2.480 * eV, 2.485 * eV, 2.490 * eV, 2.495 * eV, 2.500 * eV, 2.505 * eV, 2.510 * eV, 2.515 * eV, 2.520 * eV, 2.525 * eV,
	                                      2.530 * eV, 2.536 * eV, 2.541 * eV, 2.546 * eV, 2.551 * eV, 2.557 * eV, 2.562 * eV, 2.567 * eV, 2.572 * eV, 2.578 * eV,
	                                      2.583 * eV, 2.589 * eV, 2.594 * eV, 2.599 * eV, 2.605 * eV, 2.610 * eV, 2.616 * eV, 2.621 * eV, 2.627 * eV, 2.633 * eV,
	                                      2.638 * eV, 2.644 * eV, 2.649 * eV, 2.655 * eV, 2.661 * eV, 2.667 * eV, 2.672 * eV, 2.678 * eV, 2.684 * eV, 2.690 * eV,
	                                      2.696 * eV, 2.701 * eV, 2.707 * eV, 2.713 * eV, 2.719 * eV, 2.725 * eV, 2.731 * eV, 2.737 * eV, 2.743 * eV, 2.749 * eV,
	                                      2.755 * eV, 2.762 * eV, 2.768 * eV, 2.774 * eV, 2.780 * eV, 2.786 * eV, 2.793 * eV, 2.799 * eV, 2.805 * eV, 2.812 * eV,
	                                      2.818 * eV, 2.824 * eV, 2.831 * eV, 2.837 * eV, 2.844 * eV, 2.850 * eV, 2.857 * eV, 2.864 * eV, 2.870 * eV, 2.877 * eV,
	                                      2.884 * eV, 2.890 * eV, 2.897 * eV, 2.904 * eV, 2.911 * eV, 2.918 * eV, 2.924 * eV, 2.931 * eV, 2.938 * eV, 2.945 * eV,
	                                      2.952 * eV, 2.959 * eV, 2.966 * eV, 2.973 * eV, 2.981 * eV, 2.988 * eV, 2.995 * eV, 3.002 * eV, 3.010 * eV, 3.017 * eV,
	                                      3.024 * eV, 3.032 * eV, 3.039 * eV, 3.047 * eV, 3.054 * eV, 3.062 * eV, 3.069 * eV, 3.077 * eV, 3.084 * eV, 3.092 * eV,
	                                      3.100 * eV, 3.108 * eV, 3.115 * eV, 3.123 * eV, 3.131 * eV, 3.139 * eV};
	std::vector <G4double> rindexmatPlastic = {1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 
	                                1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
	                                1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
	                                1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
	                                1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
	                                1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
	                                1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
	                                1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
	                                1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
	                                1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
	                                1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58};
	std::vector <G4double> rindexWorld = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

	std::vector <G4double> rindexGlass = {1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47,	
	                                 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47,
	                                 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47,
	                                 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47,
	                                 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47,
	                                 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47,
	                                 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47,
	                                 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47,
	                                 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47,
	                                 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47, 1.47,
	                                 1.47, 1.47, 1.47, 1.47, 1.47, 1.47};

	std::vector <G4double> reflectivity = {0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9};

	std::vector <G4double> reflGlass = {0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04,	
	                                 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04,
	                                 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04,
	                                 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04,
	                                 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04,
	                                 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04,
	                                 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04,
	                                 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04,
	                                 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04,
	                                 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04,
	                                 0.04, 0.04, 0.04, 0.04, 0.04, 0.04};

	std::vector <G4double> transGlass = {0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,
                                0.9,0.9,0.9,0.9,0.9,0.9};


	std::vector <G4double> Screen_refl = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	                                 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

	std::vector <G4double> Foil_refl = {0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97,	
	                                 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97,
	                                 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97,
	                                 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97,
	                                 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97,
	                                 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97,
	                                 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97,
	                                 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97,
	                                 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97,
	                                 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97, 0.97,
	                                 0.97, 0.97, 0.97, 0.97, 0.97, 0.97};

//===== Scintillator Properties ===============================

	G4MaterialPropertiesTable *mptmatPlastic = new G4MaterialPropertiesTable();
	mptmatPlastic->AddProperty("RINDEX", energy, rindexmatPlastic);


	std::vector <G4double> scint =  {0.000, 0.062, 0.066, 0.071, 0.075, 0.079, 0.084, 0.088, 0.092, 0.097,
	                                 0.104, 0.111, 0.118, 0.125, 0.131, 0.137, 0.146, 0.155, 0.164, 0.170,
	                                 0.176, 0.182, 0.195, 0.209, 0.221, 0.233, 0.244, 0.258, 0.271, 0.285,
	                                 0.302, 0.320, 0.335, 0.351, 0.366, 0.382, 0.397, 0.408, 0.416, 0.426,
	                                 0.440, 0.453, 0.462, 0.470, 0.478, 0.488, 0.499, 0.512, 0.528, 0.543,
	                                 0.563, 0.583, 0.598, 0.612, 0.626, 0.645, 0.665, 0.685, 0.705, 0.730,
	                                 0.758, 0.779, 0.800, 0.824, 0.846, 0.866, 0.886, 0.906, 0.926, 0.944,
	                                 0.964, 0.988, 0.997, 1.000, 1.003, 1.001, 0.987, 0.973, 0.954, 0.916,
	                                 0.872, 0.815, 0.763, 0.691, 0.631, 0.559, 0.494, 0.428, 0.364, 0.314,
	                                 0.271, 0.218, 0.179, 0.147, 0.122, 0.099, 0.074, 0.049, 0.037, 0.028,
	                                 0.019, 0.015, 0.014, 0.013, 0.011, 0.000};

	//  mptmatPlastic -> AddProperty("EFFICIENCY", energy, efficiency);
	//  mptmatPlastic -> AddProperty("ABSLENGTH", energy, absorption);

	mptmatPlastic -> AddProperty("SCINTILLATIONCOMPONENT1", energy, scint);
	mptmatPlastic -> AddConstProperty("SCINTILLATIONYIELD", 10000./MeV);
	mptmatPlastic -> AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptmatPlastic -> AddConstProperty("SCINTILLATIONRISETIME1", 0.9 *ns);
	mptmatPlastic -> AddConstProperty("SCINTILLATIONTIMECONSTANT1", 2.1 *ns);
	
	matPlastic->SetMaterialPropertiesTable(mptmatPlastic);
    
//===== World Properties ========================================
	G4Material *WorldMat = nist -> FindOrBuildMaterial("G4_AIR");

	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld -> AddProperty("RINDEX", energy, rindexWorld);
	mptWorld -> AddProperty("REFLECTIVITY", energy, reflectivity);

	WorldMat -> SetMaterialPropertiesTable(mptWorld);

// === World ======================================================
	auto WorldSize = 2.0 *m;
	G4Box *SolidWorld = new G4Box("SolidWorld", 0.5*WorldSize, 0.5*WorldSize, 0.5*WorldSize);
	G4LogicalVolume *WorldLV = new G4LogicalVolume(SolidWorld, WorldMat, "LogicalWorld");
	G4VPhysicalVolume *WorldPV = new G4PVPlacement(0, G4ThreeVector(), WorldLV, "PhysicalWorld",0,false,0,true);
/*
 // Scintillator ==================================================

     auto ScintPos = G4ThreeVector(0.,0.,0.);
     auto ScintSol = new G4Box("ScintSol", 25. *mm, 750. *mm, 25. *mm);
     auto ScintLV = new G4LogicalVolume(ScintSol, matPlastic, "ScintLV");
     auto ScintPV = new G4PVPlacement(nullptr, ScintPos, ScintLV, "ScintPV", WorldLV, false, 0);
*/
 // PMT Shell =========================================================
 
	/*
	//auto ShellSol = new G4Box("ShellSol", 25. *mm, 50 *mm , 25. *mm);
	auto ShellSol1 = new G4Tubs("ShellSol1", 0. , 26*mm, 50 *mm, 0*deg, 360*deg);
	auto ShellSol2 = new G4Tubs("ShellSol2", 0. , 25*mm, 49 *mm, 0*deg, 360*deg);
	G4SubtractionSolid *ShellSol = new G4SubtractionSolid("ShellSol", ShellSol1, ShellSol2);
    auto ShellLog = new G4LogicalVolume(ShellSol, matShell, "ShellLog");
    ShellLog -> SetVisAttributes(new G4VisAttributes(G4Colour::Blue()));
	G4RotationMatrix *rot = new G4RotationMatrix();
	rot -> rotateX(90 *deg);
	rot -> rotateY(0 *deg);
	rot -> rotateZ(0 *deg); 
    auto ShellPhy = new G4PVPlacement(rot, G4ThreeVector(0., 800 *mm,0.), ShellLog, "ShellPhy" ,ScintLV ,false,0);
*/
// Unified volume ====================================================================================

  	G4MaterialPropertiesTable *mptGlass = new G4MaterialPropertiesTable();
	mptGlass -> AddProperty("RINDEX", energy, rindexGlass);
	mptGlass -> AddProperty("REFLECTIVITY", energy, reflGlass);
	mptGlass -> AddProperty("TRANSMITTANCE", energy, transGlass);
	matShell -> SetMaterialPropertiesTable(mptGlass);

	G4Box *ScintSol = new G4Box("ScintSol", 25. *mm, 750. *mm, 25. *mm);
	G4Tubs *ShellSol = new G4Tubs("ShellSol", 0. , 26. *mm, 50 *mm, 0. *deg, 360. *deg);

	G4RotationMatrix *rot = new G4RotationMatrix();
	rot -> rotateX(90 *deg);
	rot -> rotateY(0 *deg);
	rot -> rotateZ(0 *deg);
	G4UnionSolid *USol = new G4UnionSolid("USol", ScintSol, ShellSol, rot, G4ThreeVector(0., 800 *mm, 0.));
	
	G4Region *ShellR = new G4Region("ShellR");

	G4LogicalVolume *ULog = new G4LogicalVolume(USol, matPlastic, "ULog");
	G4LogicalVolume *ShellLog = new G4LogicalVolume(ShellSol, matShell, "ShellLog");

	ShellLog -> SetRegion(ShellR);
	ShellR -> AddRootLogicalVolume(ShellLog);

	G4PVPlacement *UPhy = new G4PVPlacement(nullptr, G4ThreeVector(0.,0.,0.), ULog, "UPhy",WorldLV, false, 0);

// Photocathode ========================================================================================
    auto PMTSol = new G4Tubs("PMTSol", 0*mm, 23*mm, 0.5 *mm, 0*deg, 360*deg);
    auto PMTLog = new G4LogicalVolume(PMTSol, matPMT, "PMTLog");
    PMTLog -> SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));
    auto PMTPhy = new G4PVPlacement(rot, G4ThreeVector(0., 753.5 *mm, 0.), PMTLog, "PMTPhy" ,ULog ,false,0);

	G4MaterialPropertiesTable *mptScreen = new G4MaterialPropertiesTable();
	mptScreen -> AddProperty("REFLECTIVITY", energy, Screen_refl);
	matScreen -> SetMaterialPropertiesTable(mptScreen);

	auto ScreenSol = new G4Tubs("ScreenSol", 0*mm, 25*mm, 0.5 *mm, 0*deg, 360*deg);
    auto ScreenLog = new G4LogicalVolume(ScreenSol, matScreen, "ScrenLog");
	ScreenLog -> SetVisAttributes(new G4VisAttributes(G4Colour::Grey()));
    auto ScreenPhy = new G4PVPlacement(rot, G4ThreeVector(0., 754.5 *mm, 0.), ScreenLog, "ScreenPhy" ,ULog ,false,0);

// Foil ==============================================================================================
	G4MaterialPropertiesTable *mptFoil = new G4MaterialPropertiesTable();
	mptFoil -> AddProperty("REFLECTIVITY", energy, Foil_refl);
	matFoil -> SetMaterialPropertiesTable(mptFoil);
	
	G4Box *OutFoil =  new G4Box("OutFoil", 25.5 *mm, 750.25 *mm, 25.5 *mm);
	G4Box *InFoil = new G4Box("InFoil", 25. *mm, 750. *mm, 25. *mm);
	G4SubtractionSolid *FoilSol = new G4SubtractionSolid("FoilSol", OutFoil, InFoil, nullptr, G4ThreeVector(0., 0.25 *mm, 0.));
	G4LogicalVolume *FoilLog = new G4LogicalVolume(FoilSol, matFoil, "FoilLog");
	G4PVPlacement *FoilPhy = new G4PVPlacement(nullptr, G4ThreeVector(0.,-0.25 *mm,0.), FoilLog, "FoilPhy", WorldLV, false, 0);

	G4Box *UpFoilUncut = new G4Box("UpFoilUncut", 25. *mm, 0.25 *mm, 25. *mm);
	G4Tubs *FoilCutter = new G4Tubs("FoilCutter", 0., 26. *mm, 0.25 *mm, 0. *deg, 360. *deg);
	G4SubtractionSolid *UpFoilSol = new G4SubtractionSolid("UpFoilSol", UpFoilUncut, FoilCutter);
	G4LogicalVolume *UpFoilLog = new G4LogicalVolume(UpFoilSol, matFoil, "UpFoilLog");
	G4PVPlacement *UpFoilPhy = new G4PVPlacement(nullptr, G4ThreeVector(0., 750.25 *mm, 0.), UpFoilLog, "UpFoilPhy", WorldLV, false, 0);

// Optical Surface (Scintillator vs PMT Shell) ===========================================================
/*
	G4OpticalSurface* PMTSurf = new G4OpticalSurface("PMTSurf");

	G4LogicalBorderSurface* PLBS = new G4LogicalBorderSurface("PLBS", UPhy, ShellPhy2, PMTSurf);
    
	PMTSurf -> SetType(dielectric_dielectric);
	PMTSurf -> SetModel(glisur);
	PMTSurf -> SetFinish(polished);
	*/
// Optical Surface (Scintillator vs World) ================================================
	G4OpticalSurface* OpSurface = new G4OpticalSurface("OpSurf");

	G4LogicalBorderSurface* LBS = new G4LogicalBorderSurface("OpLBS",UPhy, FoilPhy, OpSurface);
    G4LogicalBorderSurface* LBS2 = new G4LogicalBorderSurface("OpLBS",UPhy, UpFoilPhy, OpSurface);
	/*
	OpSurface -> SetType(dielectric_LUTDAVIS);
	OpSurface -> SetModel(DAVIS);
	OpSurface -> SetFinish(PolishedTeflon_LUT);
	*/
	
	OpSurface -> SetType(dielectric_metal);
	//OpSurface -> SetModel(unified);
	OpSurface -> SetModel(glisur);
	OpSurface -> SetFinish(polished);
	
    G4double ephoton[19] = {1.554 *eV, 1.6 *eV, 1.701 *eV, 1.806 *eV, 1.938 *eV, 2.074 *eV, 2.227 *eV, 
							2.409 *eV, 2.606 *eV, 2.848 *eV, 3.226 *eV, 3.388 *eV, 3.543 *eV, 3.721 *eV, 
							3.872 *eV, 4.128 *eV, 4.349 *eV, 4.608 *eV, 4.959 *eV};

	G4double Surf_reflectivity[19] = {0.7563, 0.7792, 0.8167, 0.8438, 0.8729, 0.8938, 0.9125, 0.9292, 
									  0.9438, 0.9458, 0.9542, 0.9542, 0.9521, 0.95, 0.9438, 0.9333, 
									  0.9313, 0.9229, 0.9125};

	G4MaterialPropertiesTable *SMPT = new G4MaterialPropertiesTable();

	SMPT -> AddProperty("REFLECTIVITY", ephoton, Surf_reflectivity, 19);

	OpSurface -> SetMaterialPropertiesTable(SMPT);
	
 return WorldPV;

}

