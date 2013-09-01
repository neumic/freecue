#include <gst/gst.h>
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "media.h"

//TODO: add fuction description comments

MediaObject* MediaObject_create( char* uri ){
   MediaObject* media_object = malloc( sizeof *media_object );
   if( NULL == media_object ) return NULL; //TODO: figure out error handling paradigm

   media_object -> pipeline = gst_element_factory_make( "playbin", "pipeline" );
   if( NULL == media_object -> pipeline ) printf("fuck");
   //TODO: figure out error handling paradigm

   g_object_set( G_OBJECT( media_object -> pipeline ), "uri", uri,  NULL );

   return media_object;
}

void MediaObject_destroy( MediaObject* media_object ){
   gst_object_unref( GST_OBJECT( media_object -> pipeline ) );
   free( media_object );
}

void MediaObject_print( MediaObject* media_object ){
   //TODO: unstubbify
   printf( "MediaObject_print stub\n" );
}

void MediaObject_play( MediaObject* media_object ){
   gst_element_set_state( media_object -> pipeline, GST_STATE_PLAYING );
}

void MediaObject_pause( MediaObject* media_object ){
   gst_element_set_state( media_object -> pipeline, GST_STATE_PAUSED );
}

void MediaObject_stop( MediaObject* media_object ){
   gst_element_set_state( media_object -> pipeline, GST_STATE_NULL );
}
