#include <string.h>
#include <stdio.h>

#include "mystack.h"
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

void test_object_create()
{
	int num = 2;
	StackObject_t *temp = createStackObject(&num, sizeof(int));
	int n = *(int *)temp->obj;
	TEST_ASSERT_EQUAL(2, n);
	free(temp->obj);
	free(temp);
}
void test_stack_create()
{
	StackMeta_t *temp = mystack_create(sizeof(int));

	TEST_ASSERT_NOT_NULL(temp);
	mystack_destroy(temp);
	// free(temp);
}
void test_stack_push()
{
	StackMeta_t *temp = mystack_create(sizeof(int));
	int n = 2;
	TEST_ASSERT_EQUAL(0, mystack_push(temp, &n));
	mystack_destroy(temp);
	// free(temp);
}
void test_stack_push_1()
{
	StackMeta_t *temp = mystack_create(sizeof(int));
	int n = 2;
	TEST_ASSERT_EQUAL(0, mystack_push(temp, &n));
	TEST_ASSERT_EQUAL(0, mystack_push(temp, &n));
	mystack_destroy(temp);
	// free(temp);
}
void test_stack_push_probe()
{
	StackMeta_t *temp = mystack_create(sizeof(int));
	int n = 2;
	mystack_push(temp, &n);
	TEST_ASSERT_EQUAL(2, *(int *)temp->stack->obj);
	mystack_destroy(temp);
	// free(temp);
}
void test_stack_push_multiple()
{
	StackMeta_t *temp = mystack_create(sizeof(int));
	int n = 2;
	mystack_push(temp, &n);
	mystack_push(temp, &n);
	n = 3;
	mystack_push(temp, &n);

	// StackObject_t *t = temp->stack->next->next;
	// TEST_ASSERT_EQUAL(3, *(int *)t->obj);
	mystack_destroy(temp);
	//(temp);
}
void test_stack_pop_probe()
{
	StackMeta_t *temp = mystack_create(sizeof(int));
	int n = 2;
	mystack_push(temp, &n);
	int a = 4;
	mystack_push(temp, &a);
	int x = 3;
	mystack_push(temp, &x);

	// int c, b = 0;
	// int v = 0;
	// mystack_pop(temp, &c);
	// TEST_ASSERT_EQUAL(3, c);
	// mystack_pop(temp, &v);
	// TEST_ASSERT_EQUAL(4, v);
	// mystack_pop(temp, &b);
	// TEST_ASSERT_EQUAL(2, b);
	mystack_destroy(temp);
	// free(temp);
}
void test_stack_pop()
{
	StackMeta_t *temp = mystack_create(sizeof(int));
	int n = 2;
	mystack_push(temp, &n);
	mystack_push(temp, &n);
	TEST_ASSERT_EQUAL(0, mystack_pop(temp, &n));
	mystack_destroy(temp);
}
void test_stack_nofelem()
{
	StackMeta_t *temp = mystack_create(sizeof(int));
	int n = 2;
	mystack_push(temp, &n);
	mystack_push(temp, &n);
	mystack_push(temp, &n);
	mystack_push(temp, &n);
	mystack_push(temp, &n);
	TEST_ASSERT_EQUAL(5, mystack_nofelem(temp));
	mystack_destroy(temp);
}
int main(int argc, char *argv[])
{
	UnityBegin();
	MY_RUN_TEST(test_object_create);
	MY_RUN_TEST(test_stack_create);
	MY_RUN_TEST(test_stack_push);
	MY_RUN_TEST(test_stack_push_1);
	MY_RUN_TEST(test_stack_push_probe);
	MY_RUN_TEST(test_stack_push_multiple);
	MY_RUN_TEST(test_stack_pop);
	MY_RUN_TEST(test_stack_pop_probe);
	MY_RUN_TEST(test_stack_nofelem);
	return UnityEnd();
}
