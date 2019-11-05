/* picolan.h generated by valac 0.46.3, the Vala compiler, do not modify */

#ifndef __PICOLAN_H__
#define __PICOLAN_H__

#include <glib-object.h>
#include <glib.h>
#include <gee.h>
#include <stdlib.h>
#include <string.h>
#include <gio/gio.h>

G_BEGIN_DECLS

typedef enum  {
	PICOLAN_SOCKET_STATE_CLOSED,
	PICOLAN_SOCKET_STATE_SYN_SENT,
	PICOLAN_SOCKET_STATE_LISTENING,
	PICOLAN_SOCKET_STATE_SYN_RECVED,
	PICOLAN_SOCKET_STATE_PENDING,
	PICOLAN_SOCKET_STATE_OPEN
} picolanSOCKET_STATE;

#define PICOLAN_TYPE_SOCKET_STATE (picolan_socket_state_get_type ())

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

#define PICOLAN_TYPE_CLIENT (picolan_client_get_type ())
#define PICOLAN_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PICOLAN_TYPE_CLIENT, picolanClient))
#define PICOLAN_CLIENT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PICOLAN_TYPE_CLIENT, picolanClientClass))
#define PICOLAN_IS_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PICOLAN_TYPE_CLIENT))
#define PICOLAN_IS_CLIENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PICOLAN_TYPE_CLIENT))
#define PICOLAN_CLIENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PICOLAN_TYPE_CLIENT, picolanClientClass))

typedef struct _picolanClient picolanClient;
typedef struct _picolanClientClass picolanClientClass;
typedef struct _picolanClientPrivate picolanClientPrivate;

#define PICOLAN_TYPE_DATAGRAM (picolan_datagram_get_type ())
#define PICOLAN_DATAGRAM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PICOLAN_TYPE_DATAGRAM, picolanDatagram))
#define PICOLAN_DATAGRAM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PICOLAN_TYPE_DATAGRAM, picolanDatagramClass))
#define PICOLAN_IS_DATAGRAM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PICOLAN_TYPE_DATAGRAM))
#define PICOLAN_IS_DATAGRAM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PICOLAN_TYPE_DATAGRAM))
#define PICOLAN_DATAGRAM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PICOLAN_TYPE_DATAGRAM, picolanDatagramClass))

typedef struct _picolanDatagram picolanDatagram;
typedef struct _picolanDatagramClass picolanDatagramClass;
typedef struct _picolanDatagramPrivate picolanDatagramPrivate;
typedef struct _picolanInterfacePrivate picolanInterfacePrivate;

#define PICOLAN_TYPE_ADDRESS_FIELD (picolan_address_field_get_type ())
#define PICOLAN_ADDRESS_FIELD(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PICOLAN_TYPE_ADDRESS_FIELD, picolanAddressField))
#define PICOLAN_ADDRESS_FIELD_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PICOLAN_TYPE_ADDRESS_FIELD, picolanAddressFieldClass))
#define PICOLAN_IS_ADDRESS_FIELD(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PICOLAN_TYPE_ADDRESS_FIELD))
#define PICOLAN_IS_ADDRESS_FIELD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PICOLAN_TYPE_ADDRESS_FIELD))
#define PICOLAN_ADDRESS_FIELD_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PICOLAN_TYPE_ADDRESS_FIELD, picolanAddressFieldClass))

typedef struct _picolanAddressField picolanAddressField;
typedef struct _picolanAddressFieldClass picolanAddressFieldClass;
typedef struct _picolanAddressFieldPrivate picolanAddressFieldPrivate;

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

typedef enum  {
	PICOLAN_PICOLAN_ERROR_COMS_FAULT,
	PICOLAN_PICOLAN_ERROR_PAYLOAD_TOO_BIG
} picolanPicolanError;
#define PICOLAN_PICOLAN_ERROR picolan_picolan_error_quark ()
struct _picolanClient {
	picolanSocketStream parent_instance;
	picolanClientPrivate * priv;
};

struct _picolanClientClass {
	picolanSocketStreamClass parent_class;
};

struct _picolanDatagram {
	GObject parent_instance;
	picolanDatagramPrivate * priv;
	guint8 remote;
	guint timeout;
};

struct _picolanDatagramClass {
	GObjectClass parent_class;
};

struct _picolanInterface {
	GObject parent_instance;
	picolanInterfacePrivate * priv;
	guint8 ttl;
};

struct _picolanInterfaceClass {
	GObjectClass parent_class;
};

struct _picolanAddressField {
	GTypeInstance parent_instance;
	volatile int ref_count;
	picolanAddressFieldPrivate * priv;
};

struct _picolanAddressFieldClass {
	GTypeClass parent_class;
	void (*finalize) (picolanAddressField *self);
};

GType picolan_socket_state_get_type (void) G_GNUC_CONST;
GType picolan_interface_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (picolanInterface, g_object_unref)
GType picolan_socket_get_type (void) G_GNUC_CONST;
GType picolan_socket_stream_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (picolanSocketStream, g_object_unref)
GQuark picolan_picolan_error_quark (void);
void picolan_socket_stream_send_ack (picolanSocketStream* self,
                                     GError** error);
void picolan_socket_stream_bind (picolanSocketStream* self,
                                 picolanInterface* iface);
picolanSocketStream* picolan_socket_stream_new (void);
picolanSocketStream* picolan_socket_stream_construct (GType object_type);
guint8 picolan_socket_get_port (picolanSocket* self);
void picolan_socket_bind (picolanSocket* self,
                          picolanInterface* iface);
GType picolan_client_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (picolanClient, g_object_unref)
picolanClient* picolan_client_new (void);
picolanClient* picolan_client_construct (GType object_type);
GType picolan_datagram_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (picolanDatagram, g_object_unref)
picolanDatagram* picolan_datagram_new (guint8 _port);
picolanDatagram* picolan_datagram_construct (GType object_type,
                                             guint8 _port);
void picolan_datagram_send_bytes (picolanDatagram* self,
                                  guint8 dest,
                                  guint8 port,
                                  GeeArrayList* data,
                                  GError** error);
void picolan_datagram_send_string (picolanDatagram* self,
                                   guint8 dest,
                                   guint8 port,
                                   const gchar* str,
                                   GError** error);
picolanInterface* picolan_interface_new (void);
picolanInterface* picolan_interface_construct (GType object_type);
gboolean picolan_interface_attach_socket (picolanInterface* self,
                                          picolanSocket* s);
gboolean picolan_interface_open (picolanInterface* self,
                                 const gchar* port_name,
                                 gint baud,
                                 GError** error);
void picolan_interface_close (picolanInterface* self);
void picolan_interface_set_address (picolanInterface* self,
                                    guint8 addr,
                                    GError** error);
void picolan_interface_send_datagram (picolanInterface* self,
                                      guint8 dest,
                                      guint8 port,
                                      GeeArrayList* data,
                                      GError** error);
void picolan_interface_ping (picolanInterface* self,
                             guint8 addr,
                             guint timeout,
                             GAsyncReadyCallback _callback_,
                             gpointer _user_data_);
gint picolan_interface_ping_finish (picolanInterface* self,
                                    GAsyncResult* _res_,
                                    GError** error);
void picolan_interface_subscribe (picolanInterface* self,
                                  guint8 port,
                                  GError** error);
void picolan_interface_unsubscribe (picolanInterface* self,
                                    guint8 port,
                                    GError** error);
gpointer picolan_address_field_ref (gpointer instance);
void picolan_address_field_unref (gpointer instance);
GParamSpec* picolan_param_spec_address_field (const gchar* name,
                                              const gchar* nick,
                                              const gchar* blurb,
                                              GType object_type,
                                              GParamFlags flags);
void picolan_value_set_address_field (GValue* value,
                                      gpointer v_object);
void picolan_value_take_address_field (GValue* value,
                                       gpointer v_object);
gpointer picolan_value_get_address_field (const GValue* value);
GType picolan_address_field_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (picolanAddressField, picolan_address_field_unref)
void picolan_address_field_set_address (picolanAddressField* self,
                                        guint8 addr);
gboolean picolan_address_field_get_address (picolanAddressField* self,
                                            guint8 addr);
guint8* picolan_address_field_get_bytes (picolanAddressField* self,
                                         gint* result_length1);
picolanAddressField* picolan_address_field_new (void);
picolanAddressField* picolan_address_field_construct (GType object_type);

G_END_DECLS

#endif