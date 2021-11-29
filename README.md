# Moteur 3D Ray-tracing

## Description

Ce projet existe dans le cadre d'un projet universitaire (2021).

Le code est situé dans la branche master.

## Resultat du projet

<p align=center>
  <img src=https://drive.google.com/file/d/1BgD3N7ZkAOllrWsLTQXhvHeUNv6PcUdB/view?usp=sharing alt="3d_engine_ray_tracing.jpg" />
</p>

Plusieurs éléments sont à noter sur la mise en scène :
- Différentes sources de lumières, dont une qui n'est pas hors-champ
- Ombres portées douces, utilisation de quad-lights
- Anti-alliassage : distribution de rayons aléatoires par pixel
- Le lapin de Stanford, le buste et deux sphères sont des maillages
- Une des sphères est décrite analytiquement et le tore est une surface implicite
- Différents matériaux mis en scène : Blinn-Phong, Oren-Nayar et Cook-Torrance
- Réflexion et réfraction : plan mirroir à gauche du lapin, tore mirroir et sphère au dessus du buste transparente
