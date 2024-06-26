/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 0;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
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
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance    title       tags mask     isfloating   monitor */
	{ "Processing", NULL,       NULL,       0,            True,        -1 },
        { "My Paint",   NULL,       NULL,       0,            True,        -1 },
        { "My RPG",     NULL,       NULL,       0,            True,        -1 },
        { "feh",        NULL,       NULL,       0,            True,        -1 },
	{ "rviz2",      NULL,       NULL,       4,            False,       -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
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

static const char *volupcmd[] =   { "amixer", "-qM", "set", "Master", "5%+", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-qM", "set", "Master", "5%-", "unmute", NULL };
static const char *mutecmd[] = { "amixer", "-qM", "set", "Master", "toggle", NULL };

static const char *audioplaycmd[] = { "playerctl", "play-pause", NULL };
static const char *audionextcmd[] = { "playerctl", "next", NULL };
static const char *audiopreviouscmd[] = { "playerctl", "previous", NULL };
static const char *audiostopcmd[] = { "playerctl", "stop", NULL };

#define SCROTUPLOADER "/mnt/john/home/Code/screenshot_uploader.py $f"
static const char *scrotuploadcmd[] = { "scrot", "-s", "-o", "-F", "/tmp/scrot.png", "-e", SCROTUPLOADER, NULL };

static const char *emacsclientcmd[] = { "emacsclient", "-c", "-a", "", NULL };

static const char *uskb[] = { "setxkbmap", "us", NULL };
static const char *frkb[] = { "setxkbmap", "fr", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ NULL,                         XF86XK_AudioRaiseVolume,      spawn,          {.v = volupcmd } },
	{ NULL,                         XF86XK_AudioLowerVolume,      spawn,          {.v = voldowncmd } },
	{ NULL,                         XF86XK_AudioMute,      spawn,          {.v = mutecmd } },
	{ NULL,                         XF86XK_AudioPlay,      spawn,          {.v = audioplaycmd } },
	{ NULL,                         XF86XK_AudioNext,      spawn,          {.v = audionextcmd } },
	{ NULL,                         XF86XK_AudioPrev,      spawn,          {.v = audiopreviouscmd } },
	{ NULL,                         XF86XK_AudioStop,      spawn,          {.v = audiostopcmd } },
	{ MODKEY,                       XK_F1,     spawn,          {.v = frkb } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = uskb } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ NULL,                         XK_Print,  spawn,          {.v = scrotuploadcmd } },
	/* { NULL,                         XK_Print,  spawn,          {.v = scrotcmd } }, */
	/* { MODKEY|ShiftMask,             XK_Print,  spawn,          {.v = scrotucmd } }, */
	/* { ShiftMask,                    XK_Print,  spawn,          {.v = fscrotucmd } }, */
	{ MODKEY,                       XK_e,      spawn,          {.v = emacsclientcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
//	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
//	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
//	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_agrave,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_semicolon, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_ampersand,              0)
	TAGKEYS(                        XK_eacute,                 1)
	TAGKEYS(                        XK_quotedbl,               2)
	TAGKEYS(                        XK_apostrophe,             3)
	TAGKEYS(                        XK_parenleft,              4)
	TAGKEYS(                        XK_minus,                  5)
	TAGKEYS(                        XK_egrave,                 6)
	TAGKEYS(                        XK_underscore,             7)
	TAGKEYS(                        XK_ccedilla,               8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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
