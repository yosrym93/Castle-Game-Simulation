#pragma once
class Tower
{
	double health;
	int N; // max number of elements tower can attack in time step
	int firePower;

	//
	// TODO: Add More Data Members As Needed
	//

public:

	void setHealth(double h);
	double GetHealth() const;
	void setNum(int );
	void setFirePower(int );
	//
	// TODO: Add More Member Functions As Needed
	//

};

