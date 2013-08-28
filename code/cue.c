#include <gst/gst.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cue.h"

struct Cue* Cue_create( GstElement* pipeline, GstState state ){
   struct Cue *cue = malloc( sizeof( struct Cue ) );
   assert( NULL != cue ); //I don't know if this is the correct thing to check

   cue -> media_pipeline = pipeline;
   cue -> media_state    = state;

   return cue;
}

void Cue_destroy( struct Cue* cue){
   assert( NULL != cue );

   free(cue);
}

void Cue_print( struct Cue* cue){
   printf( "This is a cue. More details to come.\n" );
}

void Cue_set_state( struct Cue* cue, GstState state ){
   cue -> media_state = state;
}

void Cue_set_media( struct Cue* cue, GstElement* pipeline ){
   cue -> media_pipeline = pipeline;
}

void Cue_run( struct Cue* cue){
   gst_element_set_state( cue -> media_pipeline, cue -> media_state );
}
