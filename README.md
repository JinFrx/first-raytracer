# 3D Ray-tracing Engine

## Description

A 3D Ray-tracing engine coded in C++, as part of a university project (2021).

The main goal of such project was to implement step by step a simple conventional Ray-tracing engine, starting from a given initial code.

The starting code had contained the program entry point, utilities libraries includes, and few base classes headers in order to give the student a guideline.

Multiple aspects were approached:
- Camera and projection plane for perspective
- Ray-tracing algorithm and ray intersections with analytically described objects or meshes
- Integrators and two types of light sources: Point-light and Quad-light
- Soft shadows with Quad-lights
- BRDFs: simple models like Lambert and Blinn-Phong, and microfacets models like Oren-Nayar and Cook-Torrance models.
- Reflections and refractions
- Simple antialiasing with randomly distributed rays per pixel
- A BVH acceleration structure for ray-mesh intersections
- Implicit surfaces and Sphere-tracing

## Final project scene

<p align=center>
  <img src="https://github.com/JinFrx/3d-ray-tracing-engine/blob/main/3d_engine_ray_tracing.jpg" alt="showcase image" style="width: 650px; max-width: 100%; height: auto" title="Click to enlarge picture" />
</p>

Several things to emphasize in this scene:
- Multiple light sources, including one that isn't out of frame
- Soft cast shadows: use of quad-lights
- The Stanford bunny, the bust and two spheres are meshes
- One sphere is described analytically, like planes around objects
- The torus is an implicit surface
- Multiple visible materials of different models: Blinn-Phong, Oren-Nayar and Cook-Torrance
- Reflection and refraction: perfect mirror plane to the left of the bunny, perfect mirror torus and transparent sphere on top of the bust
- Antialiasing: 32 randoms rays per pixel
