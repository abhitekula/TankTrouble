# Project Development

## What has been accomplished so far
* Integrated Box2d with OpenFrameworks.
* Created tank polygon.
* Made tank into a dynamic body so reacts appropriately to collisions.
* Made tank move and rotate properly with user input.
* Added second tank with controls with arrow keys
* Added Damping so when one tank hits the other they do not fly off forever.
* Finished adding boundary
* Made tank its own object
* Fixed tanks getting stuck inside each other
* Added tanks shooting missile
* Add collision detection of missile with other tank.
* Added score and FPS
* Added round reset
* Create the actual maze and place it on the screen.
* Add audio and sound effects.
* Add Pause Menu.
* Added 4 Powerups (Increased speed, Plus 3 Ammo, Increased Bullet Speed, Max Health)

## Solved Issues
* OpenFrameworks wrapper for Box2d does not behave the same as regular Box2d.
* Needed to use ofxBox2dPolygon instead of typical Box2d body because the body would not display on the screen.
* No draw method for Box2d body.
* Needed to convert tank's angle to vector
* Coordinate system does not start in bottom left corner which made it difficult to draw map and move in the correct direction.
* The direction the tank moved would not update while to key is pressed so if the angle of the tank changed while the forward key was pressed the tank would continue moving in whatever previous direction it was moving in.
* Second tank would not display on screen
* OFX_BOX2D_SCALE Factor exists which means 1 pixel in ofbox2d is different than 1 pixel on screen
* Figuring out how to extend classes in C++ properly, would get seg fault everytime I tried to make Tank its own class.
* Tanks are not centered on their center of mass.
* Sometimes tanks would get stuck together
* Bullet shape meant it did not bounce of walls properly
* Getting bullet to start at location of turret regardless of tanks current orientation.
* Shooting the bullet would register as a collision with the tank.
* Segfault when deleting bullet
* Sounds would be played even after round ends
* Maze would not triangulate properly so had to use ofxBox2dEdges instead
* Getting maze file to have multiple edges instead of 1 big edge
* Tanks would start inside each other
* Deleting the bullets that hit the tank would cause segfault
* Shooting when paused caused a segfault
* When powerups were removed they would stop showing up on screen but tanks would still hit them.
* Segfault after removing powerup.


## Unsolved Issues
* When the framerate is set to above the max refresh rate of the monitor everything in the game is much slower. (Temp fix: Keep fps to 30)
