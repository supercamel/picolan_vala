
namespace gpicolan
{

	public interface Socket : Object
	{
		public abstract uint8 get_port();

		public abstract void bind(Interface iface);

		public signal void on_data(List<uint8> data);
		public signal void on_destroy();

	}

}

