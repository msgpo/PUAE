 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Stuff
  *
  * Copyright 1995, 1996 Ed Hanway
  * Copyright 1995-2001 Bernd Schmidt
  */

typedef enum { KBD_LANG_US, KBD_LANG_DK, KBD_LANG_DE, KBD_LANG_SE, KBD_LANG_FR, KBD_LANG_IT, KBD_LANG_ES } KbdLang;

struct uaedev_mount_info;

struct strlist {
	struct strlist *next;
	TCHAR *option, *value;
	int unknown;
};

/* maximum number native input devices supported (single type) */
#define MAX_INPUT_DEVICES 8
/* maximum number of native input device's buttons and axles supported */
#define MAX_INPUT_DEVICE_EVENTS 256
/* 4 different customization settings */
#define MAX_INPUT_SETTINGS 4
#define GAMEPORT_INPUT_SETTINGS 3 // last slot is for gameport panel mappings
#define MAX_INPUT_SUB_EVENT 4
#define MAX_INPUT_SIMULTANEOUS_KEYS 4

// this better be here than in sound.h
#define FILTER_SOUND_OFF 0
#define FILTER_SOUND_EMUL 1
#define FILTER_SOUND_ON 2

#define FILTER_SOUND_TYPE_A500 0
#define FILTER_SOUND_TYPE_A1200 1

struct uae_input_device {
	TCHAR *name;
	TCHAR *configname;
	uae_s16 eventid[MAX_INPUT_DEVICE_EVENTS][MAX_INPUT_SUB_EVENT];
	TCHAR *custom[MAX_INPUT_DEVICE_EVENTS][MAX_INPUT_SUB_EVENT];
	uae_u16 flags[MAX_INPUT_DEVICE_EVENTS][MAX_INPUT_SUB_EVENT];
	uae_s16 extra[MAX_INPUT_DEVICE_EVENTS][MAX_INPUT_SIMULTANEOUS_KEYS];
	uae_s8 port[MAX_INPUT_DEVICE_EVENTS][MAX_INPUT_SIMULTANEOUS_KEYS];
	uae_s8 enabled;
};

#define MAX_JPORTS 4
#define MAX_JPORTNAME 128
struct jport {
	int id;
	int mode; // 0=def,1=mouse,2=joy,3=anajoy,4=lightpen
	int autofire;
	TCHAR name[MAX_JPORTNAME];
	TCHAR configname[MAX_JPORTNAME];
};
#define JPORT_NONE -1
#define JPORT_CUSTOM -2
#define JPORT_AF_NORMAL 1
#define JPORT_AF_TOGGLE 2

#define MAX_SPARE_DRIVES 20
#define MAX_CUSTOM_MEMORY_ADDRS 2

#define CONFIG_TYPE_HARDWARE 1
#define CONFIG_TYPE_HOST 2
#define CONFIG_BLEN 2560

#define TABLET_OFF 0
#define TABLET_MOUSEHACK 1
#define TABLET_REAL 2

struct wh {
	int x, y;
	int width, height;
};

#define MOUNT_CONFIG_SIZE 30
struct uaedev_config_info {
	TCHAR devname[MAX_DPATH];
	TCHAR volname[MAX_DPATH];
	TCHAR rootdir[MAX_DPATH];
	bool ishdf;
	bool readonly;
	int bootpri;
	bool autoboot;
	bool donotmount;
	TCHAR filesys[MAX_DPATH];
	int surfaces;
	int sectors;
	int reserved;
	int blocksize;
	int configoffset;
	int controller;
};

enum { CP_GENERIC = 1, CP_CDTV, CP_CD32, CP_A500, CP_A500P, CP_A600, CP_A1000,
       CP_A1200, CP_A2000, CP_A3000, CP_A3000T, CP_A4000, CP_A4000T };

#define IDE_A600A1200 1
#define IDE_A4000 2

#define GFX_WINDOW 0
#define GFX_FULLSCREEN 1
#define GFX_FULLWINDOW 2

struct uae_prefs {

	struct strlist *all_lines;

	TCHAR description[256];
	TCHAR info[256];
	int config_version;
	TCHAR config_hardware_path[MAX_DPATH];
	TCHAR config_host_path[MAX_DPATH];

	bool illegal_mem;
	bool use_serial;
	bool serial_demand;
	bool serial_hwctsrts;
	bool serial_direct;
	bool parallel_demand;
	int parallel_matrix_emulation;
	bool parallel_postscript_emulation;
	bool parallel_postscript_detection;
	int parallel_autoflush_time;
	TCHAR ghostscript_parameters[256];
	bool use_gfxlib;
	bool socket_emu;

#ifdef DEBUGGER
	bool start_debugger;
#endif
	bool start_gui;

	KbdLang keyboard_lang;

	int produce_sound;
	int sound_stereo;
	int sound_stereo_separation;
	int sound_mixed_stereo_delay;
	int sound_freq;
	int sound_maxbsiz;
	int sound_latency;
	int sound_interpol;
	int sound_filter;
	int sound_filter_type;
	int sound_volume;
	bool sound_stereo_swap_paula;
	bool sound_stereo_swap_ahi;
	bool sound_auto;

#ifdef JIT
	int comptrustbyte;
	int comptrustword;
	int comptrustlong;
	int comptrustnaddr;
	bool compnf;
	bool compfpu;
	bool comp_midopt;
	bool comp_lowopt;
	bool fpu_strict;

	bool comp_hardflush;
	bool comp_constjump;
	bool comp_oldsegv;

	int cachesize;
	int optcount[10];
#endif
	bool avoid_cmov;

	int gfx_display;
	TCHAR gfx_display_name[256];
	int gfx_framerate, gfx_autoframerate;
	int gfx_width_win, gfx_height_win;
	int gfx_width_fs, gfx_height_fs;
	int gfx_width, gfx_height;
	struct wh gfx_size_win;
	struct wh gfx_size_fs;
	struct wh gfx_size;
	struct wh gfx_size_win_xtra[4];
	struct wh gfx_size_fs_xtra[4];
	bool gfx_autoresolution;
	bool gfx_scandoubler;
	int gfx_refreshrate;
	int gfx_avsync, gfx_pvsync;
	int gfx_resolution;
	int gfx_lores_mode;
	int gfx_linedbl;
	int gfx_afullscreen, gfx_pfullscreen;
	int gfx_xcenter, gfx_ycenter;
	int gfx_xcenter_pos, gfx_ycenter_pos;
	int gfx_xcenter_size, gfx_ycenter_size;
	int gfx_max_horizontal, gfx_max_vertical;
	int gfx_saturation, gfx_luminance, gfx_contrast, gfx_gamma;
	bool gfx_blackerthanblack;
	int gfx_backbuffers;
	int gfx_api;
	int color_mode;
	int gfx_gl_x_offset; //koko
	int gfx_gl_y_offset; //koko
	int gfx_gl_smoothing; //koko
	int gfx_gl_panscan; //koko

	int gfx_filter;
	TCHAR gfx_filtershader[MAX_DPATH];
	TCHAR gfx_filtermask[MAX_DPATH];
	int gfx_filter_scanlines;
	int gfx_filter_scanlineratio;
	int gfx_filter_scanlinelevel;
	int gfx_filter_horiz_zoom, gfx_filter_vert_zoom;
	int gfx_filter_horiz_zoom_mult, gfx_filter_vert_zoom_mult;
	int gfx_filter_horiz_offset, gfx_filter_vert_offset;
	int gfx_filter_filtermode;
	int gfx_filter_bilinear;
	int gfx_filter_noise, gfx_filter_blur;
	int gfx_filter_saturation, gfx_filter_luminance, gfx_filter_contrast, gfx_filter_gamma;
	int gfx_filter_keep_aspect, gfx_filter_aspect;
	int gfx_filter_autoscale;

	bool immediate_blits;
	unsigned int chipset_mask;
	bool ntscmode;
	bool genlock;
	int chipset_refreshrate;
	int collision_level;
	int leds_on_screen;
	int keyboard_leds[3];
	bool keyboard_leds_in_use;
	int scsi;
	bool sana2;
	bool uaeserial;
	int catweasel;
	int catweasel_io;
	int cpu_idle;
	bool cpu_cycle_exact;
	int cpu_clock_multiplier;
	int cpu_frequency;
	bool blitter_cycle_exact;
	int floppy_speed;
	int floppy_write_length;
	int floppy_random_bits_min;
	int floppy_random_bits_max;
	bool tod_hack;
	uae_u32 maprom;
	int turbo_emulation;
	bool headless;

	int cs_compatible;
	int cs_ciaatod;
	int cs_rtc;
	int cs_rtc_adjust;
	int cs_rtc_adjust_mode;
	bool cs_ksmirror_e0;
	bool cs_ksmirror_a8;
	bool cs_ciaoverlay;
	bool cs_cd32cd;
	bool cs_cd32c2p;
	bool cs_cd32nvram;
	bool cs_cdtvcd;
	bool cs_cdtvram;
	int cs_cdtvcard;
	int cs_ide;
	bool cs_pcmcia;
	bool cs_a1000ram;
	int cs_fatgaryrev;
	int cs_ramseyrev;
	int cs_agnusrev;
	int cs_deniserev;
	int cs_mbdmac;
	bool cs_cdtvscsi;
	bool cs_a2091, cs_a4091;
	bool cs_df0idhw;
	bool cs_slowmemisfast;
	bool cs_resetwarning;
	bool cs_denisenoehb;
	bool cs_dipagnus;
	bool cs_agnusbltbusybug;

	TCHAR df[4][MAX_DPATH];
	TCHAR dfxlist[MAX_SPARE_DRIVES][MAX_DPATH];
	TCHAR romfile[MAX_DPATH];
	TCHAR romident[256];
	TCHAR romextfile[MAX_DPATH];
	TCHAR romextident[256];
	TCHAR keyfile[256];
	TCHAR flashfile[MAX_DPATH];
#ifdef ACTION_REPLAY
	TCHAR cartfile[MAX_DPATH];
	TCHAR cartident[256];
	int cart_internal;
#endif
	TCHAR pci_devices[256];
	TCHAR prtname[256];
	TCHAR sername[256];
	TCHAR amaxromfile[MAX_DPATH];
	TCHAR a2065name[MAX_DPATH];
	TCHAR cdimagefile[MAX_DPATH];
	TCHAR quitstatefile[MAX_DPATH];
#ifndef WIN32
	char scsi_device[256];
#endif

	TCHAR path_floppy[256];
	TCHAR path_hardfile[256];
	TCHAR path_rom[256];

	int m68k_speed;
	int cpu_model;
	int mmu_model;
	int cpu060_revision;
	int fpu_model;
	int fpu_revision;
	bool cpu_compatible;
	bool address_space_24;
	bool picasso96_nocustom;
	int picasso96_modeflags;

#ifdef HAVE_MACHDEP_TIMER
    int use_processor_clock;
#endif

	uae_u32 z3fastmem_size, z3fastmem2_size;
	uae_u32 z3fastmem_start;
	uae_u32 z3chipmem_size;
	uae_u32 z3chipmem_start;
	uae_u32 fastmem_size;
	uae_u32 chipmem_size;
	uae_u32 bogomem_size;
	uae_u32 mbresmem_low_size;
	uae_u32 mbresmem_high_size;
	uae_u32 gfxmem_size;
	uae_u32 custom_memory_addrs[MAX_CUSTOM_MEMORY_ADDRS];
	uae_u32 custom_memory_sizes[MAX_CUSTOM_MEMORY_ADDRS];

	bool kickshifter;
	bool filesys_no_uaefsdb;
	bool filesys_custom_uaefsdb;
	bool mmkeyboard;
	int uae_hide;

	struct uaedev_mount_info *mountinfo;
	int mountitems;
	struct uaedev_config_info mountconfig[MOUNT_CONFIG_SIZE];

	int nr_floppies;
	int dfxtype[4];
#ifdef DRIVESOUND
	int dfxclick[4];
	TCHAR dfxclickexternal[4][256];
	int dfxclickvolume;
#endif

	int hide_cursor;				/* Whether to hide host WM cursor or not */

	/* Target specific options */
#ifdef USE_X11_GFX
	int x11_use_low_bandwidth;
	int x11_use_mitshm;
	int x11_use_dgamode;
	int x11_hide_cursor;
#endif

#ifdef USE_SVGALIB_GFX
	int svga_no_linear;
#endif

#ifdef _WIN32
	bool win32_middle_mouse;
	bool win32_logfile;
	bool win32_notaskbarbutton;
	bool win32_alwaysontop;
	bool win32_powersavedisabled;
	bool win32_minimize_inactive;

	int win32_active_priority;
	int win32_inactive_priority;
	bool win32_inactive_pause;
	bool win32_inactive_nosound;
	int win32_iconified_priority;
	bool win32_iconified_pause;
	bool win32_iconified_nosound;

	bool win32_rtgmatchdepth;
	bool win32_rtgscaleifsmall;
	bool win32_rtgallowscaling;
	int win32_rtgscaleaspectratio;
	int win32_rtgvblankrate;
	bool win32_borderless;
	bool win32_ctrl_F11_is_quit;
	bool win32_automount_removable;
	bool win32_automount_drives;
	bool win32_automount_cddrives;
	bool win32_automount_netdrives;
	bool win32_automount_removabledrives;
	int win32_midioutdev;
	int win32_midiindev;
	int win32_uaescsimode;
	int win32_soundcard;
	int win32_samplersoundcard;
	bool win32_soundexclusive;
	bool win32_norecyclebin;
	int win32_specialkey;
	int win32_guikey;
	int win32_kbledmode;
	TCHAR win32_commandpathstart[MAX_DPATH];
	TCHAR win32_commandpathend[MAX_DPATH];
#endif

#ifdef USE_CURSES_GFX
	int curses_reverse_video;
#endif

#if defined USE_SDL_GFX || defined USE_X11_GFX
	int map_raw_keys;
#endif
	int use_gl;

#ifdef USE_AMIGA_GFX
	int  amiga_screen_type;
	char amiga_publicscreen[256];
	int  amiga_use_grey;
	int  amiga_use_dither;
#endif

#ifdef SAVESTATE
	bool statecapture;
	int statecapturerate, statecapturebuffersize;
#endif

	/* input */

	struct jport jports[MAX_JPORTS];
	int input_selected_setting;
	int input_joymouse_multiplier;
	int input_joymouse_deadzone;
	int input_joystick_deadzone;
	int input_joymouse_speed;
	int input_analog_joystick_mult;
	int input_analog_joystick_offset;
	int input_autofire_linecnt;
	int input_mouse_speed;
	int input_tablet;
	bool input_magic_mouse;
	int input_magic_mouse_cursor;
	struct uae_input_device joystick_settings[MAX_INPUT_SETTINGS][MAX_INPUT_DEVICES];
	struct uae_input_device mouse_settings[MAX_INPUT_SETTINGS][MAX_INPUT_DEVICES];
	struct uae_input_device keyboard_settings[MAX_INPUT_SETTINGS][MAX_INPUT_DEVICES];
	int dongle;
};

extern int config_changed;
extern void config_check_vsync (void);

/* Contains the filename of .uaerc */
//extern TCHAR optionsfile[];
extern void save_options (FILE *, const struct uae_prefs *, int);

extern void cfgfile_write (FILE *f, const char *format,...);
extern void cfgfile_dwrite (FILE *f, const TCHAR *option, const TCHAR *format,...);
extern void cfgfile_target_write (FILE *f, const TCHAR *option, const TCHAR *format,...);
extern void cfgfile_target_dwrite (FILE *f, const TCHAR *option, const TCHAR *format,...);

extern void cfgfile_write_bool (FILE *f, const TCHAR *option, int b);
extern void cfgfile_dwrite_bool (FILE *f,const  TCHAR *option, int b);
extern void cfgfile_target_write_bool (FILE *f, const TCHAR *option, int b);
extern void cfgfile_target_dwrite_bool (FILE *f, const TCHAR *option, int b);

extern void cfgfile_write_str (FILE *f, const TCHAR *option, const TCHAR *value);
extern void cfgfile_dwrite_str (FILE *f, const TCHAR *option, const TCHAR *value);
extern void cfgfile_target_write_str (FILE *f, const TCHAR *option, const TCHAR *value);
extern void cfgfile_target_dwrite_str (FILE *f, const TCHAR *option, const TCHAR *value);

extern void default_prefs (struct uae_prefs *, int);
extern void discard_prefs (struct uae_prefs *, int);

extern void prefs_set_attr (const char *key, const char *value);
extern const char *prefs_get_attr (const char *key);

extern int cfgfile_yesno  (const char *option, const char *value, const char *name, bool *location);
extern int cfgfile_intval (const char *option, const char *value, const char *name, int *location, int scale);
extern int cfgfile_strval (const char *option, const char *value, const char *name, int *location, const char *table[], int more);
extern int cfgfile_string (const char *option, const char *value, const char *name, char *location, int maxsz);
extern char *cfgfile_subst_path (const char *path, const char *subst, const char *file);
extern void cfgfile_subst_home (char *path, unsigned int maxlen);

int parse_cmdline_option (struct uae_prefs *, char, char *);

extern int  machdep_parse_option (struct uae_prefs *, const char *option, const char *value);
extern void machdep_save_options (FILE *, const struct uae_prefs *);
extern void machdep_default_options (struct uae_prefs *);

extern int  target_parse_option (struct uae_prefs *, const char *option, const char *value);
extern void target_save_options (FILE *, const struct uae_prefs *);
extern void target_default_options (struct uae_prefs *);

extern int  gfx_parse_option (struct uae_prefs *, const char *option, const char *value);
extern void gfx_save_options (FILE *, const struct uae_prefs *);
extern void gfx_default_options (struct uae_prefs *);

extern void audio_default_options (struct uae_prefs *p);
extern void audio_save_options (FILE *f, const struct uae_prefs *p);
extern int  audio_parse_option (struct uae_prefs *p, const char *option, const char *value);

extern int cfgfile_load (struct uae_prefs *p, const char *filename, int *type, int ignorelink, int userconfig);
extern int cfgfile_save (const struct uae_prefs *, const char *filename, int);
extern void cfgfile_parse_line (struct uae_prefs *p, char *, int);
extern int cfgfile_parse_option (struct uae_prefs *p, char *option, char *value, int);
extern int cfgfile_get_description (const char *filename, char *description, char *hostlink, char *hardwarelink, int *type);
extern void cfgfile_show_usage (void);
extern uae_u32 cfgfile_uaelib(int mode, uae_u32 name, uae_u32 dst, uae_u32 maxlen);
extern uae_u32 cfgfile_uaelib_modify (uae_u32 mode, uae_u32 parms, uae_u32 size, uae_u32 out, uae_u32 outsize);
extern uae_u32 cfgfile_modify (uae_u32 index, char *parms, uae_u32 size, char *out, uae_u32 outsize);
extern void cfgfile_addcfgparam (char *);
extern unsigned int cmdlineparser (const char *s, char *outp[], unsigned int max);
extern int cfgfile_configuration_change(int);
extern void fixup_prefs_dimensions (struct uae_prefs *prefs);
extern void fixup_prefs (struct uae_prefs *prefs);
extern void fixup_cpu (struct uae_prefs *prefs);

extern void check_prefs_changed_custom (void);
extern void check_prefs_changed_cpu (void);
extern void check_prefs_changed_audio (void);
extern int check_prefs_changed_gfx (void);

extern struct uae_prefs currprefs, changed_prefs;

extern int machdep_init (void);
extern void machdep_free (void);

/* AIX doesn't think it is Unix. Neither do I. */
#if defined(_ALL_SOURCE) || defined(_AIX)
#undef __unix
#define __unix
#endif

#define MAX_COLOR_MODES 5

/* #define NEED_TO_DEBUG_BADLY */

#if !defined(USER_PROGRAMS_BEHAVE)
#define USER_PROGRAMS_BEHAVE 0
#endif

/* Some memsets which know that they can safely overwrite some more memory
 * at both ends and use that knowledge to align the pointers. */

#define QUADRUPLIFY(c) (((c) | ((c) << 8)) | (((c) | ((c) << 8)) << 16))

/* When you call this routine, bear in mind that it rounds the bounds and
 * may need some padding for the array. */

#define fuzzy_memset(p, c, o, l) fuzzy_memset_1 ((p), QUADRUPLIFY (c), (o) & ~3, ((l) + 4) >> 2)
STATIC_INLINE void fuzzy_memset_1 (void *p, uae_u32 c, int offset, int len)
{
    uae_u32 *p2 = (uae_u32 *)((TCHAR *)p + offset);
    int a = len & 7;
    len >>= 3;
    switch (a) {
     case 7: p2--; goto l1;
     case 6: p2-=2; goto l2;
     case 5: p2-=3; goto l3;
     case 4: p2-=4; goto l4;
     case 3: p2-=5; goto l5;
     case 2: p2-=6; goto l6;
     case 1: p2-=7; goto l7;
     case 0: if (!--len) return; break;
    }

    for (;;) {
	p2[0] = c;
	l1:
	p2[1] = c;
	l2:
	p2[2] = c;
	l3:
	p2[3] = c;
	l4:
	p2[4] = c;
	l5:
	p2[5] = c;
	l6:
	p2[6] = c;
	l7:
	p2[7] = c;

	if (!len)
	    break;
	len--;
	p2 += 8;
    }
}

/* This one knows it will never be asked to clear more than 32 bytes.  Make sure you call this with a
   constant for the length.  */
#define fuzzy_memset_le32(p, c, o, l) fuzzy_memset_le32_1 ((p), QUADRUPLIFY (c), (o) & ~3, ((l) + 7) >> 2)
STATIC_INLINE void fuzzy_memset_le32_1 (void *p, uae_u32 c, int offset, int len)
{
    uae_u32 *p2 = (uae_u32 *)((TCHAR *)p + offset);

    switch (len) {
     case 9: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; p2[4] = c; p2[5] = c; p2[6] = c; p2[7] = c; p2[8] = c; break;
     case 8: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; p2[4] = c; p2[5] = c; p2[6] = c; p2[7] = c; break;
     case 7: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; p2[4] = c; p2[5] = c; p2[6] = c; break;
     case 6: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; p2[4] = c; p2[5] = c; break;
     case 5: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; p2[4] = c; break;
     case 4: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; break;
     case 3: p2[0] = c; p2[1] = c; p2[2] = c; break;
     case 2: p2[0] = c; p2[1] = c; break;
     case 1: p2[0] = c; break;
     case 0: break;
     default: printf("Hit the programmer.\n"); break;
    }
}

#if defined TARGET_AMIGAOS && defined(__GNUC__)
#include "od-amiga/amiga-kludges.h"
#endif