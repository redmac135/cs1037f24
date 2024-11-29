#include "avl.h"

#ifndef MYRECORD_AVL_H
#define MYRECORD_AVL_H

typedef struct {
  AVLNODE *root;
  int count;
  float mean;
  float stddev;
} AVLDS;

/**
 * Merges a source AVL tree into a destination AVL tree without modifying the
 * source tree.
 *
 * @param rootp_dest - pointer to pointer to the destination tree root.
 * @param rootp_source - pointer to pointer to the source tree root.
 */
void merge_avl(AVLNODE **rootp_dest, AVLNODE **rootp_source);

/**
 * Merges two AVLDS structures. Updates dest with all nodes from source.
 * Recalculates statistics.
 * Clears source.
 *
 * @param dest - pointer to the destination AVLDS structure.
 * @param source - pointer to the source AVLDS structure.
 */
void merge_avlds(AVLDS *dest, AVLDS *source);

/**
 * Clears the AVL tree in the given AVLDS structure.
 * Resets the AVL tree and metrics.
 *
 * @param ds - pointer to the AVLDS structure.
 */
void avlds_clean(AVLDS *ds);

/**
 * Adds a record to the AVLDS structure. Updates the AVL tree and recalculates
 * the statistics.
 *
 * @param ds - pointer to the AVLDS structure.
 * @param data - record data for the new node.
 * @return - 1 if successful, 0 if failed.
 */
int add_record(AVLDS *ds, RECORD data);

/**
 * Removes a record from the AVLDS structure by name. Updates the AVL tree and
 * recalculates the statistics.
 *
 * @param ds - pointer to the AVLDS structure.
 * @param name - key to match with data.name for deletion.
 * @return - 1 if successful, 0 if failed.
 */
int remove_record(AVLDS *ds, char *name);

/**
 * Calculates the mean and standard deviation of the scores stored in the AVL
 * tree represented by the AVLDS structure. Traverses tree to calculate the sum
 * of scores and sum of squares.
 *
 * @param ds - pointer to the AVLDS structure.
 */
void calculate_stats(AVLDS *ds);

/**
 * Calculates the sum of the scores stored in the AVL tree.
 *
 * @param root - pointer to the root of the tree.
 * @return - the sum of the scores.
 */
float calculate_sum(AVLNODE *root);

/**
 * Calculates the variance of the scores stored in the AVL tree.
 *
 * @param root - pointer to the root of the tree.
 * @param mean - the mean of the scores.
 * @param variance - pointer to the variance value.
 */
void calculate_variance(AVLNODE *root, float mean, float *variance);

/**
 * Estimates the squareroot of a float.
 *
 * @param x - the float value.
 * @return - the squareroot of the float.
 */
float sqrt_est(float x);

#endif
