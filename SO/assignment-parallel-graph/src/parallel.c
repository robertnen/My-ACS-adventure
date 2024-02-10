// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#include "os_graph.h"
#include "os_threadpool.h"
#include "log/log.h"
#include "utils.h"

#define NUM_THREADS		4
#define SIZE			sizeof(unsigned int)

static int sum;
static os_graph_t *graph;
static os_threadpool_t *tp;

static pthread_cond_t signal;
static pthread_mutex_t graph_lock, sum_lock;

typedef struct {
	os_graph_t *graph;
	unsigned int id;
} graph_task_t;

void process_node_t(void *idx)
{
	if (*(int *) idx < 0)
		return;

	if (!graph->num_nodes)
		return;

	unsigned int *u_idx, n, next;
	int value = 0;
	os_task_t *task;
	os_node_t *node;

	pthread_mutex_lock(&graph_lock);

	if (graph->visited[*(int *) idx]) {
		pthread_mutex_unlock(&graph_lock);
		return;
	}

	graph->visited[*(int *) idx] = PROCESSING;

	node = graph->nodes[*(int *) idx];
	n = node->num_neighbours;
	value = node->info; // to add in the sum

	pthread_mutex_unlock(&graph_lock);

	pthread_mutex_lock(&graph_lock);
	graph->visited[*(int *) idx] = DONE;
	pthread_mutex_unlock(&graph_lock);

	for (unsigned int i = 0; i < n; i++) {
		pthread_mutex_lock(&graph_lock);

		next = node->neighbours[i];

		if (graph->visited[next] == NOT_VISITED) {
			u_idx = calloc(1, SIZE);

			if (!u_idx) {
				fprintf(stderr, "Couldn't alloc memory for u_idx\n");
				return;
			}

			*u_idx = next;

			task = create_task(process_node_t, u_idx, NULL);
			enqueue_task(tp, task);
		}
		pthread_mutex_unlock(&graph_lock);
	}

	pthread_mutex_lock(&sum_lock);
	sum += value;
	pthread_mutex_unlock(&sum_lock);
}

static void process_node(unsigned int idx)
{
	unsigned int *u_idx = NULL;
	os_task_t *task = NULL;

	u_idx = calloc(1, SIZE);

	if (!u_idx) {
		fprintf(stderr, "Couldn't alloc memory for u_idx\n");
		return;
	}

	*u_idx = idx;

	task = create_task(process_node_t, u_idx, NULL);
	enqueue_task(tp, task);
}

int main(int argc, char *argv[])
{
	FILE *input_file;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s input_file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	input_file = fopen(argv[1], "r");
	DIE(input_file == NULL, "fopen");

	graph = create_graph_from_file(input_file);
	tp = create_threadpool(NUM_THREADS);

	pthread_cond_init(&signal, NULL);
	pthread_mutex_init(&graph_lock, NULL);
	pthread_mutex_init(&sum_lock, NULL);

	process_node(0);
	wait_for_completion(tp);
	destroy_threadpool(tp);

	printf("%d", sum);

	pthread_cond_destroy(&signal);
	pthread_mutex_destroy(&graph_lock);
	pthread_mutex_destroy(&sum_lock);

	return 0;
}
