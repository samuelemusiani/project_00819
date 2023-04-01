#include "weightedBody.hpp"
#include "constant.hpp"

phy::WeightedBody::WeightedBody() : Body ()
{
	//The predefined mass shoud be 1kg?
	this->set_mass(1);	//Shoud I use this method or the other constructor?
}

phy::WeightedBody::WeightedBody(phy::Point position, phy::Vector velocity, phy::Vector acceleration, double mass) : Body (position, velocity, acceleration)
{
	this->set_mass(mass);
}

void phy::WeightedBody::set_mass(double mass)
{
	this->mass = mass;
}

double phy::WeightedBody::get_mass()
{
	return this->mass;
}

double phy::WeightedBody::get_kineticEnergy()
{
	return 0.5 * this->get_mass() * this->velocity.get_magnitude() * this->velocity.get_magnitude();
}

double phy::WeightedBody::get_potentialEnergy()
{
	return this->get_mass() * phy::GRAVITY_ACCELERATION * this->position.get_yPosition();
}

double phy::WeightedBody::get_energy()
{
	return this->get_kineticEnergy() + this->get_potentialEnergy();
}
