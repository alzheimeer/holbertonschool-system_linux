#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <object.h>
#include <listobject.h>
#include <bytesobject.h>
#include <floatobject.h>
#include <string.h>
/**
 * print_python_list - print python things
 * @p: pointer to PyObject p
 */
void print_python_list(PyObject *p)
{
	size_t a, size, i;
	const char *t;
	PyListObject *list;

	setbuf(stdout, NULL);
	printf("[*] Python list info\n");
	if (PyList_Check(p) == 0)
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	list = (PyListObject *)p;
	size = PyList_GET_SIZE(p);
	a = list->allocated;
	printf("[*] Size of the Python List = %ld\n[*] Allocated = %li\n", size, a);
	for (i = 0; i < size; i++)
	{
		t = Py_TYPE(PyList_GetItem(p, i))->tp_name;
		printf("Element %li: %s\n", i, t);
	}
}
