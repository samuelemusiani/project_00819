/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Musiani Samuele #0001069143
 *
 * precisePoint.cpp: Implementation of the phy::PrecisePoint class.
 */

#include "precisePoint.hpp"
#include <math.h>

phy::PrecisePoint::PrecisePoint() : PrecisePoint(0, 0) {}

phy::PrecisePoint::PrecisePoint(double x, double y) {
  this->set_xPosition(x);
  this->set_yPosition(y);
}

phy::PrecisePoint::PrecisePoint(phy::Point p) {
  this->set_xPosition(p.get_xPosition());
  this->set_yPosition(p.get_yPosition());
}

void phy::PrecisePoint::set_xPosition(double x) { this->posX = x; }

void phy::PrecisePoint::set_yPosition(double y) { this->posY = y; }

double phy::PrecisePoint::get_xPosition() { return this->posX; }

double phy::PrecisePoint::get_yPosition() { return this->posY; }

phy::Point phy::PrecisePoint::toPoint() {
  return phy::Point(round(this->get_xPosition()), round(this->get_yPosition()));
}
