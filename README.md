# 2048
A clone of the game 2048, written in C++20 using SDL3 for rendering.

## About
- Fully functional 2048 gameplay: tile movement, merging, score tracking etc.
- Scalable grid – the size of the playing field can be changed during the game
- Текстовый рендеринг через SDL3_ttf (шрифт JetBrains Mono)
- Адаптивная отрисовка под размер окна

### Building
```bash
mkdir build
cd build
cmake ..
cmake --build . -j($nproc)
./build/2048
```

## Deps
All additional dependencies will be automatically installed and built for your platform.

## Keys
| key | action |
|---------|------------------|
| W / $\uparrow$ | Up |
| S / $\downarrow$ | Down |
| A / $\leftarrow$ | Left |
| D / $\rightarrow$ | Right |
| R | Reset |
| I | Hints |
| P / Esc | Settings |
| N | Enlarge grid |
| M | Decrease grid |

## Structure
```
2048/
├── main.cpp              # entry point
├── game/                 # game logic
│   ├── Field.cpp/h
│   ├── Line.cpp/h 
│   └── Types.hpp 
├── sdl/                  # Rendering
│   ├── GameWindow.cpp/h
│   ├── TextRenderer.cpp/h
│   ├── Renderer.cpp/h
│   └── Button.cpp/
└── assets/
```

- `Tile` - tile's value (unsigned long long int), 0 = empty
- `Score` - player's score (unsigned long long int)
- Field is an alias for  `std::vector<Line>`, where `Line` was inherited from `std::vector<Tile>` and responsible for managing the tiles in a single column.
