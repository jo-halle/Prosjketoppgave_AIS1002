# MazeGame

MazeGame er et 3D labyrintspill hvor spilleren må navigere gjennom en labyrint for å nå målet. Spillet bruker OpenGL for å vise labyrinten og spillerens bevegelse i sanntid. Dette prosjektet er skrevet i C++ og bruker Threepp-biblioteket for å håndtere 3D-grafikk.

## Funksjoner

- En tilfeldig generert labyrint med justerbare dimensjoner og kompleksitet.
- Bevegelse i sanntid med W, A, S og D-tastene.
- Mulighet for å starte, stoppe og tilbakestille spillet via et ImGui-grensesnitt.
- Visning av spilletid og en gratulasjonsmelding ved fullføring av labyrinten.

## Filstruktur

- `main.cpp`: Hovedfilen som setter opp scenen, kameraet og rendereren og starter spillet.
- `maze.cpp`: Implementasjonen av Maze-klassen som genererer og håndterer labyrinten.
- `game_imgui.cpp`: Implementasjonen av GameImGui-klassen som håndterer ImGui-grensesnittet for spillet.
- `game.cpp`: Implementasjonen av Game-klassen som håndterer spillets logikk og tilstand.
- `box.cpp`: Implementasjonen av Box-klassen som representerer spillerens boks i labyrinten.
- `texture_loader.hpp`: En hjelpeklasse for å laste inn teksturer til spillet.
- `maze.hpp`: Headerfilen for Maze-klassen.
- `game_imgui.hpp`: Headerfilen for GameImGui-klassen.
- `game.hpp`: Headerfilen for Game-klassen.
- `box.hpp`: Headerfilen for Box-klassen.
- `textures` Directory med bilde filer for tekstur i spillet

## Avhengigheter

- OpenGL
- GLFW
- GLEW
- GLM
- ImGui
- Threepp
