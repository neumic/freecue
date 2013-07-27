#!/usr/bin/python

from gi.repository import GObject
from gi.repository import GLib
from gi.repository import Gtk
from opencue import *

class CueSheet(Gtk.Window):
   def __init__(self):
      self.cuelist = []
      self.cue_count = 0
      Gtk.Window.__init__(self, title="foo")
      self.connect("delete-event", Gtk.main_quit)

      #box
      self.box = Gtk.Box(spacing=6)
      self.add(self.box)

      #button
      self.button = Gtk.Button(label="Add")
      self.button.connect("clicked", self.add_cue)
      self.box.pack_start(self.button, True, True, 0)

      #listtreeshit
      self.treestore = Gtk.TreeStore(str, str)
      treeview = Gtk.TreeView(model=self.treestore)

      #Normal Text Column
      renderer_text = Gtk.CellRendererText()
      column_text = Gtk.TreeViewColumn("Cue Name", renderer_text, text=0)
      treeview.append_column(column_text)

      #CHANGEME
      renderer_text = Gtk.CellRendererText()
      column_text = Gtk.TreeViewColumn("Media", renderer_text, text=1)
      treeview.append_column(column_text)
      renderer_text.connect("clicked", self.print_test )

      self.box.pack_start(treeview, True, True, 0)

   def add_cue(self, widget):
      self.treestore.append(None, ["Cue " + str(self.cue_count), ""])
      self.cue_count += 1
      self.cuelist.append( Cue() )

   def print_test(self, widget):
      print("foobar")

if __name__ == "__main__":
   win = CueSheet()
   win.show_all()
   Gtk.main()
