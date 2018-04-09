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
	//setter and getters..
	void setHealth(double h);
	double getHealth() const;
	void setNum(int );
	void setFirePower(int );
	int getMaxNum()const;
	int getFirePower()const;
	//
	// TODO: Add More Member Functions As Needed
	//

};

