#include <gst/gst.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "cue.h"

int main( int argc, char* argv[] ){
   GMainLoop *loop;
   GstElement *media;

   gst_init( &argc, &argv );
   loop = g_main_loop_new( NULL, FALSE );

   media = gst_element_factory_make( "playbin", "media" );
   if( !media ) return -1;

   g_object_set( G_OBJECT( media ), "uri", 
      "file:///home/nickm/projects/opencue/Hurricane_Connie_1955.ogg", NULL);

   struct Cue* cue = Cue_create( media, GST_STATE_PLAYING );

   Cue_print( cue );

   Cue_run( cue );

   g_main_loop_run( loop );

   Cue_destroy( cue );

   gst_object_unref( GST_OBJECT( media ) );

   return 0;
}


