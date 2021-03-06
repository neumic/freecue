#include <gst/gst.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cue.h"

//TODO: add fuction description comments

Cue* Cue_create( MediaObject* media_object, cueType type ){
   Cue *cue = malloc( sizeof *cue );
   //TODO: error check

   cue -> media_object = media_object;
   cue -> type         = type;

   return cue;
}

void Cue_destroy( Cue* cue){
   assert( NULL != cue ); //switch to non-assert error handling

   free(cue);
}

void Cue_print( Cue* cue){
   printf( "This is a cue. More details to come.\n" );
}

void Cue_set_state( Cue* cue, cueType type ){
   cue -> type = type;
   //TODO: error check
}

void Cue_set_media( Cue* cue, MediaObject* media_object ){
   cue -> media_object = media_object;
   //TODO: error check
}

void Cue_run( Cue* cue){
   switch( cue -> type ) {
      case PLAY:
         MediaObject_play( cue -> media_object );
         break;
      case PAUSE:
         MediaObject_pause( cue -> media_object );
         break;
      case STOP:
         MediaObject_stop( cue -> media_object );
         break;
   }
   //TODO: error check
}
