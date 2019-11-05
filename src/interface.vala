using gserial;
using Gee;


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

	void make_checksum(ArrayList<uint8> bytes, out int sum1, out int sum2) { /*{{{*/
		var index = 0;
		sum1 = sum2 = 0;
		for(index = 0; index < bytes.size; index++) {
			sum1 = (sum1 + bytes[index]) % 255;
			sum2 = (sum2 + sum1) % 255;
		}
	}/*}}}*/

	class Parser : Object /*{{{*/
	{
		public Parser() {/*{{{*/
			data = new ArrayList<uint8>();
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
							data = new ArrayList<uint8>();
						}

						break;
					case STATE.ID: 
						id = b;
						state = STATE.SIZE;
						data.add(b);
						break;
					case STATE.SIZE: 
						size = b;
						state = STATE.DATA;
						data.add(b);
						break;
					case STATE.DATA: 
						data.add(b);
						// data.size-2 because the data array includes id and size bytes
						// whereas the size is only the length of the data section
						if(((data.size-2) >= size) || (data.size >= 255)) {
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
							data.remove_at(0);
							data.remove_at(0);
							parse_packet();
						}
						break;

				}
			}
		}/*}}}*/

		private void parse_packet() {/*{{{*/

			switch(id) {
				case PACKET.PING_ECHO: 
					on_ping_echo(data[1], data[2], data[3], data[4]);
					break;
				case PACKET.PING: 
					on_ping(data[1], data[2], data[3], data[4]);
					break;
				case PACKET.GET_ADDR_LIST: 
					on_get_addr_list();
					break;
				case PACKET.DATAGRAM:
					// deep copy the payload part to a new array
					var payload = new ArrayList<uint8>();
					for(var i = 4; i < data.size; i++) {
						payload.add(data[i]);
					}

					on_datagram(data[1], data[2], data[3], payload);
					break;
			}
		}/*}}}*/

		public signal void on_get_addr_list();/*{{{*/
		public signal void on_addr(uint8 addr);
		public signal void on_ping(uint8 src, uint8 dest, uint8 p1, uint8 p2);
		public signal void on_ping_echo(uint8 src, uint8 dest, uint8 p1, uint8 p2);
		public signal void on_datagram(uint8 src, uint8 dest, uint8 port, ArrayList<uint8> payload);

		private ArrayList<uint8> data;
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
			port_map = new HashMap<uint8, Socket>();

			/*{{{*/
			parser.on_ping.connect((src, dest, p1, p2) => {
				var msg = new Gee.ArrayList<uint8>();
				msg.add(PACKET.PING_ECHO);
				msg.add(5); //packet size
				msg.add(ttl); //time to live
				msg.add(address); //source / own address
				msg.add(src); // destination address
				msg.add(p1);
				msg.add(p2);

				int cs1, cs2;
				make_checksum(msg, out cs1, out cs2);
				msg.add((uint8)cs1);
				msg.add((uint8)cs2);
				msg = stuff_bytes(msg);
				msg.add(0xAC);
				msg.insert(0, 0xAB);

				try {
					write_byte_array(msg);
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
			if(port_map.has_key(s.get_port()) == false) {
				// attach it using the port map
				port_map.set(s.get_port(), s);
				// connect the destruct signal to remove the socket from the port map when it no longer exists 
				s.on_destroy.connect(() => {
					port_map.unset(s.get_port());
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

			var msg = new Gee.ArrayList<uint8>();
			msg.add(PACKET.ADDR);
			msg.add(32); //packet size
			msg.add(ttl);

			for(var i = 0; i < 32; i++) {
				msg.add(af.get_bytes()[i]);
			}

			int cs1, cs2;
			make_checksum(msg, out cs1, out cs2);
			msg.add((uint8)cs1);
			msg.add((uint8)cs2);
			msg = stuff_bytes(msg);
			msg.add(0xAC);
			msg.insert(0, 0xAB);

			write_byte_array(msg);
		}/*}}}*/

		public void send_datagram(uint8 dest, uint8 port, ArrayList<uint8> data) throws PicolanError, Error { /*{{{*/
			if(data.size >= 250) {
				throw new PicolanError.PAYLOAD_TOO_BIG("Payload size is greater than the maximum of 250 bytes");
			}

			var msg = new ArrayList<uint8>();
			msg.add(PACKET.DATAGRAM);
			msg.add((uint8)(data.size + 5)); //packet size
			msg.add(this.ttl);
			msg.add(this.address);
			msg.add(dest);
			msg.add(port);
			msg.add((uint8)data.size);
			for(var i = 0; i < data.size; i++) {
				msg.add(data[i]);
			}

			int cs1, cs2;
			make_checksum(msg, out cs1, out cs2);
			msg.add((uint8)cs1);
			msg.add((uint8)cs2);
			msg.add(0xAC);
			msg.insert(0, 0xAB);

			write_byte_array(msg);
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
					Idle.add((owned)callback);
					parser.disconnect(handle);
					GLib.Source.remove(timeout_handle);
				}
			});

			timeout_handle = GLib.Timeout.add(timeout, () => {
				Idle.add((owned)callback);
				parser.disconnect(handle);
				return false;
			});

			var msg = new Gee.ArrayList<uint8>();
			msg.add(PACKET.PING);
			msg.add(5); //packet size
			msg.add(ttl); //time to live
			msg.add(address); //source / own address
			msg.add(addr); // destination address
			msg.add(payload1);
			msg.add(payload2);

			int cs1, cs2;
			make_checksum(msg, out cs1, out cs2);
			msg.add((uint8)cs1);
			msg.add((uint8)cs2);
			msg = stuff_bytes(msg);
			msg.add(0xAC);
			msg.insert(0, 0xAB);

			write_byte_array(msg);

			yield;
			return ping_time;
		}/*}}}*/

		public void subscribe(uint8 port) throws GLib.Error { /*{{{*/
			var msg = new Gee.ArrayList<uint8>();
			msg.add(PACKET.SUBSCRIBE);
			msg.add(4); // subscribe packet is 4 bytes
			msg.add(ttl);
			msg.add(port);
			msg.add(this.address);
			msg.add(1); // 1 for subscribe

			int cs1, cs2;
			make_checksum(msg, out cs1, out cs2);
			msg.add((uint8)cs1);
			msg.add((uint8)cs2);
			msg = stuff_bytes(msg);
			msg.add(0xAC);
			msg.insert(0, 0xAB);

			write_byte_array(msg);
		}
		/*}}}*/

		public void unsubscribe(uint8 port) throws GLib.Error { /*{{{*/
			var msg = new Gee.ArrayList<uint8>();
			msg.add(PACKET.SUBSCRIBE);
			msg.add(4); // subscribe packet is 4 bytes
			msg.add(ttl);
			msg.add(port);
			msg.add(this.address);
			msg.add(0); // 0 for unsubscribe

			int cs1, cs2;
			make_checksum(msg, out cs1, out cs2);
			msg.add((uint8)cs1);
			msg.add((uint8)cs2);
			msg = stuff_bytes(msg);
			msg.add(0xAC);
			msg.insert(0, 0xAB);

			write_byte_array(msg);
		}
		/*}}}*/

		private Gee.ArrayList<uint8> stuff_bytes(Gee.ArrayList<uint8> bytes) { /*{{{*/
			var ret = new Gee.ArrayList<uint8>();
			for(var i = 0; i < bytes.size; i++) {
				if(bytes[i] == 0xAA) {
					ret.add(0xAA);
					ret.add(0xAA);
				}
				else if(bytes[i] == 0xAB) {
					ret.add(0xAA);
					ret.add(0xAB);
				} 
				else if(bytes[i] == 0xAC) {
					ret.add(0xAA);
					ret.add(0xAC);
				}
				else {
					ret.add(bytes[i]);
				}
			}
			return ret;
		}
		/*}}}*/

		private void write_byte_array(ArrayList<uint8> buf) throws GLib.Error { /*{{{*/
			var arr = new Array<char>();
			buf.foreach((item) => {
				char c = (char)item;
				arr.append_val(c);
				return true;
			});

			port.write(arr);
		}
		/*}}}*/


		public uint8 ttl = 6;

		private uint8 address = 0;

		public signal void on_close();

		private gserial.Port port;
		private Parser parser;

		private HashMap<uint8, Socket> port_map;
		public signal void on_datagram(uint8 src, uint8 dest, uint8 port, ArrayList<uint8> payload);
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
			for(var i = 0; i < data.size; i++) {
				stdout.printf("%i ", (int)data[i]);
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