#include <string.h>
#include <stdio.h>
#include "mystack.h"
#include "myqueue.h"
#include "unity.h"
#include "testrunner.h"

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp(void)
{
}

void tearDown(void)
{
  // This is run after EACH test
}

void test_create(void)
{
  QueueMeta_t *test = myqueue_create(1);
  TEST_ASSERT_NOT_NULL(test);
  myqueue_delete(test);
}
void test_null_enqueue(void)
{
  QueueMeta_t *test = NULL;
  int a = 5;
  int b = myqueue_enqueue(test, &a);
  TEST_ASSERT_EQUAL(-1, b);
  myqueue_delete(test);
}
void test_enqueue(void)
{
  QueueMeta_t *test = myqueue_create(5);
  int a = 5;
  myqueue_enqueue(test, &a);
  TEST_ASSERT_EQUAL(5, a);
  myqueue_delete(test);
}
void test_queue_create_delete(void)
{
  QueueMeta_t *test = myqueue_create(5);
  myqueue_delete(test);
  if (test == NULL)
  {
    TEST_ASSERT_NULL(test);
  }
  TEST_ASSERT_NULL(test->stack_in);
  TEST_ASSERT_NULL(test->stack_out);
  // free(test);
}

void test_enqueue_dequeue(void)
{
  QueueMeta_t *test = myqueue_create(sizeof(int));
  int a = 5;
  myqueue_enqueue(test, &a);
  int b;
  void *c = malloc(sizeof(int));
  myqueue_dequeue(test, &c);
  myqueue_delete(test);
  // free(test);
  b = (int)c;
  TEST_ASSERT_EQUAL(a, (int)c);
}

int main()
{
  UnityBegin();
  // MY_RUN_TEST(test_queue_create_delete);
  MY_RUN_TEST(test_enqueue_dequeue);
  // MY_RUN_TEST(test_null_enqueue);
  // MY_RUN_TEST(test_enqueue);
  // MY_RUN_TEST(test_create);

  return UnityEnd();
}
