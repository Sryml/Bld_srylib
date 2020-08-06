#include <windows.h>
#include <string>
#include <shellapi.h>
#include <stdio.h>

#include <Python.h>


#include "srylib.h"





std::wstring toWideChar(const char* c)
{
    const size_t cSize = strlen(c) + 1;
    std::wstring wc(cSize, L'#');
    mbstowcs(&wc[0], c, cSize);
    return wc;
}



static char py_system[] = "system";
static char py_system_doc[] = "system(command)";



static PyObject* srylib_system(PyObject* self, PyObject* args) {
    const char* strCommand;
    char s[] = "s";
    char i[] = "i";

    if (!PyArg_ParseTuple(args, s, &strCommand))
        return NULL;

    const char* Command = "/c ";
    const size_t cSize = strlen(strCommand) + 4;
    char* str1 = new char[cSize];
    sprintf(str1, "%s%s", Command, strCommand);

    ShellExecute(NULL, L"open", L"cmd.exe", toWideChar(str1).c_str(), NULL, SW_HIDE);

    delete []str1;
    return Py_BuildValue(s, strCommand);
}


static PyMethodDef methods[] = {
    { py_system, srylib_system, METH_VARARGS, py_system_doc },
    { NULL, NULL, 0, NULL },
};




void initsrylib()
{
    char module[] = "srylib";
    Py_InitModule(module, methods);
}
