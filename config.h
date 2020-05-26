/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;       /* border pixel of windows */
static const unsigned int snap      = 32;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Inconsolata:pixelsize=19:anitalias=true:autohint=true" };
static const char dmenufont[]       = "Inconsolata:pixelsize=19:anitalias=true:autohint=true";
static const char col_background[]  = "#fdf6e3";
static const char col_foreground[]  = "#657b83";
static const char col_border[]      = "#eee8d5";
static const char col_border_selected[] = "#586e75";
static const char col_selected[]    = "#b58900";
static const char *colors[][3]      = {
    /*               fg              bg              border   */
    [SchemeNorm] = { col_foreground, col_background, col_border },
    [SchemeSel]  = { col_foreground,   col_border,     col_border_selected  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class           instance    title       tags mask     isfloating   monitor */
    { NULL,            "player",   NULL,       1 << 8,       0,           1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "",      tile },    /* first entry is default */
    { "[D]",      deck  },
    { "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ 0,    MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ 0,    MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ 0,    MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ 0,    MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_background, "-nf", col_foreground, "-sb", col_border, "-sf", col_foreground, "-p", "run:", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *tmuxcmd[]  = { "st", "-e", "tmux", NULL };
static const char *tmuxsessioncmd[]  = { "tmux_session", NULL };

static const char *mailcmd[] = { "st", "-n", "mail", "-e", "neomutt", NULL };
static const char *rsscmd[] = { "st", "-n", "rss", "-e", "newsboat", NULL };
static const char *weechatcmd[] = { "st", "-n", "weechat", "-e", "tmux", "new-session", "-A", "-s", "chat", "weechat", NULL };
static const char *playercmd[] = { "st", "-n", "player", "-e", "ncmpcpp", NULL };
static const char *ddgrcmd[] = { "st", "-e", "tmux", "new-session", "ddgr --url-handler browser", NULL };
static const char *bukucmd[] = { "st", "-e", "tmux", "new-session", "buku", NULL };
static const char *calccmd[] = { "st", "-n", "calculator", "-e", "bcal", NULL };
static const char *passcmd[] = { "passmenu", "--type", "-fn", dmenufont, "-nb", col_background, "-nf", col_foreground, "-sb", col_border, "-sf", col_foreground, "-p", "pass:", NULL };
static const char *lockcmd[] = { "lock", NULL };
static const char *mpctogglecmd[] = { "mpc", "toggle", NULL };
static const char *mpcnextcmd[] = { "mpc", "next", NULL };
static const char *mpcprevcmd[] = { "mpc", "prev", NULL };
static const char *muteunmutecmd[] = { "amixer", "set", "Master", "toggle", NULL };
static const char *volumeupcmd[] = { "amixer", "set", "Master", "10%+", NULL };
static const char *volumedowncmd[] = { "amixer", "set", "Master", "10%-", NULL };
static const char *powermenucmd[] = { "power_menu", NULL };

#define MULTIKEY_THRESHOLD_MS_PRESS 200
#define MULTIKEY_THRESHOLD_MS_HOLD 700

#include <X11/XF86keysym.h>

static Key keys[] = {
    /* repeats  modifier                     key        function        argument */
    { 0,        MODKEY,                       XK_Return, spawn,          {.v = tmuxcmd } },
    { 1,        MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { 2,        MODKEY|ShiftMask,             XK_Return, spawn,          {.v = tmuxsessioncmd } },
    { 0,        MODKEY,                       XK_b,      togglebar,      {0} },
    { 0,        MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { 0,        MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { 0,        MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { 0,        MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { 0,        MODKEY,                       XK_period, setmfact,       {.f = +0.05} },
    { 0,        MODKEY,                       XK_comma, setmfact,        {.f = -0.05} },
    { 0,        MODKEY|ShiftMask,             XK_f, zoom,           {0} },
    { 0,        MODKEY,                       XK_Tab,    view,           {0} },
    { 0,        MODKEY,                       XK_q,      killclient,     {0} },
    { 0,        MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { 0,        MODKEY,                       XK_r,      setlayout,      {.v = &layouts[1]} },
    { 0,        MODKEY,                       XK_y,      setlayout,      {.v = &layouts[2]} },
    { 0,        MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
    { 0,        MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { 0,        MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { 0,        MODKEY,                       XK_h,      focusmon,       {.i = -1 } },
    { 0,        MODKEY,                       XK_l,      focusmon,       {.i = +1 } },
    { 0,        MODKEY|ShiftMask,             XK_h,      tagmon,         {.i = -1 } },
    { 0,        MODKEY|ShiftMask,             XK_l,      tagmon,         {.i = +1 } },
    { 0,        0,                            XF86XK_MyComputer, spawn,  {.v = termcmd } },
    { 0,        0,                            XF86XK_Mail, spawn,        {.v = mailcmd } },
    { 0,        MODKEY|ShiftMask,             XK_m, spawn,               {.v = mailcmd } },
    { 0,        0,                            XF86XK_Tools, spawn,       {.v = playercmd } },
    { 0,        0,                            XF86XK_Calculator, spawn,  {.v = calccmd } },
    { 0,        0,                            XF86XK_AudioPlay, spawn,   {.v = mpctogglecmd } },
    { 0,        0,                            XF86XK_AudioNext, spawn,   {.v = mpcnextcmd } },
    { 0,        0,                            XF86XK_AudioPrev, spawn,   {.v = mpcprevcmd } },
    { 0,        0,                            XF86XK_AudioRaiseVolume, spawn,   {.v = volumeupcmd } },
    { 0,        0,                            XF86XK_AudioLowerVolume, spawn,   {.v = volumedowncmd } },
    { 0,        0,                            XF86XK_AudioMute, spawn,   {.v = muteunmutecmd } },
    { 0,        MODKEY|ShiftMask,             XK_n, spawn,               {.v = rsscmd } },
    { 0,        MODKEY|ShiftMask,             XK_p, spawn,               {.v = weechatcmd } },
    { 0,        MODKEY|ShiftMask,             XK_d, spawn,               {.v = ddgrcmd } },
    { 0,        MODKEY|ShiftMask,             XK_b, spawn,               {.v = bukucmd } },
    { 0,        MODKEY|ShiftMask,             XK_a, spawn,               {.v = lockcmd } },
    { 0,        MODKEY,                       XK_z, spawn,               {.v = passcmd } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { 2,        MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { 1,        MODKEY|ShiftMask,             XK_q,      spawn,          {.v = powermenucmd} },
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

