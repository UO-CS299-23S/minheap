#include <Python.h>
#include "minheap.h"

typedef struct {
    PyObject_HEAD
    struct MinHeap* heap;
} py_MinHeap;

static PyObject* py_MinHeap_create(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    py_MinHeap *self;
    self = (py_MinHeap *) type->tp_alloc(type, 0);
    return (PyObject *) self;
}

static int py_MinHeap_init(py_MinHeap *self, PyObject *args, PyObject *kwds) {
    int size;
    if (!PyArg_ParseTuple(args, "i", &size))
        return -1;

    self->heap = minHeap_create(size);
    return 0;
}

static void py_MinHeap_dealloc(py_MinHeap* self) {
    free(self->heap);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* py_MinHeap_insert(py_MinHeap* self, PyObject* args) {
    int val;
    if (!PyArg_ParseTuple(args, "i", &val))
        return NULL;

    minHeap_insert(self->heap, val);
    Py_RETURN_NONE;
}

static PyMethodDef MinHeap_methods[] = {
        {"insert", (PyCFunction) py_MinHeap_insert, METH_VARARGS, "Insert a value into the heap"},
        {NULL}
};

static PyTypeObject MinHeapType = {
        PyVarObject_HEAD_INIT(NULL, 0)
                .tp_name = "minheap.MinHeap",
        .tp_doc = "MinHeap objects",
        .tp_basicsize = sizeof(py_MinHeap),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
        .tp_new = py_MinHeap_create,
        .tp_init = (initproc) py_MinHeap_init,
        .tp_dealloc = (destructor) py_MinHeap_dealloc,
        .tp_methods = MinHeap_methods,
};

static PyModuleDef minheapmodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "minheap",
        .m_doc = "Example module that creates an extension type.",
        .m_size = -1,
};

PyMODINIT_FUNC PyInit_minheap(void) {
    PyObject* m;

    if (PyType_Ready(&MinHeapType) < 0)
        return NULL;

    m = PyModule_Create(&minheapmodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&MinHeapType);
    if (PyModule_AddObject(m, "MinHeap", (PyObject *) &MinHeapType) < 0) {
        Py_DECREF(&MinHeapType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}



//#define PY_SSIZE_T_CLEAN
//#include <Python.h>
//#include <stdio.h>
//#include "minheap.h"
//
//static PyObject *MinHeapError;
//
//static PyObject *
//minheap_create(PyObject *self, PyObject *args)
//{
//    int capacity;
//    if (!PyArg_ParseTuple(args, "i", &capacity))
//        return NULL;
//    MinHeap heap = minHeap_create(capacity);
//    if (heap == NULL) {
//        PyErr_SetString(MinHeapError, "Heap creation failed");
//        return NULL;
//    }
//    return PyCapsule_New(heap, "minheap.MinHeap", NULL);
//}
//
//static PyObject *
//minheap_insert(PyObject *self, PyObject *args)
//{
//    PyObject *heap_obj;
//    int value;
//    if (!PyArg_ParseTuple(args, "Oi", &heap_obj, &value))
//        return NULL;
//    MinHeap heap = (MinHeap)PyCapsule_GetPointer(heap_obj, "minheap.MinHeap");
//    int result = minHeap_insert(value, heap);
//    return PyLong_FromLong(result);
//}
//
//
//static PyMethodDef MinHeapMethods[] = {
//        {"create", minheap_create, METH_VARARGS, "Create a new MinHeap"},
//        {"insert", minheap_insert, METH_VARARGS, "Insert an element into MinHeap"},
//        {NULL, NULL, 0, NULL}
//};
//
//static struct PyModuleDef minheapmodule = {
//        PyModuleDef_HEAD_INIT,
//        "minheap",
//        NULL,
//        -1,
//        MinHeapMethods
//};
//
//PyMODINIT_FUNC
//PyInit_minheap(void)
//{
//    printf("Initializing module!\n");
//
//    PyObject *m;
//    m = PyModule_Create(&minheapmodule);
//    if (m == NULL) {
//        printf("Oops, module creation failed\n");
//        return NULL;
//    }
//    printf("Module creation succeeded!\n");
//
//    MinHeapError = PyErr_NewException("minheap.error", NULL, NULL);
//    Py_XINCREF(MinHeapError);
//    if (PyModule_AddObject(m, "error", MinHeapError) < 0) {
//        Py_XDECREF(MinHeapError);
//        Py_DECREF(m);
//        return NULL;
//    }
//
//    return m;
//}