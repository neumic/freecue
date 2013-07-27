#! /usr/bin/python

from gi.repository import GObject
from gi.repository import GLib
from gi.repository import Gst

class Cue:
   def __init__(self, name="", parent=None, media=None, message=None):
      self.name    = name
      self.parent  = parent
      self.media   = media
      self.message = message

   def execute(self):
      #for now, reads message and executes CueAudio functions
      if self.message == "play":
         self.media.play()
      elif self.message == "pause":
         self.media.pause()

   def get_info(self):
      return [self.name, self.media]

   def set_media(media):
      self.media = media

class CueAudio:
   def __init__(self):
      Gst.init_check(None)
      # Playbin is a simple element which plays video and audio in many codecs
      self.player = Gst.parse_launch("playbin uri=file:///home/nickm/projects/opencue/Big\ Max\ and\ Jungle\ Jacob.m4a")

   def play(self):
      self.player.set_state(Gst.State.PLAYING)

   def pause(self):
      self.player.set_state(Gst.State.PAUSED)

   def ready(self):
      self.player.set_state(Gst.State.READY)
      
   def null(self):
      self.player.set_state(Gst.State.NULL)
      
