/* picolan-1.0.vapi generated by valac.exe 0.44.3, do not modify. */

namespace picolan {
	[CCode (cheader_filename = "picolan.h")]
	public class AddressField {
		public AddressField ();
		public bool get_address (uint8 addr);
		public uint8[] get_bytes ();
		public void set_address (uint8 addr);
	}
	[CCode (cheader_filename = "picolan.h")]
	public class Client : picolan.SocketStream {
		public Client ();
		public override void bind (picolan.Interface _iface);
	}
	[CCode (cheader_filename = "picolan.h")]
	public class Datagram : GLib.Object, picolan.Socket {
		public uint8 remote;
		public uint timeout;
		public Datagram (uint8 _port);
		public void send_bytes (uint8 dest, uint8 port, Gee.ArrayList<uint8> data) throws picolan.PicolanError;
		public void send_string (uint8 dest, uint8 port, string str) throws picolan.PicolanError;
	}
	[CCode (cheader_filename = "picolan.h")]
	public class Interface : GLib.Object {
		public uint8 ttl;
		public Interface ();
		public bool attach_socket (picolan.Socket s);
		public void close ();
		public bool open (string port_name, int baud) throws GLib.Error;
		public async int ping (uint8 addr, uint timeout) throws GLib.Error;
		public void send_datagram (uint8 dest, uint8 port, Gee.ArrayList<uint8> data) throws picolan.PicolanError, GLib.Error;
		public void set_address (uint8 addr) throws GLib.Error;
		public void subscribe (uint8 port) throws GLib.Error;
		public void unsubscribe (uint8 port) throws GLib.Error;
		public signal void on_close ();
		public signal void on_datagram (uint8 src, uint8 dest, uint8 port, Gee.ArrayList<uint8> payload);
	}
	[CCode (cheader_filename = "picolan.h")]
	public class SocketStream : GLib.Object, picolan.Socket {
		protected picolan.Interface iface;
		protected uint8 last_ack;
		protected uint8 port;
		protected uint8 remote;
		protected uint8 remote_port;
		protected uint8 remote_sequence;
		protected uint8 sequence;
		protected picolan.SOCKET_STATE state;
		public uint timeout;
		public SocketStream ();
		public virtual void bind (picolan.Interface iface);
		protected void send_ack () throws picolan.PicolanError, GLib.Error;
		protected signal void ack_signal (Gee.ArrayList<uint8> data);
		protected signal void recv_syn_signal (Gee.ArrayList<uint8> data);
	}
	[CCode (cheader_filename = "picolan.h")]
	public interface Socket : GLib.Object {
		public abstract void bind (picolan.Interface iface);
		public abstract uint8 get_port ();
		public signal void on_data (Gee.ArrayList<uint8> data);
		public signal void on_destroy ();
	}
	[CCode (cheader_filename = "picolan.h")]
	public enum SOCKET_STATE {
		CLOSED,
		SYN_SENT,
		LISTENING,
		SYN_RECVED,
		PENDING,
		OPEN
	}
	[CCode (cheader_filename = "picolan.h")]
	public errordomain PicolanError {
		COMS_FAULT,
		PAYLOAD_TOO_BIG
	}
}
