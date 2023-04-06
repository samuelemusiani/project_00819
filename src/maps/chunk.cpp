#include "chunk.hpp"

Chunk::Chunk()
{
    this->usedPlatforms = 0;
}

Chunk::~Chunk()
{
    delete[] this->platforms;
    this->platforms=nullptr;
}

void Chunk::add_platform(phy::Point pos, int len)
{
    if(this->usedPlatforms < MAX_PLATFORMS)
    {
        this->platforms[this->usedPlatforms].set_position(pos);
        this->platforms[this->usedPlatforms].set_length(len);
        this->usedPlatforms++;
    }

}

bool Chunk::is_there_a_platform(phy::Point pos){
    //true if there is a platform, otherwise false
    for(int i=0;i<this->usedPlatforms;i++){
        if(pos.get_yPosition()==platforms[i].get_position().get_yPosition())
            if(pos.get_xPosition() >= this->platforms[i].get_position().get_xPosition() && pos.get_xPosition() <= (this->platforms[i].get_position().get_xPosition()) + this->platforms[i].get_length()-1)
                return true;
    }
    return false;
}

/* This method return a pointer to an array of Platforms in which are stored all the platforms that are in the current Chunk.
 * To get this pointer you first need to instantiate a Map object, then you can use the method get_chunk(...) to get
 * the desired Chunk,and then you can call the get_platforms() method. */
Platform* Chunk::get_platforms()
{
    return this->platforms;
}
