#include <iostream>
#include <fstream>
#include "h/Emulator.hpp"

#include <iostream>
#include <SDL3/SDL.h>
#include "h/Emulator.hpp"

const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 144;
const int SCALE = 4;

// DMG (original Game Boy) color palette
const uint32_t DMG_PALETTE[4] = {
        0xFF9BBC0F,  // Lightest (white)
        0xFF8BAC0F,  // Light gray
        0xFF306230,  // Dark gray
        0xFF0F380F   // Darkest (black)
};
const uint32_t BW_PALETTE[4] = {
        0xFFFFFFFF,  // White
        0xFFAAAAAA,  // Light gray
        0xFF555555,  // Dark gray
        0xFF000000   // Black
};
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <rom_file>" << std::endl;
        return 1;
    }

    if (! SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
            "GB Emulator",
            SCREEN_WIDTH * SCALE,
            SCREEN_HEIGHT * SCALE,
            0
    );

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            SCREEN_WIDTH,
            SCREEN_HEIGHT
    );

    if (!texture) {
        std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Emulator emulator(argv[1]);
    emulator.bootEmu();

    bool running = true;
    SDL_Event event;
    uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];

    std::cout << "Emulator started.   Press ESC to quit." << std::endl;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
                bool pressed = (event.type == SDL_EVENT_KEY_DOWN);

                // Get current joypad state
                static uint8_t joypad = 0xFF;


                switch (event.key.key) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;

                        // D-pad
                    case SDLK_RIGHT:
                        if (pressed) joypad &= ~0x01; else joypad |= 0x01;
                        break;
                    case SDLK_LEFT:
                        if (pressed) joypad &= ~0x02; else joypad |= 0x02;
                        break;
                    case SDLK_UP:
                        if (pressed) joypad &= ~0x04; else joypad |= 0x04;
                        break;
                    case SDLK_DOWN:
                        if (pressed) joypad &= ~0x08; else joypad |= 0x08;
                        break;

                        // Buttons
                    case SDLK_Z:  // A button
                        if (pressed) joypad &= ~0x10; else joypad |= 0x10;
                        break;
                    case SDLK_X:  // B button
                        if (pressed) joypad &= ~0x20; else joypad |= 0x20;
                        break;
                    case SDLK_SPACE:  // Select
                        if (pressed) joypad &= ~0x40; else joypad |= 0x40;
                        break;
                    case SDLK_RETURN:  // Start
                        if (pressed) joypad &= ~0x80; else joypad |= 0x80;
                        break;
                }

                emulator. bus->setJoypadState(joypad);
            }
        }

        // Run one frame worth of cycles
        const int CYCLES_PER_FRAME = 70224;
        int frame_cycles = 0;

        while (frame_cycles < CYCLES_PER_FRAME) {
            int cycles = emulator.cpu->cycle();
            emulator.ppu->run(cycles);
            frame_cycles += cycles;
        }

        if (emulator.ppu->frame_ready) {
            emulator.ppu->frame_ready = false;

            // Convert PPU framebuffer to SDL pixels
            for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
                uint8_t color = emulator.ppu->framebuffer[i];
                pixels[i] = DMG_PALETTE[color & 0x03];
            }

            // Update texture and render
            SDL_UpdateTexture(texture, nullptr, pixels, SCREEN_WIDTH * sizeof(uint32_t));
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, texture, nullptr, nullptr);
            SDL_RenderPresent(renderer);

            SDL_Delay(16);  // ~60 FPS
        }
    }

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
////---- Gameboy Doctor Blargg CPU instruction testing.
//int main() {
//    // Use a basic test ROM first (e.g., cpu_instrs/individual/01-special.gb)
//    Emulator emulator = Emulator("C:\\Users\\akith\\CLionProjects\\GBEmulator\\ROMS\\02-interrupts.gb");
//    emulator.bootEmu();
//
//    // Redirect cout to file
//    std::ofstream logFile("emulator_log.txt");
//    std::streambuf* coutBuf = std::cout.rdbuf();
//    std::cout.rdbuf(logFile. rdbuf());
//
//    // Run for a limited number of instructions
//    const int MAX_INSTRUCTIONS = 10000000;
//
//    for (int i = 0; i < MAX_INSTRUCTIONS; i++) {
//        emulator.cpu->cycle();
//
//        // if (emulator.cpu->isHalted()) break;
//    }
//
//    // Restore cout
//    std::cout.rdbuf(coutBuf);
//    logFile.close();
//
//    std::cout << "Log written to emulator_log.txt" << std::endl;
//    return 0;
//}