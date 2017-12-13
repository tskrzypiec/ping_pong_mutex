#include <pthread.h>
#include <stdio.h>
#include <string.h>

void ping_function(void);
void pong_function(void);

int flag=0;
pthread_mutex_t mutex;

void ping_function(void)
{
    do {
        pthread_mutex_lock( &mutex );
        if( flag )
        {
            printf("ping\n");
            flag = 0;
        }
        pthread_mutex_unlock( &mutex );
    } while(1);

    pthread_exit(0);
}


void pong_function(void)
{
    do {
        pthread_mutex_lock( &mutex );
        if( !flag )
        {
            printf("pong\n");
            flag = 1;
        }
        pthread_mutex_unlock( &mutex );
    } while(1);

    pthread_exit(0);
}

main()
{
    pthread_t ping, pong;
    pthread_mutex_init(&mutex, NULL);
    pthread_create( &ping, NULL, (void*)&ping_function, NULL );
    pthread_create( &pong, NULL, (void*)&pong_function, NULL );
    pthread_join( ping, NULL );
    pthread_join( pong, NULL );

    return 0;
}
