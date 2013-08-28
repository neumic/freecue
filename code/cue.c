#include <gst/gst.h>
#include "cue.h"

struct Cue* Cue_create( GstElement* pipeline, GstState state ){
   struct Cue *cue = malloc( sizeof( struct Cue ) );
   assert( cue != NULL ); //I don't know if this is the correct thing to check

   cue -> media_pipeline = pipeline;
   cue -> media_state    = state;

   return cue;
}

void Cue_destroy( struct Cue* cue){
   return void;
}

void Cue_print( struct Cue* cue){
   return void;
}

void Cue_set_state( struct Cue* cue, GstState state ){
   return void;
}

void Cue_set_media( struct Cue*, GstElement* pipeline ){
   return void;
}

void Cue_run( struct Cue* cue){
   return void;
}
