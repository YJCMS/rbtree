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

  if (x->parent == t->nil) {
    t->root = y;
  } else if (x == x->parent->left) {
      x->parent->left = y;
  } else {
      x->parent->right = y;
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

  if (x->parent == t->nil) {
    t->root = y;
  } else if (x == x->parent->right) {
      x->parent->right = y;
  } else {
      x->parent->left = y;
  }

  y->right = x;
  x->parent = y;
}

// insert에 사용할 insert_fixup함수
void insert_fixup(rbtree *t, node_t *z) {
  while (z->parent->color == RBTREE_RED) { // case 1, 2, 3 모두 부모가 red
    if (z->parent == z->parent->parent->left) { // z의 부모가 왼쪽 자식일 경우

      node_t *y = z->parent->parent->right; // z의 삼촌

      if (y->color == RBTREE_RED) { // z의case1 삽입된 red노드의 부모와 삼촌 모두 red인 경우
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

        if(y->color == RBTREE_RED) { // z의case1 삽입된 red노드의 부모와 삼촌 모두 red인 경우
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
  node_t *x = (node_t*) calloc(1, sizeof(node_t));
  x = t->root;
  while (x != t->nil) {
    if (key < x->key) {
      x = x->left;
    } else if (key > x->key) {
        x = x->right;
    } else if (key == x->key) {
        return x;
    } 
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *x = t->root; 

  while (x->left != t->nil) {
    x = x->left;
  }

  return x;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *x = t->root;

  while (x->right != t->nil) {
    x = x->right;
  }

  return x;
}

node_t *tree_minimum(const rbtree *t, node_t *sub_r) {
  node_t *new_r = sub_r;

  if (new_r == t->nil) {
    return new_r;
  } 

  while (new_r->left != t->nil) {
    new_r = new_r->left;
  }

  return new_r;
}

void rb_transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil) {
      t->root = v;
  } else if(u == u->parent->left) {
      u->parent->left = v;
  } else {
      u->parent->right = v;
  }
  v->parent = u->parent;
}

void rb_delete_fixup(rbtree *t, node_t *x) {
  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left) {
      node_t *w = x->parent->right;
      
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        w->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }
      
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      } else {
          if (w->right->color == RBTREE_BLACK) {
            w->left->color = RBTREE_BLACK;
            w->color = RBTREE_RED;
            right_rotate(t, w);
            w = x->parent->right;
          }
          w->color = x->parent->color;
          x->parent->color = RBTREE_BLACK;
          w->right->color = RBTREE_BLACK;
          left_rotate(t, x->parent);
          x = t->root;
      }
    } 
    else {
      node_t *w = x->parent->left;
      
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        w->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      
      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      } else {
          if (w->left->color == RBTREE_BLACK) {
            w->right->color = RBTREE_BLACK;
            w->color = RBTREE_RED;
            left_rotate(t, w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color = RBTREE_BLACK;
          w->left->color = RBTREE_BLACK;
          right_rotate(t, x->parent);
          x = t->root;
      }
    }
  } 
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase

  //p가 없는 노드이면 삭제 작업 안함
  if (p == NULL) {
    return 0;
  }

  node_t *y = p;
  color_t y_original_color = y->color;
  // x를 위에 선언 해보기
  node_t *x;

  if (p->left == t->nil) {
    x = p->right;
    rb_transplant(t, p, p->right); // p를 오른쪽 자식으로 바꾸기
  } else if(p->right == t->nil) {
    x = p->left;
    rb_transplant(t, p, p->left); // p를 왼쪽 자식으로 바꾸기
  } else {
      y = tree_minimum(t, p->right); // y는 p의 후손
      y_original_color = y->color;
      x = y->right;
      if(y != p->right) { // y가 트리에서 더 아래쪽인지 확인
        rb_transplant(t, y, y->right);  // y를 오른쪽 자식으로 바꾸기
        y->right = p->right;  // p의 오른쪽 자식
        y->right->parent = y; // y의 오른쪽 자식
      } else {
        x->parent = y; // x가 nil인 경우  
      }
      rb_transplant(t, p, y); // p를 그 후손인 y로 바꾸기
      y->left = p->left; // p의 왼쪽 자식을 y에 부여
      y->left->parent = y; // 왼쪽 자식이 없는 y
      y->color = p->color; 
  }

  if (y_original_color == RBTREE_BLACK) { // 규칙을 위반할 경우
    rb_delete_fixup(t, x); // 수정
  }

  free(p);
  return 0;
}

void inorder(const rbtree *t, node_t *x, key_t *arr, int* i, size_t n) {
  if(x != t->nil && *i < n) {
    inorder(t, x->left, arr, i, n);
    arr[(*i)++] = x->key;
    inorder(t, x->right, arr, i, n);
  }
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  int size = 0;
  int *i = &size;
  inorder(t, t->root, arr, i, n);
  return 0;

  // min값으로 구하는 방법
  // for (int i = 0; i < n; i++) {
  //   node_t *min = rbtree_min(t);
  //   arr[i] = min->key;
  //   rbtree_erase(t, min);
  // }
  // return 0;
}
