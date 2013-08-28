#include <gst/gst.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "cue.h"
#include "media.h"

int main( int argc, char* argv[] ){
   GMainLoop *loop;

   gst_init( &argc, &argv );
   loop = g_main_loop_new( NULL, FALSE );

   MediaObject* media_object = MediaObject_create( 
      "file:///home/nickm/projects/opencue/Hurricane_Connie_1955.ogg" );

   struct Cue* cue = Cue_create( media_object, PLAY);

   Cue_print( cue );

   Cue_run( cue );

   g_main_loop_run( loop );

   Cue_destroy( cue );

   return 0;
}


