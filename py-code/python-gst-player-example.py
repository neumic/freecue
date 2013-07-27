from gi.repository import GObject
from gi.repository import GLib
from gi.repository import Gtk
from gi.repository import Gst

class PlaybackInterface:

   def __init__(self):
      self.is_playing = False

      # A free example sound track
      #self.uri = "http://cdn02.cdn.gorillavsbear.net/wp-content/uploads/2012/10/GORILLA-VS-BEAR-OCTOBER-2012.mp3"
      self.uri = "file:///home/nickm/projects/opencue/Hurricane_Connie_1955.ogg"

      # GTK window and widgets
      self.window = Gtk.Window()
      self.window.connect("delete-event", Gtk.main_quit)
      self.window.set_size_request(300,50)

      # GTK box
      vbox = Gtk.Box(Gtk.Orientation.HORIZONTAL, 0)
      vbox.set_margin_top(3)
      vbox.set_margin_bottom(3)
      self.window.add(vbox)

      # Play/Stop Button
      self.playButtonImage = Gtk.Image()
      self.playButtonImage.set_from_stock("gtk-media-play", Gtk.IconSize.BUTTON)
      self.playButton = Gtk.Button.new()
      self.playButton.add(self.playButtonImage)
      self.playButton.connect("clicked", self.playToggled)
      Gtk.Box.pack_start(vbox, self.playButton, False, False, 0)

      # Play time slider
      self.slider = Gtk.HScale()
      self.slider.set_margin_left(6)
      self.slider.set_margin_right(6)
      self.slider.set_draw_value(False)
      self.slider.set_range(0, 100)
      self.slider.set_increments(1, 10)
      Gtk.Box.pack_start(vbox, self.slider, True, True, 0)

      # Time text
      self.label = Gtk.Label(label='0:00')
      self.label.set_margin_left(6)
      self.label.set_margin_right(6)
      Gtk.Box.pack_start(vbox, self.label, False, False, 0)

      self.window.show_all()

      # GStreamer Setup
      Gst.init_check(None)
      self.IS_GST010 = Gst.version()[0] == 0
      # Playbin is a simple element which plays video and audio in many codecs
      self.player = Gst.ElementFactory.make("playbin", "player")
      #I think this should go here not in play()
      self.player.set_property("uri", self.uri)

      #Send Video to a fake output
      fakesink = Gst.ElementFactory.make("fakesink", "fakesink")
      self.player.set_property("video-sink", fakesink)

      #Don't understand busses yet, need to go read that
      bus = self.player.get_bus()
      #bus.add_signal_watch_full()
      bus.connect("message", self.on_message)
      self.player.connect("about-to-finish",  self.on_finished)

   def on_message(self, bus, message):
   #Callback for messages
      t = message.type
      if t == Gst.Message.EOS:
          self.stop()
      elif t == Gst.Message.ERROR:
          err, debug = message.parse_error()
          print("Error: ",  err, debug)
          self.stop()


   def on_finished(self, player):
   #Misnamed callback for some close to end execution? called ~4 time on last test
      self.is_playing = False
      self.slider.set_value(0)
      self.label.set_text("0:00")
      print("i'm out")


   def play(self):
      self.player.set_state(Gst.State.PLAYING)
      GObject.timeout_add(1000, self.updateSlider)
      self.is_playing = True
      self.updateButtons()
      print("Playing")

   def stop(self):
      self.player.set_state(Gst.State.READY)
      self.is_playing = False
      self.updateButtons()
      print("STOPPING")

     
   def playToggled(self, w):
   #This should be factored out I think
      self.slider.set_value(0)
      #self.label.set_text("0:00")

      if(self.is_playing == False):
          self.play()
      else:
          self.stop()
      self.updateButtons()

   def updateSlider(self):
   #this isn't working at all
      if(self.is_playing == False):
        return False # cancel timeout

      try:
        if self.IS_GST010:
           nanosecs = self.player.query_position(Gst.Format.TIME)[2]
           duration_nanosecs = self.player.query_duration(Gst.Format.TIME)[2]
        else:
           nanosecs = self.player.query_position(Gst.Format.TIME)[1]
           duration_nanosecs = self.player.query_duration(Gst.Format.TIME)[1]

        # block seek handler so we don't seek when we set_value()
        # self.slider.handler_block_by_func(self.on_slider_change)

        duration = float(duration_nanosecs) / Gst.SECOND
        position = float(nanosecs) / Gst.SECOND
        self.slider.set_range(0, duration)
        self.slider.set_value(position)
        self.label.set_text ("%d" % (position / 60) + ":%02d" % (position % 60))

        #self.slider.handler_unblock_by_func(self.on_slider_change)

      except Exception as e:
          # pipeline must not be ready and does not know position
          print(e)
          pass

      return True

   def updateButtons(self):
   #maybe factor out as well?
        if(self.is_playing == False):
           self.playButtonImage.set_from_stock("gtk-media-play", Gtk.IconSize.BUTTON)
        else:
           self.playButtonImage.set_from_stock("gtk-media-stop", Gtk.IconSize.BUTTON)

if __name__ == "__main__":
     PlaybackInterface()
     Gtk.main()
