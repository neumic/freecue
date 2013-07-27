#!/usr/bin/python
from gi.repository import Gtk

class FuckinWindow(Gtk.Window):
   def __init__(self):
      Gtk.Window.__init__(self, title="FUCK YEAH")

      #button box
      self.box = Gtk.Box(spacing=6)
      self.add(self.box)

      #button1
      self.button = Gtk.Button(label="Click Here")
      self.button.connect("clicked", self.print_shit)
      self.box.pack_start(self.button, True, True, 0)

      #button2
      self.buttonalso = Gtk.Button(label="Die")
      self.buttonalso.connect("clicked", Gtk.main_quit)
      self.box.pack_start(self.buttonalso, True, True, 0)

      #listtreeshit
      self.treestore = Gtk.TreeStore(bool, str, str)
      self.treestore.append(None, [True, "Cue 1", "fuckall"])
      self.treestore.append(None, [True, "Cue 2", "fuckall"])
      self.treestore.append(None, [True, "Cue A", "fuckall"])

      treeview = Gtk.TreeView(model=self.treestore)

      #Active Toggle Column
      renderer_toggle = Gtk.CellRendererToggle()
      renderer_toggle.connect("toggled", self.active_toggled)
      column_toggle = Gtk.TreeViewColumn("Toggle", renderer_toggle, active=0)
      treeview.append_column(column_toggle)

      #Normal Text Column
      renderer_text = Gtk.CellRendererText()
      column_text = Gtk.TreeViewColumn("Text", renderer_text, text=0)
      treeview.append_column(column_text)

      #Editable text Column
      renderer_editabletext = Gtk.CellRendererText()
      renderer_editabletext.set_property("editable", True)
      column_editabletext = Gtk.TreeViewColumn("Edit Fuck", renderer_editabletext, text = 1)
      treeview.append_column(column_editabletext)
      renderer_editabletext.connect("edited", self.text_edited)

      self.box.pack_start(treeview, True, True, 0)

   def text_edited(self, widget, path, text):
      self.treestore[path][1] = text

   def active_toggled(self, widget, path):
      self.treestore[path][1] = not self.treestore[path]

   def print_shit(self, widget):
      print( "hello fucker" )

win = FuckinWindow()
win.connect("delete-event", Gtk.main_quit)
win.show_all()
Gtk.main()


