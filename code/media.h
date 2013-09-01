#ifndef _media_h
#define _media_h

#include <gst/gst.h>

//TODO: add fuction description comments

struct MediaObject {
   GstElement* pipeline;
};

typedef struct MediaObject MediaObject;

MediaObject* MediaObject_create( char* uri );

void MediaObject_destroy( MediaObject* );

void MediaObject_print( MediaObject* );

void MediaObject_play( MediaObject* );
void MediaObject_pause( MediaObject* );
void MediaObject_stop( MediaObject* );

#endif
