#include "menu.h"

/*****
* prints out a GArray of MediaObject*
*****/
void print_media_array( GArray* media_array ){
   gint i;
   for(i = 0; i < (media_array -> len); i++) {
      MediaObject_print( g_array_index( media_array, MediaObject*, i ) );
   }
}
   
void print_cue_array( GArray* cue_array ){
   gint i;
   for(i = 0; i < (cue_array -> len); i++) {
      Cue_print( g_array_index( cue_array, Cue*, i ) );
   }
}

void print_options(){
   g_print("OPTIONS:\n");
}

void menu_prompt( GIOChannel* g_io_channel );
void menu_cue_add( GArray* media_array, GArray* cue_array, GIOChannel* g_io_channel);
void menu_cue_delete( GArray* media_array, GArray* cue_array, GIOChannel* g_io_channel );
void menu_cue_select( GArray* media_array, GArray* cue_array, GIOChannel* g_io_channel );
