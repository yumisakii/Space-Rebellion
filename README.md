# Space Rebellion

## Overview
Space Rebellion is a 2D horizontal shoot 'em up built entirely from scratch to master low-level C++ fundamentals and the SFML multimedia library. The player navigates a spaceship through dynamic, timed enemy waves and environmental hazards, utilizing primary and cooldown-based explosive projectiles to survive.

## Project Context
- **Role:** Gameplay Programmer
- **Tech Stack:** C++ / SFML / Visual Studio 2022
- **Team Size:** 10 (6 Programmers, 4 Artists)
- **Development Time:** 2 weeks

## Core Systems & Architecture

### System A: Entity Memory Management & The Erase-Remove Idiom
Dynamically spawning and destroying hundreds of projectiles, enemies, and items per minute without causing memory leaks or segmentation faults in a custom C++ engine.
- **Data Structures:** All game objects inherit from a base Being class and are stored centrally in a `std::vector<std::shared_ptr<Being>>`.
- **Memory Management:** Heap allocation is handled safely using `std::make_shared` upon instantiation.
- **Cleanup Optimization:** Leverages the C++ `<algorithm>` library using the Erase-Remove idiom coupled with a lambda expression to sweep the vector and automatically deallocate any entity where `isDead()` returns true, ensuring stable memory footprints during heavy bullet-hell phases.

### System B: Frame-Independent Logic & Data-Driven Wave Spawning
Ensuring game mechanics, timers, and enemy behaviors execute consistently regardless of the user's hardware frame rate.
- **DeltaTime Integration:** The main game loop passes deltaTime to all update functions, decoupling physics from the render rate by tying player weapon cooldowns and entity velocities mathematically to dt.
- **Data-Driven Spawning:** The enemy wave manager reads from a predefined `std::vector<SpawnInfo>` struct, continuously comparing a globally accumulated GameTime against the struct's spawnTime with a strict epsilon tolerance to precisely trigger enemy instantiation.
- **Combat Math:** The special explosive bullet calculates radial distribution using trigonometry (cos and sin), splitting one projectile into eight perfectly spaced shrapnel bullets moving outward at equal velocities.

## Cross-Discipline Pipeline
- **Art Integration:** Collaborated directly with 4 artists from the G.Art team, defining technical constraints for 2D sprite sheets and individual assets to ensure compatibility with SFML's texture loading.
- **Procedural Scaling:** Managed the dynamic scaling and hit-box generation (AABB) of art assets purely through C++ code to maintain correct visual proportions regardless of the original file dimensions.
- **Version Control:** Maintained the centralized codebase utilizing Git/GitHub, resolving merge conflicts across a team of 6 programmers pushing parallel feature branches.

## Key Engineering Takeaways
- **Collision Detection:** Managed collision detection between hundreds of active entities by implementing a nested iteration loop (O(N^2)) to check intersections, which highlighted the immediate hardware limitations of raw unoptimized loop comparisons.
- **Architectural Lessons Learned:** If architecting this engine today, I would implement an Object Pool pattern for projectiles instead of allocating/destroying smart pointers every frame, and I would integrate a Quadtree for spatial partitioning to dramatically reduce the Big-O complexity of the collision checks.
