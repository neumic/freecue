#!/usr/bin/python
from gi.repository import Gst

Gst.init_check(None)
# Playbin is a simple element which plays video and audio in many codecs
player = Gst.ElementFactory.make("playbin", "player")
player.set_property("uri", "file:///home/nickm/projects/opencue/Big\ Max\ and\ Jungle\ Jacob.m4a")
#player.set_property("uri", "file:///home/nickm/projects/opencue/Hurricane_Connie_1955.ogg")
player.set_state(Gst.State.PLAYING)
