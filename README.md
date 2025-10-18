# so_long - 42 Vienna

[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

A 2D game to learn C and graphics with MiniLibX. Collect all items and reach the exit.

## Quick start

1. Ensure prerequisites (gcc, make, X11 dev headers).
2. Place a built MiniLibX at the project root (e.g., minilibx-linux/).
3. Build and run:

```bash
# build
make
# run
./so_long map/small_valid.ber
```

## Requirements

- Unix-like OS (Linux recommended)
- gcc, make
- X11 development headers (e.g., libx11-dev)

Note: Project depends on MiniLibX (e.g., https://github.com/42paris/minilibx-linux).

## Project layout

```
/
├─ minilibx-linux/
├─ libft/
├─ source/
├─ img/
├─ map/
└─ so_long
```

## Usage

```bash
./so_long path/to/map.ber
```

Quit with ESC or window close.

## Controls

- W / A / S / D — move
- ESC — quit

## Map format

- Extension: .ber
- Rules:
  - Rectangular
  - Surrounded by walls (`1`)
  - Exactly 1 player `P`
  - Exactly 1 exit `E`
  - At least 1 collectible `C`
  - Floor: `0`

Example:

```
111111
1P0C01
100001
1C0E11
111111
```

Checklist:
- [ ] Rectangular
- [ ] Perimeter walls
- [ ] 1 `P`, 1 `E`, >=1 `C`
