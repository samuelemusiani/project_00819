#include "chunk.hpp"

Chunk::Chunk()
{
    this->usedPlatforms = 0;
}

void Chunk::add_platform(int x, int y, int len)
{
    if(this->usedPlatforms>MAX_PLATFORMS)
        printf("Too many platforms\n");
    else
    {
        this->platforms[this->usedPlatforms].set_xPosition(x);
        this->platforms[this->usedPlatforms].set_yPosition(y);
        this->platforms[this->usedPlatforms].set_length(len);
        this->usedPlatforms++;
    }

}