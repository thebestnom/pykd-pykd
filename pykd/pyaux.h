#pragma once

///////////////////////////////////////////////////////////////////////////////

//  --> call back 
//  { PyThread_StateSave  state( winext->getThreadState() );
//    do_callback();
//  }
//
//  ���� ������ ��� ������ � ��� ���� � ������� ������ �������� �������� ( ��� ����� setExecutionStatus )
//  �� ����� ����������� ������������ ���� ����� ������������ ��������, � ����� �������� ����������,
//  ����� ��������� ���

class PyThread_StateSave {

public:

    PyThread_StateSave( PyThreadState  **state ) {
        if ( *state != NULL )
        {
            m_state = state;                
            PyEval_RestoreThread( *m_state );
        }
    }

    ~PyThread_StateSave() {
        *m_state =PyEval_SaveThread();
    }

private:

    PyThreadState       **m_state;
};

// { PyThread_StateRestore   state;
//   long_or_block_opreration();
// }

class PyThread_StateRestore {

public:

    explicit PyThread_StateRestore() {
        m_state = &m_ownState;
        *m_state =PyEval_SaveThread();
    }

    PyThread_StateRestore( PyThreadState  **state ) {
        if ( *state != NULL )
        {
            m_state = state;                
            *m_state =PyEval_SaveThread();
        }
    }

    ~PyThread_StateRestore() {
            PyEval_RestoreThread( *m_state );
    }

private:

    PyThreadState       **m_state;

    PyThreadState       *m_ownState;

};

///////////////////////////////////////////////////////////////////////////////