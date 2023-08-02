# A first Raytracer

<p align=center>
  <img src="https://github.com/JinFrx/first-raytracer/blob/main/3d_engine_ray_tracing.jpg" alt="showcase image" style="width: 650px; max-width: 100%; height: auto" title="Click to enlarge picture" />
</p>

<p align=center><i>Render made with this Raytracer.</i></p>

## Description

*FR*

Projet réalisé dans le cadre universitaire (2021).

Un Raytracer simple (moteur de rendu 3D par lancé de rayons) codé en C++ sur CPU.

L'objectif du projet était d'apprendre et d'implémenter étape par étape la méthode de rendu par lancé de rayons, ainsi que divers algorithmes raytracing-friendly.

Le projet a commencé sur une base de code simple permettant d'avoir une "ligne directrice" et s'est complexifié au fur et à mesure des implémentations.
Cette base de code comprenait un point d'entrée de programme, des appels à des librairies utilitaires (notamment *glm* pour l'algèbre linéaire et *assimp* pour l'importation de modèles géométriques), ainsi que quelques entêtes de classes.

Le rendu est effectué dans un buffer de texture, exportée au format .jpg. 

Différents aspects et algorithmes ont été approchés :

- Camera positionnable et orientable; Projection perspective
- Lancé de rayons conventionnel; Intersection rayon-géometrie analytique (Sphere, Plan) et rayon-maillage (*Lapin de Stanford* et autres)
- *Sphere-tracing*; Intersection rayon-surface implicite (Tore)
- Intégrateurs pour *Point-light* et *Quad-light*
- Ombre douces via *Quad-light*
- Illumination locale (BRDF et Matériaux) : modèles empiriques (*Lambert*, *Phong*, *Blinn-Phong*), modèles micro-facettes (*Cook-Torrance*, *Oren-Nayar*), miroir et transparence
- Antialiasing simple via distribution stochastique de multiples rayons par pixel
- Optimisation du rendu : accélération via une *structure BVH* et des directives *OpenMP*

---

*EN*

Project made for study purposes (2021).

A simple Raytracer coded in C++ on CPU.

The main goal of such project was to learn and build step by step a conventional Raytracer, starting from a basis in order to give the student a guideline (basically an entry point to the program, some starting headers and finally some calls to utilities libraries like *glm* or *assimp*).

Render is done inside a texture buffer, then outputted to a .jpg image.

Several aspects and algorithms were approached:

- Camera with translation and orientation; Perspective projection
- Raytracing algorithm; Ray intersection with analytic geometry (Sphere, Plane) or meshes (*Stanford Bunny* and others)
- *Sphere-tracing*; Ray intersection with implicit surfaces (Tore)
- Integrators for *Point-light* and *Quad-light*
- Soft shadows through *Quad-light*
- Local illumination (BRDF and Materials): *Lambert*, *Phong*, *Blinn-Phong*, *Cook-Torrance*, *Oren-Nayar*, mirror effect and transparency effect
- Simple antialiasing by randomly distributing rays per pixel
- Rendering optimization: acceleration through *BVH structure* for ray-mesh intersection

<!-- OLD DESCRIPTION
## Final project scene

Several things to emphasize in this scene:

- Multiple light sources, including one that isn't out of frame
- Soft cast shadows: use of quad-lights
- The Stanford bunny, the bust and two spheres are meshes
- One sphere is described analytically, like planes around objects
- The torus is an implicit surface
- Multiple visible materials of different models: Blinn-Phong, Oren-Nayar and Cook-Torrance
- Reflection and refraction: perfect mirror plane to the left of the bunny, perfect mirror torus and transparent sphere on top of the bust
- Antialiasing: 32 randoms rays per pixel
-->
