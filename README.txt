Project 2 - for CS559
By Nik Ingrassia and Jackson Reed

Renders a spaceship and mars model(imported from heightmap) in various camera modes

Controls:
- arrow keys or mouse move the camera in most modes (mouse wheel changes fov)
- arrow keys control ship in 3rd person mode
- Controls as in spec: F1 to go through modes, w to toggle wireframe, s to toggle starfield, x/esc to quit
- n toggles normals (debugging feature)
- f2 toggles between our phong and cel shader

Features:
- Cel shader in addition to phong shader
- Different phong shader (without specular) used for mars
- Stars randomized in size as well and have a parralaz effect when moving
- Can look up and down in first person mode
- Control handled in timer function to minimize delay