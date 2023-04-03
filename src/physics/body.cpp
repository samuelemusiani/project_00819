#include "body.hpp"

phy::Body::Body() : Body(phy::Point(0, 0), phy::Vector(0, 0), phy::Vector(0, 0))
{

}

phy::Body::Body(phy::Point position, phy::Vector velocity, phy::Vector acceleration)
{
	this->set_position(position);
	this->set_velocity(velocity);
	this->set_acceleration(acceleration);
}

void phy::Body::set_position(phy::Point position)
{
	this->position = position;
}

void phy::Body::set_velocity(phy::Vector velocity)
{
	this->velocity = velocity;
}

void phy::Body::set_acceleration(phy::Vector acceleration)
{
	this->acceleration = acceleration;
}


phy::Point phy::Body::get_position()
{
	return this->position;
}

phy::Vector phy::Body::get_velocity()
{
	return this->velocity;
}

phy::Vector phy::Body::get_acceleration()
{
	return this->acceleration;
}

void phy::Body::update(int time)
{
	/*
	* Valori da aggiornare:
	* Posizione
	* Velocità
	* (No accellerazione che tanto non cambia con il tempo, va settata a mano?)
	*/ 

	if(time != 0)
	{
		phy::Point newPosition = Point(
			this->position.get_xPosition() + this->velocity.get_xComponent() * time,
			this->position.get_yPosition() + this->velocity.get_yComponent() * time
			);

		phy::Vector tmpAcceleration = this->acceleration;
		tmpAcceleration.set_magnitude(tmpAcceleration.get_magnitude() * time);
		set_velocity(phy::Vector::sum(this->velocity, tmpAcceleration));
	}
}
