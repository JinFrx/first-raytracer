# 3D Ray-tracing Engine

## Description

A 3D Ray-tracing engine coded in C++, for a university project purpose (2021).

The code is located in master branch.

## Final project scene

<p align=center>
  <a href="https://drive.google.com/uc?export=view&id=1BgD3N7ZkAOllrWsLTQXhvHeUNv6PcUdB">
    <img src="https://drive.google.com/uc?export=view&id=1BgD3N7ZkAOllrWsLTQXhvHeUNv6PcUdB" alt="3d_engine_ray_tracing.jpg" style="width: 650px; max-width: 100%; height: auto" title="Click to enlarge picture" />
  </a>
</p>

Several things to emphasize in this scene:
- Multiple light sources, including one off-screen.
- Soft cast shadows, use of quad-lights.
- Antialiasing: randomly distributed rays per pixel
- The Stanford bunny, the bust and two spheres are meshes
- One sphere is described analytically, like planes around objects
- The torus is an implicit surface
- Multiple visible materials of different models: Blinn-Phong, Oren-Nayar and Cook-Torrance
- Reflection and refraction: perfect mirror plane to the left of the bunny, perfect mirror torus and transparent sphere on top of the bust
