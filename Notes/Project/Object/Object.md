The object class - as described in [[GameObject.h]] and [[GameObject.cpp]] - describes the "objects" in the world, being cuboids.
Objects have the following fields:
 - int objID = 0
 - vec3 objScale = {1, 1, 1}
 - vec3 objPosition = {0, 0, 0}
 - vec3 objRotation = {0, 0, 0} 
 - vec3 objVelocity = {0, 0, 0}
 - vec3 objAngVelocity = {0, 0, 0}
 - mat4 model = glm::mat4(1.0f)
 - Shader* shader
 - String texPath
 - [[ObjectProperties]] properties = {0, 0}

And functions:
 - void [[void UpdateModelMatrix()]]()
 - void [[SetPosition]](vec3 newPos)
 - void [[SetRotation]](vec3 newRot)
 - void [[SetScale]](vec3 newScl)
 - void [[Translate]](vec3 translation)
 - void [[Rotate]](vec3 rotation)
 - void [[Grow]](vec3 growth)
 - vector<vec3> GetVerticies() 
