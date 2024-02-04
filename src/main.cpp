
#include "ps2.h"
#include "vga.h"

struct MultibootInfo {

};


// visib pr asm
extern "C"
void megamimOS_cpp(const MultibootInfo& info);


void megamimOS_cpp(const MultibootInfo& info) {
    uint8_t* vga = (uint8_t*)0xb8000;
    vga::clearBuffer();

    // o k ou
    ps2::readData();

    while (!ps2::isOutputFull()) {
        ps2::pause();
    }

    uint8_t data = ps2::readData();

    vga[0] = 'm';
    vga[1] = (uint8_t)vga::Color::Immaculate;
    vga[2] = 'e';
    vga[3] = (uint8_t)vga::Color::Immaculate;
    vga[4] = 'g';
    vga[5] = (uint8_t)vga::Color::Immaculate;
    vga[6] = 'a';
    vga[7] = (uint8_t)vga::Color::Immaculate;
    vga[8] = 'm';
    vga[9] = (uint8_t)vga::Color::Immaculate;
    vga[10] = 'i';
    vga[11] = (uint8_t)vga::Color::Immaculate;
    vga[12] = 'm';
    vga[13] = (uint8_t)vga::Color::Immaculate;
    vga[14] = 'O';
    vga[15] = (uint8_t)vga::Color::Immaculate;
    vga[16] = 'S';
    vga[17] = (uint8_t)vga::Color::Immaculate;
    vga[20] = vga::Char::Heart;
    vga[21] = (uint8_t)vga::Color::Cherry;
}