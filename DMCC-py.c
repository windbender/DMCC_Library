//
// DMCC-py.c - DMCC python interface
//

#include "Python.h"
#include "DMCC.h"

static PyObject *
dmcc_setMotor(PyObject *self, PyObject *args)
{
    int nBoard;
    int nMotor;
    int nPower;
    // Make sure szErrorMsg is not on the stack
    // -- downside is that we could have concurrency issues with different
    // threads, but you know what, there should only be one error message
    // at a time.  If you have it from multiple threads, your code is fubar'ed 
    // anyways!
    static char szErrorMsg[80];

    // DMCC.setMotor takes 3 arguments: board number, motor number, power
    if (!PyArg_ParseTuple(args, "iii:setMotor", &nBoard, &nMotor, &nPower)) {
        return NULL;
    }
    // validate the board number
    if ((nBoard < 0) || (nBoard > 3)) {
        sprintf(szErrorMsg, "Board number %d is invalid.  Board number must be between 0 and 3.",
                nBoard);
        PyErr_SetString(PyExc_IndexError,szErrorMsg);
        return NULL;
    }
    // validate the motor number
    if ((nMotor < 1) || (nMotor > 2)) {
        sprintf(szErrorMsg, "Motor number %d is invalid.  Motor number must be between 1 and 2.",
                nMotor);
        PyErr_SetString(PyExc_IndexError,szErrorMsg);
        return NULL;
    }
    // validate the power
    if ((nPower < -10000) || (nPower > 10000)) {
        sprintf(szErrorMsg, "Power %d is invalid.  Power must be between -10000 and 10000.",
                nPower);
        PyErr_SetString(PyExc_IndexError,szErrorMsg);
        return NULL;
    }

    int session;
    session = DMCCstart(nBoard);
    setMotorPower(session, nMotor, nPower);
    DMCCend(session);

    return Py_BuildValue("i", 0);
}



static PyObject *
dmcc_getMotorVoltageInt(PyObject *self, PyObject *args)
{
    int nBoard;
    // Make sure szErrorMsg is not on the stack
    // -- downside is that we could have concurrency issues with different
    // threads, but you know what, there should only be one error message
    // at a time.  If you have it from multiple threads, your code is fubar'ed 
    // anyways!
    static char szErrorMsg[80];

    // DMCC.getMotorVoltageInt takes 1 argument: board number - MotorVoltage is 
    // actually the voltage at middle connector on the board
    if (!PyArg_ParseTuple(args, "i:getMotorVoltage", &nBoard)) {
        return NULL;
    }
    // validate the board number
    if ((nBoard < 0) || (nBoard > 3)) {
        sprintf(szErrorMsg, "Board number %d is invalid.  Board number must be between 0 and 3.",
                nBoard);
        PyErr_SetString(PyExc_IndexError,szErrorMsg);
        return NULL;
    }

    int session;
    unsigned int voltage;
    session = DMCCstart(nBoard);
    voltage = getMotorVoltage(session);
    DMCCend(session);

    return Py_BuildValue("i", voltage);
}

static PyObject *
dmcc_getMotorVoltage(PyObject *self, PyObject *args)
{
    int nBoard;
    // Make sure szErrorMsg is not on the stack
    // -- downside is that we could have concurrency issues with different
    // threads, but you know what, there should only be one error message
    // at a time.  If you have it from multiple threads, your code is fubar'ed 
    // anyways!
    static char szErrorMsg[80];

    // DMCC.getMotorVoltage takes 1 argument: board number - MotorVoltage is 
    // actually the voltage at middle connector on the board
    if (!PyArg_ParseTuple(args, "i:getMotorVoltage", &nBoard)) {
        return NULL;
    }
    // validate the board number
    if ((nBoard < 0) || (nBoard > 3)) {
        sprintf(szErrorMsg, "Board number %d is invalid.  Board number must be between 0 and 3.",
                nBoard);
        PyErr_SetString(PyExc_IndexError,szErrorMsg);
        return NULL;
    }

    int session;
    unsigned int voltage;
    double fVoltage;
    
    session = DMCCstart(nBoard);
    voltage = getMotorVoltage(session);
    DMCCend(session);
    
    fVoltage = voltage * 1.0 / 1000.0;

    return Py_BuildValue("d", fVoltage);
}

static PyObject *
dmcc_getQEI(PyObject *self, PyObject *args)
{
    int nBoard;
    int nMotor;
    
    // Make sure szErrorMsg is not on the stack
    // -- downside is that we could have concurrency issues with different
    // threads, but you know what, there should only be one error message
    // at a time.  If you have it from multiple threads, your code is fubar'ed 
    // anyways!
    static char szErrorMsg[80];

    // DMCC.getQEI takes 2 arguments: board number, motor number
    if (!PyArg_ParseTuple(args, "ii:getQEI", &nBoard, &nMotor)) {
        return NULL;
    }
    // validate the board number
    if ((nBoard < 0) || (nBoard > 3)) {
        sprintf(szErrorMsg, "Board number %d is invalid.  Board number must be between 0 and 3.",
                nBoard);
        PyErr_SetString(PyExc_IndexError,szErrorMsg);
        return NULL;
    }
    // validate the motor number
    if ((nMotor < 1) || (nMotor > 2)) {
        sprintf(szErrorMsg, "Motor number %d is invalid.  Motor number must be 1 or 2.",
                nMotor);
        PyErr_SetString(PyExc_IndexError,szErrorMsg);
        return NULL;
    }
    

    int session;
    unsigned int nQEI;
    
    session = DMCCstart(nBoard);
    nQEI = getQEI(session, nMotor);
    DMCCend(session);
    
    return Py_BuildValue("i", nQEI);
}


static PyObject *
dmcc_getQEIVel(PyObject *self, PyObject *args)
{
    int nBoard;
    int nMotor;
    
    // Make sure szErrorMsg is not on the stack
    // -- downside is that we could have concurrency issues with different
    // threads, but you know what, there should only be one error message
    // at a time.  If you have it from multiple threads, your code is fubar'ed 
    // anyways!
    static char szErrorMsg[80];

    // DMCC.getQEIVel takes 2 arguments: board number, motor number
    if (!PyArg_ParseTuple(args, "ii:getQEI", &nBoard, &nMotor)) {
        return NULL;
    }
    // validate the board number
    if ((nBoard < 0) || (nBoard > 3)) {
        sprintf(szErrorMsg, "Board number %d is invalid.  Board number must be between 0 and 3.",
                nBoard);
        PyErr_SetString(PyExc_IndexError,szErrorMsg);
        return NULL;
    }
    // validate the motor number
    if ((nMotor < 1) || (nMotor > 2)) {
        sprintf(szErrorMsg, "Motor number %d is invalid.  Motor number must be 1 or 2.",
                nMotor);
        PyErr_SetString(PyExc_IndexError,szErrorMsg);
        return NULL;
    }
    

    int session;
    int vel;
    
    session = DMCCstart(nBoard);
    vel = getQEIVel(session, nMotor);
    DMCCend(session);
    
    return Py_BuildValue("i", vel);
}


static PyMethodDef
module_functions[] = {
    { "setMotor", dmcc_setMotor, METH_VARARGS, "Set motor (board, motorNum, power)" },
    { "getMotorVoltage", dmcc_getMotorVoltage, METH_VARARGS, "Gets the Voltage (board)" },
    { "getMotorVoltageInt", dmcc_getMotorVoltageInt, METH_VARARGS, "Gets the Voltage (board) as int" },
    { "getQEI", dmcc_getQEI, METH_VARARGS, "Return the Quadrature Encoder value of the given (board, motor)" },
    { "getQEIVel", dmcc_getQEIVel, METH_VARARGS, "Return the Quadrature Encoder Velocity of the given (board, motor)" },
    { NULL }
};

void
initDMCC(void)
{
    Py_InitModule3("DMCC", module_functions, "DMCC module by Exadler");
}
