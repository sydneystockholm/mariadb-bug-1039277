#include "test.h"

void *test_thread_fn(void *arg) {
    struct test_thread *thread = arg;
    PreparedStatement_T statement = Connection_prepareStatement(thread->connection, TEST_SQL_SELECT);
    ResultSet_T result = PreparedStatement_executeQuery(statement);
    while (ResultSet_next(result))
        ;
    printf("Thread %d exited normally\n", thread->id);
    return NULL;
}

int main(int argc, char **argv) {
    struct test_thread threads[TEST_THREADS];
    URL_T url = URL_new(TEST_DB_URL);
    ConnectionPool_T pool = ConnectionPool_new(url);
    ConnectionPool_setMaxConnections(pool, TEST_THREADS);
    ConnectionPool_start(pool);
    for (int i = 0; i < TEST_THREADS; i++) {
        threads[i].id = i;
        while ((threads[i].connection = ConnectionPool_getConnection(pool)) == NULL)
            ;
    }
    for (int i = 0; i < TEST_THREADS; i++) {
        printf("Spawning thread %d\n", i);
        pthread_create(&threads[i].thread, NULL, test_thread_fn, &threads[i]);
    }
    for (int i = 0; i < TEST_THREADS; i++) {
        pthread_join(threads[i].thread, NULL);
        Connection_close(threads[i].connection);
    }
    ConnectionPool_free(&pool);
    URL_free(&url);
    return 0;
}

