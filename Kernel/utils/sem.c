// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "sem.h"

static uint32_t semLock;

typedef struct node_t {
    sem_t *sem;
    struct node_t *next;
} node_t;

node_t *firstSem = NULL;
static char counter = 0;

node_t * searchSem(char * name, node_t ** prev) {
    *prev = NULL;
    node_t * aux = firstSem;
    while (aux != NULL) {
        if (!strcmp(name, aux->sem->name))
            break;
        aux = aux->next;
    }
    return aux;
}

sem_t *semOpen(char *name, unsigned int value) {
    enter_region(&semLock);

    node_t * prev = NULL;
    node_t * aux = searchSem(name, &prev);

    if (aux != NULL) {
        leave_region(&semLock);
        return aux->sem;
    }

    sem_t *sem = pvPortMalloc(sizeof(sem_t));
    node_t *node = pvPortMalloc(sizeof(node_t));
    node->sem = sem;
    node->next = firstSem;
    firstSem = node;
    sem->name = pvPortMalloc(MAX_NAME);
    strcpy(sem->name, name);
    sem->value = value;
    sem->entering = NULL;
    sem->last = NULL;
    counter++;

    leave_region(&semLock);

    return sem;
}

char semClose(sem_t *sem) {
    if (sem == NULL)
        return EXIT_FAILURE;

    enter_region(&semLock);

    node_t *del = NULL;

    if (firstSem->sem == sem) {
        del = firstSem;
        firstSem = firstSem->next;
    } else {
        node_t *aux = firstSem;
        while (aux != NULL) {
            if (aux->next != NULL) {
                if (aux->next->sem == sem) {
                    del = aux->next;
                    aux->next = aux->next->next;
                    break;
                }
            }
            aux = aux->next;
        }
    }

    if (del == NULL) {
        leave_region(&semLock);
        return EXIT_FAILURE;
    }

    pid_t *pid = sem->entering;
    while (pid != NULL) {
        pid_t *aux = pid;
        pid = pid->next;
        vPortFree(aux);
    }
    vPortFree(sem->name);
    vPortFree(sem);
    vPortFree(del);

    counter--;
    leave_region(&semLock);

    return EXIT_SUCCESS;
}

#include "video.h"

void semWait(sem_t *sem) {
    enter_region(&semLock);

    if (sem->value > 0) {
        sem->value--;
    } else {
        leave_region(&semLock);

        pid_t *curr = pvPortMalloc(sizeof(pid_t));
        curr->pid = getPid();
        curr->next = NULL;
        if (sem->entering == NULL)
            sem->entering = curr;
        if (sem->last != NULL)
            sem->last->next = curr;
        sem->last = curr;
        block(curr->pid);

        enter_region(&semLock);
        sem->value--;
    }

    leave_region(&semLock);
}

void semPost(sem_t *sem) {
    enter_region(&semLock);

    sem->value++;

    if (sem->entering != NULL) {
        pid_t *aux = sem->entering;
        sem->entering = sem->entering->next;
        if (sem->entering == NULL)
            sem->last = NULL;
        leave_region(&semLock);
        unblockFirst(aux->pid);
        vPortFree(aux);
        enter_region(&semLock);
    }

    leave_region(&semLock);
}

char getSemaphoresData(char *out, node_t *node) {
    if (node == NULL)
        return EXIT_FAILURE;

    char written = 0;

    char flag = 0;
    for (int j = 0; j < MAX_NAME_SIZE; j++) {
        if (!flag && node->sem->name[j] == 0)
            flag = 1;
        else if (flag)
            out += addSpaces(out, 1);
        else
            *out++ = node->sem->name[j];
    }
    written += MAX_NAME_SIZE;

    out += addSpaces(out, 2);
    written += 2;

    char buffer[10];
    char copied = strcpy(out, itoa(node->sem->value, buffer, 10, 2));
    out += copied;
    out += addSpaces(out, MAX_ATTR_SIZE - copied);
    written += MAX_ATTR_SIZE;
    out += addSpaces(out, 2);
    written += 2;

    pid_t *aux_pid = node->sem->entering;

    while (aux_pid != NULL) {
        copied = strcpy(out, itoa(aux_pid->pid, buffer, 10, 10));
        aux_pid = aux_pid->next;
        copied += addSpaces(out, 1);
        out += copied;
        written += copied;
    }
    return written;
}

char *getEntering(sem_t *sem) {
    char *ans = pvPortMalloc(sizeof(pid_t * ));
    pid_t *aux = sem->entering;
    char buffer[MAX_PID];
    while (aux != NULL) {
        strcpy(ans, itoa(aux->pid, buffer, 10, 3));
        aux = aux->next;
        if (aux != NULL)
            strcpy(ans, " ");
    }
    return ans;
}

char *getSems() {
    char *ans = pvPortMalloc(MIN_SIZE + counter * SEM_DATA_MAX_SIZE);
    char *ret = ans;

    char *info = "name       value   pidsWaiting\n";
    ans += strcpy(ans, info);

    node_t *aux = firstSem;
    while (aux != NULL) {
        char writtenChars = getSemaphoresData(ans, aux);
        if (writtenChars == EXIT_FAILURE)
            return NULL;
        ans += writtenChars - 1;
        *ans++ = '\n';

        aux = aux->next;

    }
    *--ans = 0;

    return ret;
}
