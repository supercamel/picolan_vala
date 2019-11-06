/* socket_stream.c generated by valac 0.44.3, the Vala compiler
 * generated from socket_stream.vala, do not modify */

#include <glib-object.h>
#include <glib.h>
#include <gee.h>
#include <gio/gio.h>

typedef enum  {
	PICOLAN_SOCKET_STATE_CLOSED,
	PICOLAN_SOCKET_STATE_SYN_SENT,
	PICOLAN_SOCKET_STATE_LISTENING,
	PICOLAN_SOCKET_STATE_SYN_RECVED,
	PICOLAN_SOCKET_STATE_PENDING,
	PICOLAN_SOCKET_STATE_OPEN
} picolanSOCKET_STATE;

#define PICOLAN_TYPE_SOCKET_STATE (picolan_socket_state_get_type ())
typedef enum  {
	PICOLAN_MESSAGE_TYPE_ACK,
	PICOLAN_MESSAGE_TYPE_SYN,
	PICOLAN_MESSAGE_TYPE_DATA,
	PICOLAN_MESSAGE_TYPE_CLOSE,
	PICOLAN_MESSAGE_TYPE_HEARTBEAT
} picolanMESSAGE_TYPE;

#define PICOLAN_TYPE_MESSAGE_TYPE (picolan_message_type_get_type ())

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
enum  {
	PICOLAN_SOCKET_STREAM_0_PROPERTY,
	PICOLAN_SOCKET_STREAM_NUM_PROPERTIES
};
static GParamSpec* picolan_socket_stream_properties[PICOLAN_SOCKET_STREAM_NUM_PROPERTIES];
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
typedef struct _PicolanSocketStreamSendSynData PicolanSocketStreamSendSynData;
typedef struct _Block6Data Block6Data;
typedef struct _PicolanSocketStreamRecvSynData PicolanSocketStreamRecvSynData;
enum  {
	PICOLAN_SOCKET_STREAM_RECV_SYN_SIGNAL_SIGNAL,
	PICOLAN_SOCKET_STREAM_ACK_SIGNAL_SIGNAL,
	PICOLAN_SOCKET_STREAM_NUM_SIGNALS
};
static guint picolan_socket_stream_signals[PICOLAN_SOCKET_STREAM_NUM_SIGNALS] = {0};

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
struct _PicolanSocketStreamSendSynData {
	int _state_;
	GObject* _source_object_;
	GAsyncResult* _res_;
	GTask* _async_result;
	GAsyncReadyCallback _callback_;
	gboolean _task_complete_;
	picolanSocketStream* self;
	gboolean result;
};

struct _Block6Data {
	int _ref_count_;
	picolanSocketStream* self;
	GSourceFunc callback;
	gpointer callback_target;
	GDestroyNotify callback_target_destroy_notify;
	gboolean got_syn;
	guint timeout_handle;
	gulong sig_handle;
	gpointer _async_data_;
};

struct _PicolanSocketStreamRecvSynData {
	int _state_;
	GObject* _source_object_;
	GAsyncResult* _res_;
	GTask* _async_result;
	GAsyncReadyCallback _callback_;
	gboolean _task_complete_;
	picolanSocketStream* self;
	gboolean result;
	Block6Data* _data6_;
	gulong _tmp0_;
};

static gpointer picolan_socket_stream_parent_class = NULL;
static picolanSocketIface * picolan_socket_stream_picolan_socket_parent_iface = NULL;

GType picolan_socket_state_get_type (void) G_GNUC_CONST;
GType picolan_message_type_get_type (void) G_GNUC_CONST;
GType picolan_interface_get_type (void) G_GNUC_CONST;
GType picolan_socket_get_type (void) G_GNUC_CONST;
GType picolan_socket_stream_get_type (void) G_GNUC_CONST;
static guint8 picolan_socket_stream_real_get_port (picolanSocket* base);
GQuark picolan_picolan_error_quark (void);
void picolan_socket_stream_send_ack (picolanSocketStream* self,
                                     GError** error);
void picolan_interface_send_datagram (picolanInterface* self,
                                      guint8 dest,
                                      guint8 port,
                                      GeeArrayList* data,
                                      GError** error);
static void picolan_socket_stream_send_syn_data_free (gpointer _data);
static void picolan_socket_stream_send_syn_async_ready_wrapper (GObject *source_object,
                                                         GAsyncResult *res,
                                                         void *user_data);
static void picolan_socket_stream_send_syn (picolanSocketStream* self,
                                     GAsyncReadyCallback _callback_,
                                     gpointer _user_data_);
static gboolean picolan_socket_stream_send_syn_finish (picolanSocketStream* self,
                                                GAsyncResult* _res_,
                                                GError** error);
static gboolean picolan_socket_stream_send_syn_co (PicolanSocketStreamSendSynData* _data_);
static void picolan_socket_stream_recv_syn_data_free (gpointer _data);
static void picolan_socket_stream_recv_syn_async_ready_wrapper (GObject *source_object,
                                                         GAsyncResult *res,
                                                         void *user_data);
static void picolan_socket_stream_recv_syn (picolanSocketStream* self,
                                     GAsyncReadyCallback _callback_,
                                     gpointer _user_data_);
static gboolean picolan_socket_stream_recv_syn_finish (picolanSocketStream* self,
                                                GAsyncResult* _res_,
                                                GError** error);
static gboolean picolan_socket_stream_recv_syn_co (PicolanSocketStreamRecvSynData* _data_);
static Block6Data* block6_data_ref (Block6Data* _data6_);
static void block6_data_unref (void * _userdata_);
static gboolean _picolan_socket_stream_recv_syn_co_gsource_func (gpointer self);
static void __lambda12_ (Block6Data* _data6_,
                  GeeArrayList* data);
static void ___lambda12__picolan_socket_stream_recv_syn_signal (picolanSocketStream* _sender,
                                                         GeeArrayList* data,
                                                         gpointer self);
static gboolean __lambda13_ (Block6Data* _data6_);
static gboolean ___lambda13__gsource_func (gpointer self);
void picolan_socket_stream_bind (picolanSocketStream* self,
                                 picolanInterface* iface);
static void picolan_socket_stream_real_bind (picolanSocketStream* self,
                                      picolanInterface* iface);
picolanSocketStream* picolan_socket_stream_new (void);
picolanSocketStream* picolan_socket_stream_construct (GType object_type);
static void picolan_socket_stream_finalize (GObject * obj);

GType
picolan_socket_state_get_type (void)
{
	static volatile gsize picolan_socket_state_type_id__volatile = 0;
	if (g_once_init_enter (&picolan_socket_state_type_id__volatile)) {
		static const GEnumValue values[] = {{PICOLAN_SOCKET_STATE_CLOSED, "PICOLAN_SOCKET_STATE_CLOSED", "closed"}, {PICOLAN_SOCKET_STATE_SYN_SENT, "PICOLAN_SOCKET_STATE_SYN_SENT", "syn-sent"}, {PICOLAN_SOCKET_STATE_LISTENING, "PICOLAN_SOCKET_STATE_LISTENING", "listening"}, {PICOLAN_SOCKET_STATE_SYN_RECVED, "PICOLAN_SOCKET_STATE_SYN_RECVED", "syn-recved"}, {PICOLAN_SOCKET_STATE_PENDING, "PICOLAN_SOCKET_STATE_PENDING", "pending"}, {PICOLAN_SOCKET_STATE_OPEN, "PICOLAN_SOCKET_STATE_OPEN", "open"}, {0, NULL, NULL}};
		GType picolan_socket_state_type_id;
		picolan_socket_state_type_id = g_enum_register_static ("picolanSOCKET_STATE", values);
		g_once_init_leave (&picolan_socket_state_type_id__volatile, picolan_socket_state_type_id);
	}
	return picolan_socket_state_type_id__volatile;
}

GType
picolan_message_type_get_type (void)
{
	static volatile gsize picolan_message_type_type_id__volatile = 0;
	if (g_once_init_enter (&picolan_message_type_type_id__volatile)) {
		static const GEnumValue values[] = {{PICOLAN_MESSAGE_TYPE_ACK, "PICOLAN_MESSAGE_TYPE_ACK", "ack"}, {PICOLAN_MESSAGE_TYPE_SYN, "PICOLAN_MESSAGE_TYPE_SYN", "syn"}, {PICOLAN_MESSAGE_TYPE_DATA, "PICOLAN_MESSAGE_TYPE_DATA", "data"}, {PICOLAN_MESSAGE_TYPE_CLOSE, "PICOLAN_MESSAGE_TYPE_CLOSE", "close"}, {PICOLAN_MESSAGE_TYPE_HEARTBEAT, "PICOLAN_MESSAGE_TYPE_HEARTBEAT", "heartbeat"}, {0, NULL, NULL}};
		GType picolan_message_type_type_id;
		picolan_message_type_type_id = g_enum_register_static ("picolanMESSAGE_TYPE", values);
		g_once_init_leave (&picolan_message_type_type_id__volatile, picolan_message_type_type_id);
	}
	return picolan_message_type_type_id__volatile;
}

static guint8
picolan_socket_stream_real_get_port (picolanSocket* base)
{
	picolanSocketStream * self;
	guint8 result = 0U;
	self = (picolanSocketStream*) base;
	result = self->port;
	return result;
}

void
picolan_socket_stream_send_ack (picolanSocketStream* self,
                                GError** error)
{
	GeeArrayList* msg = NULL;
	GeeArrayList* _tmp0_;
	picolanInterface* _tmp1_;
	GError* _inner_error0_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = gee_array_list_new (G_TYPE_UCHAR, NULL, NULL, NULL, NULL, NULL);
	msg = _tmp0_;
	gee_abstract_collection_add ((GeeAbstractCollection*) msg, (gpointer) ((guintptr) ((guint8) PICOLAN_MESSAGE_TYPE_ACK)));
	gee_abstract_collection_add ((GeeAbstractCollection*) msg, (gpointer) ((guintptr) self->remote_sequence));
	_tmp1_ = self->iface;
	picolan_interface_send_datagram (_tmp1_, self->remote, self->remote_port, msg, &_inner_error0_);
	if (G_UNLIKELY (_inner_error0_ != NULL)) {
		g_propagate_error (error, _inner_error0_);
		_g_object_unref0 (msg);
		return;
	}
	_g_object_unref0 (msg);
}

static void
picolan_socket_stream_send_syn_data_free (gpointer _data)
{
	PicolanSocketStreamSendSynData* _data_;
	_data_ = _data;
	_g_object_unref0 (_data_->self);
	g_slice_free (PicolanSocketStreamSendSynData, _data_);
}

static void
picolan_socket_stream_send_syn_async_ready_wrapper (GObject *source_object,
                                                    GAsyncResult *res,
                                                    void *user_data)
{
	PicolanSocketStreamSendSynData* _task_data_;
	_task_data_ = g_task_get_task_data (G_TASK (res));
	if (_task_data_->_callback_ != NULL) {
		_task_data_->_callback_ (source_object, res, user_data);
	}
	_task_data_->_task_complete_ = TRUE;
}

static gpointer
_g_object_ref0 (gpointer self)
{
	return self ? g_object_ref (self) : NULL;
}

static void
picolan_socket_stream_send_syn (picolanSocketStream* self,
                                GAsyncReadyCallback _callback_,
                                gpointer _user_data_)
{
	PicolanSocketStreamSendSynData* _data_;
	picolanSocketStream* _tmp0_;
	_data_ = g_slice_new0 (PicolanSocketStreamSendSynData);
	_data_->_callback_ = _callback_;
	_data_->_async_result = g_task_new (G_OBJECT (self), NULL, picolan_socket_stream_send_syn_async_ready_wrapper, _user_data_);
	if (_callback_ == NULL) {
		_data_->_task_complete_ = TRUE;
	}
	g_task_set_task_data (_data_->_async_result, _data_, picolan_socket_stream_send_syn_data_free);
	_tmp0_ = _g_object_ref0 (self);
	_data_->self = _tmp0_;
	picolan_socket_stream_send_syn_co (_data_);
}

static gboolean
picolan_socket_stream_send_syn_finish (picolanSocketStream* self,
                                       GAsyncResult* _res_,
                                       GError** error)
{
	gboolean result;
	PicolanSocketStreamSendSynData* _data_;
	_data_ = g_task_propagate_pointer (G_TASK (_res_), error);
	if (NULL == _data_) {
		gboolean _tmp0_ = FALSE;
		return _tmp0_;
	}
	result = _data_->result;
	return result;
}

static gboolean
picolan_socket_stream_send_syn_co (PicolanSocketStreamSendSynData* _data_)
{
	switch (_data_->_state_) {
		case 0:
		goto _state_0;
		default:
		g_assert_not_reached ();
	}
	_state_0:
	_data_->result = FALSE;
	g_task_return_pointer (_data_->_async_result, _data_, NULL);
	if (_data_->_state_ != 0) {
		while (!_data_->_task_complete_) {
			g_main_context_iteration (g_task_get_context (_data_->_async_result), TRUE);
		}
	}
	g_object_unref (_data_->_async_result);
	return FALSE;
}

static void
picolan_socket_stream_recv_syn_data_free (gpointer _data)
{
	PicolanSocketStreamRecvSynData* _data_;
	_data_ = _data;
	_g_object_unref0 (_data_->self);
	g_slice_free (PicolanSocketStreamRecvSynData, _data_);
}

static void
picolan_socket_stream_recv_syn_async_ready_wrapper (GObject *source_object,
                                                    GAsyncResult *res,
                                                    void *user_data)
{
	PicolanSocketStreamRecvSynData* _task_data_;
	_task_data_ = g_task_get_task_data (G_TASK (res));
	if (_task_data_->_callback_ != NULL) {
		_task_data_->_callback_ (source_object, res, user_data);
	}
	_task_data_->_task_complete_ = TRUE;
}

static void
picolan_socket_stream_recv_syn (picolanSocketStream* self,
                                GAsyncReadyCallback _callback_,
                                gpointer _user_data_)
{
	PicolanSocketStreamRecvSynData* _data_;
	picolanSocketStream* _tmp0_;
	_data_ = g_slice_new0 (PicolanSocketStreamRecvSynData);
	_data_->_callback_ = _callback_;
	_data_->_async_result = g_task_new (G_OBJECT (self), NULL, picolan_socket_stream_recv_syn_async_ready_wrapper, _user_data_);
	if (_callback_ == NULL) {
		_data_->_task_complete_ = TRUE;
	}
	g_task_set_task_data (_data_->_async_result, _data_, picolan_socket_stream_recv_syn_data_free);
	_tmp0_ = _g_object_ref0 (self);
	_data_->self = _tmp0_;
	picolan_socket_stream_recv_syn_co (_data_);
}

static gboolean
picolan_socket_stream_recv_syn_finish (picolanSocketStream* self,
                                       GAsyncResult* _res_,
                                       GError** error)
{
	gboolean result;
	PicolanSocketStreamRecvSynData* _data_;
	_data_ = g_task_propagate_pointer (G_TASK (_res_), error);
	if (NULL == _data_) {
		gboolean _tmp0_ = FALSE;
		return _tmp0_;
	}
	result = _data_->result;
	return result;
}

static Block6Data*
block6_data_ref (Block6Data* _data6_)
{
	g_atomic_int_inc (&_data6_->_ref_count_);
	return _data6_;
}

static void
block6_data_unref (void * _userdata_)
{
	Block6Data* _data6_;
	_data6_ = (Block6Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data6_->_ref_count_)) {
		picolanSocketStream* self;
		self = _data6_->self;
		(_data6_->callback_target_destroy_notify == NULL) ? NULL : (_data6_->callback_target_destroy_notify (_data6_->callback_target), NULL);
		_data6_->callback = NULL;
		_data6_->callback_target = NULL;
		_data6_->callback_target_destroy_notify = NULL;
		_g_object_unref0 (self);
		g_slice_free (Block6Data, _data6_);
	}
}

static gboolean
_picolan_socket_stream_recv_syn_co_gsource_func (gpointer self)
{
	gboolean result;
	result = picolan_socket_stream_recv_syn_co (self);
	return result;
}

static void
__lambda12_ (Block6Data* _data6_,
             GeeArrayList* data)
{
	picolanSocketStream* self;
	GSourceFunc _tmp0_;
	gpointer _tmp0__target;
	GDestroyNotify _tmp0__target_destroy_notify;
	self = _data6_->self;
	g_return_if_fail (data != NULL);
	_data6_->got_syn = TRUE;
	_tmp0_ = _data6_->callback;
	_tmp0__target = _data6_->callback_target;
	_tmp0__target_destroy_notify = _data6_->callback_target_destroy_notify;
	_data6_->callback = NULL;
	_data6_->callback_target = NULL;
	_data6_->callback_target_destroy_notify = NULL;
	g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, _tmp0_, _tmp0__target, _tmp0__target_destroy_notify);
	g_signal_handler_disconnect ((GObject*) self, _data6_->sig_handle);
	g_source_remove (_data6_->timeout_handle);
}

static void
___lambda12__picolan_socket_stream_recv_syn_signal (picolanSocketStream* _sender,
                                                    GeeArrayList* data,
                                                    gpointer self)
{
	__lambda12_ (self, data);
}

static gboolean
__lambda13_ (Block6Data* _data6_)
{
	picolanSocketStream* self;
	gboolean result = FALSE;
	GSourceFunc _tmp0_;
	gpointer _tmp0__target;
	GDestroyNotify _tmp0__target_destroy_notify;
	self = _data6_->self;
	_tmp0_ = _data6_->callback;
	_tmp0__target = _data6_->callback_target;
	_tmp0__target_destroy_notify = _data6_->callback_target_destroy_notify;
	_data6_->callback = NULL;
	_data6_->callback_target = NULL;
	_data6_->callback_target_destroy_notify = NULL;
	g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, _tmp0_, _tmp0__target, _tmp0__target_destroy_notify);
	g_signal_handler_disconnect ((GObject*) self, _data6_->sig_handle);
	result = FALSE;
	return result;
}

static gboolean
___lambda13__gsource_func (gpointer self)
{
	gboolean result;
	result = __lambda13_ (self);
	return result;
}

static gboolean
picolan_socket_stream_recv_syn_co (PicolanSocketStreamRecvSynData* _data_)
{
	switch (_data_->_state_) {
		case 0:
		goto _state_0;
		case 1:
		goto _state_1;
		default:
		g_assert_not_reached ();
	}
	_state_0:
	_data_->_data6_ = g_slice_new0 (Block6Data);
	_data_->_data6_->_ref_count_ = 1;
	_data_->_data6_->self = g_object_ref (_data_->self);
	_data_->_data6_->_async_data_ = _data_;
	_data_->_data6_->callback = _picolan_socket_stream_recv_syn_co_gsource_func;
	_data_->_data6_->callback_target = _data_;
	_data_->_data6_->callback_target_destroy_notify = NULL;
	_data_->_data6_->got_syn = FALSE;
	_data_->_data6_->timeout_handle = (guint) 0;
	_data_->_data6_->sig_handle = (gulong) 0;
	_data_->_tmp0_ = g_signal_connect_data (_data_->self, "recv-syn-signal", (GCallback) ___lambda12__picolan_socket_stream_recv_syn_signal, block6_data_ref (_data_->_data6_), (GClosureNotify) block6_data_unref, 0);
	_data_->_data6_->sig_handle = _data_->_tmp0_;
	_data_->_data6_->timeout_handle = g_timeout_add_full (G_PRIORITY_DEFAULT, _data_->self->timeout, ___lambda13__gsource_func, block6_data_ref (_data_->_data6_), block6_data_unref);
	_data_->_state_ = 1;
	return FALSE;
	_state_1:
	;
	_data_->result = _data_->_data6_->got_syn;
	block6_data_unref (_data_->_data6_);
	_data_->_data6_ = NULL;
	g_task_return_pointer (_data_->_async_result, _data_, NULL);
	if (_data_->_state_ != 0) {
		while (!_data_->_task_complete_) {
			g_main_context_iteration (g_task_get_context (_data_->_async_result), TRUE);
		}
	}
	g_object_unref (_data_->_async_result);
	return FALSE;
}

static void
picolan_socket_stream_real_bind (picolanSocketStream* self,
                                 picolanInterface* iface)
{
	g_return_if_fail (iface != NULL);
}

void
picolan_socket_stream_bind (picolanSocketStream* self,
                            picolanInterface* iface)
{
	g_return_if_fail (self != NULL);
	PICOLAN_SOCKET_STREAM_GET_CLASS (self)->bind (self, iface);
}

picolanSocketStream*
picolan_socket_stream_construct (GType object_type)
{
	picolanSocketStream * self = NULL;
	self = (picolanSocketStream*) g_object_new (object_type, NULL);
	return self;
}

picolanSocketStream*
picolan_socket_stream_new (void)
{
	return picolan_socket_stream_construct (PICOLAN_TYPE_SOCKET_STREAM);
}

static void
picolan_socket_stream_class_init (picolanSocketStreamClass * klass,
                                  gpointer klass_data)
{
	picolan_socket_stream_parent_class = g_type_class_peek_parent (klass);
	((picolanSocketStreamClass *) klass)->bind = (void (*) (picolanSocketStream*, picolanInterface*)) picolan_socket_stream_real_bind;
	G_OBJECT_CLASS (klass)->finalize = picolan_socket_stream_finalize;
	picolan_socket_stream_signals[PICOLAN_SOCKET_STREAM_RECV_SYN_SIGNAL_SIGNAL] = g_signal_new ("recv-syn-signal", PICOLAN_TYPE_SOCKET_STREAM, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__OBJECT, G_TYPE_NONE, 1, GEE_TYPE_ARRAY_LIST);
	picolan_socket_stream_signals[PICOLAN_SOCKET_STREAM_ACK_SIGNAL_SIGNAL] = g_signal_new ("ack-signal", PICOLAN_TYPE_SOCKET_STREAM, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__OBJECT, G_TYPE_NONE, 1, GEE_TYPE_ARRAY_LIST);
}

static void
picolan_socket_stream_picolan_socket_interface_init (picolanSocketIface * iface,
                                                     gpointer iface_data)
{
	picolan_socket_stream_picolan_socket_parent_iface = g_type_interface_peek_parent (iface);
	iface->get_port = (guint8 (*) (picolanSocket*)) picolan_socket_stream_real_get_port;
	iface->bind = (void (*) (picolanSocket*, picolanInterface*)) picolan_socket_stream_bind;
}

static void
picolan_socket_stream_instance_init (picolanSocketStream * self,
                                     gpointer klass)
{
	self->timeout = (guint) 1000;
	self->port = (guint8) 0;
	self->state = PICOLAN_SOCKET_STATE_CLOSED;
}

static void
picolan_socket_stream_finalize (GObject * obj)
{
	picolanSocketStream * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, PICOLAN_TYPE_SOCKET_STREAM, picolanSocketStream);
	_g_object_unref0 (self->iface);
	G_OBJECT_CLASS (picolan_socket_stream_parent_class)->finalize (obj);
}

GType
picolan_socket_stream_get_type (void)
{
	static volatile gsize picolan_socket_stream_type_id__volatile = 0;
	if (g_once_init_enter (&picolan_socket_stream_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (picolanSocketStreamClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) picolan_socket_stream_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (picolanSocketStream), 0, (GInstanceInitFunc) picolan_socket_stream_instance_init, NULL };
		static const GInterfaceInfo picolan_socket_info = { (GInterfaceInitFunc) picolan_socket_stream_picolan_socket_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		GType picolan_socket_stream_type_id;
		picolan_socket_stream_type_id = g_type_register_static (G_TYPE_OBJECT, "picolanSocketStream", &g_define_type_info, 0);
		g_type_add_interface_static (picolan_socket_stream_type_id, PICOLAN_TYPE_SOCKET, &picolan_socket_info);
		g_once_init_leave (&picolan_socket_stream_type_id__volatile, picolan_socket_stream_type_id);
	}
	return picolan_socket_stream_type_id__volatile;
}
