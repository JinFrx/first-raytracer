# 3D Ray-tracing Engine

## Description

A 3D Ray-tracing engine coded in C++, made as part of a university project (2021).

## Final project scene

<p align=center>
  <img src="https://github.com/JinFrx/3d-ray-tracing-engine/blob/main/3d_engine_ray_tracing.jpg" alt="showcase image" style="width: 650px; max-width: 100%; height: auto" title="Click to enlarge picture" />
</p>

Several things to emphasize in this scene:
- Multiple light sources, including one that isn't out of frame.
- Soft cast shadows: use of quad-lights.
- Antialiasing: randomly distributed rays per pixel
- The Stanford bunny, the bust and two spheres are meshes
- One sphere is described analytically, like planes around objects
- The torus is an implicit surface
- Multiple visible materials of different models: Blinn-Phong, Oren-Nayar and Cook-Torrance
- Reflection and refraction: perfect mirror plane to the left of the bunny, perfect mirror torus and transparent sphere on top of the bust
