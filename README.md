# 3D Renderer using Ray Tracing

<p align=center>
  <img src="https://github.com/JinFrx/first-raytracer/blob/main/3d_engine_ray_tracing.jpg" alt="showcase image" style="width: 650px; max-width: 100%; height: auto" title="Click to enlarge picture" />
</p>

<p align=center><i>Render made with this Raytracer.</i></p>

## Description

A fundamental software 3D renderer made in C++ using ray tracing technique.

This personal programming project is part of my student projects.

It was a long and complex project.
I learned so much through the implementation of it.

All that was given to me in the entire project was a starting codebase (to concentrate more on important things), and milestone guidelines in order to achieve the overall application.

By recalling the knowledge acquired in other courses coupled with intensive research on ways to achieve solutions, I made up my way at the end of my first Raytracer.
It was at the same time a good way to practice my C++.

Several theoretical points and technical aspects were addressed:

* Build a virtual grid on top of a moveable camera object for perspective projection to cast primary rays
* Implement traditional ray intersection to display various geometries (sphere, plane, triangles for meshes)
* Add Sphere tracing to achieve intersection with Implicit surfaces (tore)
* Implement a Quad light to compute Soft shadows
* Use Multisampling through Stochastic ray tracing to achieve simple Antialiasing
* Add multiple light models like empirical models (Lambert, Phong, Blinn-Phong), and light models based on microfacets (Cook-Torrance, Oren-Nayar) to compute Local illumination
* Add materials structures
* Add mirror and transparency effects
* Build a BVH structure to accelerate mesh rendering (the display of the triangles is a bit buggy though)

## Use

If you are interested to execute it, just:

* Clone the repo
* Run the VS solution `RT_ISICG_etu.sln`
* Inside VS, build and run the solution
* The output image will be stored inside the folder `results`

Camera object and application parameters can be modified inside `main.cpp`.

If you want to modify the scene content, just add new things in the definition of `Scene::init()` inside `scene.cpp`:

```c++
// Add a material to the scene to attach it later to any object
_addMaterial(new MyMaterial(<constructor_parameters>));

// Add an geometric object to the scene
_addObject(new MyObject(<constructor_parameters>));

// Load and add a mesh object to the scene from a given file
loadFileTriangleMesh("object_custom_name", DATA_PATH + "filename.ext", Vec3f(<position>), Vec3f(<scale>));

// Attach any instancied material to any instancied object
_attachMaterialToObject("material_name", "object_name");

// Add a light object to the scene
_addLight(new MyLight(<constructor_parameters>));
```

You will find every available type of scene objects in the source code under the folders `geometry`, `lights` and `materials`.

Here, you will also find what arguments you must pass to the constructors.

Every imported mesh file along with their material file must be under the folder `data`.
