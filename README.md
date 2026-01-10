# Game Boy Emulator

A Game Boy (DMG) emulator written in C++ with SDL3, capable of running commercial games like Tetris and Dr. Mario.

## 🎮 Demo

https://github.com/user-attachments/assets/d50db1fe-ee7e-43c7-9979-e93907eaa4ce

---

## ✨ Features

- **Full Sharp LR35902 CPU** - All 512 opcodes (including CB-prefixed)
- **Complete PPU** - Background, window, and sprite rendering with scrolling
- **Timer System** - DIV, TIMA, TMA, TAC with interrupts
- **Interrupt Handling** - VBlank, STAT, Timer, Joypad
- **DMA Transfers** - Fast OAM copying
- **Joypad Input** - Keyboard controls
- **Multiple Palettes** - DMG, B&W, GBP, custom themes

---

## 🔧 What's Implemented

### ✅ CPU & Memory
- All 8/16-bit arithmetic, logic, load/store, jump, call, return, bit operations
- Interrupt handling (IME, IE, IF)
- Full memory map (ROM, VRAM, RAM, OAM, I/O, HRAM)

### ✅ Timer
- DIV, TIMA, TMA, TAC registers
- Timer overflow interrupts

### ✅ PPU
- Background rendering with SCX/SCY scrolling
- Window layer with WX/WY positioning
- Sprites (8x8, 8x16, flip, priority, palettes)
- 10 sprites per scanline
- VRAM/OAM access restrictions

### ✅ Accuracy Improvements
- DMA transfers (0xFF46)
- LCD enable/disable behavior
- Proper STAT interrupts
- Memory access restrictions during PPU modes

### ✅ Input
- Joypad support with interrupt

---

## 🎮 Compatibility

**✅ Working:** Tetris, Dr. Mario  
**⚠️ Issues:** Golf, Alleyway 
**❌ Needs MBC:** Pokémon, Super Mario Land, Zelda, Kirby's Dream Land 2

Currently supports **MBC0 only** (32KB games, no banking)

---

## 🛠️ Building

### Prerequisites
- C++17 compiler
- CMake 3.10+
- SDL3

### Ubuntu/Debian
```bash
sudo apt-get install build-essential cmake libsdl3-dev
```

### macOS
```bash
brew install cmake sdl3
```

### Build
```bash
git clone https://github.com/yourusername/gb-emulator.git
cd gb-emulator
mkdir build && cd build
cmake ..
cmake --build .
./gb_emulator path/to/rom.gb
```

---

## 🎮 Controls

| Game Boy | Keyboard |
|----------|----------|
| D-Pad    | Arrow Keys |
| A        | Z |
| B        | X |
| Start    | Enter |
| Select   | Space |
| Quit     | ESC |

**Palettes:** Press 1-4 to switch color schemes

---

## 🔬 Technical Details

- **CPU:** Sharp LR35902 @ 4.194304 MHz
- **Display:** 160x144 @ 59.7 Hz
- **Scanline:** 456 dots (OAM:  80, Draw: 172, HBlank: 204)
- **Frame:** 70224 dots (~16.74 ms)

### Memory Map
```
0x0000-0x7FFF : ROM (32 KB)
0x8000-0x9FFF : VRAM (8 KB)
0xA000-0xBFFF : External RAM
0xC000-0xDFFF :  WRAM (8 KB)
0xFE00-0xFE9F : OAM
0xFF00-0xFF7F : I/O Registers
0xFF80-0xFFFE : HRAM
0xFFFF        : IE Register
```

---

## 📚 Resources

**Documentation:**
- [Pan Docs](https://gbdev.io/pandocs/) - GB technical reference
- [GB CPU Manual](http://marc.rawer.de/Gameboy/Docs/GBCPUman. pdf) - Instruction set
- [TCAGBD](https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf) - Timing info

**Test ROMs:**
- [Blargg's Tests](https://github.com/retrio/gb-test-roms) - CPU tests
- [mooneye-gb](https://github.com/Gekkio/mooneye-gb) - Hardware tests
- [DMG Acid2](https://github.com/mattcurrie/dmg-acid2) - PPU test

**Tools:**
- [BGB](https://bgb.bircd.org/) - Debugger
- [RGBDS](https://rgbds.gbdev.io/) - Assembler/linker
- [GBDev](https://gbdev.io/) - Community hub

---

## 🚀 Future Work

### High Priority
- [ ] MBC1/3/5 support (enables most commercial games)
- [ ] Save states
- [ ] Battery-backed RAM

### Medium Priority
- [ ] Audio (APU) - 4 sound channels
- [ ] Improved timing accuracy
- [ ] Debugger (breakpoints, memory viewer)

### Low Priority
- [ ] Game Boy Color support
- [ ] Serial link cable emulation
- [ ] GUI improvements

---

## 🐛 Known Issues

- Golf & Alleyway display blank screen
- Some timing inaccuracies
- Minor sprite priority issues

---

## 📄 License

MIT License - See LICENSE file

---

## 👤 Author

**akithetsar**
- GitHub: [@akithetsar](https://github.com/akithetsar)

---

## 🙏 Acknowledgments

- Pan Docs for documentation
- Imran Nazar's GB emulation series
- GBDev community
- Test ROM authors

---

**Built with ❤️ and lots of debugging**
