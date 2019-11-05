
namespace picolan
{

	public class AddressField
	{
		public void set_address(uint8 addr) {
			var bf = addr/8;
			var bit = addr%8;
			var val = bytes[bf];
			val = val | 1<<bit;
			bytes[bf] = val;
		}

		public bool get_address(uint8 addr) {
			var bf = addr/8;
			var bit = addr%8;
			uint8 mask = 1 << bit;
			return ((bytes[bf] & mask) == 0);
		}

		public uint8[] get_bytes() {
			return bytes;
		}

		private uint8 bytes[32];
	}

}


