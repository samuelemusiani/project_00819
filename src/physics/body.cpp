/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Musiani Samuele #0001069143
 *
 * body.cpp: Implementation of the phy::Body class.
 */

#include "body.hpp"

phy::Body::Body()
    : Body(phy::Point(0, 0), phy::Vector(0, 0), phy::Vector(0, 0)) {}

phy::Body::Body(phy::Point position, phy::Vector velocity,
                phy::Vector acceleration) {
  this->set_position(position);
  this->set_velocity(velocity);
  this->set_acceleration(acceleration);
}

phy::Body::Body(phy::PrecisePoint position, phy::Vector velocity,
                phy::Vector acceleration) {
  this->set_position(position);
  this->set_velocity(velocity);
  this->set_acceleration(acceleration);
}

void phy::Body::set_position(phy::Point position) {
  // Da fare overload dell = :)

  this->position.set_xPosition(position.get_xPosition());
  this->position.set_yPosition(position.get_yPosition());
}

void phy::Body::set_position(phy::PrecisePoint position) {
  this->position = position;
}

void phy::Body::set_velocity(phy::Vector velocity) {
  this->velocity = velocity;
}

void phy::Body::set_acceleration(phy::Vector acceleration) {
  this->acceleration = acceleration;
}

phy::Point phy::Body::get_position() { return this->position.toPoint(); }

phy::PrecisePoint phy::Body::get_precisePosition() { return this->position; }

phy::Vector phy::Body::get_velocity() { return this->velocity; }

phy::Vector phy::Body::get_acceleration() { return this->acceleration; }

void phy::Body::update(double time) {
  /*
   * Valori da aggiornare:
   * Posizione
   * Velocità
   * (No accellerazione che tanto non cambia con il tempo, va settata a mano?)
   */

  if (time != 0) {
    this->set_position(phy::PrecisePoint(
        this->get_precisePosition().get_xPosition() +
            this->get_velocity().get_xComponent() * time +
            0.5 * this->get_acceleration().get_xComponent() * time * time,
        this->get_precisePosition().get_yPosition() +
            this->get_velocity().get_yComponent() * time +
            0.5 * this->get_acceleration().get_yComponent() * time * time));

    this->set_velocity(
        phy::Vector::sum(this->get_velocity(),
                         Vector(this->get_acceleration().get_magnitude() * time,
                                this->get_acceleration().get_direction())));
  }
}
