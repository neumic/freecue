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

void menu_prompt( GIOChannel* g_io_channel ){
   //TODO: add error handling. check code @ http://www.linuxjournal.com/node/8545/print
   GError *error = NULL;
   gchar* input_str;
   print_options();
   g_print("> ");
   g_io_channel_read_line( g_io_channel, &input_str, NULL, NULL, &error );
   g_print( "read: %s", input_str );
   switch( input_str[0] ){
      case 'a':
      case 'A':
         g_print( "add cue\n" );
         break;
      default:
         g_print( "not recognized\n" );
         break;
   }
}
   
void menu_cue_add( GArray* media_array, GArray* cue_array, GIOChannel* g_io_channel);
void menu_cue_delete( GArray* media_array, GArray* cue_array, GIOChannel* g_io_channel );
void menu_cue_select( GArray* media_array, GArray* cue_array, GIOChannel* g_io_channel );
