#![no_std]
#![no_main]

#[panic_handler]
fn lol(_: &core::panic::PanicInfo) -> ! {
    loop {}
}

/// The current state of the state machine.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum State {
    /// The state machine is in the neutral state. No sequence of scancode has been
    /// generated yet.
    Neutral,
    /// The E0 escape code has been received.
    E0,
}

/// Contains the state required to convert scan-codes into text.
pub struct Qwerty {
    left_shift: bool,
    right_shift: bool,
    left_control: bool,
    right_control: bool,
    caps_lock: bool,
    left_alt: bool,
    right_alt: bool,
    num_lock: bool,

    /// The current state of the state machine.
    state: State,
}

impl Qwerty {
    /// Returns a new instance of the [`Qwerty`] struct.
    pub const fn new() -> Self {
        Self {
            left_shift: false,
            right_shift: false,
            left_control: false,
            right_control: false,
            caps_lock: false,
            left_alt: false,
            right_alt: false,
            num_lock: false,

            state: State::Neutral,
        }
    }

    #[inline]
    pub fn shifted(&self) -> bool {
        self.left_shift || self.right_shift
    }

    #[inline]
    pub fn control(&self) -> bool {
        self.left_control || self.right_control
    }

    #[inline]
    pub fn alt(&self) -> bool {
        self.left_alt || self.right_alt
    }

    #[inline]
    pub fn uppercase(&self) -> bool {
        self.caps_lock ^ self.shifted()
    }

    /// Advances the state of the state machine with a new scan-code. If a character can
    /// be produced, it is returned in a [`Some(_)`] variant.
    ///
    /// If no character could be produced, [`None`] is returned instead.
    pub fn advance(&mut self, scancode: u8) -> Option<char> {
        use State::*;

        match (self.state, scancode) {
            // Continue escape sequences.
            (Neutral, 0xE0) => {
                self.state = E0;
                None
            }
            // Update modifiers.
            (Neutral, 0x2A) => {
                self.left_shift = true;
                None
            }
            (Neutral, 0xAA) => {
                self.left_shift = false;
                None
            }
            (Neutral, 0x36) => {
                self.right_shift = true;
                None
            }
            (Neutral, 0xB6) => {
                self.right_shift = false;
                None
            }
            (Neutral, 0x1D) => {
                self.left_control = true;
                None
            }
            (Neutral, 0x9D) => {
                self.left_control = false;
                None
            }
            (Neutral, 0x3A) => {
                self.caps_lock = !self.caps_lock;
                None
            }
            (E0, 0x1D) => {
                self.right_control = true;
                self.state = Neutral;
                None
            }
            (E0, 0x9D) => {
                self.right_control = false;
                self.state = Neutral;
                None
            }
            // Printable characters.
            (Neutral, 0x02) if !self.uppercase() => Some('1'),
            (Neutral, 0x02) if self.uppercase() => Some('!'),
            (Neutral, 0x03) if !self.uppercase() => Some('2'),
            (Neutral, 0x03) if self.uppercase() => Some('@'),
            (Neutral, 0x04) if !self.uppercase() => Some('3'),
            (Neutral, 0x04) if self.uppercase() => Some('#'),
            (Neutral, 0x05) if !self.uppercase() => Some('4'),
            (Neutral, 0x05) if self.uppercase() => Some('$'),
            (Neutral, 0x06) if !self.uppercase() => Some('5'),
            (Neutral, 0x06) if self.uppercase() => Some('%'),
            (Neutral, 0x07) if !self.uppercase() => Some('6'),
            (Neutral, 0x07) if self.uppercase() => Some('^'),
            (Neutral, 0x08) if !self.uppercase() => Some('7'),
            (Neutral, 0x08) if self.uppercase() => Some('&'),
            (Neutral, 0x09) if !self.uppercase() => Some('8'),
            (Neutral, 0x09) if self.uppercase() => Some('*'),
            (Neutral, 0x0A) if !self.uppercase() => Some('9'),
            (Neutral, 0x0A) if self.uppercase() => Some('('),
            (Neutral, 0x0B) if !self.uppercase() => Some('0'),
            (Neutral, 0x0B) if self.uppercase() => Some(')'),
            (Neutral, 0x0C) if !self.uppercase() => Some('-'),
            (Neutral, 0x0C) if self.uppercase() => Some('_'),
            (Neutral, 0x0D) if !self.uppercase() => Some('='),
            (Neutral, 0x0D) if self.uppercase() => Some('+'),
            (Neutral, 0x10) if !self.uppercase() => Some('q'),
            (Neutral, 0x10) if self.uppercase() => Some('Q'),
            (Neutral, 0x11) if !self.uppercase() => Some('w'),
            (Neutral, 0x11) if self.uppercase() => Some('W'),
            (Neutral, 0x12) if !self.uppercase() => Some('e'),
            (Neutral, 0x12) if self.uppercase() => Some('E'),
            (Neutral, 0x13) if !self.uppercase() => Some('r'),
            (Neutral, 0x13) if self.uppercase() => Some('R'),
            (Neutral, 0x14) if !self.uppercase() => Some('t'),
            (Neutral, 0x14) if self.uppercase() => Some('T'),
            (Neutral, 0x15) if !self.uppercase() => Some('y'),
            (Neutral, 0x15) if self.uppercase() => Some('Y'),
            (Neutral, 0x16) if !self.uppercase() => Some('u'),
            (Neutral, 0x16) if self.uppercase() => Some('U'),
            (Neutral, 0x17) if !self.uppercase() => Some('i'),
            (Neutral, 0x17) if self.uppercase() => Some('I'),
            (Neutral, 0x18) if !self.uppercase() => Some('o'),
            (Neutral, 0x18) if self.uppercase() => Some('O'),
            (Neutral, 0x19) if !self.uppercase() => Some('p'),
            (Neutral, 0x19) if self.uppercase() => Some('P'),
            (Neutral, 0x1A) if !self.uppercase() => Some('['),
            (Neutral, 0x1A) if self.uppercase() => Some('{'),
            (Neutral, 0x1B) if !self.uppercase() => Some(']'),
            (Neutral, 0x1B) if self.uppercase() => Some('}'),
            (Neutral, 0x2B) if !self.uppercase() => Some('\\'),
            (Neutral, 0x2B) if self.uppercase() => Some('|'),
            (Neutral, 0x1E) if !self.uppercase() => Some('a'),
            (Neutral, 0x1E) if self.uppercase() => Some('A'),
            (Neutral, 0x1F) if !self.uppercase() => Some('s'),
            (Neutral, 0x1F) if self.uppercase() => Some('S'),
            (Neutral, 0x20) if !self.uppercase() => Some('d'),
            (Neutral, 0x20) if self.uppercase() => Some('D'),
            (Neutral, 0x21) if !self.uppercase() => Some('f'),
            (Neutral, 0x21) if self.uppercase() => Some('F'),
            (Neutral, 0x22) if !self.uppercase() => Some('g'),
            (Neutral, 0x22) if self.uppercase() => Some('G'),
            (Neutral, 0x23) if !self.uppercase() => Some('h'),
            (Neutral, 0x23) if self.uppercase() => Some('H'),
            (Neutral, 0x24) if !self.uppercase() => Some('j'),
            (Neutral, 0x24) if self.uppercase() => Some('J'),
            (Neutral, 0x25) if !self.uppercase() => Some('k'),
            (Neutral, 0x25) if self.uppercase() => Some('K'),
            (Neutral, 0x26) if !self.uppercase() => Some('l'),
            (Neutral, 0x26) if self.uppercase() => Some('L'),
            (Neutral, 0x27) if !self.uppercase() => Some(';'),
            (Neutral, 0x27) if self.uppercase() => Some(':'),
            (Neutral, 0x28) if !self.uppercase() => Some('\''),
            (Neutral, 0x28) if self.uppercase() => Some('"'),
            (Neutral, 0x29) if !self.uppercase() => Some('`'),
            (Neutral, 0x29) if self.uppercase() => Some('~'),
            (Neutral, 0x2C) if !self.uppercase() => Some('z'),
            (Neutral, 0x2C) if self.uppercase() => Some('Z'),
            (Neutral, 0x2D) if !self.uppercase() => Some('x'),
            (Neutral, 0x2D) if self.uppercase() => Some('X'),
            (Neutral, 0x2E) if !self.uppercase() => Some('c'),
            (Neutral, 0x2E) if self.uppercase() => Some('C'),
            (Neutral, 0x2F) if !self.uppercase() => Some('v'),
            (Neutral, 0x2F) if self.uppercase() => Some('V'),
            (Neutral, 0x30) if !self.uppercase() => Some('b'),
            (Neutral, 0x30) if self.uppercase() => Some('B'),
            (Neutral, 0x31) if !self.uppercase() => Some('n'),
            (Neutral, 0x31) if self.uppercase() => Some('N'),
            (Neutral, 0x32) if !self.uppercase() => Some('m'),
            (Neutral, 0x32) if self.uppercase() => Some('M'),
            (Neutral, 0x33) if !self.uppercase() => Some(','),
            (Neutral, 0x33) if self.uppercase() => Some('<'),
            (Neutral, 0x34) if !self.uppercase() => Some('.'),
            (Neutral, 0x34) if self.uppercase() => Some('>'),
            (Neutral, 0x35) if !self.uppercase() => Some('/'),
            (Neutral, 0x35) if self.uppercase() => Some('?'),
            // Non-printable keys
            (Neutral, 0x39) => Some(' '),
            (Neutral, 0x1C) => Some('\n'),
            (Neutral, 0x0E) => Some('\x08'),
            (Neutral, 0x0F) => Some('\t'),
            _ => None,
        }
    }
}

static mut QWERTY: Qwerty = Qwerty::new();

#[no_mangle]
pub extern "C" fn qwerty_advance(scancode: u8) -> u8 {
    unsafe {
        match QWERTY.advance(scancode) {
            Some(c) => c as u8,
            None => 0,
        }
    }
}
