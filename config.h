/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=11" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
#ifdef HOST_duke
static const char *tags[] = { "%", "7", "5", "3", "1", "9"};
#else
static const char *tags[] = { " %", "7", "5", "3", "1", "9 ", " 0", "2", "4", "6", "8", "` "};
#endif

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[] = { "firefox", NULL };
static const char *lockcmd[] = { "xautolock", "-locknow", NULL };
static const char *audiomutecmd[]  = { "pulseaudio-ctl", "mute", NULL };
static const char *audiomicmutecmd[]  = { "pulseaudio-ctl", "mute-input", NULL };
static const char *audiolowervolumecmd[]  = { "pulseaudio-ctl", "down", NULL };
static const char *audioraisevolumecmd[]  = { "pulseaudio-ctl", "up", NULL };
static const char *backlightdeccmd[]  = { "xbacklight", "-10", NULL };
static const char *backlightinccmd[]  = { "xbacklight", "+10", NULL };
static const char *twiddledisplayscmd[]  = { "xlayoutdisplay", NULL };

#include <X11/XF86keysym.h>
#include "push.c"
#include "unfloat.c"
static Key keys[] = {
	/* modifier                     keycode                     function        argument */
	{ MODKEY,                       9,                          view,           {0} },
	TAGKEYS(                        10,                                         0)
	TAGKEYS(                        11,                                         1)
	TAGKEYS(                        12,                                         2)
	TAGKEYS(                        13,                                         3)
	TAGKEYS(                        14,                                         4)
	TAGKEYS(                        15,                                         5)

	TAGKEYS(                        16,                                         6)
	TAGKEYS(                        17,                                         7)
	TAGKEYS(                        18,                                         8)
	TAGKEYS(                        19,                                         9)
	/*{ MODKEY,                       19,                         view,           {.ui = ~0 } },*/
	/*{ MODKEY|ShiftMask,             19,                         tag,            {.ui = ~0 } },*/
	TAGKEYS(                        20,                                         10)
	TAGKEYS(                        21,                                         11)
	{ MODKEY|ShiftMask,             51,                         spawn,          {.v = lockcmd } },

	{ MODKEY,                       23,                         focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             23,                         focusstack,     {.i = -1 } },
	{ MODKEY,                       24,                         killclient,     {0} },
	{ MODKEY,                       25,                         togglebar,      {0} },
	{ MODKEY,                       26,                         setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             26,                         unfloatvisible, {.v = &layouts[0]} },
	{ MODKEY,                       27,                         setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             27,                         unfloatvisible, {.v = &layouts[1]} },
	{ MODKEY,                       28,                         setlayout,      {.v = &layouts[2]} },

	{ MODKEY,                       33,                         setmfact,       {.f = +0.05} },

	{ MODKEY|ShiftMask,             35,                         quit,           {0} },
	{ MODKEY|ShiftMask,             49,                         spawn,          {.v = twiddledisplayscmd } },

	{ MODKEY,                       38,                         incnmaster,     {.i = +1 } },
	{ MODKEY,                       39,                         incnmaster,     {.i = -1 } },
	{ MODKEY,                       40,                         spawn,          {.v = browsercmd } },
	{ MODKEY,                       41,                         spawn,          {.v = dmenucmd } },
	{ MODKEY,                       42,                         spawn,          {.v = termcmd } },

	{ MODKEY,                       44,                         setmfact,       {.f = -0.05} },
	{ MODKEY,                       36,                         zoom,           {0} },

	{ MODKEY,                       52,                         focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             52,                         tagmon,         {.i = -1 } },
	{ MODKEY,                       53,                         focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             53,                         tagmon,         {.i = +1 } },
	{ MODKEY,                       54,                         focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             54,                         pushdown,       {0} },
	{ MODKEY,                       55,                         focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             55,                         pushup,         {0} },

	{ MODKEY,                       65,                         setlayout,      {0} },
	{ MODKEY|ShiftMask,             65,                         unfloatvisible, {0} },

	{ 0,                            121,                        spawn,          {.v = audiomutecmd } },
	{ 0,                            198,                        spawn,          {.v = audiomicmutecmd } },
	{ 0,                            122,                        spawn,          {.v = audiolowervolumecmd } },
	{ 0,                            123,                        spawn,          {.v = audioraisevolumecmd } },
	{ 0,                            232,                        spawn,          {.v = backlightdeccmd } },
	{ 0,                            233,                        spawn,          {.v = backlightinccmd } },
	{ 0,                            235,                        spawn,          {.v = twiddledisplayscmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[0]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

