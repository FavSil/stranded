// #include "tile.h"

// Tile::Tile( int x, int y, int tileType, SDL_Rect *gTile )
// {
//     //Get the offsets
//     mBox.x = x;
//     mBox.y = y;

//     //Set the collision box
//     mBox.w = Globals::tileWidth;
//     mBox.h = Globals::tileHeight;

//     //Get the tile type
//     mType = tileType;
// }

// void Tile::render( SDL_Rect& camera )
// {
//     //If the tile is on screen
//     if( checkCollision( Globals::camera, mBox ) )
//     {
//         //Show the tile
//         Globals::gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &Globals::gTileClips[ mType ] );
//     }
// }

// int Tile::getType()
// {
//     return mType;
// }

// SDL_Rect Tile::getBox()
// {
//     return mBox;
// }

// bool Tile::checkCollision( SDL_Rect a, SDL_Rect b )
// {
//     //The sides of the rectangles
//     int leftA, leftB;
//     int rightA, rightB;
//     int topA, topB;
//     int bottomA, bottomB;

//     //Calculate the sides of rect A
//     leftA = a.x;
//     rightA = a.x + a.w;
//     topA = a.y;
//     bottomA = a.y + a.h;

//     //Calculate the sides of rect B
//     leftB = b.x;
//     rightB = b.x + b.w;
//     topB = b.y;
//     bottomB = b.y + b.h;

//     //If any of the sides from A are outside of B
//     if( bottomA <= topB )
//     {
//         return false;
//     }

//     if( topA >= bottomB )
//     {
//         return false;
//     }

//     if( rightA <= leftB )
//     {
//         return false;
//     }

//     if( leftA >= rightB )
//     {
//         return false;
//     }

//     //If none of the sides from A are outside B
//     return true;
// }
