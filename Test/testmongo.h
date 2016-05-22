
#ifndef TEST_MONGO_H
#define TEST_MONGO_H

#include "common/socketdef.h"
#include "lib/src/mongo/libbson/bcon.h"
#include "lib/src/mongo/mongoc/mongoc.h"

static void
bulk1(mongoc_collection_t *collection)
{
	mongoc_bulk_operation_t *bulk;
	bson_error_t error;
	bson_t *doc;
	bson_t reply;
	char *str;
	bool ret;
	int i;

	bulk = mongoc_collection_create_bulk_operation(collection, true, NULL);

	for (i = 0; i < 10000; i++) {
		doc = BCON_NEW("i", BCON_INT32(i));
		mongoc_bulk_operation_insert(bulk, doc);
		bson_destroy(doc);
	}

	ret = mongoc_bulk_operation_execute(bulk, &reply, &error);

	str = bson_as_json(&reply, NULL);
	printf("%s\n", str);
	bson_free(str);

	if (!ret) {
		fprintf(stderr, "Error: %s\n", error.message);
	}

	bson_destroy(&reply);
	mongoc_bulk_operation_destroy(bulk);
}

namespace TestMongo
{
	int Fun1()
	{
		mongoc_database_t *database;
		mongoc_cursor_t *cursor;
		mongoc_client_t *client;
		const bson_t *reply;
		bson_error_t error;
		bson_t ping;
		char *host_and_port = bson_strdup_printf("mongodb://192.168.1.123:27017");
		char *str;

		mongoc_init();

		client = mongoc_client_new(host_and_port);

		if (!client) {
			fprintf(stderr, "Invalid hostname or port: %s\n", host_and_port);
			return 2;
		}

		bson_init(&ping);
		bson_append_int32(&ping, "ping", 4, 1);
		database = mongoc_client_get_database(client, "test");
		cursor = mongoc_database_command(database, (mongoc_query_flags_t)0, 0, 1, 0, &ping, NULL, NULL);
		if (mongoc_cursor_next(cursor, &reply)) {
			str = bson_as_json(reply, NULL);
			fprintf(stdout, "%s\n", str);
			bson_free(str);
		}
		else if (mongoc_cursor_error(cursor, &error)) {
			fprintf(stderr, "Ping failure: %s\n", error.message);
			return 3;
		}

		mongoc_cursor_destroy(cursor);
		bson_destroy(&ping);
		mongoc_client_destroy(client);
		bson_free(host_and_port);

		return 0;
	}
	
}

#endif // !MONGO_H
