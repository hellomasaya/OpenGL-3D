Assignment2
=========================

##Harshita Sharma

Install the development packages of the following libraries:
1. GLEW
2. GLFW3
3. GLM

**Run the code:**
  
  cd path/to/project
  mkdir build
  cd build
  cmake ..
  # Run from here after editing
  make
  ./graphics_asgn1
  
##Controls:

###Airplane Movement ::

- ​	**left** : turn left(yaw)
- ​	**right** : turn right(yaw)
- ​	**up** : move straight
- ​	**down** : move back
- ​	**A** : roll anticlockwise
- ​	**D** : roll clockwise
- ​	**W** : move up
- ​	**S** : move down.

###Views ::

- ​	**1** : follow-cam view
- ​	**2** : plane-view
- ​	**3** : top-view
- ​	**4** : tower-view

###Missile and Bomb ::

- ​	**M** : Throw missile
- ​	**G** : Throw bomb

###Checkpoints:

- 8 checkpoints to conquer.
- Arrow above checkpoint(visible from far) guides airplane.

###Enemies:

- ​	**Canons** : Throws fireballs and decreases fuel(-10)
- ​	**Parachutes** : Collision decreases fuel(-5)
- ​	**Volcano** : Collision ends game - NO FLYING ZONE

###Fuel-ups:

- Initial fuel: 60
- ​	**Fuel-up** : Diamond shaped(+10)
- ​	**Parachutes** : Collision with missile increases fuel(+2)
- ​	**Smoke Ring** : Collision increases fuel(+50)

###Dashboard:(BONUS)
- Altitute
- Fuel
- Checkpoints left
- Compass

###BONUS:
- Comapss
- Transparency
