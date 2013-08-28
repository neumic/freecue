#ifndef _cue_h
#define _cue_h

#include <gst/gst.h>

struct Cue {
   GstElement* media_pipeline;
   GstState media_state;
};

struct Cue* Cue_create( GstElement*, GstState );

void Cue_destroy( struct Cue* );

void Cue_print( struct Cue* );

void Cue_set_state( struct Cue*, GstState );

void Cue_set_media( struct Cue*, GstElement* );

void Cue_run( struct Cue* );

#endif
