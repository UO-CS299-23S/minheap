#include "Python.h"
#include "structmember.h"

typedef struct {
    PyObject_HEAD
    int capacity;
    int tail;
    int* el;
} MinHeapObject;

static void MinHeap_dealloc(MinHeapObject* self) {
    free(self->el);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* MinHeap_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    MinHeapObject* self;
    self = (MinHeapObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->capacity = 0;
        self->tail = 0;
        self->el = NULL;
    }
    return (PyObject*)self;
}

static int MinHeap_init(MinHeapObject* self, PyObject* args, PyObject* kwds) {
    int capacity = 0;
    if (!PyArg_ParseTuple(args, "i", &capacity))
        return -1;

    if (capacity <= 0) {
        PyErr_SetString(PyExc_ValueError, "Capacity must be a positive integer");
        return -1;
    }

    self->capacity = capacity;
    self->tail = 0;
    self->el = (int*)malloc(capacity * sizeof(int));
    if (self->el == NULL) {
        PyErr_SetString(PyExc_MemoryError, "Failed to allocate memory");
        return -1;
    }

    return 0;
}

static PyObject* MinHeap_str(MinHeapObject* self) {
    char* str1 = (char*) malloc(self->tail * 3);
    strcpy(str1, "[");
    for (int i = 0; i < self->tail; i++) {
        char number[10];
        sprintf(number, "%d", self->el[i]);
        strcat(str1, number);
        if (i < self->tail-1) {
            strcat(str1, ", ");
        }
    }
    strcat(str1, "]");
    PyObject* result = PyUnicode_FromString(str1);
    free(str1);
    return result;
}

static PyObject* MinHeap_size(MinHeapObject* self) {
    return PyLong_FromLong(self->tail);
}

static PyObject* MinHeap_insert(MinHeapObject* self, PyObject* args) {
    int value = 0;
    if (!PyArg_ParseTuple(args, "i", &value))
        return NULL;

    if (self->tail >= self->capacity) {
        PyErr_SetString(PyExc_RuntimeError, "MinHeap is full");
        return NULL;
    }

    self->el[self->tail] = value;
    int c = self->tail;
    int temp;
    while (c != 0 && self->el[c] <= self->el[(c - 1) / 2]) {
        temp = self->el[c];
        self->el[c] = self->el[(c - 1) / 2];
        self->el[(c - 1) / 2] = temp;
        c = (c - 1) / 2;
    }

    self->tail++;
    Py_RETURN_NONE;
}

static PyObject* MinHeap_min(MinHeapObject* self) {
    if (self->tail == 0)
        return PyLong_FromLong(0);
    return PyLong_FromLong(self->el[0]);
}

static PyObject* MinHeap_del(MinHeapObject* self) {
    if (self->tail == 0)
        return PyLong_FromLong(0);

    int result = self->el[0];
    int temp = self->el[self->tail - 1];
    self->el[0] = temp;
    int c = 0;
    int size = self->tail - 1;
    int left_child, right_child, min_child, temp_child;

    while (1) {
        left_child = 2 * c + 1;
        right_child = 2 * c + 2;
        min_child = left_child;

        if (right_child < size && self->el[right_child] < self->el[left_child])
            min_child = right_child;

        if (min_child >= size || self->el[min_child] >= self->el[c])
            break;

        temp_child = self->el[c];
        self->el[c] = self->el[min_child];
        self->el[min_child] = temp_child;
        c = min_child;
    }

    self->tail--;
    return PyLong_FromLong(result);
}

static PyMethodDef MinHeap_methods[] = {
    { "size", (PyCFunction)MinHeap_size, METH_NOARGS, "Returns the number of elements in the MinHeap" },
    { "insert", (PyCFunction)MinHeap_insert, METH_VARARGS, "Inserts an element into the MinHeap" },
    { "min", (PyCFunction)MinHeap_min, METH_NOARGS, "Returns the minimum value in the MinHeap" },
    { "delete", (PyCFunction)MinHeap_del, METH_NOARGS, "Removes and returns the minimum value from the MinHeap" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject MinHeapType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "minheap.MinHeap",
    .tp_basicsize = sizeof(MinHeapObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)MinHeap_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "MinHeap objects",
    .tp_methods = MinHeap_methods,
    .tp_init = (initproc)MinHeap_init,
    .tp_new = MinHeap_new,
    .tp_str = MinHeap_str,
};

static PyModuleDef minheap_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "minheap",
    .m_doc = "Module for MinHeap",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_minheap(void) {
    PyObject* m;
    if (PyType_Ready(&MinHeapType) < 0)
        return NULL;

    m = PyModule_Create(&minheap_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&MinHeapType);
    if (PyModule_AddObject(m, "MinHeap", (PyObject*)&MinHeapType) < 0) {
        Py_DECREF(&MinHeapType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
