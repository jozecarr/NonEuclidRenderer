void [[HandleCollisions]](float deltaTime)

For every object, if it has some velocity and is collidable, check against every other collidable object using where each of them will be in the next frame to see if they will intersect after applying their velocities, and if they won't - apply the objects velocity - and if they will - set the velocity to 0.