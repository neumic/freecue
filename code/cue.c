#include <gst/gst.h>
#include <assert.h>
#include <stdlib.h>
#include "cue.h"

struct Cue* Cue_create( GstElement* pipeline, GstState state ){
   struct Cue *cue = malloc( sizeof( struct Cue ) );
   assert( cue != NULL ); //I don't know if this is the correct thing to check

   cue -> media_pipeline = pipeline;
   cue -> media_state    = state;

   return cue;
}

void Cue_destroy( struct Cue* cue){
}

void Cue_print( struct Cue* cue){
}

void Cue_set_state( struct Cue* cue, GstState state ){
}

void Cue_set_media( struct Cue* cue, GstElement* pipeline ){
}

void Cue_run( struct Cue* cue){
}
