
#include "GeoManager.hh"
// singleton
GeoManager* GeoManager::me = 0;

GeoManager::GeoManager(){
    material_man = GetMaterialManager();
    DefineMaterials();
	LoadDimensions();
}

GeoManager::~GeoManager(){
    dictionary.clear();
	dimensions.clear();
}

GeoManager* GeoManager::Get(){
	if (!me)
	  me = new GeoManager();
	return me;
}

//public methods
void GeoManager::Add( G4String name, G4LogicalVolume* log, G4VPhysicalVolume* phys){
    dictionary[name] = std::make_pair( log, phys);
}

G4LogicalVolume* GeoManager::GetLogicalVolume( G4String name ){
    if( dictionary.find(name)==dictionary.end() ){
        return 0;
    }
    else{
        return dictionary[name].first;
    }
}

G4VPhysicalVolume* GeoManager::GetPhysicalVolume( G4String name ){
    if( dictionary.find(name)==dictionary.end() ){
        return 0;
    }
    else{
        return dictionary[name].second;
    }
}

G4NistManager* GeoManager::GetMaterialManager(){
    return G4NistManager::Instance();
}

G4Material* GeoManager::GetMaterial(G4String name){
    return material_man->FindOrBuildMaterial( name );
}

G4double  GeoManager::GetDimensions(G4String name){
	if( dimensions.find(name)==dimensions.end() ){
		return 0;		
	}else{
		return dimensions[name];
	}
}

//Cryostat walls
G4int  GeoManager::GetCryostatCoordinateNP(int ithLayer){
	if(ithLayer>=4){
		G4cerr<<"Cryostat layer "<<ithLayer<<" not specified in data file!"<<G4endl;
		return 0;
	}else{
		return fCryostatCoordinateNP[ithLayer];
	}
}
G4double*  GeoManager::GetCryostatCoordinateR(int ithLayer){
	if(ithLayer>=4){
		G4cerr<<"Cryostat layer "<<ithLayer<<" not specified in data file!"<<G4endl;
		return 0;
	}else{
		return fCryostatCoordinateR[ithLayer];
	}
}
G4double*  GeoManager::GetCryostatCoordinateZ(int ithLayer){
	if(ithLayer>=4){
		G4cerr<<"Cryostat layer "<<ithLayer<<" not specified in data file!"<<G4endl;
		return 0;
	}else{
		return fCryostatCoordinateZ[ithLayer];
	}
}

//Plates in code stages
G4String  GeoManager::GetCryoPlateName(int ip){
	if(ip<0||ip>fCryoPlates.size()){
		G4cerr<<"Cryostat plate "<<ip<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoPlates[ip].name;
	}
}
G4Material*  GeoManager::GetCryoPlateMaterial(int ip){
	if(ip<0||ip>fCryoPlates.size()){
		G4cerr<<"Cryostat plate "<<ip<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoPlates[ip].material;
	}
}
G4double  GeoManager::GetCryoPlateR(int ip){
	if(ip<0||ip>fCryoPlates.size()){
		G4cerr<<"Cryostat plate "<<ip<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoPlates[ip].r;
	}
}
G4double  GeoManager::GetCryoPlateH(int ip){
	if(ip<0||ip>fCryoPlates.size()){
		G4cerr<<"Cryostat plate "<<ip<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoPlates[ip].thickness;
	}
}
G4double  GeoManager::GetCryoPlateZ(int ip){
	if(ip<0||ip>fCryoPlates.size()){
		G4cerr<<"Cryostat plate "<<ip<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoPlates[ip].z;
	}
}
std::vector< std::pair<G4int, G4ThreeVector> >*  GeoManager::GetCryoPlateHoles(int ip){
	if(ip<0||ip>fCryoPlates.size()){
		G4cerr<<"Cryostat plate "<<ip<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoPlates[ip].holes;
	}
}
//Beams in cold stages
G4String  GeoManager::GetCryoBeamName(int ib){
	if(ib<0||ib>fCryoBeams.size()){
		G4cerr<<"Cryostat beam "<<ib<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoBeams[ib].name;
	}
}
G4Material*  GeoManager::GetCryoBeamMaterial(int ib){
	if(ib<0||ib>fCryoBeams.size()){
		G4cerr<<"Cryostat beam "<<ib<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoBeams[ib].material;
	}
}
G4double  GeoManager::GetCryoBeamR(int ib){
	if(ib<0||ib>fCryoBeams.size()){
		G4cerr<<"Cryostat beam "<<ib<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoBeams[ib].r;
	}
}
G4double  GeoManager::GetCryoBeamL(int ib){
	if(ib<0||ib>fCryoBeams.size()){
		G4cerr<<"Cryostat beam "<<ib<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoBeams[ib].l;
	}
}
G4ThreeVector  GeoManager::GetCryoBeamPos(int ib){
	if(ib<0||ib>fCryoBeams.size()){
		G4cerr<<"Cryostat beam "<<ib<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoBeams[ib].pos;
	}
}

//private methods
void  GeoManager::DefineMaterials( ){

    G4double a;  // mass of a mole;
    G4double z;  // z=mean number of protons
    G4int natoms;
    G4int ncomp;
    G4double density;
    G4String symbol, name;

    G4Material* LHe = new G4Material("LHe", z=2., a= 4.00*g/mole, density= 0.141*g/cm3);

    G4Material* NaI = new G4Material("NaI", density = 3.67*g/cm3, ncomp=2);
    G4Element* Na = new G4Element( "Sodium", "Na", z = 11., a = 23 * g/mole );
    G4Element* I = new G4Element( "Iodine", "I", z = 53., a = 127 * g/mole );
    NaI->AddElement(Na, natoms = 1);
    NaI->AddElement( I, natoms = 1);

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

void LoadDimensions(){
	
}



