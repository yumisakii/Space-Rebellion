# Space Rebellion

## Overview
Space Rebellion is a 2D horizontal shoot 'em up built entirely from scratch to master low-level C++ fundamentals and the SFML multimedia library[cite: 11]. The player navigates a spaceship through dynamic, timed enemy waves and environmental hazards, utilizing primary and cooldown-based explosive projectiles to survive[cite: 11].

## Project Context
- **Role:** Gameplay Programmer[cite: 11]
- **Tech Stack:** C++ / SFML / Visual Studio 2022[cite: 11]
- **Team Size:** 10 (6 Programmers, 4 Artists)[cite: 11]
- **Development Time:** 2 weeks[cite: 11]

## Core Systems & Architecture

### System A: Entity Memory Management & The Erase-Remove Idiom
Dynamically spawning and destroying hundreds of projectiles, enemies, and items per minute without causing memory leaks or segmentation faults in a custom C++ engine[cite: 12].
- **Data Structures:** All game objects inherit from a base Being class and are stored centrally in a `std::vector<std::shared_ptr<Being>>`[cite: 12].
- **Memory Management:** Heap allocation is handled safely using `std::make_shared` upon instantiation[cite: 12].
- **Cleanup Optimization:** Leverages the C++ `<algorithm>` library using the Erase-Remove idiom coupled with a lambda expression to sweep the vector and automatically deallocate any entity where `isDead()` returns true, ensuring stable memory footprints during heavy bullet-hell phases[cite: 12].

### System B: Frame-Independent Logic & Data-Driven Wave Spawning
Ensuring game mechanics, timers, and enemy behaviors execute consistently regardless of the user's hardware frame rate[cite: 12].
- **DeltaTime Integration:** The main game loop passes deltaTime to all update functions, decoupling physics from the render rate by tying player weapon cooldowns and entity velocities mathematically to dt[cite: 12].
- **Data-Driven Spawning:** The enemy wave manager reads from a predefined `std::vector<SpawnInfo>` struct, continuously comparing a globally accumulated GameTime against the struct's spawnTime with a strict epsilon tolerance to precisely trigger enemy instantiation[cite: 12].
- **Combat Math:** The special explosive bullet calculates radial distribution using trigonometry (cos and sin), splitting one projectile into eight perfectly spaced shrapnel bullets moving outward at equal velocities[cite: 12, 13].

## Cross-Discipline Pipeline
- **Art Integration:** Collaborated directly with 4 artists from the G.Art team, defining technical constraints for 2D sprite sheets and individual assets to ensure compatibility with SFML's texture loading[cite: 13].
- **Procedural Scaling:** Managed the dynamic scaling and hit-box generation (AABB) of art assets purely through C++ code to maintain correct visual proportions regardless of the original file dimensions[cite: 13].
- **Version Control:** Maintained the centralized codebase utilizing Git/GitHub, resolving merge conflicts across a team of 6 programmers pushing parallel feature branches[cite: 13].

## Key Engineering Takeaways
- **Collision Detection:** Managed collision detection between hundreds of active entities by implementing a nested iteration loop (O(N^2)) to check intersections, which highlighted the immediate hardware limitations of raw unoptimized loop comparisons[cite: 13].
- **Architectural Lessons Learned:** If architecting this engine today, I would implement an Object Pool pattern for projectiles instead of allocating/destroying smart pointers every frame, and I would integrate a Quadtree for spatial partitioning to dramatically reduce the Big-O complexity of the collision checks[cite: 13].
