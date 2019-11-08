
namespace picolan
{
	public class Datagram : Object, Socket
	{
		public Datagram(uint8 _port) {
			port = _port;
			timeout = 1000;
		}

		~Datagram() {
			on_destroy();
		}

		public void send_bytes(uint8 dest, uint8 port, List<uint8> data) throws PicolanError {
			const uint MAX_SEGMENT_SIZE = 250;
			uint parts = data.length()/MAX_SEGMENT_SIZE;
			List<uint8> segment_data;
			for(var i = 0; i < parts; i++) {
				segment_data = new List<uint8>();
				for(var j = 0; j < MAX_SEGMENT_SIZE; j++) {
					segment_data.append(data.nth_data(i*MAX_SEGMENT_SIZE + j));
				}

				try {
					iface.send_datagram(dest, port, segment_data);
				} catch(GLib.Error error) {
					throw new PicolanError.COMS_FAULT("%s", error.message);
				}
			}

			var remainder = data.length()%250;
			segment_data = new List<uint8>(); 
			for(var j = 0; j < remainder; j++) {
				segment_data.append(data.nth_data(parts*MAX_SEGMENT_SIZE+j));	
			}
			try {
				iface.send_datagram(dest, port, segment_data);
			} catch(GLib.Error error) {
				throw new PicolanError.COMS_FAULT("%s", error.message);
			}
		}

		public void send_string(uint8 dest, uint8 port, string str) throws PicolanError {
			var arr = new List<uint8>();
			for(var i = 0; i < str.length; i++) {
				arr.append((uint8)str[i]);
			}

			send_bytes(dest, port, arr);
		}

		
		public void bind(Interface _iface) {
			iface = _iface;
			iface.attach_socket(this);
			iface.on_datagram.connect((src, dest, _port, payload) => {
				if(port == _port) {
					on_data(payload);
				}
			});
		}

		/*
		public void receive_data(uint8 from, ArrayList<uint8> data) {
			remote = from;
			on_data(data);
		}
		*/

		public uint8 get_port() {
			return port;
		}

		private Interface iface;
		public uint8 remote = 0;

		public uint timeout;
		private uint8 port;

	}

}

