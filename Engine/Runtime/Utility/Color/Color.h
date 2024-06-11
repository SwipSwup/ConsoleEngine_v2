//
// Created by david on 01/06/2024.
//

#ifndef CONSOLEENGINE_V2_COLOR_H
#define CONSOLEENGINE_V2_COLOR_H

#include <string>
#include <cstdint>

namespace Engine
{

    struct Color
    {
    public:
        //todo rewrite to only user rgb;
        Color() = default;
        Color(std::string escapeCode);
        Color(int r, int g, int b, bool bIsBackground);

        const char* GetEscapeCode();
        int GetEscapeCodeLength() const;
        long GetHashCode() const;

        Color operator+(Color color);
        Color* operator+=(Color color);
        bool operator==(Color color);
        bool operator!=(Color color);

    private:
        std::string escapeCode;
        int escapeCodeLength;
        long hash = 0;

    public:
        //Regular text
        static const Color BLK;
        static const Color RED;
        static const Color GRN;
        static const Color YEL;
        static const Color BLU;
        static const Color MAG;
        static const Color CYN;
        static const Color WHT;

        //Regular bold text
        static const Color BBLK;
        static const Color BRED;
        static const Color BGRN;
        static const Color BYEL;
        static const Color BBLU;
        static const Color BMAG;
        static const Color BCYN;
        static const Color BWHT;

        //Regular underline text
        static const Color UBLK;
        static const Color URED;
        static const Color UGRN;
        static const Color UYEL;
        static const Color UBLU;
        static const Color UMAG;
        static const Color UCYN;
        static const Color UWHT;

        //Regular background
        static const Color BLKB;
        static const Color REDB;
        static const Color GRNB;
        static const Color YELB;
        static const Color BLUB;
        static const Color MAGB;
        static const Color CYNB;
        static const Color WHTB;

        //High intensty background
        static const Color BLKHB;
        static const Color REDHB;
        static const Color GRNHB;
        static const Color YELHB;
        static const Color BLUHB;
        static const Color MAGHB;
        static const Color CYNHB;
        static const Color WHTHB;

        //High intensty text
        static const Color HBLK;
        static const Color HRED;
        static const Color HGRN;
        static const Color HYEL;
        static const Color HBLU;
        static const Color HMAG;
        static const Color HCYN;
        static const Color HWHT;

        //Bold high intensity text
        static const Color BHBLK;
        static const Color BHRED;
        static const Color BHGRN;
        static const Color BHYEL;
        static const Color BHBLU;
        static const Color BHMAG;
        static const Color BHCYN;
        static const Color BHWHT;

        //Reset
        static const Color reset;
        static const Color CRESET;
        static const Color COLOR_RESET;
    };

} // Engine

#endif //CONSOLEENGINE_V2_COLOR_H
