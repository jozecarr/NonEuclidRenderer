function: void [[ApplyGravity]](float deltaTime)

For each object in the [[World]]'s object vector, if a given object has the hasGravity property, decrease its downward velocity by 9.81, (deceleration). 
This is called every frame, applying the acceleration of 9.81ms<sup>-2</sup> in the downwards direction.
