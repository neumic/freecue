#ifndef _cue_h
#define _cue_h

#include <gst/gst.h>
#include "media.h"

enum cueType {
   PLAY,
   PAUSE,
   STOP
};

typedef enum cueType cueType;

struct Cue {
   MediaObject* media_object;
   cueType type;
};

typedef struct Cue Cue;

struct Cue* Cue_create( MediaObject*, cueType );

void Cue_destroy( Cue* );

void Cue_print( Cue* );

void Cue_set_type( Cue*, cueType );

void Cue_set_media( Cue*, MediaObject* );

void Cue_run( Cue* );

#endif
