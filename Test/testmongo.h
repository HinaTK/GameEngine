
#ifndef TEST_MONGO_H
#define TEST_MONGO_H

#include "common/socketdef.h"
#include "lib/src/mongo/libbson/bcon.h"
#include "lib/src/mongo/mongoc/mongoc.h"

// static void
// bulk1(mongoc_collection_t *collection)
// {
// 	mongoc_bulk_operation_t *bulk;
// 	bson_error_t error;
// 	bson_t *doc;
// 	bson_t reply;
// 	char *str;
// 	bool ret;
// 	int i;
// 
// 	bulk = mongoc_collection_create_bulk_operation(collection, true, NULL);
// 
// 	for (i = 0; i < 10000; i++) {
// 		doc = BCON_NEW("i", BCON_INT32(i));
// 		mongoc_bulk_operation_insert(bulk, doc);
// 		bson_destroy(doc);
// 	}
// 
// 	ret = mongoc_bulk_operation_execute(bulk, &reply, &error);
// 
// 	str = bson_as_json(&reply, NULL);
// 	printf("%s\n", str);
// 	bson_free(str);
// 
// 	if (!ret) {
// 		fprintf(stderr, "Error: %s\n", error.message);
// 	}
// 
// 	bson_destroy(&reply);
// 	mongoc_bulk_operation_destroy(bulk);
// }

namespace TestMongo
{
	int Fun1()
	{
		mongoc_client_t *client;
		mongoc_collection_t *collection;
		mongoc_cursor_t *cursor;
		bson_error_t error;
		const bson_t *doc;
		const char *uristr = "mongodb://192.168.1.123/";
		const char *collection_name = "test";
		bson_t query;
		char *str;

		mongoc_init();

		client = mongoc_client_new(uristr);

		if (!client) {
			fprintf(stderr, "Failed to parse URI.\n");
			return EXIT_FAILURE;
		}

		bson_init(&query);

		collection = mongoc_client_get_collection(client, "test", collection_name);
		cursor = mongoc_collection_find(collection,
			MONGOC_QUERY_NONE,
			0,
			0,
			0,
			&query,
			NULL,  /* Fields, NULL for all. */
			NULL); /* Read Prefs, NULL for default */

		while (mongoc_cursor_next(cursor, &doc)) {
			str = bson_as_json(doc, NULL);
			fprintf(stdout, "%s\n", str);
			bson_free(str);
		}

		if (mongoc_cursor_error(cursor, &error)) {
			fprintf(stderr, "Cursor Failure: %s\n", error.message);
			return EXIT_FAILURE;
		}

		bson_destroy(&query);
		mongoc_cursor_destroy(cursor);
		mongoc_collection_destroy(collection);
		mongoc_client_destroy(client);

		mongoc_cleanup();

		return EXIT_SUCCESS;
	}
	
}

#endif // !MONGO_H
