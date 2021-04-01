#include <Python.h>
/**
 * print_python_int - prints info about python int object
 * @p: Python generic object
 */
void print_python_int(PyObject *p)
{
	PyLongObject *_base, *_dig;
	Py_ssize_t s, i, j;
	digit *_p, u, *cout;
	twodigits z;
	int dig;

	if (!p || !PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}
	_dig = (PyLongObject *)p;
	dig = (33 * _PyLong_DECIMAL_SHIFT) /
		(10 * PyLong_SHIFT - 33 * _PyLong_DECIMAL_SHIFT);
	s = 1 + abs(Py_SIZE(_dig)) + abs(Py_SIZE(_dig)) / dig;
	_base = _PyLong_New(s);
	if (_base == NULL)
		return;
	_p = _dig->ob_digit, cout = _base->ob_digit,  s = 0;
	for (i = abs(Py_SIZE(_dig)); --i >= 0; )
	{
		u = _p[i];
		for (j = 0; j < s; j++)
		{
			z = (twodigits)cout[j] << PyLong_SHIFT | u;
			u = (digit)(z / _PyLong_DECIMAL_BASE);
			cout[j] = (digit)(z - (twodigits)u * _PyLong_DECIMAL_BASE);
		}
		while (u)
			cout[s++] = u % _PyLong_DECIMAL_BASE, u /= _PyLong_DECIMAL_BASE;
	}
	s == 0 ? cout[s++] = 0 : 0, Py_SIZE(_dig) < 0 ? putchar('-') : 0;
	for (i = s; --i >= 0;)
		i == s - 1 ? printf("%u", cout[i]) : printf("%09u", cout[i]);
	printf("\n");
}
