#include "config.h"
#include <common/node_id.c>
#include <common/setup.h>
#include <common/status_levels.c>
#include <stdio.h>

#define fwrite test_fwrite
static size_t test_fwrite(const void *ptr, size_t size, size_t nmemb,
			  FILE *stream);
#include "../log.c"

/* AUTOGENERATED MOCKS START */
/* Generated stub for command_fail */
struct command_result *command_fail(struct command *cmd UNNEEDED, enum jsonrpc_errcode code UNNEEDED,
				    const char *fmt UNNEEDED, ...)

{ fprintf(stderr, "command_fail called!\n"); abort(); }
/* Generated stub for command_param_failed */
struct command_result *command_param_failed(void)

{ fprintf(stderr, "command_param_failed called!\n"); abort(); }
/* Generated stub for command_success */
struct command_result *command_success(struct command *cmd UNNEEDED,
				       struct json_stream *response)

{ fprintf(stderr, "command_success called!\n"); abort(); }
/* Generated stub for fromwire_bigsize */
bigsize_t fromwire_bigsize(const u8 **cursor UNNEEDED, size_t *max UNNEEDED)
{ fprintf(stderr, "fromwire_bigsize called!\n"); abort(); }
/* Generated stub for fromwire_channel_id */
bool fromwire_channel_id(const u8 **cursor UNNEEDED, size_t *max UNNEEDED,
			 struct channel_id *channel_id UNNEEDED)
{ fprintf(stderr, "fromwire_channel_id called!\n"); abort(); }
/* Generated stub for json_add_hex_talarr */
void json_add_hex_talarr(struct json_stream *result UNNEEDED,
			 const char *fieldname UNNEEDED,
			 const tal_t *data UNNEEDED)
{ fprintf(stderr, "json_add_hex_talarr called!\n"); abort(); }
/* Generated stub for json_add_node_id */
void json_add_node_id(struct json_stream *response UNNEEDED,
				const char *fieldname UNNEEDED,
				const struct node_id *id UNNEEDED)
{ fprintf(stderr, "json_add_node_id called!\n"); abort(); }
/* Generated stub for json_add_num */
void json_add_num(struct json_stream *result UNNEEDED, const char *fieldname UNNEEDED,
		  unsigned int value UNNEEDED)
{ fprintf(stderr, "json_add_num called!\n"); abort(); }
/* Generated stub for json_add_str_fmt */
void json_add_str_fmt(struct json_stream *js UNNEEDED,
		      const char *fieldname UNNEEDED,
		      const char *fmt UNNEEDED, ...)
{ fprintf(stderr, "json_add_str_fmt called!\n"); abort(); }
/* Generated stub for json_add_string */
void json_add_string(struct json_stream *js UNNEEDED,
		     const char *fieldname UNNEEDED,
		     const char *str TAKES UNNEEDED)
{ fprintf(stderr, "json_add_string called!\n"); abort(); }
/* Generated stub for json_add_time */
void json_add_time(struct json_stream *result UNNEEDED, const char *fieldname UNNEEDED,
			  struct timespec ts UNNEEDED)
{ fprintf(stderr, "json_add_time called!\n"); abort(); }
/* Generated stub for json_array_end */
void json_array_end(struct json_stream *js UNNEEDED)
{ fprintf(stderr, "json_array_end called!\n"); abort(); }
/* Generated stub for json_array_start */
void json_array_start(struct json_stream *js UNNEEDED, const char *fieldname UNNEEDED)
{ fprintf(stderr, "json_array_start called!\n"); abort(); }
/* Generated stub for json_object_end */
void json_object_end(struct json_stream *js UNNEEDED)
{ fprintf(stderr, "json_object_end called!\n"); abort(); }
/* Generated stub for json_object_start */
void json_object_start(struct json_stream *ks UNNEEDED, const char *fieldname UNNEEDED)
{ fprintf(stderr, "json_object_start called!\n"); abort(); }
/* Generated stub for json_stream_log_suppress_for_cmd */
void json_stream_log_suppress_for_cmd(struct json_stream *js UNNEEDED,
					    const struct command *cmd UNNEEDED)
{ fprintf(stderr, "json_stream_log_suppress_for_cmd called!\n"); abort(); }
/* Generated stub for json_stream_success */
struct json_stream *json_stream_success(struct command *cmd UNNEEDED)
{ fprintf(stderr, "json_stream_success called!\n"); abort(); }
/* Generated stub for notify_warning */
void notify_warning(struct lightningd *ld UNNEEDED, struct log_entry *l UNNEEDED)
{ fprintf(stderr, "notify_warning called!\n"); abort(); }
/* Generated stub for param */
bool param(struct command *cmd UNNEEDED, const char *buffer UNNEEDED,
	   const jsmntok_t params[] UNNEEDED, ...)
{ fprintf(stderr, "param called!\n"); abort(); }
/* Generated stub for towire_bigsize */
void towire_bigsize(u8 **pptr UNNEEDED, const bigsize_t val UNNEEDED)
{ fprintf(stderr, "towire_bigsize called!\n"); abort(); }
/* Generated stub for towire_channel_id */
void towire_channel_id(u8 **pptr UNNEEDED, const struct channel_id *channel_id UNNEEDED)
{ fprintf(stderr, "towire_channel_id called!\n"); abort(); }
/* AUTOGENERATED MOCKS END */

static size_t num_written;
static size_t test_fwrite(const void *ptr, size_t size, size_t nmemb,
			  FILE *stream)
{
	num_written++;
	return nmemb;
}

static size_t try_log(struct log_book *lb, const char *prefix,
		      const struct node_id *node_id,
		      enum log_level level)
{
	struct logger *log = new_logger(NULL, lb, node_id, "%s", prefix);

	num_written = 0;
	log_(log, level, NULL, false, "test_log");
	tal_free(log);
	return num_written;
}

int main(int argc, char *argv[])
{
	struct log_book *lb;
	struct node_id node_id;
	struct lightningd *ld;
	char tmpfiletemplate[] = "/tmp/run-log_filter.XXXXXX";

	common_setup(argv[0]);

	assert(node_id_from_hexstr("0266e4598d1d3c415f572a8488830b60f7e744ed9235eb0b1ba93283b315c03518",
				   strlen("0266e4598d1d3c415f572a8488830b60f7e744ed9235eb0b1ba93283b315c03518"), &node_id));

	ld = tal(tmpctx, struct lightningd);
	ld->logfiles = NULL;
	lb = ld->log_book = new_log_book(ld, 1024*1024);
	ld->log = new_logger(ld, lb, NULL, "dummy");
	assert(arg_log_to_file("-", ld) == NULL);

	assert(mkstemp(tmpfiletemplate) >= 0);
	assert(arg_log_to_file(tmpfiletemplate, ld) == NULL);

	/* Log level default. */
	assert(opt_log_level("BROKEN", lb) == NULL);
	assert(try_log(lb, "prefix", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_INFORM) == 0);
	assert(try_log(lb, "prefix", NULL, LOG_DBG) == 0);
	assert(try_log(lb, "prefix", NULL, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix", NULL, LOG_IO_IN) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix", &node_id, LOG_INFORM) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_DBG) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_IO_IN) == 0);

	/* Now use debug as default */
	assert(opt_log_level("debug", lb) == NULL);
	assert(try_log(lb, "prefix", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_INFORM) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_DBG) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix", NULL, LOG_IO_IN) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix", &node_id, LOG_INFORM) == 2);
	assert(try_log(lb, "prefix", &node_id, LOG_DBG) == 2);
	assert(try_log(lb, "prefix", &node_id, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_IO_IN) == 0);

	/* Log level exception for prefix */
	assert(opt_log_level("broken:prefix2", lb) == NULL);
	assert(try_log(lb, "prefix", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_INFORM) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_DBG) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix", NULL, LOG_IO_IN) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix", &node_id, LOG_INFORM) == 2);
	assert(try_log(lb, "prefix", &node_id, LOG_DBG) == 2);
	assert(try_log(lb, "prefix", &node_id, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_IO_IN) == 0);

	assert(try_log(lb, "prefix2", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix2", NULL, LOG_INFORM) == 0);
	assert(try_log(lb, "prefix2", NULL, LOG_DBG) == 0);
	assert(try_log(lb, "prefix2", NULL, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix2", NULL, LOG_IO_IN) == 0);
	assert(try_log(lb, "prefix2", &node_id, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix2", &node_id, LOG_INFORM) == 0);
	assert(try_log(lb, "prefix2", &node_id, LOG_DBG) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_IO_IN) == 0);

	/* Log level exception for nodeid: that only does broken! */
	assert(opt_log_level("broken:0266e4598", lb) == NULL);
	assert(try_log(lb, "prefix", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_INFORM) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_DBG) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix", NULL, LOG_IO_IN) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix", &node_id, LOG_INFORM) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_DBG) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix", &node_id, LOG_IO_IN) == 0);

	/* File exceptions: log stdout prefix to stdout */
	assert(opt_log_level("io:stdout1:-", lb) == NULL);
	assert(try_log(lb, "stdout1", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "stdout1", NULL, LOG_INFORM) == 2);
	assert(try_log(lb, "stdout1", NULL, LOG_DBG) == 2);
	assert(try_log(lb, "stdout1", NULL, LOG_IO_OUT) == 1);
	assert(try_log(lb, "stdout1", NULL, LOG_IO_IN) == 1);
	assert(try_log(lb, "prefix", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_INFORM) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_DBG) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix", NULL, LOG_IO_IN) == 0);

	/* File exceptions: log stdout2 prefix to stdout */
	assert(opt_log_level("broken:stdout2:-", lb) == NULL);
	assert(try_log(lb, "stdout2", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "stdout2", NULL, LOG_INFORM) == 1);
	assert(try_log(lb, "stdout2", NULL, LOG_DBG) == 1);
	assert(try_log(lb, "stdout2", NULL, LOG_IO_OUT) == 0);
	assert(try_log(lb, "stdout2", NULL, LOG_IO_IN) == 0);
	assert(try_log(lb, "prefix", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_INFORM) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_DBG) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_IO_OUT) == 0);
	assert(try_log(lb, "prefix", NULL, LOG_IO_IN) == 0);

	/* File exception: tmpfile logs everything */
	assert(opt_log_level(tal_fmt(tmpctx, "io::%s", tmpfiletemplate), lb) == NULL);
	assert(try_log(lb, "stdout1", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "stdout1", NULL, LOG_INFORM) == 2);
	assert(try_log(lb, "stdout1", NULL, LOG_DBG) == 2);
	assert(try_log(lb, "stdout1", NULL, LOG_IO_OUT) == 2);
	assert(try_log(lb, "stdout1", NULL, LOG_IO_IN) == 2);
	assert(try_log(lb, "stdout2", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "stdout2", NULL, LOG_INFORM) == 1);
	assert(try_log(lb, "stdout2", NULL, LOG_DBG) == 1);
	assert(try_log(lb, "stdout2", NULL, LOG_IO_OUT) == 1);
	assert(try_log(lb, "stdout2", NULL, LOG_IO_IN) == 1);
	assert(try_log(lb, "prefix", NULL, LOG_BROKEN) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_INFORM) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_DBG) == 2);
	assert(try_log(lb, "prefix", NULL, LOG_IO_OUT) == 1);
	assert(try_log(lb, "prefix", NULL, LOG_IO_IN) == 1);

	/* Close output file, avoid upsetting valgrind */
	fclose(ld->log_book->log_files[1]->f);

	/* Freeing (last) log frees logbook */
	tal_free(ld->log);
	common_shutdown();
}
