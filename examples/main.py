#!/usr/bin/python3

import gi
gi.require_version('picolan', '1.0')
gi.require_version('GLib', '2.0')
from gi.repository import picolan
from gi.repository import GLib

def on_close():
    print("Closed")

iface = picolan.Interface.new()
iface.open("/dev/pts/4", 1000000)

def on_ping(ping, result):
    time = ping.ping_finish(result)
    print(time)

iface.set_address(6)
iface.subscribe(12)

iface.ping(15, 1000, on_ping)

iface.connect("on-close", on_close)


loop = GLib.MainLoop()
loop.run()


