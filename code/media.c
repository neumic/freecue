#include <gst/gst.h>
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "media.h"

MediaObject* MediaObject_create( char* uri ){
   MediaObject* media_object = malloc( sizeof *media_object );
   if( NULL == media_object ) return NULL; //figure out error handling paradigm

   media_object -> pipeline = gst_element_factory_make( "playbin", "pipeline" );
   if( NULL == media_object -> pipeline ) printf("fuck");

   g_object_set( G_OBJECT( media_object -> pipeline ), "uri", uri,  NULL );

   return media_object;
}

void MediaObject_destroy( MediaObject* media_object ){
   gst_object_unref( GST_OBJECT( media_object -> pipeline ) );
   free( media_object );
}

void MediaObject_play( MediaObject* media_object ){
   gst_element_set_state( media_object -> pipeline, GST_STATE_PLAYING );
   GstState* state = malloc( sizeof *state );
   gst_element_get_state( media_object -> pipeline, state, NULL, GST_CLOCK_TIME_NONE );
   if( GST_STATE_READY == *state ){
      printf( "stream claims to be playing" );
   }
}

void MediaObject_pause( MediaObject* media_object ){
   gst_element_set_state( media_object -> pipeline, GST_STATE_PAUSED );
}

void MediaObject_stop( MediaObject* media_object ){
   gst_element_set_state( media_object -> pipeline, GST_STATE_NULL );
}
