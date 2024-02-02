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



class Char {
private:
    char inner;

public:
    /* ---------------------------------------------------------------------- */
    /*                                  ENUMS                                 */
    /* ---------------------------------------------------------------------- */

    enum: char {
        Heart = 3,
        Diamond = 4,
    };

    /* ---------------------------------------------------------------------- */
    /*                                 METHODS                                */
    /* ---------------------------------------------------------------------- */

    Char(char inner) : inner(inner) {}

    /* ---------------------------------------------------------------------- */

    explicit operator char() const {
        return inner;
    }

};

/* -------------------------------------------------------------------------- */
/*                                    UTILS                                   */
/* -------------------------------------------------------------------------- */

inline
void clearBuffer() {
    for (int i = 0; i < 2 * 80 * 25; i++) {
        VGA_BUFFER[i] = 0;
    }
}

inline
void putchar(Char character, int x, int y, Color color = Color::Immaculate) {
    VGA_BUFFER[2 * (y * 80 + x)] = (char)character;
    VGA_BUFFER[2 * (y * 80 + x) + 1] = (char)color;
}

inline
void putString(const char* string, int x, int y, Color color = Color::Immaculate) {
    for (int i = 0; string[i] != 0; i++) {
        putchar(string[i], x + i, y, color);
    }
}

} // namespace vga

struct MultibootInfo {

};

extern "C"
void megamimOS_cpp(const MultibootInfo& info);

void megamimOS_cpp(const MultibootInfo& info) {
    char* vga = (char*)0xb8000;

    vga::clearBuffer();

    vga[0] = 'm';
    vga[1] = (unsigned char)vga::Color::Immaculate;
    vga[2] = 'e';
    vga[3] = (unsigned char)vga::Color::Immaculate;
    vga[4] = 'g';
    vga[5] = (unsigned char)vga::Color::Immaculate;
    vga[6] = 'a';
    vga[7] = (unsigned char)vga::Color::Immaculate;
    vga[8] = 'm';
    vga[9] = (unsigned char)vga::Color::Immaculate;
    vga[10] = 'i';
    vga[11] = (unsigned char)vga::Color::Immaculate;
    vga[12] = 'm';
    vga[13] = (unsigned char)vga::Color::Immaculate;
    vga[14] = 'O';
    vga[15] = (unsigned char)vga::Color::Immaculate;
    vga[16] = 'S';
    vga[17] = (unsigned char)vga::Color::Immaculate;
    vga[20] = vga::Char::Heart;
    vga[21] = (unsigned char)vga::Color::Cherry;
}