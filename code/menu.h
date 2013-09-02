#ifndef _menu_h
#define _menu_h

#include <glib.h>
#include "cue.h"
#include "media.h"

void print_media_array( GArray* media_array );
void print_cue_array( GArray* cue_array );
void print_options();

void menu_prompt( GIOChannel* g_io_channel );
void menu_cue_add( GArray* media_array, GArray* cue_array, GIOChannel* g_io_channel);
void menu_cue_delete( GArray* media_array, GArray* cue_array, GIOChannel* g_io_channel );
void menu_cue_select( GArray* media_array, GArray* cue_array, GIOChannel* g_io_channel );

#endif
