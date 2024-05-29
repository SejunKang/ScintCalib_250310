#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4UnionSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4EllipticalCone.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "DetectorConstruction.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4SDParticleFilter.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();

	auto matPlastic = nist -> FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

    auto matPMT = nist-> FindOrBuildMaterial("G4_Pyrex_Glass");
/*	
	G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
	SiO2->AddElement(nist->FindOrBuildElement("Si"),1);
	SiO2->AddElement(nist->FindOrBuildElement("O"),2);

	G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);
	H2O->AddElement(nist->FindOrBuildElement("H"),2);
	H2O->AddElement(nist->FindOrBuildElement("O"),1);

	G4Element *C = nist->FindOrBuildElement("C");

	G4Material *matPlastic = new G4Material("Aerogel", 0.200*g/cm3, 3);
	matPlastic -> AddMaterial(SiO2, 62.5*perCent);
	matPlastic -> AddMaterial(H2O, 37.4*perCent);
	matPlastic -> AddElement(C, 0.1*perCent);
*/
//===== Optical Properties ====================================
	G4double energy[2] = {1.239841939*eV/0.9,1.239841939*eV/0.2};
	G4double rindexmatPlastic[2] = {1.1, 1.3};
	G4double rindexWorld[2] = {1.0,1.0};

	G4double reflectivity[2] = { 0.3, 0.5 };

//===== Scintillator Properties ===============================

	G4MaterialPropertiesTable *mptmatPlastic = new G4MaterialPropertiesTable();
	mptmatPlastic->AddProperty("RINDEX", energy, rindexmatPlastic, 2);


	G4double scint[2] =  {0.1,1.0};

	//  mptmatPlastic -> AddProperty("EFFICIENCY", energy, efficiency);
	//  mptmatPlastic -> AddProperty("ABSLENGTH", energy, absorption);

	mptmatPlastic -> AddProperty("SCINTILLATIONCOMPONENT1", energy, scint,2);
	//mptmatPlastic -> AddProperty("SCINTILLATIONCOMPONENT2", energy, scint,2);
	mptmatPlastic -> AddConstProperty("SCINTILLATIONYIELD", 5./MeV);
	mptmatPlastic -> AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptmatPlastic -> AddConstProperty("SCINTILLATIONTIMECONSTANT1", 20. *ns);
	//mptmatPlastic -> AddConstProperty("SCINTILLATIONTIMECONSTANT2", 45. *ns);
	//mptmatPlastic -> AddConstProperty("SCINTILLATIONYIELD", 1.0);
	//mptmatPlastic -> AddConstProperty("SCINTILLATIONYIELD2", 0.0);

	matPlastic->SetMaterialPropertiesTable(mptmatPlastic);

//=====================================================
//===== World Properties ========================================
	G4Material *WorldMat = nist -> FindOrBuildMaterial("G4_AIR");

	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld -> AddProperty("RINDEX", energy, rindexWorld,2);
	mptWorld -> AddProperty("REFLECTIVITY", energy, reflectivity, 2);

	WorldMat -> SetMaterialPropertiesTable(mptWorld);

// === World ======================================================
	auto WorldSize = 5.5 *m;
	G4Box *SolidWorld = new G4Box("SolidWorld", 0.5*WorldSize, 0.5*WorldSize, 0.5*WorldSize);
	G4LogicalVolume *WorldLV = new G4LogicalVolume(SolidWorld, WorldMat, "LogicalWorld");

	G4VPhysicalVolume *WorldPV = new G4PVPlacement(0, G4ThreeVector(), WorldLV, "PhysisWorld",0,false,0,true);

// === Solids ========================================
/*
	G4Box *SolidRadiator = new G4Box("SolidRadiator", 0.4*m, 0.4*m, 0.01*m);
	G4LogicalVolume *LogicRadiator = new G4LogicalVolume(SolidRadiator, matPlastic, "LogicalRadiator");

	G4VPhysicalVolume *PhysRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.25*m), LogicRadiator, "PhysRadiator", WorldLV, false, 0, true);
*/

 // Cylinder ============================================
     Cylsize = 5. * cm;
     CylDiameter = 50.* cm;
     CylHeight = 100. * cm;

     auto CylPos = G4ThreeVector(0.,0.,0. *cm);
     CylSol = new G4Tubs("Cylinder", 0., .5 * CylDiameter, .5 * CylHeight, 0., 360. *deg);

     CylLV = new G4LogicalVolume(CylSol, matPlastic, "Cylinder");

 // Elliptical Cone ============================================
     auto ConePos = G4ThreeVector(0.,0.,100.*cm);
     G4EllipticalCone* ConeSol = new G4EllipticalCone("Cone", 0.225,0.225,61.11*cm, 50*cm);

     ConeLV = new G4LogicalVolume(ConeSol, matPlastic, "Cone");

 // Scintillator ==================================================
     auto SciSol = new G4UnionSolid("Scisol", CylSol, ConeSol, 0, G4ThreeVector(ConePos));
     auto SciLV = new G4LogicalVolume(SciSol, matPlastic, "Scintillator");
     auto SciPV = new G4PVPlacement(0,G4ThreeVector(), SciLV, "Scintillator", WorldLV, false,0);


//PMT 
auto PMTSol = new G4Tubs("PMTSol", 0., 25 *mm, 5*cm, 0., 360 *deg);
auto PMTLog = new G4LogicalVolume(PMTSol, matPlastic, "PMTLog");
PMTLog -> SetVisAttributes(new G4VisAttributes(G4Colour::Gray()));
auto PMTPhy = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 152.5 *cm), PMTLog, "PMT" ,WorldLV ,false,0);


// Optical Surface (Scint - World)
	G4OpticalSurface* OpSurface = new G4OpticalSurface("OpSurf");

	G4LogicalBorderSurface* LBS = new G4LogicalBorderSurface("OpLBS",SciPV, WorldPV, OpSurface);

	OpSurface -> SetType(dielectric_dielectric);
	OpSurface -> SetModel(unified);
	OpSurface -> SetFinish(groundbackpainted);

	G4double Surf_rindex[2] = { 1.35, 1.4 };
	G4double Surf_reflectivity[2] = { 0.8, 0.9 };
	G4double Surf_efficiency[2] = { 0.8, 1.0 };

	G4MaterialPropertiesTable *SMPT = new G4MaterialPropertiesTable();

	SMPT -> AddProperty("RINDEX", energy, Surf_rindex, 2);
	SMPT -> AddProperty("REFLECTIVITY", energy, Surf_reflectivity, 2);
	SMPT -> AddProperty("EFFICIENCY", energy, Surf_efficiency, 2);


	OpSurface -> SetMaterialPropertiesTable(SMPT);
return WorldPV;
// Optical Surface (Scint - PMT)
/*G4OpticalSurface* OpSurface2 = new G4OpticalSurface("OpSurf2");

	G4LogicalBorderSurface* LBS2 = new G4LogicalBorderSurface("OpLBS2",SciPV, PMTPhy, OpSurface2);

	OpSurface2 -> SetType(dielectric_dielectric);
	OpSurface2 -> SetModel(unified);
	OpSurface2 -> SetFinish(groundbackpainted);

	G4double Surf_reflectivity2[3] = { 0., 0. };
	
	G4MaterialPropertiesTable *SMPT2 = new G4MaterialPropertiesTable();

	SMPT2 -> AddProperty("REFLECTIVITY2", energy, Surf_reflectivity2, 3);
	
	OpSurface2 -> SetMaterialPropertiesTable(SMPT2);

return SciPV;

// Optical Surface (PMT - World)
	G4OpticalSurface* OpSurface3 = new G4OpticalSurface("OpSurf3");

	G4LogicalBorderSurface* LBS3 = new G4LogicalBorderSurface("OpLBS3",PMTPhy, WorldPV, OpSurface3);

	OpSurface3 -> SetType(dielectric_dielectric);
	OpSurface3 -> SetModel(unified);
	OpSurface3 -> SetFinish(groundbackpainted);

	G4double Surf_rindex3[4] = { 1.35, 1.4 };
	G4double Surf_reflectivity3[4] = {1.0, 1.0 };
	G4double Surf_efficiency3[4] = { 0.8, 1.0 };

	G4MaterialPropertiesTable *SMPT3 = new G4MaterialPropertiesTable();

	SMPT3 -> AddProperty("RINDEX3", energy, Surf_rindex3, 4);
	SMPT3 -> AddProperty("REFLECTIVITY3", energy, Surf_reflectivity3, 4);
	SMPT3 -> AddProperty("EFFICIENCY3", energy, Surf_efficiency3 , 4);


	OpSurface3 -> SetMaterialPropertiesTable(SMPT3);

	return WorldPV;*/
}

//Sensitive Detector Construction
void DetectorConstruction::ConstructSDandField()
{
auto mfd = new G4MultiFunctionalDetector("Detector");
G4SDManager::GetSDMpointer()->AddNewDetector(mfd);

void AddNewDetector(G4VSensitiveDetector *aSD);
auto psEDep = new G4PSEnergyDeposit("EDep");
auto filterPhoton = new G4SDParticleFilter("photon-filter", "opticalphoton");
psEDep->SetFilter(filterPhoton);
mfd->RegisterPrimitive(psEDep);
G4bool RegisterPrimitive(G4VPrimitiveScorer *aPS);
SetSensitiveDetector("Scintillator", mfd);
}
