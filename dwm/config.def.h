/* See LICENSE file for copyright and license details. */

/* function keys */
#include <X11/XF86keysym.h>
const char *upvol[]          = { "/usr/bin/pulsemixer", "--change-volume", "+5", NULL };
const char *downvol[]        = { "/usr/bin/pulsemixer", "--change-volume", "-5", NULL };
const char *mutevol[]        = { "/usr/bin/pulsemixer", "--mute",                NULL };
const char *brightdown[]     = { "/usr/bin/xbacklight", "-dec",            "10", NULL };
const char *brightup[]       = { "/usr/bin/xbacklight", "-inc",            "10", NULL };

/* appearance */
static const unsigned int borderpx  = 3;         /* border pixel of windows */
static const int gappx     = 10;                 /* gaps between windows */
static const unsigned int snap      = 32;        /* snap pixel */
static const unsigned int systraypinning = 0;    /* 0: sloppy systray follows selected monitor,
                                                   >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;     /* 0: systray in the right corner,
                                                   >0: systray on left of status text */
static const unsigned int systrayspacing = 2;    /* systray spacing */
static const int systraypinningfailfirst = 1;    /* 1: if pinning fails, display systray on the first monitor,
                                                    0: display systray on the last monitor*/
static const int showsystray        = 1;         /* 0 means no systray */
static const int showbar            = 1;         /* 0 means no bar */
static const int topbar             = 1;         /* 0 means bottom bar */
static const int user_bh            = 20;         /* 0 means that dwm will calculate bar height,
                                                  >=1 means dwm will user_bh as bar height */
/* Display modes of the tab bar: never shown, always shown, shown only in  
   monocle mode in the presence of several windows.                        
   Modes after showtab_nmodes are disabled. */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab            = showtab_auto;        /* Default tab barshow mode */
static const int toptab             = True;               /* False means bottom tab bar */
static const char *fonts[]          = { 
        "TerminessTTF Nerd Font:style=Medium:size=14:antialias=true:autohint=true",
        "Symbols Nerd Font:style=1000-em:size=14:antialias=true:autohint=true",
};
static const char dmenufont[]       = "TerminessTTF Nerd Font:style=Medium:size=14:antialias=true:autohint=true";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#1d2021";
static const char col_gray3[]       = "#ebdbb2";
static const char col_gray4[]       = "#ebdbb2";
static const char col_cyan[]        = "#458588";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeTitle] = { col_cyan, col_gray1, col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const char *tagsel[][2] = {
        /* fg         bg       */
	{ "#458588", "#282828" },
	{ "#d65d0e", "#282828" },
	{ "#98971a", "#282828" },
	{ "#d79921", "#282828" },
	{ "#689d6a", "#282828" },
	{ "#cc241d", "#282828" },
	{ "#a89984", "#282828" },
	{ "#b16286", "#282828" },
	{ "#ebdbb2", "#282828" },
};

static const unsigned int ulinepad	= 2;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask    iscentered     isfloating   monitor    scratch key*/
	{ NULL,       NULL,       NULL,       0,           0,             False,       -1,        0 },
	//{ "Gimp",     NULL,       NULL,       0,         0,             1,           -1,        0 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,    0,             0,           -1,        0 },
        { NULL,       NULL,      "scratchpad", 0,          1,             1,           -1,      's' },
        { NULL,       NULL,      "pulsemixer", 0,          1,             1,           -1,      'v' },
        { NULL,       NULL,      "nmtui",      0,          1,             1,           -1,      'n' },

};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "horizgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "###",      horizgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "st", "-t", "scratchpad", NULL}; 
static const char *pulsemixercmd[] = {"v", "st", "-t", "pulsemixer", "-e", "pulsemixer",  NULL}; 
static const char *nmtuicmd[] = {"n", "st", "-t", "nmtui", "-e", "nmtui",  NULL}; 

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_w,      tabmode,        {-1} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      inplacerotate,  {.i = +1} },
	{ MODKEY|ShiftMask,             XK_k,      inplacerotate,  {.i = -1} },
	{ MODKEY|ShiftMask,             XK_h,      inplacerotate,  {.i = +2} },
	{ MODKEY|ShiftMask,             XK_l,      inplacerotate,  {.i = -2} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { MODKEY|ControlMask|ShiftMask, XK_h,      layoutscroll,   {.i = -1 } },
        { MODKEY|ControlMask|ShiftMask, XK_l,      layoutscroll,   {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
        { MODKEY,                       XK_n,      togglescratch, {.v = nmtuicmd } },
        { MODKEY,                       XK_v,      togglescratch, {.v = pulsemixercmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
        { ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
};

