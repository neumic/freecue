#include <gst/gst.h>
#include <stdlib.h>

GstElement* pipeline_array [100];
int pipeline_array_size = 0;

void add_pipeline( char* uri ){
   GstElement* pipeline = gst_pipeline_new( "audio-player" );
   GstElement* player  = gst_element_factory_make( "playbin", "player" );
   g_object_set( G_OBJECT( player ), "uri", uri, NULL );
   gst_bin_add( GST_BIN( pipeline ), player );
   pipeline_array[pipeline_array_size] = pipeline;
   pipeline_array_size++;
}

struct Cue {
   GstElement* pipeline;
   GstState cueState;
   struct Cue* nextCue;
};

int main( int argc, char* argv[] ){
   GMainLoop* loop;

   gst_init( &argc, &argv );

   loop = g_main_loop_new( NULL, FALSE );

   add_pipeline( "file:///home/nickm/projects/opencue/Hurricane_Connie_1955.ogg" );
   add_pipeline( "file:///home/nickm/projects/opencue/Hurricane_Connie_1955.ogg" );

   gst_element_set_state( pipeline_array[0], GST_STATE_PLAYING );

   g_print( "hurderp" );
   g_main_loop_run( loop );
   gst_element_set_state( pipeline_array[1], GST_STATE_NULL );

   return 0;
}


