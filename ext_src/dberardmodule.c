#define PY_SSIZE_T_CLEAN
#include <Python.h>
// ^^ Python.h needs to be added BEFORE andy standard headers apparently

static PyObject *
dberard_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return PyLong_FromLong(sts);
}


static PyMethodDef SpamMethods[] = {
    // ...
    {"system",  dberard_system, METH_VARARGS,
     "Execute a shell command."},
    // ...
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "dberard",   /* name of module */
    NULL, // spam_doc, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    SpamMethods
};

typedef struct {
  PyObject_HEAD
  const char *data;
} Animal;

PyObject* animal_new(PyTypeObject *subtype, PyObject *args, PyObject *kwargs) {
  fflush(stdout);
  Animal *self = (Animal*)subtype->tp_alloc(subtype, 0);
  printf("  Alloc animal of type %s \n", subtype->tp_name);
  fflush(stdout);
  if (self != NULL) {
    self->data = "generic animal";
  }
  return (PyObject*)self;
}

void animal_dealloc(PyObject* self) {
  //printf("Animal dealloc attempt\n");
  //fflush(stdout);
  Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject* animal_repr(PyObject *self) {
  PyObject* obj = PyUnicode_FromString("Animal()");
  //printf("Animal repr %p\n", obj);
  //fflush(stdout);
  return obj;
}


PyTypeObject Animal_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "dberard.Animal",
    .tp_basicsize = sizeof(Animal),
    .tp_doc = PyDoc_STR("Animal objects"),
    .tp_new = animal_new,
    .tp_dealloc = (destructor)animal_dealloc,
    .tp_repr = (reprfunc)animal_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
};

PyMODINIT_FUNC
PyInit_dberard(void)
{
    PyObject* m = PyModule_Create(&spammodule);

    if (PyType_Ready(&Animal_Type)) {
        return;
    }

    Py_INCREF(&Animal_Type);
    if (PyModule_AddObject(m, "Animal", (PyObject *)&Animal_Type) < 0) {
        printf("Animal object failed to create\n");
        fflush(stdout);
        Py_DECREF(&Animal_Type);
        return NULL;
    }

    return m;
}
