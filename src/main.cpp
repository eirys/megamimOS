namespace vga {
    #define VGA_BUFFER ((unsigned char*)0xB8000)

    unsigned int cursor_x;
    unsigned int cursor_y;

    enum class Color: unsigned char {
        Carbon = 0x0,
        Marine = 0x1,
        Grass = 0x2,
        Teal = 0x3,
        Crimson = 0x4,
        Grape = 0x5,
        Poop = 0x6,
        Cloud = 0x7,
        Ash = 0x8,
        Indigo = 0x9,
        Chartreuse = 0xA,
        Sky = 0xB,
        Cherry = 0xC,
        Barbie = 0xD,
        Daffodil = 0xE,
        Immaculate = 0xF
    };

    struct Char {
        char inner;

        Char(char inner) : inner(inner) {}

        enum: char {
            Heart = 3,
            Diamond = 4,
        };

        explicit operator char() const {
            return inner;
        }
    };

    void putchar(Char character, int x, int y) {
        VGA_BUFFER[2 * (y * 80 + x)] = (char)character;
    }
}

struct MultibootInfo {

};

extern "C" void megamimOS_cpp(const MultibootInfo& info);


void megamimOS_cpp(const MultibootInfo& info) {
    char *vga =  (char*) 0xb8000;

    for (int i = 0; i < 2 * 80 * 25; i++) {
        vga[i] = 0;
    }

    vga[0] = 'm';
    vga[1] = 0x0f;
    vga[2] = 'e';
    vga[3] = 0x0f;
    vga[4] = 'g';
    vga[5] = 0x0f;
    vga[6] = 'a';
    vga[7] = 0x0f;
    vga[8] = 'm';
    vga[9] = 0x0f;
    vga[10] = 'i';
    vga[11] = 0x0f;
    vga[12] = 'm';
    vga[13] = 0x0f;
    vga[14] = 'O';
    vga[15] = 0x0f;
    vga[16] = 'S';
    vga[17] = 0x0f;
    vga[20] = vga::Char::Heart;
    vga[21] = (unsigned char)vga::Color::Cherry;

    // vga::Char('m', vga::Color::White).put(12, 12);
    // putchar()
}