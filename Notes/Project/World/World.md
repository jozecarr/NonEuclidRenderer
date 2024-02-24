Class for handling a "World", being a list of objects and some other world information. The files [[World.h]] and [[World.cpp]] describe this class.
 
 - vector<Object*> objects = {}
 - int objCount = 0;
 - float gravityStrength = -9.81f;
 
 - void [[AddObject]]([[Object]]* obj)
 - void [[Update]](float deltaTime)
 - void [[HandleCollisions]](float deltaTime)
 - void [[ApplyGravity]](float deltaTime)
