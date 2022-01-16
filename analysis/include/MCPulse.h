#ifndef MCPULSE_H
#define MCPULSE_H 1

#include <string>
#include <vector>
#include <ostream>

using namespace std;

class MCPulse{

public:

	static unsigned int GetNType(){ return nType;}

	MCPulse(){
		time = -1;
		for(unsigned int i=0; i<nType; i++){
			energy.push_back(0);
		}
	}

	MCPulse( double t, vector<double> a){
		time = t;

		unsigned int m = nType<a.size()?nType:a.size();
		for(unsigned int i=0; i<m; i++)
			energy.push_back( a[i] );
		for(unsigned int i=m+1; i<nType; i++)
			energy.push_back( 0 );
		
	}

	MCPulse( const MCPulse& a){
		time = a.time;
		energy = a.energy;
	}

	~MCPulse(){}

	MCPulse& operator=( const MCPulse& a){
		time = a.time;
		energy = a.energy;
		return *this;
	}

	bool operator<( const MCPulse& a ){
		return time < a.time;
	}

	MCPulse& operator+( const MCPulse& a){

		if( time<0 ){
			time = a.time;
		}
		else{
			time = time<a.time?time:a.time;
		}

		for(unsigned int i=0; i<nType; i++){
			energy[i] += a.energy[i];
		}

		return (*this);
	}

	void operator+=( const MCPulse& a){
		if( time<0 )
			time = a.time;
		else
			time = time<a.time ? time : a.time;

		for(unsigned int i=0; i<nType; i++){
			energy[i] += a.energy[i];
		}
	}


	void SetTime( double a ){
		time = a;
	}
	
	double GetTime(){
		return time;
	}

	void SetEnergy( int i, double a ){
		if(i<nType) energy[i] = a;
	}
	
	void SetEnergy( vector<double> a ){
		if(a.size()==nType)
			energy = a;
	}

	vector<double> GetEnergy(){
		return energy;
	}

	friend ostream& operator<<( ostream& os, const MCPulse& a);

private:

	static const unsigned int nType = 3;

	double time;

	vector<double> energy;
};

ostream& operator<<( ostream& os, const MCPulse& a){

	os << a.time;

	vector<double> en = a.energy;
	for( unsigned int i=0; i<en.size(); i++ )
		os << ' ' << en[i];

	return os;
}


#endif
