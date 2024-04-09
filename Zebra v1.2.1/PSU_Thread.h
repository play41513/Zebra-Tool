//---------------------------------------------------------------------------

#ifndef test_threadH
#define test_threadH
#include <string>
using namespace std;
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
struct tag_cmd_desc {
	char *cmd;
	int (*pfn)(char *s);
	};
	typedef struct tag_cmd_desc CMD_DESC;

class CL_CMD_TASK : public TThread
{
protected:
	void __fastcall Execute(void);
private:
	int cmd_TimeOut;

public:
	__fastcall CL_CMD_TASK(bool CreateSuspended);
	void __fastcall Polling_Task(void);


};
//---------------------------------------------------------------------------
#endif
