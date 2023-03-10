/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 1;        /* horizontal padding for statusbar */
static const int vertpadbar         = 2;        /* vertical padding for statusbar */
static const char *fonts[]          = { 
    "Hermit:size=11:antialias=true:hinting=true",
    "FontAwesome:size=11:antialias=true:hinting=true"
};
static const char dmenufont[]           = "Hermit:size=11";
static const char normbgcolor[]         = "#1D1F21";
static const char normbordercolor[]     = "#5F819D";
static const char normfgcolor[]         = "#C5C8C6";
static const char selfgcolor[]          = "#324C80";
static const char selbordercolor[]      = "#2B4F98";
static const char selbgcolor[]          = "#A1CDCD";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor, selbgcolor,  selbordercolor  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"st", "-n", "spmusic", "-g", "144x41", "-e", "ncmpcpp", NULL };
const char *spcmd4[] = {"st", "-n", "sppulse", "-g", "120x34", "-e", "pulsemixer", NULL };
const char *spcmd5[] = {"st", "-n", "launch", "-e", "~/.scripts/launch.sh", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spfm",    spcmd2},
	{"spmusic",     spcmd3},
    {"sppulse",     spcmd4},
    {"launch",      spcmd5},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask     isfloating   monitor */
	{ "Gimp",	        NULL,			NULL,		0,				1,			 -1 },
	{ "Firefox",        NULL,			NULL,		2,			    0,			 -1 },
	{ "qutebrowser",    NULL,			NULL,		2,			    0,			 -1 },
	{ "Pcmanfm",        NULL,			NULL,		1 << 1,			0,			 -1 },
	{ "Nemo",           NULL,			NULL,		1 << 1,			0,			 -1 },
	{ NULL,		        "spterm",		NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		        "spfm",		    NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		        "spmusic",	    NULL,		SPTAG(2),		1,			 -1 },
	{ NULL,		        "sppulse",	    NULL,		SPTAG(3),		1,			 -1 },
    { NULL,             "launch",       NULL,       SPTAG(4),       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "grid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ NULL,       NULL },
};

/* key definitions */

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)												\
	{1, {{MODKEY, KEY}},								view,           {.ui = 1 << TAG} },	\
	{1, {{MODKEY|ControlMask, KEY}},					toggleview,     {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ShiftMask, KEY}},						tag,            {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask|ShiftMask, KEY}},			toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browser[] = { "qutebrowser", NULL };
static const char *browser2[] = { "firefox", NULL };
static const char *fm[] = { "pcmanfm", NULL };
static const char *fm2[] = { "nemo", NULL };

static Keychord keychords[] = {
	/* Keys        function        argument */
	{1, {{MODKEY|ShiftMask, XK_Return}},		    spawn,          {.v = dmenucmd } },
	{1, {{MODKEY, XK_Return}},			            spawn,          {.v = termcmd } },
	{2, {{MODKEY, XK_w}, {0, XK_q}},			    spawn,          {.v = browser } },
	{2, {{MODKEY, XK_w}, {0, XK_f}},			    spawn,          {.v = browser2 } },
    {2, {{MODKEY, XK_p}, {0, XK_p}},                spawn,          {.v = fm } },
    {2, {{MODKEY, XK_p}, {0, XK_n}},                spawn,          {.v = fm2 } },
	{1, {{Mod1Mask, XK_b}},							togglebar,      {0} },
	{1, {{MODKEY|ShiftMask,XK_j}},                  rotatestack,    {.i = +1 } },
	{1, {{MODKEY|ShiftMask,XK_k}},                  rotatestack,    {.i = -1 } },
	{1, {{MODKEY, XK_j}},							focusstack,     {.i = +1 } },
	{1, {{MODKEY, XK_k}},							focusstack,     {.i = -1 } },
	{1, {{MODKEY, XK_i}},							incnmaster,     {.i = +1 } },
	{1, {{MODKEY, XK_d}},							incnmaster,     {.i = -1 } },
	{1, {{MODKEY, XK_h}},							setmfact,       {.f = -0.05} },
	{1, {{MODKEY, XK_l}},							setmfact,       {.f = +0.05} },
	{1, {{MODKEY|ControlMask, XK_Return}},			zoom,           {0} },
	{1, {{MODKEY, XK_g}},                           goback,         {0} },
	{1, {{MODKEY, XK_Tab}},							view,           {0} },
	{1, {{MODKEY, XK_q}},					        killclient,     {0} },
	{1, {{MODKEY|ControlMask, XK_j}},               aspectresize,   {.i = +24} },
	{1, {{MODKEY|ControlMask, XK_k}},               aspectresize,   {.i = -24} },
	{1, {{MODKEY|ShiftMask, XK_t}},					setlayout,      {.v = &layouts[0]} },
	{1, {{MODKEY|ShiftMask, XK_f}},					setlayout,      {.v = &layouts[1]} },
	{1, {{MODKEY|ShiftMask, XK_m}},					setlayout,      {.v = &layouts[2]} },
	{1, {{MODKEY|ShiftMask, XK_g}},					setlayout,      {.v = &layouts[3]} },
	{1, {{MODKEY|ControlMask,XK_comma}},            cyclelayout,    {.i = -1 } },
	{1, {{MODKEY|ControlMask,XK_period}},           cyclelayout,    {.i = +1 } },
	{1, {{MODKEY, XK_space}},						setlayout,      {0} },
	{1, {{ MODKEY, XK_f}},                togglefullscr,  {0} },
	{1, {{MODKEY|ShiftMask, XK_space}},				togglefloating, {0} },
	{1, {{MODKEY, XK_0}},							view,           {.ui = ~0 } },
	{1, {{MODKEY|ShiftMask, XK_0}},					tag,            {.ui = ~0 } },
	{1, {{MODKEY, XK_comma}},						focusmon,       {.i = -1 } },
	{1, {{MODKEY, XK_period}},						focusmon,       {.i = +1 } },
	{1, {{MODKEY|ShiftMask, XK_comma}},				tagmon,         {.i = -1 } },
	{1, {{MODKEY|ShiftMask, XK_period}},			tagmon,         {.i = +1 } },
    {1, {{MODKEY, XK_t}},                           togglescratch,  {.ui = 0 } },
    {1, {{MODKEY, XK_r}},                           togglescratch,  {.ui = 1 } },
    {1, {{MODKEY, XK_m}},                           togglescratch,  {.ui = 2 } },
    {1, {{MODKEY, XK_v}},                           togglescratch,  {.ui = 3 } },
    {2, {{MODKEY, XK_s}, {0, XK_l}},                togglescratch,  {.ui = 4 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{1, {{MODKEY|ShiftMask, XK_q}},					quit,           {0} },
	{1, {{MODKEY|ShiftMask, XK_r}},      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

