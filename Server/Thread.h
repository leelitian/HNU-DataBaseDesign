#ifndef __THREAD_H
#define __THREAD_H

#include <WINSOCK2.H>   
#include <deque>
#include <string>
#include <iostream>
#include <pthread.h>
#pragma comment(lib, "pthreadVC2.lib")
#pragma comment(lib, "ws2_32.lib") 

#define SERVER_PORT		10000    
#define MSGSIZE			10240

using namespace std;

/**
 * ִ��������࣬����accept()��������ִ��
 */
class CTask {
protected:
	string m_strTaskName;   //���������
	int connfd;    //���յĵ�ַ

public:
	CTask() = default;
	CTask(string& taskName) : m_strTaskName(taskName), connfd(0) {}
	virtual int Run() = 0;
	void SetConnFd(int data);   //���ý��յ��׽������Ӻš�
	int GetConnFd();
	virtual ~CTask() {}

};


/**
 * �̳߳����ʵ��
 */
class CThreadPool
{
private:
	static  deque<CTask*> m_deqTaskList;     /** ������� */
	static  bool shutdown;                    /** �߳��˳���־ */
	int     m_iThreadNum;                     /** �̳߳����������߳��� */
	pthread_t* pthread_id;

	static pthread_mutex_t m_pthreadMutex;    /** �߳�ͬ���� */
	static pthread_cond_t m_pthreadCond;      /** �߳�ͬ������������ */

protected:
	static void* ThreadFunc(void* threadData); /** ���̵߳��̻߳ص����� */
	static int MoveToIdle(pthread_t tid);       /** �߳�ִ�н����󣬰��Լ����뵽�����߳��� */
	static int MoveToBusy(pthread_t tid);       /** ���뵽æµ�߳���ȥ */

	int Create();          /** �����̳߳��е��߳� */

public:
	CThreadPool(int threadNum = 10);
	int AddTask(CTask* task);      /** ���������ӵ���������� */
	int StopAll();                 /** ʹ�̳߳��е��߳��˳� */
	int getTaskSize();             /** ��ȡ��ǰ��������е������� */
};
#endif 