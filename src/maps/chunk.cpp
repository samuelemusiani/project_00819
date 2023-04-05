#include "chunk.hpp"

Chunk::Chunk()
{
    this->usedPlatforms = 0;
}

void Chunk::add_platform(int x, int y, int len)
{
    if(this->usedPlatforms < MAX_PLATFORMS)
    {
        this->platforms[this->usedPlatforms].set_xPosition(x);
        this->platforms[this->usedPlatforms].set_yPosition(y);
        this->platforms[this->usedPlatforms].set_length(len);
        this->usedPlatforms++;
    }

}

bool Chunk::is_there_a_platform(int x, int y){
    //true if there is a platform, otherwise false
    for(int i=0;i<this->usedPlatforms;i++){
        if(y==Chunk::platforms[i].get_yPosition())
            if(x >= Chunk::platforms[i].get_xPosition() && x <= (Chunk::platforms[i].get_xPosition())+Chunk::platforms[i].get_length()-1)
                return true;
    }
    return false;
}

Platform* Chunk::get_platforms()    // use this function like this:
{                                   //      Platform* x;
    return Chunk::platforms;        //      x = Chunk::get_platforms({chunk_that_you_want})
}                                   // { x[i] will return the i element of the platform's array }
