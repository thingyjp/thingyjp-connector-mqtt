#define GETTEXT_PACKAGE "gtk20"
#include <glib.h>
#include <mosquittomainloop.h>
#include <mosquitto.h>

static gboolean connectedcallback(MosquittoClient* client, void* something,
		gpointer userdata) {
	g_message("connect callback");
	int mid;
	mosquitto_subscribe(mosquitto_client_getmosquittoinstance(client), &mid,
			"#", 0);
	return TRUE;
}

void errorcallback(struct mosquitto* mosq, void* data) {
	g_message("error callback");
}

int main(int argc, char** argv) {
	int ret = 0;

	gchar* mqttid = NULL;
	gchar* mqtthost = "mqtt.public.thingy.jp";
	gint mqttport = 8883;
	gchar* mqttrootcert = NULL;
	gchar* mqttdevicecert = NULL;
	gchar* mqttdevicekey = NULL;

	GError* error = NULL;
	GOptionEntry entries[] = { MQTTOPTS, { NULL } };
	GOptionContext* optioncontext = g_option_context_new(NULL);
	g_option_context_add_main_entries(optioncontext, entries, GETTEXT_PACKAGE);
	if (!g_option_context_parse(optioncontext, &argc, &argv, &error)) {
		g_print("option parsing failed: %s\n", error->message);
		ret = 1;
		goto err_args;
	}

	MosquittoClient* client = mosquitto_client_new_withclientcert(mqttid,
			mqtthost, 8883, mqttrootcert, mqttdevicecert, mqttdevicekey);

	g_signal_connect(client, MOSQUITTO_CLIENT_SIGNAL_CONNECTED,
			(GCallback )connectedcallback, NULL);

	GMainLoop* mainloop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(mainloop);

	err_args: return ret;
}

