#include <gst/gst.h>
#include <glib.h>
#include "media.h"

MediaObject* MediaObject_create( char* uri ){
   MediaObject* media = malloc( sizeof* media );
   if( NULL == media ) return NULL; //figure out error handling paradigm

   media -> pipeline = gst_element_factory_make( "playbin", "pipeline" );
   //error handling here

   g_object_set( G_OBJECT( media -> pipeline ), "uri", uri,  NULL);
}

void MediaObject_destroy( MediaObject* media ){
   gst_object_unref( GST_OBJECT( media -> pipeline ) );
   free(media);
}

void MediaObject_play( MediaObject* ){}
void MediaObject_pause( MediaObject* ){}
void MediaObject_stop( MediaObject* ){}
