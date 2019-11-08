/* client.c generated by valac 0.44.3, the Vala compiler
 * generated from client.vala, do not modify */

#include <glib-object.h>
#include <glib.h>

#define PICOLAN_TYPE_SOCKET (picolan_socket_get_type ())
#define PICOLAN_SOCKET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PICOLAN_TYPE_SOCKET, picolanSocket))
#define PICOLAN_IS_SOCKET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PICOLAN_TYPE_SOCKET))
#define PICOLAN_SOCKET_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), PICOLAN_TYPE_SOCKET, picolanSocketIface))

typedef struct _picolanSocket picolanSocket;
typedef struct _picolanSocketIface picolanSocketIface;

#define PICOLAN_TYPE_INTERFACE (picolan_interface_get_type ())
#define PICOLAN_INTERFACE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PICOLAN_TYPE_INTERFACE, picolanInterface))
#define PICOLAN_INTERFACE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PICOLAN_TYPE_INTERFACE, picolanInterfaceClass))
#define PICOLAN_IS_INTERFACE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PICOLAN_TYPE_INTERFACE))
#define PICOLAN_IS_INTERFACE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PICOLAN_TYPE_INTERFACE))
#define PICOLAN_INTERFACE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PICOLAN_TYPE_INTERFACE, picolanInterfaceClass))

typedef struct _picolanInterface picolanInterface;
typedef struct _picolanInterfaceClass picolanInterfaceClass;

#define PICOLAN_TYPE_SOCKET_STREAM (picolan_socket_stream_get_type ())
#define PICOLAN_SOCKET_STREAM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PICOLAN_TYPE_SOCKET_STREAM, picolanSocketStream))
#define PICOLAN_SOCKET_STREAM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PICOLAN_TYPE_SOCKET_STREAM, picolanSocketStreamClass))
#define PICOLAN_IS_SOCKET_STREAM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PICOLAN_TYPE_SOCKET_STREAM))
#define PICOLAN_IS_SOCKET_STREAM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PICOLAN_TYPE_SOCKET_STREAM))
#define PICOLAN_SOCKET_STREAM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PICOLAN_TYPE_SOCKET_STREAM, picolanSocketStreamClass))

typedef struct _picolanSocketStream picolanSocketStream;
typedef struct _picolanSocketStreamClass picolanSocketStreamClass;
typedef struct _picolanSocketStreamPrivate picolanSocketStreamPrivate;
typedef enum  {
	PICOLAN_SOCKET_STATE_CLOSED,
	PICOLAN_SOCKET_STATE_SYN_SENT,
	PICOLAN_SOCKET_STATE_LISTENING,
	PICOLAN_SOCKET_STATE_SYN_RECVED,
	PICOLAN_SOCKET_STATE_PENDING,
	PICOLAN_SOCKET_STATE_OPEN
} picolanSOCKET_STATE;

#define PICOLAN_TYPE_SOCKET_STATE (picolan_socket_state_get_type ())

#define PICOLAN_TYPE_CLIENT (picolan_client_get_type ())
#define PICOLAN_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PICOLAN_TYPE_CLIENT, picolanClient))
#define PICOLAN_CLIENT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PICOLAN_TYPE_CLIENT, picolanClientClass))
#define PICOLAN_IS_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PICOLAN_TYPE_CLIENT))
#define PICOLAN_IS_CLIENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PICOLAN_TYPE_CLIENT))
#define PICOLAN_CLIENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PICOLAN_TYPE_CLIENT, picolanClientClass))

typedef struct _picolanClient picolanClient;
typedef struct _picolanClientClass picolanClientClass;
typedef struct _picolanClientPrivate picolanClientPrivate;
enum  {
	PICOLAN_CLIENT_0_PROPERTY,
	PICOLAN_CLIENT_NUM_PROPERTIES
};
static GParamSpec* picolan_client_properties[PICOLAN_CLIENT_NUM_PROPERTIES];
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
typedef enum  {
	PICOLAN_MESSAGE_TYPE_ACK,
	PICOLAN_MESSAGE_TYPE_SYN,
	PICOLAN_MESSAGE_TYPE_DATA,
	PICOLAN_MESSAGE_TYPE_CLOSE,
	PICOLAN_MESSAGE_TYPE_HEARTBEAT
} picolanMESSAGE_TYPE;

#define PICOLAN_TYPE_MESSAGE_TYPE (picolan_message_type_get_type ())

struct _picolanSocketIface {
	GTypeInterface parent_iface;
	guint8 (*get_port) (picolanSocket* self);
	void (*bind) (picolanSocket* self, picolanInterface* iface);
};

struct _picolanSocketStream {
	GObject parent_instance;
	picolanSocketStreamPrivate * priv;
	guint timeout;
	picolanInterface* iface;
	guint8 port;
	picolanSOCKET_STATE state;
	guint8 sequence;
	guint8 remote;
	guint8 remote_sequence;
	guint8 remote_port;
	guint8 last_ack;
};

struct _picolanSocketStreamClass {
	GObjectClass parent_class;
	void (*bind) (picolanSocketStream* self, picolanInterface* iface);
};

struct _picolanClient {
	picolanSocketStream parent_instance;
	picolanClientPrivate * priv;
};

struct _picolanClientClass {
	picolanSocketStreamClass parent_class;
};

static gpointer picolan_client_parent_class = NULL;

GType picolan_interface_get_type (void) G_GNUC_CONST;
GType picolan_socket_get_type (void) G_GNUC_CONST;
GType picolan_socket_stream_get_type (void) G_GNUC_CONST;
GType picolan_socket_state_get_type (void) G_GNUC_CONST;
GType picolan_client_get_type (void) G_GNUC_CONST;
static void picolan_client_real_bind (picolanSocketStream* base,
                               picolanInterface* _iface);
gboolean picolan_interface_attach_socket (picolanInterface* self,
                                          picolanSocket* s);
static void __lambda13_ (picolanClient* self,
                  guint8 src,
                  guint8 dest,
                  guint8 _port,
                  GList* payload);
static void picolan_client_process_datagram (picolanClient* self,
                                      GList* dg);
static void ___lambda13__picolan_interface_on_datagram (picolanInterface* _sender,
                                                 guint8 src,
                                                 guint8 dest,
                                                 guint8 port,
                                                 GList* payload,
                                                 gpointer self);
GType picolan_message_type_get_type (void) G_GNUC_CONST;
picolanClient* picolan_client_new (void);
picolanClient* picolan_client_construct (GType object_type);
picolanSocketStream* picolan_socket_stream_new (void);
picolanSocketStream* picolan_socket_stream_construct (GType object_type);

static gpointer
_g_object_ref0 (gpointer self)
{
	return self ? g_object_ref (self) : NULL;
}

static void
__lambda13_ (picolanClient* self,
             guint8 src,
             guint8 dest,
             guint8 _port,
             GList* payload)
{
	if (((picolanSocketStream*) self)->port == _port) {
		picolan_client_process_datagram (self, payload);
	}
}

static void
___lambda13__picolan_interface_on_datagram (picolanInterface* _sender,
                                            guint8 src,
                                            guint8 dest,
                                            guint8 port,
                                            GList* payload,
                                            gpointer self)
{
	__lambda13_ ((picolanClient*) self, src, dest, port, payload);
}

static void
picolan_client_real_bind (picolanSocketStream* base,
                          picolanInterface* _iface)
{
	picolanClient * self;
	picolanInterface* _tmp0_;
	picolanInterface* _tmp1_;
	picolanInterface* _tmp2_;
	self = (picolanClient*) base;
	g_return_if_fail (_iface != NULL);
	_tmp0_ = _g_object_ref0 (_iface);
	_g_object_unref0 (((picolanSocketStream*) self)->iface);
	((picolanSocketStream*) self)->iface = _tmp0_;
	_tmp1_ = ((picolanSocketStream*) self)->iface;
	picolan_interface_attach_socket (_tmp1_, (picolanSocket*) self);
	_tmp2_ = ((picolanSocketStream*) self)->iface;
	g_signal_connect_object (_tmp2_, "on-datagram", (GCallback) ___lambda13__picolan_interface_on_datagram, self, 0);
}

static void
picolan_client_process_datagram (picolanClient* self,
                                 GList* dg)
{
	gconstpointer _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = g_list_nth_data (dg, (guint) 0);
	if (((guint8) ((guintptr) _tmp0_)) == PICOLAN_MESSAGE_TYPE_SYN) {
		gconstpointer _tmp1_;
		gconstpointer _tmp2_;
		_tmp1_ = g_list_nth_data (dg, (guint) 1);
		((picolanSocketStream*) self)->remote_sequence = (guint8) ((guintptr) _tmp1_);
		_tmp2_ = g_list_nth_data (dg, (guint) 2);
		((picolanSocketStream*) self)->remote_port = (guint8) ((guintptr) _tmp2_);
		g_signal_emit_by_name ((picolanSocketStream*) self, "recv-syn-signal", dg);
	} else {
		gconstpointer _tmp3_;
		_tmp3_ = g_list_nth_data (dg, (guint) 0);
		if (((guint8) ((guintptr) _tmp3_)) == PICOLAN_MESSAGE_TYPE_ACK) {
			g_signal_emit_by_name ((picolanSocketStream*) self, "ack-signal", dg);
		}
	}
}

picolanClient*
picolan_client_construct (GType object_type)
{
	picolanClient * self = NULL;
	self = (picolanClient*) picolan_socket_stream_construct (object_type);
	return self;
}

picolanClient*
picolan_client_new (void)
{
	return picolan_client_construct (PICOLAN_TYPE_CLIENT);
}

static void
picolan_client_class_init (picolanClientClass * klass,
                           gpointer klass_data)
{
	picolan_client_parent_class = g_type_class_peek_parent (klass);
	((picolanSocketStreamClass *) klass)->bind = (void (*) (picolanSocketStream*, picolanInterface*)) picolan_client_real_bind;
}

static void
picolan_client_instance_init (picolanClient * self,
                              gpointer klass)
{
}

GType
picolan_client_get_type (void)
{
	static volatile gsize picolan_client_type_id__volatile = 0;
	if (g_once_init_enter (&picolan_client_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (picolanClientClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) picolan_client_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (picolanClient), 0, (GInstanceInitFunc) picolan_client_instance_init, NULL };
		GType picolan_client_type_id;
		picolan_client_type_id = g_type_register_static (PICOLAN_TYPE_SOCKET_STREAM, "picolanClient", &g_define_type_info, 0);
		g_once_init_leave (&picolan_client_type_id__volatile, picolan_client_type_id);
	}
	return picolan_client_type_id__volatile;
}

