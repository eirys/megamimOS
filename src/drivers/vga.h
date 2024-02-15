/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:38:11 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 01:41:50 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "core.h"

namespace vga {

/* -------------------------------------------- */
/*                   VGA PORTS                  */
/* -------------------------------------------- */

static constexpr const u16 CONTROL_PORT = 0x3D4;
static constexpr const u16 DATA_PORT = 0x3D5;

static constexpr const u8 WIDTH = 80;
static constexpr const u8 HEIGHT = 25;

class Char;

/**
 * @brief The VGA buffer, located at the RAM address 0xB8000.
*/
Char* const  BUFFER = (Char*)0xB8000;

/* -------------------------------------------- */

enum class Color: u8 {
    Carbon      = 0x00,
    Marine      = 0x01,
    Grass       = 0x02,
    Teal        = 0x03,
    Crimson     = 0x04,
    Grape       = 0x05,
    Poop        = 0x06,
    Cloud       = 0x07,
    Ash         = 0x08,
    Indigo      = 0x09,
    Chartreuse  = 0x0A,
    Sky         = 0x0B,
    Cherry      = 0x0C,
    Barbie      = 0x0D,
    Daffodil    = 0x0E,
    Immaculate  = 0x0F,

    First       = Carbon,
    Last        = Immaculate
};

class Char {
public:
    /* ---------------------------------------- */
    /*                   ENUMS                  */
    /* ---------------------------------------- */

    /**
     * @brief Every vga characters.
     * @note https://en.wikipedia.org/wiki/Code_page_437
     */
    enum: u8 {
        Empty           = 0x00,

        SmileyW         = 0x01,
        SmileyB         = 0x02,
        Heart           = 0x03,
        Diamond         = 0x04,
        Club            = 0x05,
        Spades          = 0x06,
        Bullet          = 0x07,
        BulletI         = 0x08,
        BulletW         = 0x09,
        BulletIW        = 0x0A,
        Male            = 0x0B,
        Female          = 0x0C,
        Music           = 0x0D,
        MusicS          = 0x0E,
        Sun             = 0x0F,

        TriangleR       = 0x10,
        TriangleL       = 0x11,
        ArrowUD         = 0x12,
        ExclamationD    = 0x13,
        Pilcrow         = 0x14,
        Section         = 0x15,
        RectangleB      = 0x16,
        ArrowUDB        = 0x17,
        ArrowU          = 0x18,
        ArrowD          = 0x19,
        ArrowR          = 0x1A,
        ArrowL          = 0x1B,
        RighAngle       = 0x1C,
        ArrowLR         = 0x1D,
        TriangleU       = 0x1E,
        TriangleD       = 0x1F,

        Space           = 0x20,
        Exclamation     = 0x21,
        Quote           = 0x22,
        Hash            = 0x23,
        Dollar          = 0x24,
        Percent         = 0x25,
        Ampersand       = 0x26,
        Apostrophe      = 0x27,
        ParenthesisL    = 0x28,
        ParenthesisR    = 0x29,
        Star            = 0x2A,
        Plus            = 0x2B,
        Comma           = 0x2C,
        Minus           = 0x2D,
        Dot             = 0x2E,
        Slash           = 0x2F,

        Colon           = 0x3A,
        SemiColon       = 0x3B,
        ChevronL        = 0x3C,
        Equal           = 0x3D,
        ChevronR        = 0x3E,
        Question        = 0x3F,

        At              = 0x40,

        BraceL          = 0x5B,
        Backslash       = 0x5C,
        BraceR          = 0x5D,
        Caret           = 0x5E,
        Underscore      = 0x5F,

        Grave           = 0x60,

        BracketL        = 0x7B,
        BrokenBar       = 0x7C,
        BracketR        = 0x7D,
        Tilde           = 0x7E,
        House           = 0x7F,

        CMCedilla       = 0x80,
        UUmlaut         = 0x81,
        EAcute          = 0x82,
        ACircumflex     = 0x83,
        AUmlaut         = 0x84,
        AGrave          = 0x85,
        ARing           = 0x86,
        Ccedilla        = 0x87,
        ECircumflex     = 0x88,
        EUmlaut         = 0x89,
        EGrave          = 0x8A,
        IUmlaut         = 0x8B,
        ICircumflex     = 0x8C,
        IGrave          = 0x8D,
        AMUmlaut        = 0x8E,
        AMRing          = 0x8F,

        EMAcute         = 0x90,
        AEDiphtong      = 0x91,
        AEMDiphtong     = 0x92,
        OCircumflex     = 0x93,
        OUmlaut         = 0x94,
        OGrave          = 0x95,
        UCircumflex     = 0x96,
        UGrave          = 0x97,
        YUmlaut         = 0x98,
        OMUmlaut        = 0x99,
        UMUmlaut        = 0x9A,
        Cent            = 0x9B,
        Pound           = 0x9C,
        Yen             = 0x9D,
        Peseta          = 0x9E,
        FWithHook       = 0x9F,

        AAcute          = 0xA0,
        IAcute          = 0xA1,
        OAcute          = 0xA2,
        UAcute          = 0xA3,
        NTilde          = 0xA4,
        NMTilde         = 0xA5,
        AOrdinal        = 0xA6,
        OOrdinal        = 0xA7,
        QuestionI       = 0xA8,
        LogicalNotR     = 0xA9,
        LogicalNot      = 0xAA,
        OneHalf         = 0xAB,
        OneFourth       = 0xAC,
        ExclamationI    = 0xAD, // Inverted exclamation
        ChevronLD       = 0xAE,
        ChevronRD       = 0xAF,

        LightShade      = 0xB0,
        MediumShade     = 0xB1,
        DarkShade       = 0xB2,

        First = Empty,
        Last = DarkShade
    };

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Char(u8 inner) : m_inner(inner) {}

    Char() = default;
    Char(Char&& other) = default;
    Char(const Char& other) = default;
    Char& operator=(Char&& other) = default;
    Char& operator=(const Char& other) = default;
    ~Char() = default;

    explicit operator u8() const;

    /* ---------------------------------------- */

    bool    operator==(const Char& other) const;
    bool    operator!=(const Char& other) const;

    /* ---------------------------------------- */

    bool    isAlpha() const;
    bool    isNum() const;
    bool    isAlphanum() const;

private:
    /* ---------------------------------------- */
    /*                ATTRIBUTES                */
    /* ---------------------------------------- */

    u8 m_inner = Empty;

}; // class Char

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

void init();

/* -------------------------------------------- */

void putChar(
    const Char character,
    const u8 x,
    const u8 y,
    const Color fontColor = Color::Immaculate
);
void setBgColor(
    const u8 x,
    const u8 y,
    const Color bgColor
);
void clearBuffer(Color color = Color::Immaculate);

/* ------------------ CURSOR ------------------ */

void disableCursor();
void setCursorPos(u8 x, u8 y);

} // namespace vga