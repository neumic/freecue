#include <gst/gst.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include <limits.h>

#include "cue.h"
#include "media.h"

static gboolean bus_call( GstBus*     bus,
                          GstMessage* msg,
                          gpointer    data )
{
   GMainLoop* loop = (GMainLoop *) data;

   switch( GST_MESSAGE_TYPE( msg ) ){
      case GST_MESSAGE_EOS:
         g_print( "End of stream\n");
         g_main_loop_quit( loop );
         break;

      case GST_MESSAGE_ERROR: {
         gchar*  debug;
         GError* error;

         gst_message_parse_error( msg, &error, &debug );
         g_free( debug );

         g_printerr( "Error: %s\n", error->message);
         g_error_free( error );

         g_main_loop_quit( loop );
         break;
      }

      default:
         break;
   }

   return TRUE;
}

gchar* path_to_uri( gchar* path, gchar* working_dir ){
   gchar* uri = {0};
   if( g_path_is_absolute( path ) ){
      uri = g_filename_to_uri( path, NULL, NULL );
   }
   else{
      uri = g_filename_to_uri( g_build_filename( working_dir, path, NULL ), NULL, NULL );
   }

   return uri;
}

void print_media_array( GArray* media_array ){
   gint i;
   for(i = 0; i < (media_array -> len); i++) {
      MediaObject_print( g_array_index( media_array, MediaObject*, i ) );
   }
}
   


int main( int argc, gchar* argv[] ){
   GMainLoop *loop;

   GstBus *bus;
   guint bus_watch_id;

   gst_init( &argc, &argv );

   loop = g_main_loop_new( NULL, FALSE );

   gchar* uri;
   MediaObject* media_object;
   GArray* media_array = g_array_new( FALSE, FALSE, sizeof (MediaObject*) );
   gint i = 1;

   for(i = 1; i < argc; i++) {
      uri = path_to_uri( argv[i], g_get_current_dir() );
      media_object = MediaObject_create( uri );
      g_array_append_val( media_array, media_object );
   }

   print_media_array( media_array );

   struct Cue* cue = Cue_create( g_array_index( media_array, MediaObject*, 0 ), PLAY );
   Cue_print( cue );

   bus = gst_pipeline_get_bus( GST_PIPELINE( g_array_index( media_array, MediaObject*, 0 ) -> pipeline ) );
   bus_watch_id = gst_bus_add_watch( bus, bus_call, loop );
   gst_object_unref( bus );

   Cue_run( cue );

   g_main_loop_run( loop );
   g_print( "returned, stopping.\n");

   Cue_destroy( cue );
   for(i = 0; i < (media_array -> len); i++) {
      MediaObject_destroy( g_array_index( media_array, MediaObject*, i ) );
   }
   g_source_remove( bus_watch_id );
   g_main_loop_unref( loop );

   return 0;
}


