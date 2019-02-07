/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;       /* border pixel of windows */
static const unsigned int snap      = 32;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Menlo for Powerline:size=10", "Font Awesome:size=10" };
static const char dmenufont[]       = "Menlo for Powerline:size=10";
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
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class           instance    title       tags mask     isfloating   monitor */
    { "Firefox",       NULL,       NULL,       1 << 0,       0,           1 },
    { "qutebrowser",   NULL,       NULL,       1 << 0,       0,           1 },
    { "google-chrome", NULL,       NULL,       1 << 0,       0,           1 },
    { NULL,            "develop",  NULL,       1 << 1,       0,           0 },
    { NULL,            "ddgr",     NULL,       1 << 3,       0,           1 },
    { NULL,            "mail",     NULL,       1 << 4,       0,           1 },
    { NULL,            "rss",      NULL,       1 << 6,       0,           0 },
    { NULL,            "weechat",  NULL,       1 << 7,       0,           0 },
    { NULL,            "player",   NULL,       1 << 8,       0,           0 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_background, "-nf", col_foreground, "-sb", col_border, "-sf", col_foreground, "-p", "run:", NULL };
static const char *termcmd[]  = { "st", "-e", "tmux", NULL };

static const char *mailcmd[] = { "st", "-n", "mail", "-e", "neomutt", NULL };
static const char *rsscmd[] = { "st", "-n", "rss", "-e", "newsboat", NULL };
static const char *weechatcmd[] = { "st", "-n", "weechat", "-e", "tmux", "new-session", "-A", "-s", "chat", "weechat", NULL };
static const char *playercmd[] = { "st", "-n", "player", "-e", "ncmpcpp", NULL };
static const char *ddgrcmd[] = { "st", "-n", "ddgr", "-e", "tmux", "new-session", "-A", "-s", "duck", "ddgr --url-handler=w3m", NULL };
static const char *filebrowsercmd[] = { "st", "-e", "nnn", NULL };
static const char *calccmd[] = { "st", "-n", "calculator", "-e", "bcal", NULL };
static const char *taskcmd[] = { "st", "-n", "taskwarrior", "-e", "tmux", "new-session", "-A", "-s", "tasks", "tasksh", NULL };
static const char *developcmd[] = { "st", "-n", "develop", "-e", "tmux", "new-session", "-A", "-s", "develop", NULL };
static const char *passcmd[] = { "passmenu", "--type", "-fn", dmenufont, "-nb", col_background, "-nf", col_foreground, "-sb", col_border, "-sf", col_foreground, "-p", "pass:", NULL };
static const char *lockcmd[] = { "lock.sh", NULL };
static const char *mpctogglecmd[] = { "mpc", "toggle", NULL };
static const char *mpcnextcmd[] = { "mpc", "next", NULL };
static const char *mpcprevcmd[] = { "mpc", "prev", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_period, setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_comma, setmfact,        {.f = -0.05} },
    { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_h,      focusmon,       {.i = -1 } },
    { MODKEY,                       XK_l,      focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_h,      tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_l,      tagmon,         {.i = +1 } },
    { 0,                            XF86XK_MyComputer, spawn,  {.v = termcmd } },
    { 0,                            XF86XK_Mail, spawn,        {.v = mailcmd } },
    { 0,                            XF86XK_HomePage, spawn,    {.v = filebrowsercmd } },
    { 0,                            XF86XK_Tools, spawn,       {.v = playercmd } },
    { 0,                            XF86XK_Calculator, spawn,  {.v = calccmd } },
    { 0,                            XF86XK_Search, spawn,      {.v = taskcmd } },
    { 0,                            XF86XK_AudioPlay, spawn,   {.v = mpctogglecmd } },
    { 0,                            XF86XK_AudioNext, spawn,   {.v = mpcnextcmd } },
    { 0,                            XF86XK_AudioPrev, spawn,   {.v = mpcprevcmd } },
    { MODKEY|ShiftMask,             XK_n, spawn,               {.v = rsscmd } },
    { MODKEY|ShiftMask,             XK_p, spawn,               {.v = weechatcmd } },
    { MODKEY|ShiftMask,             XK_d, spawn,               {.v = ddgrcmd } },
    { MODKEY|ShiftMask,             XK_o, spawn,               {.v = developcmd } },
    { MODKEY|ShiftMask,             XK_a, spawn,               {.v = lockcmd } },
    { MODKEY,                       XK_z, spawn,               {.v = passcmd } },
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

