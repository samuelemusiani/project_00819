/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Peronese Lorenzo #0001081726
*
* chunk.cpp: Implementation of the Chunk class
*/

#include "chunk.hpp"

void Chunk::add_platform(phy::Point pos, int len)
{
    Platform p = Platform(pos,len);
    this->platforms.push_back(p);
}

bool Chunk::is_there_a_platform(phy::Point pos){
    //true if there is a platform, otherwise false
    for(int i=0;i<this->platforms.size();i++){
        if(pos.get_yPosition()==platforms[i].get_position().get_yPosition())
            if(pos.get_xPosition() >= this->platforms[i].get_position().get_xPosition() && pos.get_xPosition() <= (this->platforms[i].get_position().get_xPosition()) + this->platforms[i].get_length()-1)
                return true;
    }
    return false;
}

/* This method return a pointer to an array of Platforms in which are stored all the platforms that are in the current Chunk.
 * To get this pointer you first need to instantiate a Map object, then you can use the method get_chunk(...) to get
 * the desired Chunk,and then you can call the get_platforms() method. */
nostd::vector<Platform> Chunk::get_platforms()
{
    return this->platforms;
}
