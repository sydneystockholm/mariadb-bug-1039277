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

#define TEST_SQL_SELECT \
    "SELECT 1"

struct test_thread {
    int id;
    pthread_t thread;
    Connection_T connection;
};

