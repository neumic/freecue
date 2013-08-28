#include <gst/gst.h>
#include <glib.h>
#include <stdlib.h>
#include "media.h"

MediaObject* MediaObject_create( char* uri ){
   MediaObject* media_object = malloc( sizeof *media_object );
   if( NULL == media_object ) return NULL; //figure out error handling paradigm

   media_object -> pipeline = gst_element_factory_make( "playbin", "pipeline" );
   //error handling here

   g_object_set( G_OBJECT( media_object -> pipeline ), "uri", uri,  NULL );
   return media_object;
}

void MediaObject_destroy( MediaObject* media_object ){
   gst_object_unref( GST_OBJECT( media_object -> pipeline ) );
   free( media_object );
}

void MediaObject_play( MediaObject* media_object ){}
void MediaObject_pause( MediaObject* media_object ){}
void MediaObject_stop( MediaObject* media_object ){}
