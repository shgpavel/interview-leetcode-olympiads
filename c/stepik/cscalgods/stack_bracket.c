#include <stdio.h>
#include <stdlib.h>

struct bracket_info {
  int bracket_char;
  size_t position;
};

typedef struct stack_node {
  struct bracket_info info;
  struct stack_node *next;
} stack_node;

typedef struct stack {
  stack_node *top;
} stack;

static inline stack_node **find_indirect(stack *s, stack_node *target) {
  stack_node **node_ptr = &s->top;
  while (*node_ptr != target) {
    node_ptr = &(*node_ptr)->next;
  }
  return node_ptr;
}

void remove_node(stack *s, stack_node *target) {
  stack_node **node_ptr = find_indirect(s, target);
  *node_ptr = target->next;
}

void insert_before(stack *s, stack_node *before, stack_node *new_node) {
  stack_node **node_ptr = find_indirect(s, before);
  *node_ptr = new_node;
  new_node->next = before;
}

size_t stack_size(stack *s) {
  size_t count = 0;
  stack_node *current = s->top;
  while (current) {
    current = current->next;
    count++;
  }
  return count;
}

void stack_init(stack *s) { s->top = NULL; }

int stack_is_empty(stack *s) { return s->top == NULL; }

void stack_push(stack *s, int bracket_char, size_t position) {
  stack_node *new_node = (stack_node *)malloc(sizeof(stack_node));
  new_node->info.bracket_char = bracket_char;
  new_node->info.position = position;
  new_node->next = s->top;
  s->top = new_node;
}

struct bracket_info stack_pop(stack *s) {
  if (stack_is_empty(s)) {
    exit(EXIT_FAILURE);
  }
  stack_node *top_node = s->top;
  struct bracket_info info = top_node->info;
  s->top = top_node->next;
  free(top_node);
  return info;
}

struct bracket_info stack_peek(stack *s) {
  if (stack_is_empty(s)) {
    return (struct bracket_info){0, 0};
  }
  return s->top->info;
}

void stack_clear(stack *s) {
  while (!stack_is_empty(s)) {
    stack_pop(s);
  }
}

inline int is_closing_bracket(int ch) {
  return ch == ')' || ch == ']' || ch == '}';
}

inline int is_opening_bracket(int ch) {
  return ch == '(' || ch == '[' || ch == '{';
}

int main() {
  stack s;
  stack_init(&s);

  int ch;
  for (size_t position = 1; (ch = getchar()) != '\n'; ++position) {
    struct bracket_info last_bracket = stack_peek(&s);

    switch (ch) {
      case ')':
        if (last_bracket.bracket_char == '(') {
          stack_pop(&s);
        } else {
          goto handle_bracket;
        }
        break;
      case ']':
        if (last_bracket.bracket_char == '[') {
          stack_pop(&s);
        } else {
          goto handle_bracket;
        }
        break;
      case '}':
        if (last_bracket.bracket_char == '{') {
          stack_pop(&s);
        } else {
          goto handle_bracket;
        }
        break;
      default:
      handle_bracket:
        if (is_closing_bracket(ch) || is_opening_bracket(ch)) {
          stack_push(&s, ch, position);
        }
        if (is_closing_bracket(ch)) {
          goto end_loop;
        }
        break;
    }
  }

end_loop:
  if (stack_is_empty(&s)) {
    printf("Success\n");
  } else {
    printf("%zu\n", stack_pop(&s).position);
  }
  stack_clear(&s);
  return 0;
}
