#include "chunk.hpp"

Chunk::Chunk()
{
    this->usedPlatforms = 0;
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

Platform* Chunk::get_platforms()    // use this function like this:
{                                   //      Map m;
    return this->platforms;         //      Platform* x;
}                                   //      x = m.Map::get_chunk({chunk_that_you_want}).Chunk::get_platforms({chunk_that_you_want})
                                    // { x[i] will return the i platform of the array }
