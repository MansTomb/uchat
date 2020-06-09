#include "server.h"

int mx_create_message_queue(int queue_size, t_message_queue *queue) {
    queue->data = calloc(queue_size, sizeof(t_message));
    queue->size = queue_size;
    queue->current = 0;

    return 0;
}

void mx_delete_message_queue(t_message_queue *queue) {
    free(queue->data);
    queue->data = NULL;
}

int mx_enqueue(t_message_queue *queue, t_message *message) {
    if (queue->current == queue->size)
        return -1;
    memcpy(&queue->data[queue->current], message, sizeof(t_message));
    queue->current++;
    return 0;
}

int mx_dequeue(t_message_queue *queue, t_message *message) {
    if (queue->current == 0)
        return -1;
    memcpy(message, &queue->data[queue->current - 1], sizeof(t_message));
    queue->current--;
    return 0;
}

int mx_dequeue_all(t_message_queue *queue) {
    queue->current = 0;
    return 0;
}
