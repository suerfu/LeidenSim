
#include "GeoManager.hh"
#include "TTree.h"
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
G4double  GeoManager::GetCryoBeamRI(int ib){
	if(ib<0||ib>fCryoBeams.size()){
		G4cerr<<"Cryostat beam "<<ib<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoBeams[ib].rI;
	}
}
G4double  GeoManager::GetCryoBeamRO(int ib){
	if(ib<0||ib>fCryoBeams.size()){
		G4cerr<<"Cryostat beam "<<ib<<" not specified in data file!"<<G4endl;
		return "N.A.";
	}else{
		return fCryoBeams[ib].rO;
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

void GeoManager::LoadDimensions(){

	//General dimensions
	TTree *t = new TTree("tDimension","General Dimensions");
	t->ReadFile(fDimensionFile, "name/C:dim/D");
	std::string name;
	double dim;
	t->SetBranchAddress("name", &name);
	t->SetBranchAddress("dim", &dim);
	for(int i=0; i<t->GetEntries(); i++){
		t->GetEntry(i);
		dimensions[G4String(name)] = dim*mm;
	}

	//Cryostat walls
	LoadCryoWalls();
	//Cryostat plates
	LoadCryoPlate();
	//Cryostat beams
	LoadCryoBeam();

}

void GeoManager::LoadCryoWalls(){
	//Cryostat walls
	TTree *tCW = new TTree("tCW", "Cryostat wall coordinates");
	tCW->ReadFile(fCryostatWallFile, "z[4]/D:r[4]/D");
	double z[4], r[4];
	tCW->SetBranchAddress("z",z);
	tCW->SetBranchAddress("r",r);
	for(int i=0; i<4; i++){
		fCryostatCoordinateNP[i]=0;
		fCryostatCoordinateR[i] = new G4double[tCW->GetEntries()];
		fCryostatCoordinateZ[i] = new G4double[tCW->GetEntries()];
	}
	for(int ip=0; ip<tCW->GetEntries(); ip++){
		tCW->GetEntry(ip);
		for(int i=0; i<4; i++){
			fCryostatCoordinateR[i][ip] = r[i]*mm;
			fCryostatCoordinateZ[i][ip] = z[i]*mm;
			if(r[i]<0&&fCryostatCoordinateNP[i]==0){
				fCryostatCoordinateNP[i] = ip;
			}
		}
	}
	for(int i=0; i<4; i++){
		if(fCryostatCoordinateNP[i]==0)
			fCryostatCoordinateNP[i] = tCW->GetEntries();
	}
}
void GeoManager::LoadCryoPlate(){
	//first load drill chart
	fDrillChart = new std::vector<G4double>;
	std::ifstream cryoPlateFile(fCryoPlateFile, std::ifstream::in);
	char temp[256];
	cryoPlateFile.getLine(temp, 256);
	cryoPlateFile.getLine(temp, 256);
	//drill charge on line 3
	cryoPlateFile.getLine(temp, 256);
	TString drillChart(temp+1);//remove the # in the first position.
	TString drill;
	Ssiz_t from = 0;
	while(drillChart.Tokenize(drill, from, " ")){
		G4double drillR = drill.Atof()*mm;
		fDrillChart->push_back(drillR);
	}
	cryoPlateFile.close();

	TTree *tCP = new TTree("tCP", "Plates in Cryostat");
	tCP->ReadFile(fCryoPlateFile, "name/C:r/D:thickness/D:z/D:material/C:nHoles/I:xhole[6]/D:yhole[6]/D:drill[6]/I");
	string name, material;
	double r, thickness, z, x[6], y[6];
	int nHoles, drill[6];
	tCP->SetBranchAddress("name", &name);
	tCP->SetBranchAddress("r",    &r);
	tCP->SetBranchAddress("thickness", &thickness);
	tCP->SetBranchAddress("z",    &z);
	tCP->SetBranchAddress("material", &material);
	tCP->SetBranchAddress("nHoles",&nHoles);
	tCP->SetBranchAddress("xhole", x);
	tCP->SetBranchAddress("yhole", y);
	tCP->SetBranchAddress("drill", drill);
	for(int i=0; i<tCP->GetEntries(); i++){
		tCP->GetEntry(i);
		CryoPlate plate;
		plate.name = name;
		plate.r = r*mm;
		plate.thickness = thickness*mm;
		plate.z = z*mm;
		plate.material = GetMaterial(G4String(material));
		plate.holes = new std::vector< std::pair<G4int, G4ThreeVector> >;
		for(int ih=0; ih<nHoles; ih++){
			plate.holes->push_back( 
						std::make_pair( drill[ih], 
							G4ThreeVector(x[ih],y[ih],0)));
		}
		fCryoPlates.push_back(plate);
	}

}

void GeoManager::LoadCryoBeam(){
	TTree *tCB = new TTree("tCB", "Beams in Cryostat");
	tCB->ReadFile(fCryoBeamFile, "name/C:rO/D:rI/D:l/D:pos[3]/D:material/C");
	string name, material;
	double rO, rI, l, pos[3];
	tCB->SetBranchAddress("name", &name);
	tCB->SetBranchAddress("rI",    &rI);
	tCB->SetBranchAddress("rO",    &rO);
	tCB->SetBranchAddress("l",    &l);
	tCB->SetBranchAddress("pos",  pos);
	tCB->SetBranchAddress("material". &material);
	for(int i=0; i<tCB->GetEntries(); i++){
		tCB->GetEntry(i);
		CryoBeam beam;
		beam.name = name;
		beam.rI = rI*mm;
		beam.rO = rO*mm;
		beam.l = l*mm;
		beam.pos = G4ThreeVector(pos[0]*mm, pos[1]*mm,pos[2]*mm);
		fCryoBeams.push_back(beam);
	}
}





