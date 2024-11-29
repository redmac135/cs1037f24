#include "myrecord_avl.h"
#include "avl.h"
#include <stdlib.h>

void merge_avl(AVLNODE **rootp_dest, AVLNODE **rootp_source) {
  if (*rootp_source == NULL) {
    return;
  }
  avl_insert(rootp_dest, (*rootp_source)->data);
  merge_avl(rootp_dest, &(*rootp_source)->left);
  merge_avl(rootp_dest, &(*rootp_source)->right);
  avl_delete(rootp_source, (*rootp_source)->data.name);

  return;
}

void merge_avlds(AVLDS *dest, AVLDS *source) {
  merge_avl(&dest->root, &source->root);
  calculate_stats(dest);
  avlds_clean(source);

  return;
}

void avlds_clean(AVLDS *ds) {
  avl_clean(&ds->root);
  ds->count = 0;
  ds->mean = 0.0;
  ds->stddev = 0.0;

  return;
}

int add_record(AVLDS *ds, RECORD data) {
  if (avl_search(ds->root, data.name) != NULL) {
    return 0;
  }
  avl_insert(&ds->root, data);
  calculate_stats(ds);

  return 1;
}

int remove_record(AVLDS *ds, char *name) {
  if (avl_search(ds->root, name) == NULL) {
    return 0;
  }
  avl_delete(&ds->root, name);
  calculate_stats(ds);

  return 1;
}

void calculate_stats(AVLDS *ds) {
  ds->count = avl_count_nodes(ds->root);
  ds->mean = calculate_sum(ds->root) / ds->count;

  float variance = 0;
  calculate_variance(ds->root, ds->mean, &variance);

  ds->stddev = sqrt_est(variance / ds->count);

  return;
}

float calculate_sum(AVLNODE *root) {
  if (root == NULL) {
    return 0.0;
  }

  return root->data.score + calculate_sum(root->left) +
         calculate_sum(root->right);
}

void calculate_variance(AVLNODE *root, float mean, float *variance) {
  if (root == NULL) {
    return;
  }

  *variance += (root->data.score - mean) * (root->data.score - mean);
  calculate_variance(root->left, mean, variance);
  calculate_variance(root->right, mean, variance);

  return;
}

float sqrt_est(float x) {
  float root = x / 3, last, diff = 1;
  if (x <= 0)
    return 0;
  for (int i = 0; i < 32; i++) {
    last = root;
    root = (root + x / root) / 2;
    diff = root - last;
  }
  return root;
}
