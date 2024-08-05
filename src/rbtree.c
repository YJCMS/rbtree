#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree* p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t* nil = (node_t *)calloc(1, sizeof(node_t));
  nil->color = RBTREE_BLACK;
  p->nil = nil;
  p->root = nil;
  return p;
}

void delete_node_t (rbtree *t, node_t *node) {
  // 후위순회로 서브트리 순차적으로 제거
  if (node != t->nil) {
    delete_node_t(t, node->left);
    delete_node_t(t, node->right);
    free(node);
  }  
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  delete_node_t(t, t->root);
  free(t->nil);
  free(t);
}

// insert에 사용할 left_rotate 함수
void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  x->right = y->left;

  if (y->left != t->nil) {
    y->left->parent = x;
  }

  y->parent = x->parent;

  if (x->parent != t->nil) {
    t->root == t;
  } else if (x == x->parent->left) {
      x->parent->left = y;
  } else {
      x->parent->left = y;
  }

  y->left = x;
  x->parent = y;
}

// insert에 사용할 right_rotate 함수
void right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;
  x->left = y->right;

  if (y->right != t->nil) {
    y->right->parent = x;
  }

  y->parent = x->parent;

  if (x->parent != t->nil) {
    t->root == t;
  } else if (x == x->parent->right) {
      x->parent->right = y;
  } else {
      x->parent->right = y;
  }

  y->right = x;
  x->parent = y;
}

// insert에 사용할 insert_fixup함수
void insert_fixup(rbtree *t, node_t *z) {
  while (z->parent->color == RBTREE_RED) { // case 1, 2, 3 모두 부모가 red
    if (z->parent == z->parent->parent->left) { // z의 부모가 왼쪽 자식일 경우

      node_t *y = z->parent->parent->right; // z의 삼촌

      if (y->color == RBTREE_BLACK) { // z의case1 삽입된 red노드의 부모와 삼촌 모두 red인 경우
        z->parent->color = RBTREE_BLACK; 
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      } else {
          if(z == z->parent->right) {  // case2
            z = z->parent; 
            left_rotate(t, z);
          }
          z->parent->color = RBTREE_BLACK;  // case3
          z->parent->parent->color = RBTREE_RED;
          right_rotate(t, z->parent->parent);
      }
    } else {
        node_t *y =  z->parent->parent->left; // 방향 외에는 위의 코드와 같음

        if(y->color == RBTREE_RED) {
          z->parent->color = RBTREE_BLACK;
          y->color = RBTREE_BLACK;
          z->parent->parent->color = RBTREE_RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->left) {
            z = z->parent;
            right_rotate(t, z);
          } 
          z->parent->color = RBTREE_BLACK;
          z->parent->parent->color = RBTREE_RED;
          left_rotate(t, z->parent->parent);
        }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *z = (node_t*) calloc(1, sizeof(node_t));
  z->key = key;

  node_t *x = t->root;
  node_t *y = t->nil;

  while (x != t->nil) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z->parent = y;

  if (y == t->nil) {
    t->root = z;
  } else if (z->key < y->key) {
      y->left = z;
  } else {
      y->right = z;
  }
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
  
  insert_fixup(t, z);

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
