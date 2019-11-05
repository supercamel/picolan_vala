using Gee;

namespace picolan
{
	public enum SOCKET_STATE
	{
		CLOSED,
		SYN_SENT,
		LISTENING,
		SYN_RECVED,
		PENDING,
		OPEN
	}

	internal enum MESSAGE_TYPE
	{
		ACK,
		SYN,
		DATA,
		CLOSE,
		HEARTBEAT
	}


	public class SocketStream : Object, Socket
	{

		public uint8 get_port() {
			return port;
		}

		protected void send_ack() throws PicolanError, Error {
			var msg = new ArrayList<uint8>();
			msg.add(MESSAGE_TYPE.ACK);
			msg.add(remote_sequence);
			iface.send_datagram(remote, remote_port, msg);
		}

		private async bool send_syn() throws PicolanError, Error {

		}

		private async bool recv_syn() throws PicolanError, Error {
			SourceFunc callback = recv_syn.callback;
			bool got_syn = false;
			uint timeout_handle = 0;
			ulong sig_handle = 0;
			sig_handle = recv_syn_signal.connect((data) => {
				got_syn = true;
				Idle.add((owned)callback);
				disconnect(sig_handle);
				GLib.Source.remove(timeout_handle);
			});

			timeout_handle = GLib.Timeout.add(timeout, () => {
				Idle.add((owned)callback);
				disconnect(sig_handle);
				return false;
			});

			yield;
			return got_syn;
		}

		public virtual void bind(Interface iface) { }

		protected signal void recv_syn_signal(ArrayList<uint8> data);
		protected signal void ack_signal(ArrayList<uint8> data);

		public uint timeout = 1000;

		protected Interface iface;
		protected uint8 port = 0;
		protected SOCKET_STATE state = SOCKET_STATE.CLOSED;
		protected uint8 sequence;
		protected uint8 remote;
		protected uint8 remote_sequence;
		protected uint8 remote_port;
		protected uint8 last_ack;
	}

}


