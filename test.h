#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <zdb.h>

#define TEST_THREADS 32

//Note: need to CREATE DATABASE test_db

#define TEST_DB_HOST "localhost"
#define TEST_DB_PORT "3306"
#define TEST_DB_NAME "test_db"
#define TEST_DB_USER "root"
#define TEST_DB_PASS ""

#define TEST_DB_URL \
    "mysql://" TEST_DB_HOST ":" TEST_DB_PORT "/" TEST_DB_NAME \
        "?user=" TEST_DB_USER \
        "&password=" TEST_DB_PASS

#define TEST_SQL_CREATE \
    "CREATE TABLE IF NOT EXISTS events (" \
        "scope_id INT(11) UNSIGNED NOT NULL," \
        "timestamp_id MEDIUMINT(11) UNSIGNED NOT NULL," \
        "key_id INT(11) UNSIGNED NOT NULL," \
        "value_id INT(11) UNSIGNED NOT NULL," \
        "data MEDIUMBLOB NOT NULL," \
        "PRIMARY KEY (scope_id, timestamp_id, key_id, value_id))"

#define TEST_SQL_SELECT \
    "SELECT value_id, LENGTH(data) len FROM events " \
        "WHERE scope_id = ? AND timestamp_id = ? AND key_id = ? " \
        "ORDER BY 2 DESC LIMIT ?"

struct test_thread {
    int id;
    pthread_t thread;
    ConnectionPool_T pool;
};

