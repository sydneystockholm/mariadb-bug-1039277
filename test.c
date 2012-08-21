#include "test.h"

void *test_thread_fn(void *arg) {
    struct test_thread *thread = arg;
    Connection_T connection = ConnectionPool_getConnection(thread->pool);
    PreparedStatement_T statement = Connection_prepareStatement(connection, TEST_SQL_SELECT);
    ResultSet_T result = PreparedStatement_executeQuery(statement);
    while (ResultSet_next(result))
        ;
    Connection_close(connection);
    printf("Thread %d exited normally\n", thread->id);
    return NULL;
}

int main(int argc, char **argv) {
    struct test_thread threads[TEST_THREADS];
    URL_T url = URL_new(TEST_DB_URL);
    ConnectionPool_T pool = ConnectionPool_new(url);
    ConnectionPool_start(pool);
    for (int i = 0; i < TEST_THREADS; i++) {
        printf("Spawning thread %d\n", i);
        threads[i].id = i;
        threads[i].pool = pool;
        pthread_create(&threads[i].thread, NULL, test_thread_fn, &threads[i]);
    }
    for (int i = 0; i < TEST_THREADS; i++) {
        pthread_join(threads[i].thread, NULL);
    }
    ConnectionPool_free(&pool);
    URL_free(&url);
    return 0;
}

