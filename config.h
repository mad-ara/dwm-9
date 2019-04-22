/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
#define FONT "monospace:bold:size=11"
static const char *fonts[]          = { FONT };
#define COL_GRAY1 "#222222"
#define COL_GRAY2 "#444444"
#define COL_GRAY3 "#bbbbbb"
#define COL_GRAY4 "#eeeeee"
#define COL_CYAN "#005577"
static const char *colors[][3]      = {
		/*               fg         bg         border   */
		[SchemeNorm] = { COL_GRAY3, COL_GRAY1, COL_GRAY2 },
		[SchemeSel]  = { COL_GRAY4, COL_CYAN,  COL_CYAN  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-b", "-fn", FONT, "-nb", COL_GRAY1, "-nf", COL_GRAY3, "-sb", COL_CYAN, "-sf", COL_GRAY4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
/* j4-dmenu-desktop is stupid and likes its dmenu arguments all mashed together into one, with the arguments quoted/escaped */
static const char *j4dmenucmd[] = { "j4-dmenu-desktop", "--dmenu=dmenu -i -b -fn "FONT" -nb '"COL_GRAY1"' -nf '"COL_GRAY3"' -sb '"COL_CYAN"' -sf '"COL_GRAY4"'", NULL };
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
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_Escape, view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_y,      spawn,          {.v = twiddledisplayscmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = j4dmenucmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_o,      spawn,          {.v = browsercmd } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0, XF86XK_AudioMute,                     spawn,          {.v = audiomutecmd } },
	{ 0, XF86XK_AudioMicMute,                  spawn,          {.v = audiomicmutecmd } },
	{ 0, XF86XK_AudioLowerVolume,              spawn,          {.v = audiolowervolumecmd } },
	{ 0, XF86XK_AudioRaiseVolume,              spawn,          {.v = audioraisevolumecmd } },
	{ 0, XF86XK_MonBrightnessDown,             spawn,          {.v = backlightdeccmd } },
	{ 0, XF86XK_MonBrightnessUp,               spawn,          {.v = backlightinccmd } },
	{ 0, XF86XK_Display,                       spawn,          {.v = twiddledisplayscmd } },
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

