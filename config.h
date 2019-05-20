/* See LICENSE file for copyright and license details. */

/* clion (clang?) gets upset with a quoted string being passed in from the command line */
#define VERSION "6.2"

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
static const char *tags[] = { "&", "[", "{", "}", "(", "="};
#else
static const char *tags[] = { "&", "[", "{", "}", "(", "=", "*", ")", "+", "]", "!"};
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
	{ MODKEY|ShiftMask,             KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tag,            {.ui = 1 << TAG} }, \
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
	/* modifier                     key                         function        argument */
	{ MODKEY,                       XK_o,                       spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_e,                       spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_u,                       spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_comma,                   togglebar,      {0} },
	{ MODKEY,                       XK_j,                       focusstack,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_j,                       pushdown,       {0} },
	{ MODKEY,                       XK_k,                       focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_k,                       pushup,         {0} },
	{ MODKEY,                       XK_h,                       setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_h,                       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_l,                       setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_l,                       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Return,                  zoom,           {0} },
	{ MODKEY,                       XK_Tab,                     view,           {0} },
	{ MODKEY,                       XK_semicolon,               killclient,     {0} },
	{ MODKEY,                       XK_period,                  setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_period,                  unfloatvisible, {.v = &layouts[0]} },
	{ MODKEY,                       XK_p,                       setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_p,                       unfloatvisible, {.v = &layouts[1]} },
	{ MODKEY,                       XK_y,                       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                   setlayout,      {0} },
	{ MODKEY|ControlMask,           XK_space,                   unfloatvisible, {0} },
	{ MODKEY,                       XK_apostrophe,              focusmon,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_apostrophe,              tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_q,                       focusmon,       {.i = +1 } },
	{ MODKEY|ControlMask,           XK_q,                       tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_ampersand,                               0)
	TAGKEYS(                        XK_bracketleft,                             1)
	TAGKEYS(                        XK_braceleft,                               2)
	TAGKEYS(                        XK_braceright,                              3)
	TAGKEYS(                        XK_parenleft,                               4)
	TAGKEYS(                        XK_equal,                                   5)
	TAGKEYS(                        XK_asterisk,                                6)
	TAGKEYS(                        XK_parenright,                              7)
	TAGKEYS(                        XK_plus,                                    8)
	TAGKEYS(                        XK_bracketright,                            9)
	TAGKEYS(                        XK_exclam,                                  10)
	{ MODKEY|ControlMask,           XK_numbersign,              quit,           {0} },
	{ MODKEY|ControlMask,           XK_at,                      spawn,          {.v = twiddledisplayscmd} },
	{ MODKEY|ControlMask,           XK_backslash,               spawn,          {.v = lockcmd} },
    { 0,                            XF86XK_AudioMute,           spawn,          {.v = audiomutecmd } },
	{ 0,                            XF86XK_AudioMicMute,        spawn,          {.v = audiomicmutecmd } },
	{ 0,                            XF86XK_AudioLowerVolume,    spawn,          {.v = audiolowervolumecmd } },
	{ 0,                            XF86XK_AudioRaiseVolume,    spawn,          {.v = audioraisevolumecmd } },
	{ 0,                            XF86XK_MonBrightnessDown,   spawn,          {.v = backlightdeccmd } },
	{ 0,                            XF86XK_MonBrightnessUp,     spawn,          {.v = backlightinccmd } },
	{ 0,                            XF86XK_Display,             spawn,          {.v = twiddledisplayscmd } },
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

