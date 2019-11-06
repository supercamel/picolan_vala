
namespace picolan
{

	public class Client : SocketStream
	{
		public override void bind(Interface _iface) {
			iface = _iface;
			iface.attach_socket(this);
			iface.on_datagram.connect((src, dest, _port, payload) => {
				if(port == _port) {
					process_datagram(payload);
				}
			});
		}

		private void process_datagram(List<uint8> dg) {
			if(dg[0] == MESSAGE_TYPE.SYN) {
				this.remote_sequence = dg[1];
				this.remote_port = dg[2];
				recv_syn_signal(dg);
			} else if(dg[0] == MESSAGE_TYPE.ACK) {
				ack_signal(dg);
			}
		}

	}

}


