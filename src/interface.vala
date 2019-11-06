using gserial;


namespace picolan
{
	enum PACKET {/*{{{*/
		INVALID,
		GET_ADDR_LIST,
		ADDR,
		PING,
		PING_ECHO,
		DATAGRAM,
		SUBSCRIBE,
		NULL
	}/*}}}*/

	enum STATE {/*{{{*/
		START,
		ID,
		SIZE,
		DATA,
		CHECK1,
		CHECK2
	}/*}}}*/

	void make_checksum(List<uint8> bytes, out int sum1, out int sum2) { /*{{{*/
		var index = 0;
		sum1 = sum2 = 0;
		for(index = 0; index < bytes.length(); index++) {
			sum1 = (sum1 + bytes[index]) % 255;
			sum2 = (sum2 + sum1) % 255;
		}
	}/*}}}*/

	class Parser : Object /*{{{*/
	{
		public Parser() {/*{{{*/
			data = new List<uint8>();
		}/*}}}*/

		public void read(uint8 b) {/*{{{*/
			if((b == 0xAA) && (stuff_flag == false)) {
				stuff_flag = true;
			} else {
				if(stuff_flag == false) {
					if((b == 0xAB) || (b == 0xAC)) {
						state = STATE.START;
					}
				}
				stuff_flag = false;

				switch(state) { 
					case STATE.START: 
						if(b == 0xAB) {
							state = STATE.ID;
							data = new List<uint8>();
						}

						break;
					case STATE.ID: 
						id = b;
						state = STATE.SIZE;
						data.append(b);
						break;
					case STATE.SIZE: 
						size = b;
						state = STATE.DATA;
						data.append(b);
						break;
					case STATE.DATA: 
						data.append(b);
						// data.size-2 because the data array includes id and size bytes
						// whereas the size is only the length of the data section
						if(((data.length()-2) >= size) || (data.length() >= 255)) {
							state = STATE.CHECK1;
						}
						break;
					case STATE.CHECK1: 
						check1 = b;
						state = STATE.CHECK2;
						break;
					case STATE.CHECK2: 
						check2 = b;
						state = STATE.START;

						int cs1, cs2;
						make_checksum(data, out cs1, out cs2);

						if((cs1 == check1) && (cs2 == check2)) {
							data.delete_link(data.nth(0));
							data.delete_link(data.nth(0));
							parse_packet();
						}
						break;

				}
			}
		}/*}}}*/

		private void parse_packet() {/*{{{*/

			switch(id) {
				case PACKET.PING_ECHO: 
					on_ping_echo(data.nth_data(1), data.nth_data(2), data.nth_data(3), data.nth_data(4));
					break;
				case PACKET.PING: 
					on_ping(data.nth_data(1), data.nth_data(2), data.nth_data(3), data.nth_data(4));
					break;
				case PACKET.GET_ADDR_LIST: 
					on_get_addr_list();
					break;
				case PACKET.DATAGRAM:
					// deep copy the payload part to a new array
					var payload = new List<uint8>();
					for(var i = 4; i < data.length(); i++) {
						payload.append(data.nth_data(i));
					}

					on_datagram(data.nth_data(1), data.nth_data(2), data.nth_data(3), payload);
					break;
			}
		}/*}}}*/

		public signal void on_get_addr_list();/*{{{*/
		public signal void on_addr(uint8 addr);
		public signal void on_ping(uint8 src, uint8 dest, uint8 p1, uint8 p2);
		public signal void on_ping_echo(uint8 src, uint8 dest, uint8 p1, uint8 p2);
		public signal void on_datagram(uint8 src, uint8 dest, uint8 port, List<uint8> payload);

		private List<uint8> data;
		private uint8 id;
		private uint8 size;
		private STATE state;
		private uint8 check1;
		private uint8 check2;
		private bool stuff_flag = false;/*}}}*/
	}/*}}}*/


	public errordomain PicolanError {
		COMS_FAULT,
		PAYLOAD_TOO_BIG
	}

	public class Interface : Object
	{
		public Interface() {/*{{{*/
			parser = new Parser();
			port_map = new HashTable<uint8, Socket>();

			/*{{{*/
			parser.on_ping.connect((src, dest, p1, p2) => {
				var msg = new List<uint8>();
				msg.append(PACKET.PING_ECHO);
				msg.append(5); //packet size
				msg.append(ttl); //time to live
				msg.append(address); //source / own address
				msg.append(src); // destination address
				msg.append(p1);
				msg.append(p2);

				int cs1, cs2;
				make_checksum(msg, out cs1, out cs2);
				msg.append((uint8)cs1);
				msg.append((uint8)cs2);
				msg = stuff_bytes(msg);
				msg.append(0xAC);
				msg.insert(0xAB, 0);

				try {
					port.write(msg);
				} catch(Error error) {
					// silently ignore failures when replying to a ping
					stdout.printf("Error while responding to a ping.\n");
					stdout.printf("%s\n", error.message);

				}
			});
			/*}}}*/

			/*{{{*/
			parser.on_get_addr_list.connect(() => {
				try {
					set_address(this.address);
				} catch(Error error) {
					stdout.printf("Error responding to request for this address.\n");
					stdout.printf("%s\n", error.message);
				}
			});
			/*}}}*/

			/*{{{*/
			parser.on_datagram.connect((src, dest, port, payload) => {
				on_datagram(src, dest, port, payload);
				/*
				   if(dest == this.address) {
				   if(port_map.has_key(port)) {
				   port_map[port].receive_data(src, payload);
				   }
				   }
				 */
			});
			/*}}}*/

			/*{{{*/
			GLib.Timeout.add(10, () => {
				if(port.is_open()) {
					try {
						if(port.available() > 0) {
							uint len = port.available();
							var bytes = new GLib.Array<char>();
							port.read_bytes(len, out bytes);

							for(uint i = 0; i < bytes.length; i++) {
								parser.read(bytes.index(i));
							}
						}
					}
					catch(Error e) {
						stdout.printf("Error in loop: %s\n", e.message);
						port.close();
						on_close();
					}
				}
				return true;
			} , 1);
			/*}}}*/

		}/*}}}*/

		/*{{{*/
		public bool attach_socket(Socket s) {
			// if socket isn't attached for a port
			if(port_map.contains(s.get_port()) == false) {
				// attach it using the port map
				port_map.insert(s.get_port(), s);
				// connect the destruct signal to remove the socket from the port map when it no longer exists 
				s.on_destroy.connect(() => {
					port_map.remove(s.get_port());
				});
				return true;
			} else {
				return false;
			}
		}

		/*}}}*/

		public bool open(string port_name, int baud) throws GLib.Error {/*{{{*/
			port = new gserial.Port();	
			port.set_baud(baud);
			port.open(port_name);
			return port.is_open();
		}

		/*}}}*/

		public void close() {/*{{{*/
			port.close();
			on_close();
		}

		/*}}}*/

		public void set_address(uint8 addr) throws GLib.Error {/*{{{*/
			address = addr;

			var af = new AddressField();
			af.set_address(addr);

			var msg = new List<uint8>();
			msg.append(PACKET.ADDR);
			msg.append(32); //packet size
			msg.append(ttl);

			for(var i = 0; i < 32; i++) {
				msg.append(af.get_bytes()[i]);
			}

			int cs1, cs2;
			make_checksum(msg, out cs1, out cs2);
			msg.append((uint8)cs1);
			msg.append((uint8)cs2);
			msg = stuff_bytes(msg);
			msg.append(0xAC);
			msg.insert(0xAB, 0);

			port.write(msg);
		}/*}}}*/

		public void send_datagram(uint8 dest, uint8 port_num, List<uint8> data) throws PicolanError, Error { /*{{{*/
			if(data.length() >= 250) {
				throw new PicolanError.PAYLOAD_TOO_BIG("Payload size is greater than the maximum of 250 bytes");
			}

			var msg = new List<uint8>();
			msg.append(PACKET.DATAGRAM);
			msg.append((uint8)(data.length() + 5)); //packet size
			msg.append(this.ttl);
			msg.append(this.address);
			msg.append(dest);
			msg.append(port_num);
			msg.append((uint8)data.length());
			for(var i = 0; i < data.length(); i++) {
				msg.append(data.nth_data(i));
			}

			int cs1, cs2;
			make_checksum(msg, out cs1, out cs2);
			msg.append((uint8)cs1);
			msg.append((uint8)cs2);
			msg.append(0xAC);
			msg.insert(0xAB, 0);

			port.write(msg);
		}/*}}}*/

		public async int ping(uint8 addr, uint timeout) throws GLib.Error {/*{{{*/
			SourceFunc callback = ping.callback;
			uint8 payload1 = (uint8)Random.int_range(0, 255);
			uint8 payload2 = (uint8)Random.int_range(0, 255);

			int ping_time = -1;
			var timer = new Timer();
			uint timeout_handle = 0;
			ulong handle = 0;
			handle = parser.on_ping_echo.connect((src, dest, p1, p2) => {
				if((p1 == payload1) && (p2 == payload2)) {
					ulong micros = 0;
					timer.elapsed(out micros);
					ping_time = (int)(micros/1000);
					Idle.append((owned)callback);
					parser.disconnect(handle);
					GLib.Source.remove(timeout_handle);
				}
			});

			timeout_handle = GLib.Timeout.add(timeout, () => {
				Idle.append((owned)callback);
				parser.disconnect(handle);
				return false;
			});

			var msg = new List<uint8>();
			msg.append(PACKET.PING);
			msg.append(5); //packet size
			msg.append(ttl); //time to live
			msg.append(address); //source / own address
			msg.append(addr); // destination address
			msg.append(payload1);
			msg.append(payload2);

			int cs1, cs2;
			make_checksum(msg, out cs1, out cs2);
			msg.append((uint8)cs1);
			msg.append((uint8)cs2);
			msg = stuff_bytes(msg);
			msg.append(0xAC);
			msg.insert(0xAB, 0);

			port.write(msg);

			yield;
			return ping_time;
		}/*}}}*/

		public void subscribe(uint8 port_num) throws GLib.Error { /*{{{*/
			var msg = new List<uint8>();
			msg.append(PACKET.SUBSCRIBE);
			msg.append(4); // subscribe packet is 4 bytes
			msg.append(ttl);
			msg.append(port_num);
			msg.append(this.address);
			msg.append(1); // 1 for subscribe

			int cs1, cs2;
			make_checksum(msg, out cs1, out cs2);
			msg.append((uint8)cs1);
			msg.append((uint8)cs2);
			msg = stuff_bytes(msg);
			msg.append(0xAC);
			msg.insert(0xAB, 0);

			port.write(msg);
		}
		/*}}}*/

		public void unsubscribe(uint8 port_num) throws GLib.Error { /*{{{*/
			var msg = new List<uint8>();
			msg.append(PACKET.SUBSCRIBE);
			msg.append(4); // subscribe packet is 4 bytes
			msg.append(ttl);
			msg.append(port_num);
			msg.append(this.address);
			msg.append(0); // 0 for unsubscribe

			int cs1, cs2;
			make_checksum(msg, out cs1, out cs2);
			msg.append((uint8)cs1);
			msg.append((uint8)cs2);
			msg = stuff_bytes(msg);
			msg.append(0xAC);
			msg.insert(0xAB, 0);

			port.write(msg);
		}
		/*}}}*/

		private List<uint8> stuff_bytes(List<uint8> bytes) { /*{{{*/
			var ret = new List<uint8>();
			for(var i = 0; i < bytes.length(); i++) {
				if(bytes[i] == 0xAA) {
					ret.append(0xAA);
					ret.append(0xAA);
				}
				else if(bytes[i] == 0xAB) {
					ret.append(0xAA);
					ret.append(0xAB);
				} 
				else if(bytes[i] == 0xAC) {
					ret.append(0xAA);
					ret.append(0xAC);
				}
				else {
					ret.append(bytes[i]);
				}
			}
			return ret;
		}
		/*}}}*/


		public uint8 ttl = 6;

		private uint8 address = 0;

		public signal void on_close();

		private gserial.Port port;
		private Parser parser;

		private HashTable<uint8, Socket> port_map;
		public signal void on_datagram(uint8 src, uint8 dest, uint8 port, List<uint8> payload);
	}

}

int main() {
	var iface = new picolan.Interface();

	try {
		iface.open("/dev/pts/4", 1000000);
		iface.on_close.connect(() => {
			stdout.printf("Port closed\n");
		});

		iface.set_address(6);

		iface.ping.begin(1, 1000, (obj, res) => {
			int time = iface.ping.end(res);
			stdout.printf("time: %i\n", time);
		});

		var dg = new picolan.Datagram(80);
		dg.bind(iface);
		dg.on_data.connect((data) => {
			stdout.printf("got some data\n");
			for(var i = 0; i < data.length(); i++) {
				stdout.printf("%i ", (int)data.nth_data(i));
			}
			stdout.printf("\n");
		});

		GLib.Timeout.add(1000, () => {
			dg.send_string(1, 20, "Hello world!!");
			return true;
		} , 1);

	}
	catch(GLib.Error error) {
		stdout.printf("Error caught\n");
		stdout.printf("Error: %s\n", error.message);
	}

	GLib.MainLoop loop = new GLib.MainLoop ();
	loop.run();
	return 0;
}
