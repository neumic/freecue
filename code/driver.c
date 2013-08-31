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
   

int main( int argc, gchar* argv[] ){
   gchar* uri = {0};

   if( argc > 1 ){
      uri = path_to_uri( argv[1], g_get_current_dir() );
   }
   GMainLoop *loop;

   GstBus *bus;
   guint bus_watch_id;

   gst_init( &argc, &argv );

   loop = g_main_loop_new( NULL, FALSE );

   MediaObject* media_object = MediaObject_create( uri );
      

   struct Cue* cue = Cue_create( media_object, PLAY );
   Cue_print( cue );

   bus = gst_pipeline_get_bus( GST_PIPELINE( media_object -> pipeline ) );
   bus_watch_id = gst_bus_add_watch( bus, bus_call, loop );
   gst_object_unref( bus );

   Cue_run( cue );

   g_main_loop_run( loop );
   g_print( "returned, stopping.\n");

   Cue_destroy( cue );
   MediaObject_destroy( media_object );
   g_source_remove( bus_watch_id );
   g_main_loop_unref( loop );

   return 0;
}


