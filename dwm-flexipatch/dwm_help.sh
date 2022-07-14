#!/bin/sh



{ Mod3Mask|ShiftMask,           XK_period,       floatpos,               {.v = " 26w  26h" } }, // ↘
/* Client is positioned in a floating grid, movement is relative to client's current position */
Mod3Mask|Mod1Mask,            XK_u,            floatpos,               {.v = "-1p -1p" } }, // ↖
Mod3Mask|Mod1Mask,            XK_i,            floatpos,               {.v = " 0p -1p" } }, // ↑
Mod3Mask|Mod1Mask,            XK_o,            floatpos,               {.v = " 1p -1p" } }, // ↗
Mod3Mask|Mod1Mask,            XK_j,            floatpos,               {.v = "-1p  0p" } }, // ←
Mod3Mask|Mod1Mask,            XK_k,            floatpos,               {.v = " 0p  0p" } }, // ·
Mod3Mask|Mod1Mask,            XK_l,            floatpos,               {.v = " 1p  0p" } }, // →
Mod3Mask|Mod1Mask,            XK_m,            floatpos,               {.v = "-1p  1p" } }, // ↙
Mod3Mask|Mod1Mask,            XK_comma,        floatpos,               {.v = " 0p  1p" } }, // ↓
Mod3Mask|Mod1Mask,            XK_period,       floatpos,               {.v = " 1p  1p" } }, // ↘
ndif // FLOATPOS_PATCH
f SETBORDERPX_PATCH
{ MODKEY|ControlMask,           XK_minus,      setborderpx,            {.i = -1 } },
{ MODKEY|ControlMask,           XK_plus,       setborderpx,            {.i = +1 } },
{ MODKEY|ControlMask,           XK_numbersign, setborderpx,            {.i = 0 } },
#endif // SETBORDERPX_PATCH
#if CYCLELAYOUTS_PATCH
{ MODKEY|ControlMask,           XK_comma,      cyclelayout,            {.i = -1 } },
{ MODKEY|ControlMask,           XK_period,     cyclelayout,            {.i = +1 } },
#endif // CYCLELAYOUTS_PATCH
#if MPDCONTROL_PATCH
{ MODKEY,                       XK_F1,         mpdchange,              {.i = -1} },
{ MODKEY,                       XK_F2,         mpdchange,              {.i = +1} },
{ MODKEY,                       XK_Escape,     mpdcontrol,             {0} },
#endif // MPDCONTROL_PATCH
TAGKEYS(                        XK_1,                                  0)
TAGKEYS(                        XK_2,                                  1)
TAGKEYS(                        XK_3,                                  2)
TAGKEYS(                        XK_4,                                  3)
TAGKEYS(                        XK_5,                                  4)
TAGKEYS(                        XK_6,                                  5)
TAGKEYS(                        XK_7,                                  6)
TAGKEYS(                        XK_8,                                  7)
TAGKEYS(                        XK_9,                                  8)

echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
