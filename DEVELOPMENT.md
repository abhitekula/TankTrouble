# Project Development

## What has been accomplished so far
* Integrated Box2d with OpenFrameworks.
* Created tank polygon.
* Made tank into a dynamic body so reacts appropriately to collisions.
* Made tank move and rotate properly with user input.

## Issues
* OpenFrameworks wrapper for Box2d does not behave the same as regular Box2d.
* Needed to use ofxBox2dPolygon instead of typical Box2d body because the body would not display on the screen.
* No draw method for Box2d body.
* Needed to convert tank's angle to vector
* Coordinate system does not start in bottom left corner which made it difficult to draw map and move in the correct direction.
* The direction the tank moved would not update while to key is pressed so if the angle of the tank changed while the forward key was pressed the tank would continue moving in whatever previous direction it was moving in.

## ToDo

* Create box around whole world so tank cannot leave the box.
* Create the actual maze and place it on the screen.
* Resize tank and elements of screen when windows is resized.
* Add other tank.
* Add audio and sound effects.
* Add missiles so tanks can fight each other.
