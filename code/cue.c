#include "cue.h"

void add_pipeline( char* uri, GstElement* pipeline_array[], int* pipeline_array_size );
   GstElement* pipeline = gst_pipeline_new( "audio-player" );
   GstElement* player  = gst_element_factory_make( "playbin", "player" );
   g_object_set( G_OBJECT( player ), "uri", uri, NULL );
   gst_bin_add( GST_BIN( pipeline ), player );
   pipeline_array[pipeline_array_size] = pipeline;
   pipeline_array_size&++;
}

void run_cue( struct Cue cue ){
   gst_element_set_state( cue.pipeline, cue.state );
}



