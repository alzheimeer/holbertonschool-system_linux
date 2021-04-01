#include <Python.h>

/**
 * print_python_int - print int
 * @p: pointer to PyObject p
 */
void print_python_int(PyObject *p)
{
	unsigned long value = 0;
	Py_ssize_t size, i, _abs;
	digit *number;


	if (PyLong_Check(p) == 0 || p == NULL)
	{
		printf("Invalid Int Object\n");
		return;
	}

	number = ((PyLongObject *)(p))->ob_digit;
	size = ((PyVarObject *)(p))->ob_size, _abs = abs(size);


	if (_abs > 3 || (_abs == 3 && number[2] > 15))
	{
		printf("C unsigned long int overflow\n");
		return;
	}

	for (i = 0; i < _abs; i++)
		value += number[i] * (1L << (i * PyLong_SHIFT));

	if (size < 0)
		printf("-");

	printf("%lu\n", value);
}
